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
StateSignal USER_driverMessageChar0(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar1(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar2(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar3(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar4(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar5(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar6(8, false, 1, 0.0, 0, 0, 0.0, 0);
StateSignal USER_driverMessageChar7(8, false, 1, 0.0, 0, 0, 0.0, 0);

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
