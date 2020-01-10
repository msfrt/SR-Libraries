#include "PWMControl.h"

// constructor : uses initializer list
PWMDevice::PWMDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
                     int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq) :
                     pwm_pin_(output_pin), table_(table_rows, table_columns), pwm_min_dc_(pwm_min),
                     pwm_max_dc_(pwm_max), pwm_normal_freq_(pwm_normal_freq), pwm_soft_start_freq_(pwm_soft_start_freq),
                     pwm_control_timer_(pwm_control_freq), soft_start_duration_(soft_start_dur) {};




void PWMDevice::set_pwm(int table_row_val, int table_col_val, int engine_state, int override_percent){

  // encapsulate everything in the PWM update timer.
  if (pwm_control_timer_.isup()){

    // update the engine state variable
    this->engine_state_ = engine_state;

    // first, based upon the engine state, we need to determine what exactly can and needs to be done
    switch (this->engine_state_) {

      // the engine is off
      case 0:
      // the engine is cranking
      case 1:
        // immediately set the output value to 0
        this->pwm_percent_target_ = 0;
        this->pwm_percent_actual_ = 0;
        this->device_on_ = false;
        break;

      // the engine is running
      case 2:
        // this function has all of the conditions for dynamic control under normal operation
        determine_dynamic_pwm(table_row_val, table_col_val);
        break;

      // the engine is in a cool-down cycle
      case 3:
        determine_cooldown_pwm();
        break;

    } // end switch statement

    // one last thing before writing the PWM... if there is an active override present, and the engine is NOT cranking,
    // forget all of the calculations done above and set the pwm_percent_actual_ to the override_percent
    if (override_percent >= 0 && override_percent <= 100 && engine_state_ != 1){
      this->pwm_percent_target_ = override_percent;
      this->pwm_percent_actual_ = override_percent;
    }

    // before setting the PWM, set the appropriate frequency if necessary
    write_pwm_frequency();

    // fucking send it
    write_pwm_duty_cycle();

    Serial.print("   Target: "); Serial.println(pwm_percent_target_);
    Serial.print("   Actual: "); Serial.println(pwm_percent_actual_);
    Serial.print("Frequency: "); Serial.println(pwm_actual_freq_);

  } // end timer
}


// sauce it into the table's function
void PWMDevice::fill_table(int *first_element){
  this->table_.fill_table(first_element);
}




void PWMDevice::determine_dynamic_pwm(int &table_row_val, int &table_col_val){

  // well, what does the fan table say?
  this->pwm_percent_target_ = this->table_.find(table_row_val, table_col_val);

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
  this->pwm_percent_target_ = 0; // eventually, we would like the fans to be off

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



// void PWMDevice::pwm_actual(){
//
//
//   if (pwm_actual_ == 0){ // if the pwm value is 0, change the device to the off position
//     this->device_on_ = false;
//     this->device_soft_start_ = false;
//   }
//
//   if (this->current_eng_state_ == 2){ // if the engine is on
//
//     if (this->device_on_){// if the device is on
//
//       if (this->device_soft_start_){ // check if the device is still within the soft start period
//
//         if (pwm_soft_start_timer_.isup()){ //if the soft start period is up, disable the function
//           device_soft_start_ = false;
//         }
//       }
//     }
//
//     else{ // if the device is off
//       this->device_on_ = true;
//       this->device_soft_start_ = true;
//       this->pwm_soft_start_timer_.reset();
//     }
//   }
//
//   else if (this->current_eng_state_ == 1){
//     this->device_on_ = false;
//     this->device_soft_start_ = false;
//   }
//
//   else{ // if the engine is off
//
//     // if the engine just turned off, reset the shutdown timer function
//     if (prev_eng_state == 2 && current_eng_state_ == 0){pwm_shutdown_timer_.reset();}
//
//     if (device_on_){ // if the device is on
//
//       // check if the device is still within the soft start period
//       if (this->device_soft_start_){
//
//         if (pwm_soft_start_timer_.isup()){ //if the soft start period is up, disable the function
//           device_soft_start_ = false;
//         }
//       }
//
//       if (pwm_shutdown_timer_.isup()){ // check if the device is still within the shutdown period
//         this->device_on_ = false;
//         this->device_soft_start_ = false;
//       }
//     }
//   }
//
//
//   if (device_on_){ // check if the device is on
//     if (pwm_target_ > pwm_actual_){pwm_actual_++;} // if the current pwm is less then the actual, increment the actual
//     if (pwm_target_ < pwm_actual_){pwm_actual_--;} // if the current pwm is more then the actual, decrement the actual
//   }
//
//   else{ // if the device is off, set the actual pwm to 0
//     pwm_actual_ = 0;
//   }
//
//
// }
//
//
// void PWMDevice::set_pwm(int xval, int yval, int engState){
//
//   if (pwm_update_timer_.isup() || engState == 1){
//
//     current_eng_state_ = engState; // record the current engine state
//
//     //--------Tests
//     pwm_target_ = xval;
//     //---------
//
//     pwm_actual();
//
//     if (device_soft_start_){ // if the device is in startup, use the startup pwm frequency
//       analogWriteFrequency(pwm_pin_, pwm_soft_start_freq_);
//     }
//     else{
//       analogWriteFrequency(pwm_pin_, pwm_freq_);
//     }
//
//     analogWrite(pwm_pin_, pwm_actual_); // set the analog pin to calculated values
//
//     prev_eng_state = current_eng_state_; // record the previous engine state
//   }
//
// }
