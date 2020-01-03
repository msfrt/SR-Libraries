#include "readADC.h"
#include <EasyTimer.h>

ADCSensor my_sensor(9, 0, 0, 1000, 10);

EasyTimer sample_timer(100); // 50hz
EasyTimer print_timer(2); // 2Hz

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
    my_sensor.sample();
  }

  if (print_timer.isup()){
    Serial.print("Average value: ");
    Serial.println(my_sensor.avg());
    Serial.print("Minumum value: ");
    Serial.println(my_sensor.min());
    Serial.print("Maximum value: ");
    Serial.println(my_sensor.max());
    Serial.println();
  }

}
