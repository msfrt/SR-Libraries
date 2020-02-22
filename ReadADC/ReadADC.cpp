#include "ReadADC.h"
#include <SPI.h>



// constructor
ADCSensor::ADCSensor(int chip_select, uint16_t ADC_channel_number, int zero_mV, int mV_per_sensor_unit){
  this->chip_select_ = chip_select;
  this->ADC_channel_number_ = ADC_channel_number;
  this->zero_mV_ = zero_mV;
  this->mV_per_sensor_unit_ = mV_per_sensor_unit;

  this->read_value_ = 0;
  this->read_mvoltage_ = 0;
  this->running_read_total_ = 0; // used to store values for an average calculation
  this->running_read_count_ = 0;
  this->read_min_ = 4095; // max value of a read
  this->read_max_ = 0;

  this->actual_avg_ = 0;
  this->actual_min_ = 0;
  this->actual_max_ = 0;
  this->values_updated = false;
}

void ADCSensor::begin(){
  // set the chip select pin as an output:
  pinMode(this->chip_select_, OUTPUT);

  // set the chip select pin high
  digitalWrite(this->chip_select_, HIGH);
}

// sample the sensor
void ADCSensor::sample(){

  // Start the SPI communication
  // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

  // set the CS pin low to enable the chip:
  digitalWrite(this->chip_select_, LOW);

  // In order to tell the ADC which input to read you must send it a binary value corresponding to the channel.
  // ADC_channel_number should be a value between 0 and 7 corresponding to the input you want to read. The binary
  // representation of this value must be bit shifted so that it is in the correct position during the SPI communication
  // sequence. The SPI sequence lasts 16 clock cycles so both the sent value and recieved value are 16 bits, one for
  // each clock cycle.
  //
  // Example: The the position of the channelNo must be in the following position
  // "00XXX00000000000", (X represents the position) as defined by the ADC's datasheet. To achieve this, the value
  // input into this function is bit shifted by 11 to the left. The SPI.transfer16( )sends this value and returns
  // the value sent back by the ADC.

  // send the channel number for the ADC to read
  this->read_value_ = SPI.transfer16(this->ADC_channel_number_ << 11);
  this->read_value_ = SPI.transfer16(this->ADC_channel_number_ << 11);
  this->read_value_ = SPI.transfer16(this->ADC_channel_number_ << 11);
  this->read_value_ = SPI.transfer16(this->ADC_channel_number_ << 11);
  this->read_value_ = SPI.transfer16(this->ADC_channel_number_ << 11);

  // set the CS pin high to de-select the chip:
  digitalWrite(this->chip_select_,HIGH);

  // end the SPI communication
  SPI.endTransaction();

  // if the read value is less than the current minimum, it is the new minimum
  if (this->read_value_ < this->read_min_){this->read_min_ = this->read_value_;}

  // if the read value is more than the current maximum, it is the new maximum
  if (this->read_value_ > this->read_max_){this->read_max_ = this->read_value_;}

  // add the read value to the running total for average calculation and increment the read counter
  this->running_read_total_ += this->read_value_;
  this->running_read_count_++;

  // there is at least one new sample since calculating the actual values, so set the values_updated bool to false
  this->values_updated = false;
}


// resets the sampling variables
void ADCSensor::reset(){
  this->running_read_total_ = 0;
  this->running_read_count_ = 0;
  this->read_min_ = 4095;
  this->read_max_ = 0;
}

void ADCSensor::calculate(){

  float mV = 0.00; // initialize a temp variable only once to save processing power

  // calculate the average values
  float sensor_read_avg = (this->running_read_total_) / (this->running_read_count_);
  mV = (sensor_read_avg / 4095.0) * 5000; // read 0 = 0V, 4095 = 5V. 5000mV = 5V.
  this->actual_avg_ = (mV - this->zero_mV_) / this->mV_per_sensor_unit_; // calculates the sensor value

  // set the last calculated mv average to the mv getter variable
  this->read_mvoltage_ = mV;

  // calculate the min values
  mV = (static_cast<float>(this->read_min_) / 4095.0) * 5000;
  this->actual_min_ = (mV - this->zero_mV_) / this->mV_per_sensor_unit_;

  // calculate the max values
  mV = (static_cast<float>(this->read_max_) / 4095.0) * 5000;
  this->actual_max_ = (mV - this->zero_mV_) / this->mV_per_sensor_unit_;

  this->reset();
  this->values_updated = true;
}

float ADCSensor::avg(){
  if (!values_updated){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_avg_;
}

float ADCSensor::min(){
  if (!values_updated){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_min_;
}

float ADCSensor::max(){
  if (!values_updated){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_max_;
}
