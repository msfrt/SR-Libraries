#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "Arduino.h"
#include "EasyTimer.h"
#include "LookupTable.h"

class PwmDevice{

  private:

      LookupTable table_;

      int pwm_min_dc_; // minimum duty cycle that the device should be pwmed
      int pwm_max_dc_; // maximum duty cycle that the device should be pwmed

      int pwm_normal_freq_; // the pwm frequency of the device under normal operation
      int pwm_soft_start_freq_; // the pwm frequency of the device under the soft start function

      const int pwm_pin_; // pin on the teensy which the device is connected to

      EasyTimer pwm_control_timer_ = 1; // timer to control the control function update frequency
      EasyTimer pwm_soft_start_timer_ = 1; // timer to control the soft start function
      EasyTimer pwm_shutdown_timer_ = 1; // timer to control the shutdown function

      int pwm_actual_ = 0; // the current pwm value of the device
      int pwm_target_ = 0; // the target pwm value of the device
      bool device_on_ = false; // true when the device is on (pwm value > 0)
      bool device_soft_start_ = false; // true when the soft start function is active
      int prev_eng_state = false; // engine state during the last control function loop (0=off;1=cranking;2=on)
      int current_eng_state_ = false; // engine state during the current control function loop (0=off;1=cranking;2=on)

      void pwm_target(int, int); // calculate the target pwm value
      void pwm_actual(); // calculate the actual pwm value


  public:
    PwmDevice() = delete;
    PwmDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur, int shutdown_dur,
              int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq);

    // getters

    bool soft_start_state(){return device_soft_start_;}
    bool device_state(){return device_on_;}
    int current_pwm(){return pwm_actual_;}

    // setters

    // control functions

    void set_pwm(int, int, int); // set the pwm frequency of the device



};

#endif
