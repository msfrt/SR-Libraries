#include "StateCAN.h"

const int& Signal::operator=(int new_value){
  this->value_ = new_value;
  return value_;
}

const int& Signal::operator=(float new_value){
  this->value_ = static_cast<int>(new_value);
  return value_;
}

const int& Signal::operator=(unsigned int new_value){
  this->value_ = static_cast<int>(new_value);
  return value_;
}
