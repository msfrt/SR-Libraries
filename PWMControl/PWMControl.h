#ifndef PWM_CONTROL_H
#define PWM_CONTROL_H

#include "Arduino.h"
#include "EasyTimer.h"

class PwmDevice{

  private:
      int control_table_[20][20];
      int control_table_x_entries_ = 0;
      int control_table_y_entries_ = 0;
      int pwm_min_val_ = 0;
      int pwm_max_val_ = 0;
      int pwm_soft_start_duration_ = 0;
      int pwm_shutdown_duration_ = 0;
      int pwm_update_freq_ = 0;
      int pwm_freq_ = 0;
      int pwm_soft_start_freq_ = 0;
      const int pwm_pin_ = -1;
      int pwm_actual_ = 0;



  public:
    PwmDevice() = default;
    PwmDevice(int ct[20][20], int xe, int ye, int pmin, int pmax, int ssd, int sd, int uf, int pf, int ssf, int p) :
              control_table_(ct), control_table_x_entries_(xe), control_table_y_entries_(ye), pwm_min_val_(pmin),
              pwm_max_val_(pmax), pwm_soft_start_duration_(ssd), pwm_shutdown_duration_(sd), pwm_update_freq_(uf),
              pwm_freq_(pf), pwm_soft_start_freq_(ssf), pwm_pin_(p) {}; // new constructor

    // getters

    // setters

    // control functions

    int find_x_val(int xval);
    int find_y_val(int yval);
    int pwm_target(int xval, int yval);
    int pwm_actual(int target, bool carOn);
    void set_pwm(int xval, int yval, bool carOn);



};

#endif
