#include "PWMControl.h"

// constructor
PwmDevice::PwmDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
                     int shutdown_dur, int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq); :
                     pwm_pin_(output_pin), table_(table_rows, table_columns), pwm_min_dc_(pwm_min),
                     pwm_max_dc_(pwm_max), pwm_normal_freq_(pwm_normal_freq), pwm_soft_start_freq_(pwm_soft_start_freq){
                       pwm_control_timer_.set_frequency(pwm_control_freq); // set the freq of the control loop timer
                       pwm_soft_start_timer_.set_delay_millis(soft_start_dur); // set duration of the soft start timer function
                       pwm_shutdown_timer_.set_delay_millis(shutdown_dur); // set the duration of the shutdown timer
                     };




void PwmDevice::pwm_actual(){


  if (pwm_actual_ == 0){ // if the pwm value is 0, change the device to the off position
    this->device_on_ = false;
    this->device_soft_start_ = false;
  }

  if (this->current_eng_state_ == 2){ // if the engine is on

    if (this->device_on_){// if the device is on

      if (this->device_soft_start_){ // check if the device is still within the soft start period

        if (pwm_soft_start_timer_.isup()){ //if the soft start period is up, disable the function
          device_soft_start_ = false;
        }
      }
    }

    else{ // if the device is off
      this->device_on_ = true;
      this->device_soft_start_ = true;
      this->pwm_soft_start_timer_.reset();
    }
  }

  else if (this->current_eng_state_ == 1){
    this->device_on_ = false;
    this->device_soft_start_ = false;
  }

  else{ // if the engine is off

    // if the engine just turned off, reset the shutdown timer function
    if (prev_eng_state == 2 && current_eng_state_ == 0){pwm_shutdown_timer_.reset();}

    if (device_on_){ // if the device is on

      // check if the device is still within the soft start period
      if (this->device_soft_start_){

        if (pwm_soft_start_timer_.isup()){ //if the soft start period is up, disable the function
          device_soft_start_ = false;
        }
      }

      if (pwm_shutdown_timer_.isup()){ // check if the device is still within the shutdown period
        this->device_on_ = false;
        this->device_soft_start_ = false;
      }
    }
  }


  if (device_on_){ // check if the device is on
    if (pwm_target_ > pwm_actual_){pwm_actual_++;} // if the current pwm is less then the actual, increment the actual
    if (pwm_target_ < pwm_actual_){pwm_actual_--;} // if the current pwm is more then the actual, decrement the actual
  }

  else{ // if the device is off, set the actual pwm to 0
    pwm_actual_ = 0;
  }


}


void PwmDevice::set_pwm(int xval, int yval, int engState){

  if (pwm_update_timer_.isup() || engState == 1){

    current_eng_state_ = engState; // record the current engine state

    //--------Tests
    pwm_target_ = xval;
    //---------

    pwm_actual();

    if (device_soft_start_){ // if the device is in startup, use the startup pwm frequency
      analogWriteFrequency(pwm_pin_, pwm_soft_start_freq_);
    }
    else{
      analogWriteFrequency(pwm_pin_, pwm_freq_);
    }

    analogWrite(pwm_pin_, pwm_actual_); // set the analog pin to calculated values

    prev_eng_state = current_eng_state_; // record the previous engine state
  }

}
