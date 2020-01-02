#include "readADC.h"
#include <EasyTimer.h>

ADCSensor my_sensor(9, 7, 0, 30, 10);

EasyTimer sample_timer(50); // 50hz
EasyTimer print_timer(2); // 2Hz

void setup(){
  // initialize serial communication for debugging purposes
  Serial.begin(112500);
}

void loop(){

  if (sample_timer.isup()){
    my_sensor.sample();
  }

  if (print_timer.isup()){
    Serial.print("Average value: ");
    Serial.println(my_sensor.avg());
    my_sensor.reset();
  }

}
