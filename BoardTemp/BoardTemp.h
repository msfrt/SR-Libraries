#ifndef BOARD_IS_VERY_PIPING_HOT_H
#define BOARD_IS_VERY_PIPING_HOT_H

#include "Arduino.h"

// board temp is kinda a little muffed up, so here's a class to sample it and what not.
// it's not like a normal sensor, but this class makes it act like one.


class BoardTempDiode{
  
  public:
    // constructors
    BoardTempDiode() = delete;
    BoardTempDiode(int pin, int read_bits, float temp_cal, float mv_cal) :
              pin_(pin), read_bits_(read_bits), t_cal_(temp_cal), mv_cal_(mv_cal) {};

    
    void begin(); // Initialize the board temp pin and set max values
    void sample(); // Sample the board temp
    float value(); // Return the average of the last sampling period.
  
    // return the last calculated millivoltage (useful for calibration)
    float get_mV(){return read_mvoltage_;}
  
    void set_uC_mV(float new_mVoltage){uC_millivoltage_ = new_mVoltage;}
  
  private:
  
    int pin_;
    int read_bits_;
    float max_read_val_;

    float t_cal_; // temperature at calibration
    float mv_cal_; // millivoltage at calibration

    float uC_millivoltage_ = 3300; // teensies are 3.3V

    float value_;

    unsigned int running_read_total_ = 0;
    unsigned int read_count_ = 0;
    float read_mvoltage_;
    bool values_updated_ = false;

    void reset();
    void calculate();

};



#endif
