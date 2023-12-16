#include "PWMControl.h"
#include "StateCAN.h"

// constructor : uses initializer list
PWMDevice::PWMDevice(int output_pin,
                     int &temperature_signal, int pwm_min, int pwm_max,
                     int soft_start_dur, int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq) :
                     pwm_pin_(output_pin), temperature_signal_(temperature_signal),
                     pwm_min_dc_(pwm_min), pwm_max_dc_(pwm_max), pwm_normal_freq_(pwm_normal_freq),
                     pwm_soft_start_freq_(pwm_soft_start_freq),
                     pwm_control_timer_(pwm_control_freq), soft_start_duration_(soft_start_dur) {};


bool PWMDevice::set_pwm() {


  // encapsulate other calculations and writing in the PWM update timer. The PWM updates are only ran from within
  // this function. The function is also ran when the engine state changes
  counter++;
  if (pwm_control_timer_.isup()) {

    // this function has all of the conditions for dynamic control under normal operation
    determine_dynamic_pwm();

    // before setting the PWM, set the appropriate frequency if necessary
    write_pwm_frequency();

    // fucking send it
    write_pwm_duty_cycle();

    return true;

  } // end timer

  return false;
}

void PWMDevice::determine_dynamic_pwm(){

  // change this to the CAN signal value

  // check if we need to turn the device on and enable soft start
  if (this->device_on_ == false && this->pwm_percent_target_ > 0){
    this->soft_start_until_time_ = millis() + this->soft_start_duration_;
    this->device_on_ = true;
  }

  if(counter >= 50000) {
    this->pwm_percent_target_ = 0;
  } else {
    this->pwm_percent_target_ = 75;
  }
  // this next chunk does the increment/decrement of the fan PWM
  if (this->pwm_percent_actual_ < this->pwm_percent_target_){this->pwm_percent_actual_++;}
  if (this->pwm_percent_actual_ > this->pwm_percent_target_){this->pwm_percent_actual_--;}

  // check one last time to see if the device status should be set to off
  if (this->pwm_percent_actual_ < 1){this->device_on_ = false;}
}

void PWMDevice::determine_cooldown_pwm(){

  // if the target is above the minimum, set the new target to the minimum. target is unchanged otherwise
  if (this->pwm_percent_target_ > this->pwm_percent_cooldown_minimum_){
    this->pwm_percent_target_ = this->pwm_percent_cooldown_minimum_;
  }

  // if actual pwm is more than target, decrement that bad boi
  if (this->pwm_percent_actual_ > this->pwm_percent_target_){
    this->pwm_percent_actual_--;
  }

  // if we've reached the point where the output is actualy 0, be sure to set the device state to off
  if (this->pwm_percent_actual_ < 1){this->device_on_ = false;}

}



// maps duty cycle percentage to min and max PWM duty cycle values, and then writes it to the pin
void PWMDevice::write_pwm_duty_cycle(){
  this->pwm_output_ = map(this->pwm_percent_actual_, 0, 100, this->pwm_min_dc_, this->pwm_max_dc_);
  analogWrite(this->pwm_pin_, this->pwm_output_);
}


void PWMDevice::write_pwm_frequency(){

  // if we are currently in a soft start period...
  if (millis() < this->soft_start_until_time_){
    this->pwm_actual_freq_ = this->pwm_soft_start_freq_;
  } else { // normal frequency
    this->pwm_actual_freq_ = this->pwm_normal_freq_;
  }

  // write the frequency
  analogWriteFrequency(this->pwm_pin_, this->pwm_actual_freq_);
}
