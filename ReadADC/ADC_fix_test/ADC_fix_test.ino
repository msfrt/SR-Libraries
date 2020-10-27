#include <EasyTimer.h>
#include "ReadADC.h"
#include <SPI.h>


ADCChip adc1(10);
ADCSensor sens0(0, 0, 1);
ADCSensor sens1(1, 0, 1);
ADCSensor sens2(2, 0, 1);
ADCSensor sens3(3, 0, 1);
ADCSensor sens4(4, 0, 1);
ADCSensor sens5(5, 0, 1);
ADCSensor sens6(6, 0, 1);
ADCSensor sens7(7, 0, 1);

EasyTimer print_timer(10);


void setup() {
  

  // Initialize serial communication
  Serial.begin(112500);

  //initialize the CAN Bus and set its baud rate to 1Mb
  // cbus2.begin();
  // cbus2.setBaudRate(1000000);

  // initialize SPI communication
  SPI.begin();

  // initialize ADCs
  adc1.begin();

}


void loop() {


  

  adc1.sample(sens0, sens1);


  if (print_timer.isup()){
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println("sens0:");
    Serial.println(sens0.read_value());
    Serial.println(sens0.min());
    Serial.println(sens0.avg());
    Serial.println(sens0.max());

    Serial.println();
    Serial.println("sens1:");
    Serial.println(sens1.read_value());
    Serial.println(sens1.min());
    Serial.println(sens1.avg());
    Serial.println(sens1.max());
  }

  // Serial.println(sens1.read_value());
  // Serial.println(sens2.read_value());
  // Serial.println(sens3.read_value());
  // Serial.println(sens4.read_value());
  // Serial.println(sens5.read_value());
  // Serial.println(sens6.read_value());
  // Serial.println(sens7.read_value());

}