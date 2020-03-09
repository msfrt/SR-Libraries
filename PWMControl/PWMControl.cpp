#include "PWMControl.h"
#include "StateCAN.h"

// constructor : uses initializer list
PWMDevice::PWMDevice(int output_pin, int table_rows, int table_columns, int table_row_sf, int table_col_sf,
                     StateSignal &row_signal, StateSignal &col_signal, StateSignal &override_sig, int pwm_min, int pwm_max,
                     int soft_start_dur, int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq) :
                     pwm_pin_(output_pin), table_(table_rows, table_columns), table_row_scale_fact_(table_row_sf),
                     table_col_scale_fact_(table_col_sf), row_signal_(row_signal), col_signal_(col_signal),
                     override_signal_(override_sig),
                     pwm_min_dc_(pwm_min), pwm_max_dc_(pwm_max), pwm_normal_freq_(pwm_normal_freq),
                     pwm_soft_start_freq_(pwm_soft_start_freq),
                     pwm_control_timer_(pwm_control_freq), soft_start_duration_(soft_start_dur) {};


bool PWMDevice::set_pwm(const int &engine_state){


  // encapsulate other calculations and writing in the PWM update timer. The PWM updates are only ran from within
  // this function. The function is also ran when the engine state changes
  if (pwm_control_timer_.isup() || (this->engine_state_ != engine_state)){

    // update the engine state variable
    this->engine_state_ = engine_state;

    // first, based upon the engine state, we need to determine what exactly can and needs to be done
    switch (this->engine_state_) {

      // the engine is off
      case 0:
        // decrements current value until off
        turn_device_off_pwm();
        break;

      // cranking is also handled her for redundancy
      case 1:
        // immediately set the output value to 0
        this->pwm_percent_target_ = 0;
        this->pwm_percent_actual_ = 0;
        this->device_on_ = false;
        break;

      // the engine is running
      case 2:
        // this function has all of the conditions for dynamic control under normal operation
        determine_dynamic_pwm();
        break;

      // the engine is in a cool-down cycle
      case 3:
        determine_cooldown_pwm();
        break;

    } // end switch statement

    // one last thing before writing the PWM... if there is an active override present, and the engine is NOT cranking,
    // forget all of the calculations done above and set the pwm_percent_actual_ to the override_percent
    if (override_signal_.value() >= 0 && override_signal_.value() <= 100 && engine_state_ != 1){
      this->pwm_percent_target_ = override_signal_.value();
      this->pwm_percent_actual_ = override_signal_.value();
    }

    // before setting the PWM, set the appropriate frequency if necessary
    write_pwm_frequency();

    // send it
    write_pwm_duty_cycle();

    return true;

  } // end timer

  return false;
}


// sauce it into the table's function
void PWMDevice::fill_table(int *first_element){
  this->table_.fill_table(first_element);
}




void PWMDevice::determine_dynamic_pwm(){

  // determine what value to use depending on if the signal is valid or not
  int row_val = row_signal_.value() * table_row_scale_fact_;
  int col_val = col_signal_.value() * table_col_scale_fact_;

  // well, what does the fan table say?
  this->pwm_percent_target_ = this->table_.find(row_val, col_val);

  // check if we need to turn the device on and enable soft start
  if (this->device_on_ == false && this->pwm_percent_target_ > 0){
    this->soft_start_until_time_ = millis() + this->soft_start_duration_;
    this->device_on_ = true;
  }

  // this next chunk does the increment/decrement of the fan PWM
  if (this->pwm_percent_actual_ < this->pwm_percent_target_){this->pwm_percent_actual_++;}
  if (this->pwm_percent_actual_ > this->pwm_percent_target_){this->pwm_percent_actual_--;}

  // check one last time to see if the device status should be set to off
  if (this->pwm_percent_actual_ < 1){this->device_on_ = false;}

}



void PWMDevice::determine_cooldown_pwm(){

  // if the target is above the cooldown target, set the new target to the minimum. target is unchanged otherwise
  if (this->pwm_percent_target_ > this->pwm_percent_cooldown_target_){
    this->pwm_percent_target_ = this->pwm_percent_cooldown_target_;
  }

  // if actual pwm is more than target, decrement that bad boi
  if (this->pwm_percent_actual_ > this->pwm_percent_target_){
    this->pwm_percent_actual_--;
  }

  // if we've reached the point where the output is actualy 0, be sure to set the device state to off
  if (this->pwm_percent_actual_ < 1){this->device_on_ = false;}

}



void PWMDevice::turn_device_off_pwm(){

  // set the target 0
  this->pwm_percent_target_ = 0;

  // decrement
  if (this->pwm_percent_actual_ > this->pwm_percent_target_){
    this->pwm_percent_actual_--;
  }

  // turn status off if need be
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
