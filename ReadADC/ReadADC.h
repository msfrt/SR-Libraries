#ifndef READADC_H
#define READADC_H

#include "SPI.h"


class ADCSensor{
  private:
    int chip_select_;
    uint16_t ADC_channel_number_; // input number of the ADC which will be read (0-7)
    int zero_mV_; // the sensor zero voltage in milliVolts * 10
    int mV_per_sensor_unit_; // milliVolts * 10 per sensor unit

    int read_value_; // 12-bit number (0V-5V) that is returned from the ADC
    float read_mvoltage_;
    unsigned long running_read_total_; // used to store values for an average calculation
    int running_read_count_;
    int read_min_;
    int read_max_;

    float actual_avg_;
    float actual_min_;
    float actual_max_;
    bool values_updated; // this is false when the actual values are not the most current (ex. the sensor has been sampled
                  // since the last time the actual values were calculated)

    void reset(); // reset the sample values
    void calculate(); // turns the read values into legible sensor values

  public:
    // constructors
    ADCSensor() = delete; // delete the default constructor
    ADCSensor(int chip_select, uint16_t ADC_channel_number, int zero_mV, int mV_per_sensor_unit);

    // member-functions
    void begin(); // used to intilize the pin
    void sample(); // sample the ADC

    // getters (automatically calculate the real-life values if appropriate)
    float avg();
    float min();
    float max();
    int read_value() const {return read_value_;}
    float read_mvoltage() const {return read_mvoltage_;} // returns the last calculated average millivolt reading
    float last_calc_avg() {return actual_avg_;} // does no calculation
    int sample_count(){return running_read_count_;}
};


#endif
