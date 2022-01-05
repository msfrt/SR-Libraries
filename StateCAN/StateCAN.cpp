#include "StateCAN.h"
#include "Arduino.h"


unsigned int StateCounter::value(){
  if (this->current_position_ < (this->num_positions_ - 1)){
    this->current_position_++;
  } else {
    this->current_position_ = 0;
  }
  return this->current_position_;
}


// check for timeout validity (utilizes short-circuting)
bool StateSignal::timeout_check(){
  if ((this->timeout_delay_ >= 0) && // if the timeout delay isn't disabled
     (millis() >= static_cast<unsigned int>(timeout_delay_)) && // this is so valid_ isn't set to true upon startup
     (millis() - this->last_recieve_ >= static_cast<unsigned int>(this->timeout_delay_))){
    this->set_validity(false);
  } else {
    this->set_validity(true);
  }
  return this->valid_;
}

const int StateSignal::operator=(int new_value){
  updated_ = true;
  this->value_ = new_value;
  this->last_recieve_ = millis();
  return value_;
}

const int StateSignal::operator=(float new_value){
  updated_ = true;
  this->value_ = new_value;
  this->last_recieve_ = millis();
  return value_;
}

const int StateSignal::operator=(double new_value){
  updated_ = true;
  this->value_ = new_value;
  this->last_recieve_ = millis();
  return value_;
}


// getters that take into account faults
float StateSignal::value(){
  updated_ = false;
  if (this->valid_) {
    return this->value_;
  } else {
    return this->secondary_value_;
  }
}

// returns an int value, but the casting in here takes care of what we need it to do
int StateSignal::can_value(){
  updated_ = false;
  if (this->valid_) {
    if (this->signed_){

      // the following are for valid and signed values
      switch (this->bit_length_) {
        case 16: // 16-bit, signed
          return static_cast<int16_t>(this->value_ * this->inverse_factor_);
          break;
        case 32: // 32-bit, signed
          return static_cast<int32_t>(this->value_ * this->inverse_factor_);
          break;
        case 8: // 8-bit, signed
          return static_cast<int8_t>(this->value_ * this->inverse_factor_);
          break;
        default:
          return this->value_ * this->inverse_factor_;
          break;

        // add support for 4 and 2 bit integers? Not necessary (I think).
      } // end bit-length switch/case

    } else { // valid, but unsigned

      // it was supposed to be unsigned, you fool
      if (this->value_ < 0){return 0;}

      // the following are for valid but unsigned values
      switch (this->bit_length_) {
        case 16: // 16-bit, unsigned
          return static_cast<uint16_t>(this->value_ * this->inverse_factor_);
          break;
        case 32: // 32-bit, unsigned
          return static_cast<uint32_t>(this->value_ * this->inverse_factor_);
          break;
        case 8: // 8-bit, unsigned
          return static_cast<uint8_t>(this->value_ * this->inverse_factor_);
          break;
        case 4: // 4-bit, unsigned (no native support. This just does some masking, but won't do any bounds check)
          return static_cast<uint8_t>(this->value_ * this->inverse_factor_) & B00001111;
          break;
        case 2: // 2-bit, unsigned
          return static_cast<uint8_t>(this->value_ * this->inverse_factor_) & B00000011;
          break;
        case 1: // 1-bit, unsigned (aka, true or false)
          if (this->value_ < 0.1){return 0;} else {return 1;} // no math here because who tf scales a bool?
        default:
          return this->value_ * this->inverse_factor_;
          break;
      } // end bit-length switch/case

    } // end unsigned



  } else { // the signal is invalid

    if (this->signed_){

      // the following are for valid and signed values
      switch (this->bit_length_) {
        case 16: // 16-bit, signed
          return static_cast<int16_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        case 32: // 32-bit, signed
          return static_cast<int32_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        case 8: // 8-bit, signed
          return static_cast<int8_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        default:
          return this->secondary_value_ * this->inverse_factor_;
          break;

        // add support for 4 and 2 bit integers? Not necessary (I think).
      } // end bit-length switch/case

    } else { // valid, but unsigned

      // it was supposed to be unsigned, you fool
      if (this->secondary_value_ < 0){return 0;}

      // the following are for valid but unsigned values
      switch (this->bit_length_) {
        case 16: // 16-bit, unsigned
          return static_cast<uint16_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        case 32: // 32-bit, unsigned
          return static_cast<uint32_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        case 8: // 8-bit, unsigned
          return static_cast<uint8_t>(this->secondary_value_ * this->inverse_factor_);
          break;
        case 4: // 4-bit, unsigned (no native support. This just does some masking, but won't do any bounds check)
          return static_cast<uint8_t>(this->secondary_value_ * this->inverse_factor_) & B00001111;
          break;
        case 2: // 2-bit, unsigned
          return static_cast<uint8_t>(this->secondary_value_ * this->inverse_factor_) & B00000011;
          break;
        case 1: // 1-bit, unsigned (aka, true or false)
          if (this->secondary_value_ < 0.1){return 0;} else {return 1;} // no math here because who tf scales a bool?
          break;
        default:
          return this->secondary_value_ * this->inverse_factor_;
          break;
      } // end bit-length switch/case

    }

  }

}




// setters
void StateSignal::set_can_value(int incoming_value){
  updated_ = true;

  // we need to cast to floats here so integer math doesn't remove precision.
  // also, if the value is signed, we need to do some funky stuff to fill the rest of the value
  if (this->signed_){
    // first we need to cast the unsigned CAN data into a signed integer type of the appropriate size (which is why
    // setting the bit-length is important in the signal definitions page)
    // second, we cast that signed value to a float, and then after that we take take of the factor
    switch (this->bit_length_) {
      case 16: // most common, so up at the top
        this->value_ = static_cast<float>(static_cast<int16_t>(incoming_value)) / this->inverse_factor_;
        break;
      case 8:
        this->value_ = static_cast<float>(static_cast<int8_t>(incoming_value)) / this->inverse_factor_;
        break;
      case 32:
        this->value_ = static_cast<float>(static_cast<int32_t>(incoming_value)) / this->inverse_factor_;
        break;
      case 64:
        this->value_ = static_cast<float>(static_cast<int64_t>(incoming_value)) / this->inverse_factor_;
        break;
    }

  } else {
    this->value_ = static_cast<float>(incoming_value) / this->inverse_factor_;
  }
  this->last_recieve_ = millis();
}


void StateSignal::set_validity(bool valid){
  updated_ = true;

  this->valid_ = valid;
}
