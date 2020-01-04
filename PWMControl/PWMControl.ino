#include "PWMControl.h"

//include these libraries in order to get the FlexCAN_T4 library. You can find this in the GitHub.
#include <circular_buffer.h>
#include <FlexCAN_T4.h>
#include <imxrt_flexcan.h>

//create the CAN send message and recieve message variables
static CAN_message_t msg, rxmsg;

FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;

//timer to send data at a slower set rate
unsigned long sendTimer = 0;




PwmDevice testDevice(1,1,1,1,10000,10000,10,100,500,5);

int pwm = 0;
int eng_state = 0;

void setup()
{
  Serial.begin(115200);

  //initialize the CAN Bus and set its baud rate to 1M
  Can1.begin();
  Can1.setBaudRate(1000000);
}

void loop()
{
  delay(100);

  Serial.print("PWM: ");
  Serial.println(testDevice.current_pwm());

  Serial.print("State: ");
  Serial.println(testDevice.device_state());

  Serial.print("Soft start state: ");
  Serial.println(testDevice.soft_start_state());

  Serial.print("Engine state: ");
  Serial.println(eng_state);

  Serial.println("---------------------------------");
  Serial.println();

  testDevice.set_pwm(pwm,0,eng_state);

  readCAN();

}


void readCAN(){

  if (Can1.read(rxmsg)) // make sure there's a message available to read
  {
    // store the message ID and length
    int rxID = rxmsg.id;
    int rxDataLen = rxmsg.len;

    // assign the message data into a more easily readable array, rxData
    int rxData[rxDataLen];
    // for(int i=0; i<rxDataLen; i++)
    // {
    //   rxData[i]=rxmsg.buf[i];
    //   Serial.print(rxData[i]);
    //   Serial.print(" ");
    // }
    pwm = rxmsg.buf[0];
    eng_state = rxmsg.buf[1];
  }
}
