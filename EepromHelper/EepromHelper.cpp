#include "EepromHelper.h"
#include <Arduino.h>
#include <SPI.H>

// #define DEBUG_EEPROM


void EEPROM_25LC128::begin(){
  // set the chip select pin as an output:
  pinMode(this->chip_select_, OUTPUT);

  // write the CS pin high to disable the eeprom chip
  digitalWrite(this->chip_select_, HIGH);
}



bool EEPROM_25LC128::writeByte(uint16_t address, uint8_t data, bool verify){

  // before ANYTHING, read the current adress and compare to the data we want to store. If it's the same, there's
  // simply no need to write new data, as the number of write cycles is limited before the chip degrades into oblivion
  if (data == this->readByte(address)){

    // debugging print statement
    #ifdef DEBUG_EEPROM
    Serial.print("The data 0x"); Serial.print(data, HEX); Serial.print(" already exists at 0x");
    Serial.print(address, HEX); Serial.println("!");
    #endif

    return true; // data is already there, so it's like we wrote it
  }

  //Serial.println("Never got here!");

  // if verify, set the curernt write attempt to 0. Otherwise, current attempt is one less than the max
  if (verify){
    this->current_write_attempt_ = 0;
  } else {
    this->current_write_attempt_ = this->max_write_attempts_ - 1;
  }

  while (this->safe_to_write_ && (this->current_write_attempt_ < this->max_write_attempts_)){

    // hold until it's safe to write again
    while(micros() < this->next_write_time_){}

    // verify and break if applicable
    if (verify && (this->current_write_attempt_ != 0)){
      if (this->readByte(address) == data){
        break;
      } else {

        // debugging print statement
        #ifdef DEBUG_EEPROM
        Serial.print("Attempt "); Serial.print(current_write_attempt_); Serial.print(" to write \""); Serial.print(data);
        Serial.print("\" at address 0x"); Serial.print(address, HEX); Serial.println(" has failed!");
        #endif
      }
    }

    // Start the SPI communication
    // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
    SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

    // take the CS pin low to enable the chip
    digitalWrite(this->chip_select_, LOW);
    // send the "WREN" command
    SPI.transfer(0b00000110);
    // take the CS high to disable the chip and set the write enable latch
    digitalWrite(this->chip_select_, HIGH);



    // The following 5 commands are for writing the data to the specified address

    // take the CS pin low to enable the chip
    digitalWrite(this->chip_select_, LOW);
    // send the "WRITE" command
    SPI.transfer(0b00000010);
    // send the address for which the data will be written to
    SPI.transfer16(address);
    // send the data
    SPI.transfer(data);
    // take the CS high to disable the chip (the data wont be written to the module until this is completed)
    digitalWrite(this->chip_select_, HIGH);

    // end the SPI communication
    SPI.endTransaction();

    // update the last write time
    this->next_write_time_ = micros() + this->us_delay_time_;

    // increment the write attempt counter
    this->current_write_attempt_++;

  } // end write attempt loop


  // return true if write was sucessful and verify was true
  if (!this->safe_to_write_ || (verify && this->current_write_attempt_ == this->max_write_attempts_)){
    return false;
  } else {
    return true;
  }
}


uint8_t EEPROM_25LC128::readByte(uint16_t address){

  // if there was just a write, be sure to wait before trying to read
  while(micros() < this->next_write_time_){}

  // initialize the variable to store the recieved data
  uint8_t data;

  // Start the SPI communication
  // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

  // take the CS pin low to enable the chip
  digitalWrite(this->chip_select_, LOW);

  // send the "READ" command
  SPI.transfer(0b00000011);
  // send the address for which the data will be written to
  SPI.transfer16(address);
  // send the data (the 0 is needed so you can call SPI.transfer() so it will return the data sent by the EEPROM)
  data = SPI.transfer(0);

  // take the CS high to disable the chip (the data wont be written to the module until this is completed)
  digitalWrite(this->chip_select_, HIGH);

  // end the SPI communication
  SPI.endTransaction();

  return data;
}
