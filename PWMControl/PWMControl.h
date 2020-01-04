#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "Arduino.h"
#include "EasyTimer.h"

class PwmDevice{

  private:

      int control_table_x_entries_; // number of entries in the x axis of the table
      int control_table_y_entries_; // number of entries in the y axis of the table

      int pwm_min_val_; // minimum value that the device should be pwmed
      int pwm_max_val_; // maximum value that the device should be pwmed

      int pwm_soft_start_duration_; // length of the soft start function in ms
      int pwm_shutdown_duration_; // length of the shutdown function in ms

      int pwm_update_freq_; // frequency at which the control function is ran
      int pwm_freq_; // the pwm frequency of the device under normal operation
      int pwm_soft_start_freq_; // the pwm frequency of the device under the soft start function

      const int pwm_pin_; // pin on the teensy which the device is connected to

      EasyTimer pwm_update_timer_ = 1; // timer to control the control function frequency
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
    PwmDevice(int xe, int ye, int pmin, int pmax, int ssd, int sd, int uf, int pf, int ssf, int p) :
              control_table_x_entries_(xe), control_table_y_entries_(ye), pwm_min_val_(pmin),
              pwm_max_val_(pmax), pwm_soft_start_duration_(ssd), pwm_shutdown_duration_(sd), pwm_update_freq_(uf),
              pwm_freq_(pf), pwm_soft_start_freq_(ssf), pwm_pin_(p)
              {

                pwm_update_timer_.set_frequency(uf); // set the freq of the control loop timer
                pwm_soft_start_timer_.set_delay_millis(ssd); // set duration of the soft start timer function
                pwm_shutdown_timer_.set_delay_millis(pwm_shutdown_duration_); // set the duration of the shutdown timer

              }; // new constructor

    // getters

    bool soft_start_state(){return device_soft_start_;}
    bool device_state(){return device_on_;}
    int current_pwm(){return pwm_actual_;}

    // setters

    // control functions

    void set_pwm(int, int, int); // set the pwm frequency of the device



};

#endif
