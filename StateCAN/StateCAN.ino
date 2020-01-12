#include "EasyTimer.h"
#include <FlexCAN_T4.h>
#include "StateCAN.h"

LEDBlink onboard_led(13, 2);

CAN_message_t msg;
StateSignal test_sig(100, 0, 0, 0, -12);
int16_t sent_data;

void setup(){
  test_sig = 69.69;

  Serial.begin(115200);
  delay(1000);

  uint8_t byte1 = test_sig.can_value();
  uint8_t byte2 = test_sig.can_value() >> 8;
  sent_data = (byte2 << 8) | byte1;

  Serial.print("  valid: "); Serial.println(sent_data);

  // now make the sensor invalid
  test_sig.set_validity(false);

  byte1 = test_sig.can_value();
  byte2 = test_sig.can_value() >> 8;
  sent_data = (byte2 << 8) | byte1;

  Serial.print("invalid: "); Serial.println(sent_data);



}

void loop(){
  onboard_led.run();
}
