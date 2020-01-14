#include "EasyTimer.h"
#include <FlexCAN_T4.h>
#include "StateCAN.h"

LEDBlink onboard_led(13, 2);

CAN_message_t msg;
StateSignal test_sig(4, false, 1, 0, 0, 0, -12);

void setup(){
  test_sig = 17;

  Serial.begin(115200);
  delay(1000);

  uint8_t byte1 = test_sig.can_value();

  Serial.print("byte1: "); Serial.println(byte1, BIN);


}

void loop(){
  onboard_led.run();
}
