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
    return static_cast<int16_t>(this->value_ * this->inverse_factor_);

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
