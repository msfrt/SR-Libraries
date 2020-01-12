#include "StateCAN.h"
#include "Arduino.h"

const int StateSignal::operator=(int new_value){
  this->value_ = new_value;
  return value_;
}

const int StateSignal::operator=(float new_value){
  this->value_ = new_value;
  return value_;
}

const int StateSignal::operator=(double new_value){
  this->value_ = new_value;
  return value_;
}

// getters that take into account faults
float StateSignal::value() const{
  if (this->valid_) {
    return this->value_;
  } else {
    return this->secondary_value_;
  }
}

// returns an int value, but the casting in here takes care of what we need it to do
int StateSignal::can_value() const{
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
        case 4: // 4-bit, signed
          return static_cast<int8_t>(this->value_ * this->inverse_factor_) >> 4; // no native support for 4-bit int
          break;
        case 2: // 2-bit, signed
          return static_cast<int8_t>(this->value_ * this->inverse_factor_) >> 6; // no native support for 2-bit int
          break;
      } // end bit-length switch/case

    } else { // valid, but unsigned

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
        case 4: // 4-bit, unsigned
          return static_cast<uint8_t>(this->value_ * this->inverse_factor_); // no native support for 4-bit int
          break;
        case 2: // 2-bit, unsigned
          return static_cast<uint8_t>(this->value_ * this->inverse_factor_) >> 6; // no native support for 2-bit int
          break;
        case 1: // 1-bit, unsigned (aka, true or false)
          return static_cast<bool>(this->value_ * this->inverse_factor_);
      } // end bit-length switch/case

    } // end valid if/else



  } else { // the signal is invalid
    return static_cast<int16_t>(this->secondary_value_ * this->inverse_factor_);
  }
}




// setters
void StateSignal::set_can_value(int incoming_value){
  // we need to cast to floats here so integer math doesn't remove precision
  this->value_ = static_cast<float>(incoming_value) / this->inverse_factor_;
}

void StateSignal::set_validity(bool valid){
  this->valid_ = valid;
}
