#include "readADC.h"
#include "Arduino.h"
#include "SPI.h"


// constructor
ADCSensor::ADCSensor(int chip_select, int ADC_channel_number, int zero_milliVolt10,
                     int milliVolt10_per_unit, int scale_fact){
  this->chip_select_ = chip_select;
  this->ADC_channel_number_ = ADC_channel_number;
  this->zero_milliVolt10_ = zero_milliVolt10;
  this->milliVolt10_per_unit_ = milliVolt10_per_unit;
  this->CAN_scale_factor_ = scale_fact;

  this->read_value_ = 0;
  this->read_voltage_ = 0;
  this->running_read_total_ = 0; // used to store values for an average calculation
  this->running_read_count_ = 0;
  this->read_min_ = 4095; // max value of a read
  this->read_max_ = 0;

  // set the chip select pin as an output:
  pinMode(chip_select_, OUTPUT);

  // set the chip select pin high
  digitalWrite(chip_select_, HIGH);
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
}


// resets the sampling variables
void ADCSensor::reset(){
  this->running_read_total_ = 0;
  this->running_read_count_ = 0;
  this->read_min_ = 4095;
  this->read_max_ = 0;
}

// slower, uses floating-point math to calculate average value
double ADCSensor::avg(){
  double sensor_read_avg = static_cast<double>(this->running_read_total_) /
                           static_cast<double>(this->running_read_count_);
  double milli10voltage = (sensor_read_avg / 4095) * 50000; // read 0 = 0V, 4095 = 5V. 50000mV10 = 5V.
  return (milli10voltage - this->zero_milliVolt10_) / this->milliVolt10_per_unit_;
}
