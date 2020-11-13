// a sketch for testing StateCAN signals

#include "EasyTimer.h"
#include <FlexCAN_T4.h>
#include "StateCAN.h"

#include "output.hpp"

LEDBlink onboard_led(13, 2);

CAN_message_t cigs_inside;
StateSignal test_sig(4, false, 1, 0, 0, 0, -12);
StateCounter my_counter(16);

EasyTimer print_timer(2);

void setup(){
  test_sig = 17;

  Serial.begin(115200);
  delay(1000);

  //uint8_t byte1 = test_sig.can_value();


}

void loop(){
  onboard_led.run();

  if (print_timer.isup()){
    Serial.println(my_counter.value());
  }

}
