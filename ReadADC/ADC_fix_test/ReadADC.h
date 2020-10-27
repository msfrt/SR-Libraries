#ifndef READADC_H
#define READADC_H

#include "SPI.h"


class ADCSensor{

private:

  unsigned int channel_;  // the channel (0-7) of the ADC that this sensor is on
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
  bool values_updated_; // this is false when the actual values are not the most current (ex. the sensor has been sampled
                // since the last time the actual values were calculated)

  void reset(); // reset the sample values
  void calculate(); // turns the read values into legible sensor values

  // use this to input the raw read value from the SPI transaction
  void sample(int read_value);

  // allows the ADCChip class access to private stuff
  friend class ADCChip;

public:

  // constructors
  ADCSensor() = delete; // delete the default constructor
  ADCSensor(unsigned int channel, int zero_mV, int mV_per_sensor_unit);

  // getters (automatically calculate the real-life values if appropriate)
  float avg();
  float min();
  float max();
  int read_value() const {return read_value_;}
  float read_mvoltage() const {return read_mvoltage_;} // returns the last calculated average millivolt reading
  float last_calc_avg() {return actual_avg_;} // does no calculation
  int sample_count(){return running_read_count_;}
  unsigned int get_channel() const {return channel_;}

  
};


class ADCChip {

private:
  int chip_select_;


public:

  // default constructor
  ADCChip() = delete;

  // constructor
  ADCChip(int chip_select) : chip_select_(chip_select) {}

  // member-functions
  void begin(); // used to intilize the pin

  // sample a single sensor
  void sample(ADCSensor &sensor0);

  // sample many sensors
  void sample(ADCSensor &sensor0, ADCSensor &sensor1);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5, ADCSensor &sensor6);
  void sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5, ADCSensor &sensor6, ADCSensor &sensor7);

};


#endif
