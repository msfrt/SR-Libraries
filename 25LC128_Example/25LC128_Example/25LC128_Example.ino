//----------------------------------------------------------------------------------------------------------------------
//  Written by:     Nicholas Kopec
//  Purpose:        Example functions for communication with the 25LC128 EEPROM module
//  Description:    25LC128_Example.ino
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//  TODOS:
//    - add function for reading pages/multiple bytes
//    - validate function for writing pages 
//    - needs to be changed into a header file format before being used in other code
//----------------------------------------------------------------------------------------------------------------------

// include the SPI library:
#include <SPI.h>

// define the chip select pin for the ADC
const int eepromCS = 9;

//----------------------------------------------------------------------------------------------------------------------
// EEPROM memory has a limitied number of write cycles per address before it physically degrades. Therefore you must
// therefore you must limit the amount of times that you write to each address. It is good practice to only rewrite
// to the memory if the variable is changed. In this code the teensy only writes to the EEPROM once per power cycle so
// the functionality could be tested
//----------------------------------------------------------------------------------------------------------------------

// switch to only write to the EEPROM one time
bool sent = false;



//----------------------------------------------------------------------------------------------------------------------
//
//                                eepromWriteByte Parameters
//
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// The 25LC128 has a storage structure of 16384 x 8bit organization. This means that there are 16384 address locations
// that each hold 8bits. In order to read/write to the EEPROM module you must send the address of the location you are
// interested in. This will be a number between 0 and 16384 stored with a 16bit interger where the 2 MSBs are dont
// cares.
//----------------------------------------------------------------------------------------------------------------------

// set the address to be read/write to
uint16_t address = 4;

// set the 1 byte data to be written
uint8_t data = 255;



//----------------------------------------------------------------------------------------------------------------------
//
//                                eepromWritePage Parameters
//
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
// Along with writing data to the EEPROM module one page at a time, you can also write multiple bytes to it at once.
// This is called page writing. You can think of a page as a block of storage in the EEPROM module. The 25LC128 has a
// 16384 x 8bit storage organizarion with 64 byte pages (each page is made up of 64 bytes). When you do a page write
// (writing to more than one address at a time) you can only write to data that is within the same page. As you only
// specify the address of the first byte that you write, writing multiple bytes of data writes the bytes sequencially.
// If you write more that one page of data or go past the end of a page, it begins to overwrite the data at the beginning
// of the page. This means that it is critically important that you stay within a page when writing data. Since the
// EEPROM module is made up of 16384 x 8bit organization and has 64bit pages, this means that there are 256 pages in
// total (16384/64). Each page starts at an addresses that are interger multiples of the page size {0,64,128,256,....}
// and end at addresses that are interger multiples of the page size - 1 {63, 127,255,....}.
//----------------------------------------------------------------------------------------------------------------------

// number of bytes in a page (constant for the 25LC128)
const uint8_t pageSize = 64;

// number of pages in the 25LC128
const uint8_t numPages = 256;


//----------------------------------------------------------------------------------------------------------------------
// As stated above, when you write to a page you can only write to one page at a time. For this program my data array
// will consist of 16bit intergers. If you were to use a int, they are 32bit values for the T4 and the array size can
// only be 16 indices.
//----------------------------------------------------------------------------------------------------------------------

// data to be sent to EEPROM using a page write (each element is a 16bit interger - default int is 32 bit)
int16_t pageData[32];


void setup() {

  // set the chip select pin as an output:
  pinMode(eepromCS, OUTPUT);

  // write the CS pin high to disable the eeprom chip
  digitalWrite(eepromCS, HIGH);

  // initialize serial communication
  Serial.begin(9600);

  // initialize SPI:
  SPI.begin();

}

void loop() {

  // slow down the read rate for testing
  delay(1000);



  //--------------------------------------------------------------------------------------------------------------------
  //                      For sending one byte
  //--------------------------------------------------------------------------------------------------------------------


   // only write the data to the EEPROM module once
   if(!sent){

   // write the data
   eepromWriteByte(eepromCS, address, data);

   // toggle sent to prevent the eeprom from being written to
   sent = true;
  }

  // repeatly read the data that was written
  else{
   Serial.println(eepromRead(eepromCS, address));
  }

  //--------------------------------------------------------------------------------------------------------------------
  //                      For sending one page *HAS NOT BEEN VALIDATED YET* (also rewrites to the module constantly)
  //--------------------------------------------------------------------------------------------------------------------

  // populate the data array to be written to EEPROM. You must do this every time you call the writePage function bc
  // SPI.transfer replaces the array data with recieved data.
  // for(auto i=0; i<(sizeof(pageData) / sizeof(pageData[0])); i++)
  // {
  //   pageData[i] = (sizeof(pageData) / sizeof(pageData[0])) - i;
  // }

  // eepromWritePage(eepromCS, 0, pageData, sizeof(pageData));


  // Serial.println(sizeof(pageData[0]));
  // Serial.println(sizeof(pageData));
  // Serial.println(sizeof(pageData) / sizeof(pageData[0]));
  // for(auto i=0; i<(sizeof(pageData) / sizeof(pageData[0])); i++)
  // {
  //   Serial.print(pageData[i]);
  //   Serial.print(",");
  // }
  // Serial.println();


}

// data needs to be less than 64 bytes since it is an int (2 bytes), it can only be 32 indices
void eepromWritePage(int eepromCS, uint16_t pageNum, int16_t data[], int dataSize){
  //--------------------------------------------------------------------------------------------------------------------
  //
  //
  // Inputs:
  //   eepromCS: pin number on the teensy which is connected to the EEPROMS's chip select pin
  //   pageNum: the page number to write to (0-255)
  //   data: the data array to be written (up to 64bytes)
  //   dataSize: the size of the data array in bytes
  //
  // Returns:
  //   none
  //--------------------------------------------------------------------------------------------------------------------

  // do not attempt to write to the eeprom if the data is larger than a page
  if(dataSize <= pageSize)
  {
    // Start the SPI communication
    // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
    SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

    // calculate the address of the page
    uint16_t address = pageSize * pageNum;


    //--------------------------------------------------------------------------------------------------------------------
    // The following three commands are needed to write data to the EEPROM module. As specified in the datasheet
    // (which you should read), you must first set the write enable latch in the EEPROM module. This is done by
    // sending the "WREN" instruction which is "00000110". After you send the "WREN" command to complete the setting of the
    // write enable latch.
    //--------------------------------------------------------------------------------------------------------------------


    // // take the CS pin low to enable the chip
    // digitalWrite(eepromCS, LOW);
    // // send the "WREN" command
    // SPI.transfer(0b00000110);
    // // take the CS high to disable the chip and set the write enable latch
    // digitalWrite(eepromCS, HIGH);



    // The following 5 commands are for writing the data to the specified address

    // take the CS pin low to enable the chip
    digitalWrite(eepromCS, LOW);
    // send the "WRITE" command
    SPI.transfer(0b00000010);
    // send the address for which the data will be written to
    SPI.transfer16(address);
    // send the data
    SPI.transfer(data, dataSize);
    // take the CS high to disable the chip (the data wont be written to the module until this is completed)
    digitalWrite(eepromCS, HIGH);

    // end the SPI communication
    SPI.endTransaction();
  }
}

void eepromWriteByte(int eepromCS, uint16_t address, uint8_t data){
  //--------------------------------------------------------------------------------------------------------------------
  // This function is an example of the process of writing a byte of data to the EEPROM module. In the datasheet there
  // are two methods for writing data to the EEPROM: a single byte or multiple bytes that can be up to a page long(read
  // the datasheet). This is for the method of writing a single byte. A function still needs to be developed in order to
  // write a page, this can be used to write up to 64 bytes. Page size is specific to each EEPROM module.
  //
  // Inputs:
  //   eepromCS: pin number on the teensy which is connected to the EEPROMS's chip select pin
  //   address: address for the data to be written to (should be between 0 and 16384 for the 25LC128)
  //   data: the data to be written (8 bits)
  //
  // Returns:
  //   none
  //--------------------------------------------------------------------------------------------------------------------


  // Start the SPI communication
  // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));


  //--------------------------------------------------------------------------------------------------------------------
  // The following three commands are needed to write data to the EEPROM module. As specified in the datasheet
  // (which you should read), you must first set the write enable latch in the EEPROM module. This is done by
  // sending the "WREN" instruction which is "00000110". After you send the "WREN" command to complete the setting of the
  // write enable latch.
  //--------------------------------------------------------------------------------------------------------------------


  // take the CS pin low to enable the chip
  digitalWrite(eepromCS, LOW);
  // send the "WREN" command
  SPI.transfer(0b00000110);
  // take the CS high to disable the chip and set the write enable latch
  digitalWrite(eepromCS, HIGH);



  // The following 5 commands are for writing the data to the specified address

  // take the CS pin low to enable the chip
  digitalWrite(eepromCS, LOW);
  // send the "WRITE" command
  SPI.transfer(0b00000010);
  // send the address for which the data will be written to
  SPI.transfer16(address);
  // send the data
  SPI.transfer(data);
  // take the CS high to disable the chip (the data wont be written to the module until this is completed)
  digitalWrite(eepromCS, HIGH);

  // end the SPI communication
  SPI.endTransaction();
}

int eepromRead(int eepromCS, uint16_t address){

  //--------------------------------------------------------------------------------------------------------------------
  // This function is for reading data that is stored in the EEPROM module. The function is designed to read a single
  // address of memory. As specified by the datasheet, the 25LC128 is allows you to read data sequentially by keeping the
  // CS pin low. After calling SPI.transfer() to get the first byte of data, you can continue to call the SPI.transfer()
  // and the EEPROM will return the byte of data in the next address automatically. Again, read the datasheet.
  //
  // Inputs:
  //   eepromCS: pin number on the teensy which is connected to the EEPROMS's chip select pin
  //   address: address for the data to be written to (should be between 0 and 16384 for the 25LC128)
  //
  // Returns:
  //   data: the byte of data that was returned by the EEPROM module
  //--------------------------------------------------------------------------------------------------------------------


  // initialize the variable to store the recieved data
  uint8_t data;

  // Start the SPI communication
  // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

  // take the CS pin low to enable the chip
  digitalWrite(eepromCS, LOW);

  // send the "READ" command
  SPI.transfer(0b00000011);
  // send the address for which the data will be written to
  SPI.transfer16(address);
  // send the data (the 0 is needed so you can call SPI.transfer() so it will return the data sent by the EEPROM)
  data = SPI.transfer(0);

  // take the CS high to disable the chip (the data wont be written to the module until this is completed)
  digitalWrite(eepromCS, HIGH);

  // end the SPI communication
  SPI.endTransaction();

  return data;
}
