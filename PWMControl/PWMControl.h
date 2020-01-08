#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "Arduino.h"
#include "EasyTimer.h"
#include "LookupTable.h"

class PwmDevice{

  private:

      const int pwm_pin_; // pin on the teensy which the device is connected to

      LookupTable table_; // this is the lookup table that holds D.C. information

      int pwm_min_dc_; // minimum duty cycle that the device should be pwmed
      int pwm_max_dc_; // maximum duty cycle that the device should be pwmed

      int pwm_normal_freq_; // the pwm frequency of the device under normal operation
      int pwm_soft_start_freq_; // the pwm frequency of the device under the soft start function

      EasyTimer pwm_control_timer_; // timer to control the control function update frequency

      unsigned long soft_start_until_time_ = 0; // whenever this time is greater than current micro time, it is in ss mode
      int soft_start_duration_; // the duration in millis for the duration of soft start

      int pwm_percent_actual_ = 0; // the current pwm percentage value of the device
      int pwm_percent_target_ = 0; // the target pwm percentage value of the device
      // add pwm_percent_error_? for faster spool times when not in startup??
      int pwm_output_ = 0; // the actual PWM value that is being written
      bool device_on_ = false; // true when the device is on (pwm value > 0)
      bool device_soft_start_ = false; // true when the soft start function is active
      int engine_state_prev_ = 0; // engine state during the last control function loop (0=off;1=crank;2=on;3=cooldown)
      int engine_state_ = 0; // engine state during the current control function loop (0=off;1=crank;2=on;3=cooldown)

      // the following is called when the engine is running, and fans should not be set to 0
      void determine_dynamic_pwm(int &table_row_val, int &table_col_val);

      // cool-down "mode"
      void determine_cooldown_pwm();

      // write the actual PWM duty cycle
      void write_pwm_duty_cycle();

      // write the PWM frequency
      void write_pwm_frequency();

  public:
    PwmDevice() = delete;
    PwmDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
                         int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq);

    // getters
    int pwm_percent_target(){return pwm_percent_target_;}
    int pwm_percent_actual(){return pwm_percent_actual_;}
    bool device_on(){return device_on_;}

    // setters
    // set the pwm frequency of the device. for override percent, -1 means no override;
    void set_pwm(int table_row_val, int table_col_val, int engine_state, int override_percent);

    // this simply just passes the table information through to the LookupTable object.
    // Look at LookupTable README for documentation if needed
    void set_table(int *first_element);

};

void PwmDevice::set_table(int table[]){
}

#endif
