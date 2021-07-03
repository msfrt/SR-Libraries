// Written by Dave Yonkers, 2020
#ifndef TIMER_H
#define TIMER_H

#include "Arduino.h"


// timers! Beware, this class does not check for garbage values
// such as frequency = 0, or a negative frequency, or a frequency faster than the clock-speed.
class EasyTimer{

  public:
    // constructor. creates a timer with the desired frequency.
    EasyTimer(int freq);

    // member functions
    bool check(); // will check the timer to return true if time is up, or false if it is not yet time
    bool isup(); // same as check()
    bool is_up(); // same as check()
    void set_frequency(int freq); // frequency in Hz.
    void set_delay_millis(int delay); // delay in milliseconds.
    // void set_delay_micros(int delay); // delay in microseconds.
    void reset(); // resets a timer

  private:
    unsigned long freq_; // Hz
    unsigned long last_time_; // for use by timer to hold last time
    // unsigned long us_; // microseconds
    unsigned long ms_;  // milliseconds
};

class LEDBlink{
  public:
    LEDBlink(int pin, int freq); // constructor
    void run(); // call this every loop to check for LED
    void set_frequency(int freq); // frequency in Hz.
  private:
    int led_pin_;
    bool led_on_;
    unsigned long freq_;
    unsigned long last_time_; // in microseconds
    unsigned long ms_;  // milliseconds
};

#endif
