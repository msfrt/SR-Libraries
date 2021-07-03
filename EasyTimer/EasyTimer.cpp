// Written by Dave Yonkers, 2020
#include "Arduino.h"
#include "EasyTimer.h"

// creates a timer with the desired frequency.
EasyTimer::EasyTimer(int freq){
  freq_ = freq;
  //us_ = 1000000 / freq; // microseconds delay
  ms_ = 1000 / freq;  // milliseconds delay

  last_time_ = 0;
}


// this function returns true if it is time, false if time has not been reached yet
bool EasyTimer::check(){
  if (millis() - last_time_ >= ms_){
    last_time_ = millis(); // reset the timer
    return true;
  } else {
    return false;
  }
}

// this function returns true if it is time, false if time has not been reached yet - same as check()
bool EasyTimer::isup(){
  return this->check();
}

// this function returns true if it is time, false if time has not been reached yet - same as check()
bool EasyTimer::is_up(){
  return this->check();
}


void EasyTimer::set_frequency(int freq){
  freq_ = freq;
  // us_ = 1000000 / freq; // microseconds delay
  ms_ = 1000 / freq; // milliseconds delay
}


void EasyTimer::set_delay_millis(int ms){
  freq_ = 1000 / ms;
  ms_ = ms;
}

// void EasyTimer::set_delay_micros(int us){
//   freq_ = 1000000 / us;
//   us_ = us; // microseconds delay
// }

void EasyTimer::reset(){
  last_time_ = millis(); // sets the last time to the current time
}


// creates a LED Blink with the desired frequency.
LEDBlink::LEDBlink(int pin, int freq){
  freq_ = freq;
  ms_ = 1000 / freq; // millseconds delay
  last_time_ = 0;

  led_pin_ = pin;
  pinMode(led_pin_, OUTPUT); // initialize the pin
}

// update the frequency of LED blinking
void LEDBlink::set_frequency(int freq){
  freq_ = freq;
  ms_ = 1000 / freq; // microseconds delay
}

// check to see what state the LED is on and if we should update it
void LEDBlink::run(){
  if (millis() - last_time_ >= ms_){
    last_time_ = millis(); // reset the timer

    // do the LED stuffs
    if (led_on_){led_on_ = false; digitalWrite(led_pin_, LOW);}
    else {led_on_ = true; digitalWrite(led_pin_, HIGH);}
  }
}
