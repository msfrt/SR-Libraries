#ifndef DONT_SMOKE_CIGS_INSIDE
#define DONT_SMOKE_CIGS_INSIDE

#include <FlexCAN_T4.h>

CAN_message_t msg;

StateSignal my_cigarette(8, true, 1, 0, 0, 0, -12);


void can_msgs(){

}

#endif
