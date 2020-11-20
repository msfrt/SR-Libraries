/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <FlexCAN_T4.h>
#include <StateCAN.h>

// Message: TEST_1_BE [0x1a6]
StateSignal TEST_10bit1_BE(10, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool1_BE(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool2_BE(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_4bit2_BE(4, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool5_BE(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_4bit3_BE(4, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool4_BE(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool3_BE(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_7bit2_BE(7, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_7bit3_BE(7, true, 1, 0.0, 0, 0, 0.0, 0);

// Message: TEST_2 [0x1a5]
StateSignal TEST_10bit2(10, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_10bit1(10, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_24bit1(24, true, 1, 0.0, 0, 0, 0.0, 0);

// Message: TEST_1 [0x1a4]
StateSignal TEST_bool5(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool4(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool3(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool2(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_bool1(1, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_4bit1(4, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_4bit2(4, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_4bit3(4, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_7bit1(7, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_7bit2(7, true, 1, 0.0, 0, 0, 0.0, 0);
StateSignal TEST_7bit3(7, true, 1, 0.0, 0, 0, 0.0, 0);

// Message: PDM_09 [0x103]
StateSignal PDM_OBD_oilPressure(1, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_OBD_oilTemp(1, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_OBD_fuelPressure(1, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_engineState(8, true, 1, 0.0, 0, 3, 0.0, 0);

// Message: PDM_25 [0x113]
StateSignal PDM_counterMsg275(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_carMiles(16, true, 10, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_engineHours(16, true, 1, 0.0, -32768, 32767, 0.0, 0);
StateSignal PDM_engineMinutes(16, true, 1, 0.0, -32768, 32767, 0.0, 0);

// Message: PDM_31 [0x119]
StateSignal PDM_driverDisplayLEDs(8, true, 1, 0.0, -128, 127, 0.0, 0);

// Message: PDM_24 [0x112]
StateSignal PDM_counterMsg274(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fanLeftPWM(8, false, 1, 0.0, 0, 255, 0.0, 0);
StateSignal PDM_fanRightPWM(8, false, 1, 0.0, 0, 255, 0.0, 0);
StateSignal PDM_wpPWM(8, false, 1, 0.0, 0, 255, 0.0, 0);
StateSignal PDM_teensyTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: TCGPS_10 [0xa0]
StateSignal TCGPS_counterMsg160(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal TCGPS_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, 0);
StateSignal TCGPS_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, 0);

// Message: DD_10 [0xd2]
StateSignal DD_counterMsg210(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal DD_boardTemp(16, true, 10, 0.0, 0, 150, 0.0, 0);
StateSignal DD_teensyTemp(16, true, 10, 0.0, 0, 150, 0.0, 0);
StateSignal DD_requestDRS(16, true, 1, 0.0, 0, 5, 0.0, 0);

// Message: USER_12 [0x2c8]
StateSignal USER_driverMessageChar0(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar1(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar2(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar3(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar4(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar5(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar6(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar7(8, false, 1, 0.0, 0, 0, 0.0, 0);

// Message: USER_11 [0x2c7]
StateSignal USER_driverSignal(8, true, 1, 0.0, -128, 127, 0.0, 0);

// Message: ATCCF_15 [0x19f]
StateSignal ATCCF_counterMsg415(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_boardTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_teensyTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: USER_10 [0x2c6]
StateSignal USER_fanLeftOverride(8, true, 1, 0.0, -128, 127, 0.0, 0);
StateSignal USER_fanRightOverride(8, true, 1, 0.0, -128, 127, 0.0, 0);
StateSignal USER_wpOverride(8, true, 1, 0.0, -128, 127, 0.0, 0);
StateSignal USER_brakeLightOverride(8, true, 1, 0.0, -128, 127, 0.0, 0);

// Message: PDM_30 [0x118]
StateSignal PDM_driverMessageChar0(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar1(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar2(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar3(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar4(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar5(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar6(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal PDM_driverMessageChar7(8, false, 1, 0.0, 0, 0, 0.0, 0);

// Message: PDM_23 [0x111]
StateSignal PDM_counterMsg273(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_boardTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal PDM_brakelightVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_starterRelayVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_22 [0x110]
StateSignal PDM_counterMsg272(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_keepAliveVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_keepAliveVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_keepAliveVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_21 [0x10f]
StateSignal PDM_counterMsg271(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_dataVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_dataVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_dataVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_20 [0x10e]
StateSignal PDM_counterMsg270(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_mainVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_mainVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_mainVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_19 [0x10d]
StateSignal PDM_counterMsg269(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fuelVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fuelVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fuelVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_18 [0x10c]
StateSignal PDM_counterMsg268(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fuelCurrentAvg(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fuelCurrentMax(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fuelCurrentMin(16, true, 100, 0.0, -327, 327, 0.0, 0);

// Message: PDM_17 [0x10b]
StateSignal PDM_counterMsg267(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_wpVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_wpVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_wpVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_16 [0x10a]
StateSignal PDM_counterMsg266(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_wpCurrentAvg(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_wpCurrentMax(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_wpCurrentMin(16, true, 100, 0.0, -327, 327, 0.0, 0);

// Message: PDM_15 [0x109]
StateSignal PDM_counterMsg265(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fanLeftVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fanLeftVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fanLeftVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_14 [0x108]
StateSignal PDM_counterMsg264(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fanLeftCurrentAvg(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fanLeftCurrentMax(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fanLeftCurrentMin(16, true, 100, 0.0, -327, 327, 0.0, 0);

// Message: PDM_11 [0x105]
StateSignal PDM_counterMsg261(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_pdmVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_pdmVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_pdmVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_13 [0x107]
StateSignal PDM_counterMsg263(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fanRightVoltAvg(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fanRightVoltMax(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal PDM_fanRightVoltMin(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: PDM_12 [0x106]
StateSignal PDM_counterMsg262(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_fanRightCurrentAvg(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fanRightCurrentMax(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_fanRightCurrentMin(16, true, 100, 0.0, -327, 327, 0.0, 0);

// Message: PDM_10 [0x104]
StateSignal PDM_counterMsg260(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal PDM_dataLog(1, false, 1, 0.0, 0, 1, 0.0, 0);
StateSignal PDM_pdmCurrentAvg(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_pdmCurrentMax(16, true, 100, 0.0, -327, 327, 0.0, 0);
StateSignal PDM_pdmCurrentMin(16, true, 100, 0.0, -327, 327, 0.0, 0);

// Message: ATCCR_14 [0x1d0]
StateSignal ATCCR_counterMsg464(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCR_tireTempRRI(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_tireTempRRM(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_tireTempRRO(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCR_13 [0x1cf]
StateSignal ATCCR_counterMsg463(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCR_tireTempRLI(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_tireTempRLM(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_tireTempRLO(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCR_12 [0x1ce]
StateSignal ATCCR_counterMsg462(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCR_teensyTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_coolantTempRadInlet(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_coolantTempRadOutlet(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCR_11 [0x1cd]
StateSignal ATCCR_counterMsg461(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCR_boardTemp(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_rotorTempRL(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCR_rotorTempRR(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCR_10 [0x1cc]
StateSignal ATCCR_counterMsg460(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCR_suspensionTravelRL(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal ATCCR_suspensionTravelRR(16, true, 1000, 0.0, -32, 32, 0.0, 0);

// Message: ATCCF_14 [0x19e]
StateSignal ATCCF_counterMsg414(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_tireTempFRI(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_tireTempFRM(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_tireTempFRO(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCF_13 [0x19d]
StateSignal ATCCF_counterMsg413(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_tireTempFLI(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_tireTempFLM(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_tireTempFLO(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCF_12 [0x19c]
StateSignal ATCCF_counterMsg412(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_coolantTempRadMiddle(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_rotorTempFL(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_rotorTempFR(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCF_11 [0x19b]
StateSignal ATCCF_counterMsg411(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_brakePressureF(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_brakePressureR(16, true, 10, 0.0, -3276, 3276, 0.0, 0);
StateSignal ATCCF_steeringWheelAngle(16, true, 10, 0.0, -3276, 3276, 0.0, 0);

// Message: ATCCF_10 [0x19a]
StateSignal ATCCF_counterMsg410(4, false, 1, 0.0, 0, 15, 0.0, 0);
StateSignal ATCCF_brakeBias(16, true, 10, 0.0, 0, 100, 0.0, 0);
StateSignal ATCCF_suspensionTravelFL(16, true, 1000, 0.0, -32, 32, 0.0, 0);
StateSignal ATCCF_suspensionTravelFR(16, true, 1000, 0.0, -32, 32, 0.0, 0);




/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/


/*
 * Decode a CAN frame for the message TEST_1_BE
 * \param imsg A reference to the incoming CAN message frame
 */
void read_TEST_1_BE(CAN_message_t &imsg) {

	TEST_10bit1_BE.set_can_value((((imsg.buf[1] & 0b11000000)) | (imsg.buf[0] << 8) >> 6));
	TEST_bool1_BE.set_can_value((((imsg.buf[1] & 0b00000010)) >> 1));
	TEST_bool2_BE.set_can_value(((imsg.buf[1] & 0b00000001)));
	TEST_4bit2_BE.set_can_value((((imsg.buf[2] & 0b01111000)) >> 3));
	TEST_bool5_BE.set_can_value((((imsg.buf[2] & 0b00000010)) >> 1));
	TEST_4bit3_BE.set_can_value((((imsg.buf[3] & 0b11110000)) >> 4));
	TEST_bool4_BE.set_can_value((((imsg.buf[3] & 0b00000100)) >> 2));
	TEST_bool3_BE.set_can_value((((imsg.buf[4] & 0b00100000)) >> 5));
	TEST_7bit2_BE.set_can_value((((imsg.buf[5] & 0b11111100)) | ((imsg.buf[4] & 0b00000001) << 8) >> 2));
	TEST_7bit3_BE.set_can_value((((imsg.buf[7] & 0b11100000)) | ((imsg.buf[6] & 0b00001111) << 8) >> 5));

}

/*
 * Decode a CAN frame for the message TEST_2
 * \param imsg A reference to the incoming CAN message frame
 */
void read_TEST_2(CAN_message_t &imsg) {

	TEST_10bit2.set_can_value((imsg.buf[0]) | ((imsg.buf[1] & 0b00000011) << 8));
	TEST_10bit1.set_can_value((((imsg.buf[2] & 0b11111000)) | ((imsg.buf[3] & 0b00011111) << 8) >> 3));
	TEST_24bit1.set_can_value((imsg.buf[5]) | (imsg.buf[6] << 8) | (imsg.buf[7] << 16));

}

/*
 * Decode a CAN frame for the message TEST_1
 * \param imsg A reference to the incoming CAN message frame
 */
void read_TEST_1(CAN_message_t &imsg) {

	TEST_bool5.set_can_value(((imsg.buf[0] & 0b00000001)));
	TEST_bool4.set_can_value((((imsg.buf[0] & 0b00000010)) >> 1));
	TEST_bool3.set_can_value((((imsg.buf[0] & 0b00000100)) >> 2));
	TEST_bool2.set_can_value((((imsg.buf[0] & 0b00100000)) >> 5));
	TEST_bool1.set_can_value((((imsg.buf[0] & 0b10000000)) >> 7));
	TEST_4bit1.set_can_value((((imsg.buf[1] & 0b11000000)) | ((imsg.buf[2] & 0b00000011) << 8) >> 6));
	TEST_4bit2.set_can_value((((imsg.buf[2] & 0b11110000)) >> 4));
	TEST_4bit3.set_can_value(((imsg.buf[3] & 0b00001111)));
	TEST_7bit1.set_can_value((((imsg.buf[4] & 0b11111110)) >> 1));
	TEST_7bit2.set_can_value(((imsg.buf[5] & 0b01111111)));
	TEST_7bit3.set_can_value((((imsg.buf[6] & 0b11110000)) | ((imsg.buf[7] & 0b00000111) << 8) >> 4));

}

/*
 * Decode a CAN frame for the message PDM_09
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_09(CAN_message_t &imsg) {

	PDM_OBD_oilPressure.set_can_value(((imsg.buf[0] & 0b00000001)));
	PDM_OBD_oilTemp.set_can_value(((imsg.buf[1] & 0b00000001)));
	PDM_OBD_fuelPressure.set_can_value(((imsg.buf[2] & 0b00000001)));
	PDM_engineState.set_can_value((imsg.buf[7]));

}

/*
 * Decode a CAN frame for the message PDM_25
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_25(CAN_message_t &imsg) {

	PDM_counterMsg275.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_carMiles.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_engineHours.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_engineMinutes.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_31
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_31(CAN_message_t &imsg) {

	PDM_driverDisplayLEDs.set_can_value((imsg.buf[0]));

}

/*
 * Decode a CAN frame for the message PDM_24
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_24(CAN_message_t &imsg) {

	PDM_counterMsg274.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftPWM.set_can_value((imsg.buf[2]));
	PDM_fanRightPWM.set_can_value((imsg.buf[3]));
	PDM_wpPWM.set_can_value((imsg.buf[4]));
	PDM_teensyTemp.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message TCGPS_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_TCGPS_10(CAN_message_t &imsg) {

	TCGPS_counterMsg160.set_can_value(((imsg.buf[0] & 0b00001111)));
	TCGPS_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	TCGPS_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message DD_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_DD_10(CAN_message_t &imsg) {

	DD_counterMsg210.set_can_value(((imsg.buf[0] & 0b00001111)));
	DD_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	DD_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	DD_requestDRS.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message USER_12
 * \param imsg A reference to the incoming CAN message frame
 */
void read_USER_12(CAN_message_t &imsg) {

	USER_driverMessageChar0.set_can_value((imsg.buf[0]));
	USER_driverMessageChar1.set_can_value((imsg.buf[1]));
	USER_driverMessageChar2.set_can_value((imsg.buf[2]));
	USER_driverMessageChar3.set_can_value((imsg.buf[3]));
	USER_driverMessageChar4.set_can_value((imsg.buf[4]));
	USER_driverMessageChar5.set_can_value((imsg.buf[5]));
	USER_driverMessageChar6.set_can_value((imsg.buf[6]));
	USER_driverMessageChar7.set_can_value((imsg.buf[7]));

}

/*
 * Decode a CAN frame for the message USER_11
 * \param imsg A reference to the incoming CAN message frame
 */
void read_USER_11(CAN_message_t &imsg) {

	USER_driverSignal.set_can_value((imsg.buf[0]));

}

/*
 * Decode a CAN frame for the message ATCCF_15
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_15(CAN_message_t &imsg) {

	ATCCF_counterMsg415.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_teensyTemp.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));

}

/*
 * Decode a CAN frame for the message USER_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_USER_10(CAN_message_t &imsg) {

	USER_fanLeftOverride.set_can_value((imsg.buf[0]));
	USER_fanRightOverride.set_can_value((imsg.buf[1]));
	USER_wpOverride.set_can_value((imsg.buf[2]));
	USER_brakeLightOverride.set_can_value((imsg.buf[3]));

}

/*
 * Decode a CAN frame for the message PDM_30
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_30(CAN_message_t &imsg) {

	PDM_driverMessageChar0.set_can_value((imsg.buf[0]));
	PDM_driverMessageChar1.set_can_value((imsg.buf[1]));
	PDM_driverMessageChar2.set_can_value((imsg.buf[2]));
	PDM_driverMessageChar3.set_can_value((imsg.buf[3]));
	PDM_driverMessageChar4.set_can_value((imsg.buf[4]));
	PDM_driverMessageChar5.set_can_value((imsg.buf[5]));
	PDM_driverMessageChar6.set_can_value((imsg.buf[6]));
	PDM_driverMessageChar7.set_can_value((imsg.buf[7]));

}

/*
 * Decode a CAN frame for the message PDM_23
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_23(CAN_message_t &imsg) {

	PDM_counterMsg273.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_brakelightVoltAvg.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_starterRelayVoltAvg.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_22
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_22(CAN_message_t &imsg) {

	PDM_counterMsg272.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_keepAliveVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_keepAliveVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_keepAliveVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_21
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_21(CAN_message_t &imsg) {

	PDM_counterMsg271.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_dataVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_dataVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_dataVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_20
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_20(CAN_message_t &imsg) {

	PDM_counterMsg270.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_mainVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_mainVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_mainVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_19
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_19(CAN_message_t &imsg) {

	PDM_counterMsg269.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fuelVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fuelVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fuelVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_18
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_18(CAN_message_t &imsg) {

	PDM_counterMsg268.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fuelCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fuelCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fuelCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_17
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_17(CAN_message_t &imsg) {

	PDM_counterMsg267.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_wpVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_wpVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_wpVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_16
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_16(CAN_message_t &imsg) {

	PDM_counterMsg266.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_wpCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_wpCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_wpCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_15
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_15(CAN_message_t &imsg) {

	PDM_counterMsg265.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanLeftVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanLeftVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_14
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_14(CAN_message_t &imsg) {

	PDM_counterMsg264.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanLeftCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanLeftCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanLeftCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_11
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_11(CAN_message_t &imsg) {

	PDM_counterMsg261.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_pdmVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_pdmVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_pdmVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_13
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_13(CAN_message_t &imsg) {

	PDM_counterMsg263.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanRightVoltAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanRightVoltMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanRightVoltMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_12
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_12(CAN_message_t &imsg) {

	PDM_counterMsg262.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_fanRightCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_fanRightCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_fanRightCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message PDM_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_PDM_10(CAN_message_t &imsg) {

	PDM_counterMsg260.set_can_value(((imsg.buf[0] & 0b00001111)));
	PDM_dataLog.set_can_value((((imsg.buf[0] & 0b10000000)) >> 7));
	PDM_pdmCurrentAvg.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	PDM_pdmCurrentMax.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	PDM_pdmCurrentMin.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_14
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_14(CAN_message_t &imsg) {

	ATCCR_counterMsg464.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_tireTempRRI.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_tireTempRRM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_tireTempRRO.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_13
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_13(CAN_message_t &imsg) {

	ATCCR_counterMsg463.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_tireTempRLI.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_tireTempRLM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_tireTempRLO.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_12
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_12(CAN_message_t &imsg) {

	ATCCR_counterMsg462.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_teensyTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_coolantTempRadInlet.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_coolantTempRadOutlet.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_11
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_11(CAN_message_t &imsg) {

	ATCCR_counterMsg461.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_boardTemp.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCR_rotorTempRL.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_rotorTempRR.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCR_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCR_10(CAN_message_t &imsg) {

	ATCCR_counterMsg460.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCR_suspensionTravelRL.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCR_suspensionTravelRR.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_14
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_14(CAN_message_t &imsg) {

	ATCCF_counterMsg414.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_tireTempFRI.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_tireTempFRM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_tireTempFRO.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_13
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_13(CAN_message_t &imsg) {

	ATCCF_counterMsg413.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_tireTempFLI.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_tireTempFLM.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_tireTempFLO.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_12
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_12(CAN_message_t &imsg) {

	ATCCF_counterMsg412.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_coolantTempRadMiddle.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_rotorTempFL.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_rotorTempFR.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_11
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_11(CAN_message_t &imsg) {

	ATCCF_counterMsg411.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_brakePressureF.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_brakePressureR.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_steeringWheelAngle.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}

/*
 * Decode a CAN frame for the message ATCCF_10
 * \param imsg A reference to the incoming CAN message frame
 */
void read_ATCCF_10(CAN_message_t &imsg) {

	ATCCF_counterMsg410.set_can_value(((imsg.buf[0] & 0b00001111)));
	ATCCF_brakeBias.set_can_value((imsg.buf[2]) | (imsg.buf[3] << 8));
	ATCCF_suspensionTravelFL.set_can_value((imsg.buf[4]) | (imsg.buf[5] << 8));
	ATCCF_suspensionTravelFR.set_can_value((imsg.buf[6]) | (imsg.buf[7] << 8));

}



#endif
