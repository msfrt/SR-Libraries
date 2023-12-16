#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "Arduino.h"
#include "EasyTimer.h"
#include "LookupTable.h"
#include "StateCAN.h"

class PWMDevice {

  private:

      const int pwm_pin_; // pin on the teensy which the device is connected to

      //StateSignal &temperature_signal_;
      int &temperature_signal_;
      int pwm_min_dc_; // minimum duty cycle that the device should be pwmed
      int pwm_max_dc_; // maximum duty cycle that the device should be pwmed

      int pwm_normal_freq_; // the pwm frequency of the device under normal operation
      int pwm_soft_start_freq_; // the pwm frequency of the device under the soft start function
      int pwm_actual_freq_;

      EasyTimer pwm_control_timer_; // timer to control the control function update frequency

      unsigned long soft_start_until_time_ = 0; // whenever this time is greater than current micro time, it is in ss mode
      int soft_start_duration_; // the duration in millis for the duration of soft start

      int pwm_percent_actual_ = 0; // the current pwm percentage value of the device
      int pwm_percent_target_ = 0; // the target pwm percentage value of the device
      int pwm_percent_cooldown_minimum_ = 50; // if the device was above 'X' percent, it will decrease until it hits 'X'
      // add pwm_percent_error_? for faster spool times when not in startup??
      int pwm_output_ = 0; // the actual PWM value that is being written
      bool device_on_ = false; // true when the device is on (pwm value > 0)
      bool device_soft_start_ = false; // true when the soft start function is active
      int engine_state_prev_ = 0; // engine state during the last control function loop (0=off;1=crank;2=on;3=cooldown)
      int engine_state_ = 0; // engine state during the current control function loop (0=off;1=crank;2=on;3=cooldown)

      // the following is called when the engine is running, and fans should not be set to 0
      void determine_dynamic_pwm();

      // cool-down "mode"
      void determine_cooldown_pwm();

      // write the actual PWM duty cycle
      void write_pwm_duty_cycle();

      // write the PWM frequency
      void write_pwm_frequency();

  public:
    PWMDevice() = delete;
    PWMDevice(int output_pin, int &temperature_signal,
              int pwm_min, int pwm_max, int soft_start_dur, int pwm_control_freq, 
              int pwm_normal_freq, int pwm_soft_start_freq);

    // getters
    int target(){return pwm_percent_target_;}
    int actual(){return pwm_percent_actual_;}
    int freq(){return pwm_actual_freq_;}
    bool device_on(){return device_on_;}

    // setters
    // set the pwm of the device. for override percent, -1 means no override;
    bool set_pwm();

};

#endif
