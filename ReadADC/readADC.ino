#include "readADC.h"
#include <EasyTimer.h>

// from left to right, 9 is the teensy pin connected to the ADC, 0 is the ADC pin that the sensor is on,
// 0 is the zero-value of the sensor in mV, 1000 is the mV per sensor unit,
ADCSensor my_sensor(9, 0, 0, 1000);

EasyTimer sample_timer(100); // 50hz timer from the EasyTimer library
EasyTimer print_timer(2); // 2Hz timer from the EasyTimer library

void setup(){
  // initialize serial communication for debugging purposes
  Serial.begin(112500);

  // initialize SPI:
  SPI.begin();

  // initialize sensor
  my_sensor.begin();
}

void loop(){

  if (sample_timer.isup()){
    my_sensor.sample(); // sample the ADC sensor at 50Hz
  }

  if (print_timer.isup()){ // get the values of the sensor every 2Hz
    Serial.print("Average value: ");
    Serial.println(my_sensor.avg());
    Serial.print("Minumum value: ");
    Serial.println(my_sensor.min());
    Serial.print("Maximum value: ");
    Serial.println(my_sensor.max());
    Serial.println();
  }

}
