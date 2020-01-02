#ifndef READADC_H
#define READADC_H

#include "SPI.h"


class ADCSensor{
  private:
    int chip_select_;
    int ADC_channel_number_; // input number of the ADC which will be read (0-7)
    int zero_milliVolt10_; // the sensor zero voltage in milliVolts * 10
    int milliVolt10_per_unit_; // milliVolts * 10 per sensor unit
    int CAN_scale_factor_; // inverse of what's in the DBC. example: 0.1 in DBC == 10 here.

    int read_value_; // 12-bit number (0V-5V) that is returned from the ADC
    int read_voltage_;
    unsigned long running_read_total_; // used to store values for an average calculation
    int running_read_count_;
    int read_min_;
    int read_max_;

  public:
    // constructors
    ADCSensor() = delete; // delete the default constructor
    ADCSensor(int chip_select, int ADC_channel_number, int zero_milliVolt10, int milliVolt10_per_unit, int scale_fact);

    void sample(); // sample the ADC
    void reset(); // reset the sample values

    // getters
    double avg(); // get the sensor's avg value (in sensor units)
    //int CAN_avg(); // returns the factored integer value for CAN
    //double min();
    //int CAN_min();
    //double max();
    //int CAN_max();
    int sample_count(){return running_read_count_;}
};


#endif
