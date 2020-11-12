/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <StateCAN.h>

// Message: TCGPS_11 [0xa1]
StateSignal TCGPS_laptrigger(8, true, 1, 0, None, None, 0, 0);

// Message: MM5_02 [0x17c]
StateSignal MM5_Az(16, false, -7849, -4.1745795, None, None, 0, 0);

// Message: MM5_01 [0x178]
StateSignal MM5_rollRate(16, false, -200, 163.9, None, None, 0, 0);
StateSignal MM5_Ax(16, false, -7849, 4.1745795, None, None, 0, 0);

// Message: MM5_00 [0x174]
StateSignal MM5_yawRate(16, false, 200, -163.9, None, None, 0, 0);
StateSignal MM5_Ay(16, false, -7849, 4.1745795, None, None, 0, 0);

// Message: M400_dataSet2 [0x65]
StateSignal M400_oilTemp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_la1LongTermTrim(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignEtComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignBaseAdvance(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ign3Advance(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelUsed(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_fuelPressure(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelInjDutyCycle(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelEtComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelAtComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuel3IndivTrim(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_exhaustGasTemp4(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_exhaustGasTemp1(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_ecuCpuUsage(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_auxOut7DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_auxOut4DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_auxOut1DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_manifoldPressure(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignMapComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignComp1(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ign4Advance(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ign1Advance(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelStartingComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelLambdaComp(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_fuelFpComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelComp1(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuel4IndivTrim(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_fuel1IndivTrim(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_exhaustGasTemp2(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_ecuInternalTemp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_auxOut8DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_auxOut5DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_auxOut2DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_oilPressure(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_inletAirTemp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignComp2(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ignAtComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_ign2Advance(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelTemp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelMapComp(16, true, 10, 0, None, None, 0, 0);
StateSignal M400_fuelFtComp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelComp2(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_fuelActualPulseW(16, true, 500, 0, -65.536, 65.534, 0, 0);
StateSignal M400_fuel2IndivTrim(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_exhaustGasTemp3(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_engineTemp(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_batteryVoltage(16, true, 100, 0, -327.68, 327.67, 0, 0);
StateSignal M400_auxOut6DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_auxOut3DutyCycle(16, true, 1, 0, -32768, 32767, 0, 0);

// Message: M400_dataSet1 [0x64]
StateSignal M400_la1AimValue(16, true, 1000, 0, -32.768, 32.767, 0, 0);
StateSignal M400_fuelCutLevelTotal(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_gear(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_ignCutLevelTotal(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_tcSlipAimError(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_tcIgnretard(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_groundSpeed(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_driveSpeed(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_la1ShortTermTrim(16, true, 100, 0, -327.68, 327.67, 0, 0);
StateSignal M400_fuelOverallTrim(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_gearDet(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_rpm(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_tcSlipAimValue(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_tcLaunchAimRPM(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_groundSpeedLeft(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_driveSpeedLeft(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_lambda1(16, true, 1000, 0, -32.768, 32.767, 0, 0);
StateSignal M400_ignOverallTrim(16, true, 1, 0, -32768, 32767, 0, 0);
StateSignal M400_gearSensorVoltage(16, true, 1000, 0, -32.768, 32.767, 0, 0);
StateSignal M400_throttlePosition(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_wheelSlip(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_tcPowerReduction(16, true, 10, 0, 0, 75, 0, 0);
StateSignal M400_groundSpeedRight(16, true, 10, 0, -3276.8, 3276.7, 0, 0);
StateSignal M400_driveSpeedRight(16, true, 10, 0, -3276.8, 3276.7, 0, 0);

#endif
