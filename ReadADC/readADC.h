#ifndef READADC_H
#define READADC_H

#include "SPI.h"


class ADCSensor{
  private:
    int chip_select_;
    int ADC_channel_number_; // input number of the ADC which will be read (0-7)
    int zero_mV_; // the sensor zero voltage in milliVolts * 10
    int mV_per_sensor_unit_; // milliVolts * 10 per sensor unit
    int CAN_scale_factor_; // inverse of what's in the DBC. example: 0.1 in DBC == 10 here.

    int read_value_; // 12-bit number (0V-5V) that is returned from the ADC
    int read_voltage_;
    unsigned long running_read_total_; // used to store values for an average calculation
    int running_read_count_;
    int read_min_;
    int read_max_;

    double actual_avg_;
    double actual_min_;
    double actual_max_;

  public:
    // constructors
    ADCSensor() = delete; // delete the default constructor
    ADCSensor(int chip_select, int ADC_channel_number, int zero_mV, int mV_per_sensor_unit, int scale_fact);


    void begin(); // used to intilize the pin
    void sample(); // sample the ADC
    void reset(); // reset the sample values
    void calculate(); // turns the read values into legible sensor values

    // getters - be sure to call calculate() prior to using a getter
    double avg(); // get the sensor's avg value (in sensor units)
    //double min(){return actual_min_;}
    //double max(){return actual_max_;}
    int sample_count(){return running_read_count_;}
};


#endif
