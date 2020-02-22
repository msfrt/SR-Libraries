#ifndef EEPROM_HELPER_H
#define EEPROM_HELPER_H

#include <Arduino.h>


template <class T>
class EEPROM_Value{

  private:
    uint16_t address_;
    uint8_t size_; // size in bytes of the type T
    T value_;

    // allow EEPROM_25LC128 to access private member variables
    friend class EEPROM_25LC128;

  public:

    EEPROM_Value() = delete;
    EEPROM_Value(uint16_t memory_address) : address_(memory_address) {
      size_ = sizeof(T);
    }

    // get the value
    T value() {return value_;}

    // allow us to use the = operator to assign values
    const T operator=(T new_value) {value_ = new_value; return value_;}

};




class EEPROM_25LC128{
  private:
    const int chip_select_;
    unsigned long next_write_time_ = 0;
    const unsigned long us_delay_time_ = 3200; // microseconds - this delay has been proven to work on TC board
    bool safe_to_write_ = true; // if it's safe to write. Only updated through the setter
    const int max_write_attempts_ = 16; // when verify-write is true, this is the maximum attempts before failure is accepted
    int current_write_attempt_ = 0;


  public:

    // constructors
    EEPROM_25LC128() = delete;
    EEPROM_25LC128(int chip_select_pin) : chip_select_(chip_select_pin) {};

    // prepares chip for reading and writing
    void begin();

    // reads data from the eeprom chip
    uint8_t readByte(uint16_t address);

    // read data from a redundant address
    uint8_t readByteRedundant(uint16_t address1, uint16_t address2, uint16_t address3);

    // writes data to the eeprom chip
    bool writeByte(uint16_t address, uint8_t data, bool verify = false);

    // write redundant data to three adresses
    bool writeByteRedundant(uint16_t address1, uint16_t address2, uint16_t address3, uint8_t data);

    // used for writing EEPROM_Values
    template <class T1>
    bool write(EEPROM_Value<T1> eeprom_value);

    // used for reading EEPROM_Values
    template <class T2>
    T2 read(EEPROM_Value<T2> eeprom_value);

};


// templated. keep in this file.
template <class T1>
bool EEPROM_25LC128::write(EEPROM_Value<T1> eeprom_value){

  // used to store the current byte that will be written
  uint8_t write_byte = 0;

  // make a copy so we can bitshift without destroying original value
  T1 current_value = eeprom_value.value_;

  // loop to set each byte. We set the least significant first in the last byte position.
  for (int byte = eeprom_value.size_ - 1; byte >= 0; byte--){

    // copy over the last 8-bits
    write_byte = current_value;

    // read the value at the current byte address
    this->writeByte(eeprom_value.address_ + byte, write_byte, true);

    // shift the current_value over by 8-bits to get ready for the next byte to set
    current_value >>= 8;
  }

  return true;
}


// templated. keep in this file.
template <class T2>
T2 EEPROM_25LC128::read(EEPROM_Value<T2> eeprom_value){

  uint8_t read_byte = 0;

  // set the value to zero, then we'll bitshift the value left 8 bits if necessary when each byte comes in
  eeprom_value = 0;

  // loop to fetch each byte
  for (uint8_t byte = 0; byte < eeprom_value.size_; byte++){

    // shift current value over 1 byte
    eeprom_value = eeprom_value.value_ << 8;

    // read the value at the current byte address
    read_byte = this->readByte(eeprom_value.address_ + byte);

    // update the last 8-bits of the value by adding the new byte
    eeprom_value = eeprom_value.value_ + read_byte;
  }

  // return the final value (which is also stored in the EEPROM_Value object, obviously)
  return eeprom_value.value_;

}


#endif
