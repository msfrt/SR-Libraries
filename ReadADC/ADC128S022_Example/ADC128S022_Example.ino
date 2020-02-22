//----------------------------------------------------------------------------------------------------------------------
//  Written by:     Nicholas Kopec
//  Purpose:        Example functions for communication with the ADC128S022 EEPROM module
//  Description:    ADC128S022_Example.ino
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//  TODOS:
//    - needs to be changed into a header file format before being used in other code
//----------------------------------------------------------------------------------------------------------------------


// include the SPI library:
#include <SPI.h>

// define the chip select pin for the ADC
const int adcCS = 9;
unsigned long timer = 0;

void setup() {
  // set the chip select pin as an output:
  pinMode(adcCS, OUTPUT);

  // set the chip select pin high
  digitalWrite(adcCS, HIGH);

  // initialize serial communication
  Serial.begin(112500);

  // initialize SPI:
  SPI.begin();
}

void loop() {

  // call anaRead() every 5uS which is 200000 Hz or 200000 Sps, the max rate for the ADC128S022
  if ((micros() - timer) > 5){
    anaRead(adcCS,0);
    timer = micros();
  }


}

int anaRead(int adcCS, uint16_t channelNo) {

  //--------------------------------------------------------------------------------------------------------------------
  // anaRead takes in a ADC's chip select pin number and the ADC channel number to be read, reads the value of the
  // input, and then returns the read value which is a 12 bit number (0 - 4095)  porportional to the voltage at the
  // selected input of the ADC (0V - 5V)
  //
  // Inputs:
  //     adcCS: pin number on the teensy which is connected to the ADC's chip select pin
  //     channelNo: input number of the ADC which will be read (0-7)
  //
  // Returns:
  //     readValue: the value returned by the ADC which will be a 12 bit number between 0 and 4095 which corresponds to
  //     the voltage at the selected input of the ADC (0V - 5V)
  //--------------------------------------------------------------------------------------------------------------------


  uint16_t readValue = 0;

  // Start the SPI communication
  // SPISettings(clk frequency, bit order, SPI Mode (google arduino SPI modes for details))
  SPI.beginTransaction(SPISettings(3200000, MSBFIRST, SPI_MODE0));

  // take the CS pin low to enable the chip:
  digitalWrite(adcCS,LOW);

  //--------------------------------------------------------------------------------------------------------------------
  // In order to tell the ADC which input to read you must send it a binary value corresponding to the channel.
  // channelNo should be a value between 0 and 7 corresponding to the input you want to read. The binary representation
  // of this value must be bit shifted so that it is in the correct position during the SPI communication sequence.
  // The SPI sequence lasts 16 clock cycles so both the sent value and recieved value are 16 bits, one for each clock cycle.
  //
  // Example: If you want to read the 2nd channel of the ADC the function call would be adaRead(adcSC, 2). 2 in a 16 bit
  // binary number is "0000000000000010" (MSB first). The the position of the channelNo must be in the following position
  // "00XXX00000000000", (X represents the position) as defined by the ADC's datasheet. To achieve this, the value
  // inputted into this function is bit shifted by 11 to the left. The SPI.transfer16( )sends this value and returns
  // the value sent back by the ADC.
  //--------------------------------------------------------------------------------------------------------------------


  // send the channelNo for the ADC to read
  readValue = SPI.transfer16(channelNo << 11);

  //--------------------------------------------------------------------------------------------------------------------
  // the following is for debugging the bitshifting process
  // // bit shift the inputted channelNo
  // uint16_t channelNoShifted = channelNo << 11;
  //
  // // read out the binary representation of the channelNo interger
  // for (int i=0; i<16; i++){
  //   if (i == 16){
  //     Serial.println(bitRead(channelNoShifted, i));
  //   }
  //   else{
  //     Serial.print(bitRead(channelNoShifted, i));
  //   }
  // }
  //--------------------------------------------------------------------------------------------------------------------

  //--------------------------------------------------------------------------------------------------------------------
  // the following is for debugging the returned value from the ADC
  float voltage = (float(readValue) / 4095) * 5;
  Serial.print("Input ");
  Serial.print(channelNo);
  Serial.print(": ");
  Serial.print(readValue);
  Serial.print("  which is: ");
  Serial.print(voltage, 4);
  Serial.println(" Volts");
  //--------------------------------------------------------------------------------------------------------------------


  // take the CS pin high to de-select the chip:
  digitalWrite(adcCS,HIGH);

  // end the SPI communication
  SPI.endTransaction();

  // return value read by ADC
  return readValue;
}
