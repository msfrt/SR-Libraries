#include "EasyTimer.h"

LEDBlink onboard_led(13, 20);

void setup(){
  Serial.begin(115200);


  int my_signed_int = -100;
  unsigned int my_unsigned_int = my_signed_int;
  int my_second_signed_int = my_signed_int;

  delay(500);

  Serial.println(my_signed_int);
  Serial.println(my_unsigned_int);
  Serial.println(my_second_signed_int);
  Serial.println();
  Serial.println(my_signed_int, BIN);
  Serial.println(my_unsigned_int, BIN);
  Serial.println(my_second_signed_int, BIN);
}

void loop(){
  onboard_led.run();
}
