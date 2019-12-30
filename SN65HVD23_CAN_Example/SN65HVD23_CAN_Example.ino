//----------------------------------------------------------------------------------------------------------------------
//  Written by:     Nicholas Kopec
//  Purpose:        Example functions for communication with the SN65HVD23 CAN transciever module
//  Description:    SN65HVD23_Example.ino
//----------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------
//  TODOS:
//    -add example for recieving messages
//----------------------------------------------------------------------------------------------------------------------

//include these libraries in order to get the FlexCAN_T4 library. You can find this in the GitHub.
#include <circular_buffer.h>
#include <FlexCAN_T4.h>
#include <imxrt_flexcan.h>



//create the CAN send message and recieve message variables
static CAN_message_t msg, rxmsg;
//----------------------------------------------------------------------------------------------------------------------
//  The following is new for CAN on the T4 and this library. This is for creating a CAN 2.0 bus.
//  This is the format: FlexCAN_T4< bus number, RX size, TX size> bus name. The bus number specifies which bus the
//  teensy uses at a hardware level. For example CAN1 is CRX1 & CTX1, which are pins 22 & 23 (look at the T4 pinout).
//  RX size is the size of the message being recieved by the teensy (keep it 256). TX size is the size of the transmitted
//  message (keep it 16). Bus name is the name given to the bus that is created from this setup.
//----------------------------------------------------------------------------------------------------------------------
FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can1;

//timer to send data at a slower set rate
unsigned long sendTimer = 0;



void setup()
{
  //initialize serial communication
  Serial.begin(112500);

  //initialize the CAN Bus and set its baud rate to 1M
  Can0.begin();
  Can0.setBaudRate(1000000);

}

void loop()
{

  if(millis() - sendTimer > 10)
  {
    CANMessage();
    sendTimer = millis();
  }

  readCAN();


}

void CANMessage()
{

  //add data to the can message
  msg.buf[0] = 1;
  msg.buf[1] = 9;
  msg.buf[2] = 0;
  msg.buf[3] = 10;
  msg.buf[4] = 50;
  msg.buf[5] = 0;
  msg.buf[6] = 99;
  msg.buf[7] = 0;

  //call the send function sendCAN(id, msg length, bus number)
  sendCAN(0x00, 8, 1);
}

void sendCAN(int id, int len, int busNo)
{

  msg.len = len; //CAN message length unit: Byte (8 bits)
  msg.id = id; //CAN ID

  switch(busNo)
  {
  case 1:
    Can1.write(msg); //Send the message
    break;
  }
}



readCAN()
{

  if (Can1.read(rxmsg)) // make sure there's a message available to read
  {
    // store the message ID and length
    int rxID = rxmsg.id;
    int rxDataLen = rxmsg.len;

    // assign the message data into a more easily readable array, rxData
    int rxData[rxDataLen];
    for(int i=0; i<rxDataLen; i++)
    {
      rxData[i]=rxmsg.buf[i];
      Serial.print(rxData[i]);
      Serial.print(" ");
    }

  }
}
