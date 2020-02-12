#include "Arduino.h"
#include "BoardTemp.h"

// must call in setup();
void BoardTempDiode::begin(){
  this->max_read_val_ = pow(2, this->read_bits_) - 1; // max value that analogRead can return
  pinMode(this->pin_, INPUT); // initialize pin
}

void BoardTempDiode::sample(){
  this->running_read_total_ += analogRead(this->pin_);
  this->read_count_++;
  this->values_updated_ = false;
}

void BoardTempDiode::reset(){
  this->running_read_total_ = 0;
  this->read_count_ = 0;
}

// this is where the wonk begins
void BoardTempDiode::calculate(){
   // get the average
  this->running_read_total_ /= this->read_count_;
  // turn the average into the millivoltage
  this->read_mvoltage_ = (this->running_read_total_ / this->max_read_val_) * this->uC_millivoltage_;

  // formula here: https://www.openimpulse.com/blog/2012/07/low-cost-diode-temperature-sensor/
  // the diode that we use changes -2mV/ºC
  this->value_ = this->t_cal_ + (this->mv_cal_ - this->read_mvoltage_) * 0.5;

  this->values_updated_ = true;
}

float BoardTempDiode::value(){
  this->calculate();
  this->reset();
  return this->value_;
}
