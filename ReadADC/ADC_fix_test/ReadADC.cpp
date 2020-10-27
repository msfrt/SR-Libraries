#include "ReadADC.h"
#include <SPI.h>



// constructor
// param channel - The channel of the ADC that this sensor is on
// param zero_mV - the millivolt where the sensor is equal to zero
// param mV_per_sensor_unit - the millivolts per units measured (ex. mV per degree C)
ADCSensor::ADCSensor(unsigned int channel, int zero_mV, int mV_per_sensor_unit){
  
  this->channel_ = channel;
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
  this->values_updated_ = false;
}


void ADCChip::begin(){
  // set the chip select pin as an output:
  pinMode(this->chip_select_, OUTPUT);

  // set the chip select pin high
  digitalWrite(this->chip_select_, HIGH);
}


// read the sample value and add it to the appropriate variables
void ADCSensor::sample(int value){

  this->read_value_ = value;

  // if the read value is less than the current minimum, it is the new minimum
  if (value < this->read_min_){this->read_min_ = value;}

  // if the read value is more than the current maximum, it is the new maximum
  if (value> this->read_max_){this->read_max_ = value;}

  // add the read value to the running total for average calculation and increment the read counter
  this->running_read_total_ += value;
  this->running_read_count_++;

  // there is at least one new sample since calculating the actual values, so set the values_updated_ bool to false
  this->values_updated_ = false;
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
  this->values_updated_ = true;
}

float ADCSensor::avg(){
  if (!values_updated_){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_avg_;
}

float ADCSensor::min(){
  if (!values_updated_){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_min_;
}

float ADCSensor::max(){
  if (!values_updated_){ // if the values are not the most current, update them before returning the average!
    this->calculate();
  }
  return this->actual_max_;
}

// sample a single channel. This is the most basic form of sampling, and requires two transactions
void ADCChip::sample(ADCSensor &sensor0){

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
  //
  // One last thing to note is that the ADC returns the read value in the SECOND transaction. So, if you
  // individually sample every ADC channel, you essentially need two transactions for every read. This is why
  // it's better for you to chain channel readings using a multi-sample function

  // send the channel number for the ADC to read
  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  // set the CS pin high to de-select the chip:
  digitalWrite(this->chip_select_,HIGH);

  // end the SPI communication
  SPI.endTransaction();

}


void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  // begin the daisy-chain
  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}

void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}


void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(sensor3.get_channel() << 11));
  sensor3.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}


void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(sensor3.get_channel() << 11));
  sensor3.sample(SPI.transfer16(sensor4.get_channel() << 11));
  sensor4.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}

void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(sensor3.get_channel() << 11));
  sensor3.sample(SPI.transfer16(sensor4.get_channel() << 11));
  sensor4.sample(SPI.transfer16(sensor5.get_channel() << 11));
  sensor5.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}

void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5, ADCSensor &sensor6){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(sensor3.get_channel() << 11));
  sensor3.sample(SPI.transfer16(sensor4.get_channel() << 11));
  sensor4.sample(SPI.transfer16(sensor5.get_channel() << 11));
  sensor5.sample(SPI.transfer16(sensor6.get_channel() << 11));
  sensor6.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}

void ADCChip::sample(ADCSensor &sensor0, ADCSensor &sensor1, ADCSensor &sensor2, ADCSensor &sensor3, ADCSensor &sensor4, ADCSensor &sensor5, ADCSensor &sensor6, ADCSensor &sensor7){

  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));
  digitalWrite(this->chip_select_, LOW);

  SPI.transfer16(sensor0.get_channel() << 11);
  sensor0.sample(SPI.transfer16(sensor1.get_channel() << 11));
  sensor1.sample(SPI.transfer16(sensor2.get_channel() << 11));
  sensor2.sample(SPI.transfer16(sensor3.get_channel() << 11));
  sensor3.sample(SPI.transfer16(sensor4.get_channel() << 11));
  sensor4.sample(SPI.transfer16(sensor5.get_channel() << 11));
  sensor5.sample(SPI.transfer16(sensor6.get_channel() << 11));
  sensor6.sample(SPI.transfer16(sensor7.get_channel() << 11));
  sensor7.sample(SPI.transfer16(0 << 11));  // the channel input here does not really matter

  digitalWrite(this->chip_select_,HIGH);
  SPI.endTransaction();
}
