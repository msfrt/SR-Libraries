%By: Nicholas Kopec 2020
%this function turns data returned from darab2matlab() and converts it to a
%timeseries that can more easily be used by sims

function [data] = processData_SR19(chNames, chData)
%PROCESSDATA Summary of this function goes here
%   Detailed explanation goes here

data.xtime = table2array(chData(:,find(string(chNames) == "xtime")));
data.tSample = data.xtime(2,1) - data.xtime(1,1);
data.tStart = data.xtime(1,1);
data.tEnd = data.xtime(end,1);

%% ATCCF

data.ATCCF.boardTemp = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_boardTemp"))), data.xtime);
data.ATCCF.brakePressureF = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_brakePressureF"))), data.xtime);
data.ATCCF.brakePressureR = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_brakePressureR"))), data.xtime);
data.ATCCF.coolantTempRadMiddle = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_coolantTempRadMiddle"))), data.xtime);
data.ATCCF.rotorTempFL = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_rotorTempFL"))), data.xtime);
data.ATCCF.rotorTempFR = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_rotorTempFR"))), data.xtime);
data.ATCCF.steeringWheelAngle = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_steeringWheelAngle_"))), data.xtime);
data.ATCCF.suspensionTravelFL = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_suspensionTravelFL"))), data.xtime);
data.ATCCF.suspensionTravelFR = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_suspensionTravelFR"))), data.xtime);
data.ATCCF.teensyTemp = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_teensyTemp"))), data.xtime);
data.ATCCF.tireTempFLI = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFLI"))), data.xtime);
data.ATCCF.tireTempFLM = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFLM"))), data.xtime);
data.ATCCF.tireTempFLO = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFLO"))), data.xtime);
data.ATCCF.tireTempFRI = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFRI"))), data.xtime);
data.ATCCF.tireTempFRM = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFRM"))), data.xtime);
data.ATCCF.tireTempFRO = timeseries( table2array(chData(:,find(string(chNames) == "ATCCF_tireTempFRO"))), data.xtime);
data.ATCCF.boardTemp = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_boardTemp"))), data.xtime);
data.ATCCF.coolantTempRadInlet = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_coolantTempRadInlet"))), data.xtime);
data.ATCCF.coolantTempRadOutlet = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_coolantTempRadOutlet"))), data.xtime);
data.ATCCF.rotorTempRL = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_rotorTempRL"))), data.xtime);
data.ATCCF.rotorTempRR = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_rotorTempRR"))), data.xtime);
data.ATCCF.suspensionTravelRL = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_suspensionTravelRL"))), data.xtime);
data.ATCCF.suspensionTravelRR = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_suspensionTravelRR"))), data.xtime);
data.ATCCF.teensyTemp = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_teensyTemp"))), data.xtime);
data.ATCCF.tireTempRLI = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRLI"))), data.xtime);
data.ATCCF.tireTempRLM = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRLM"))), data.xtime);
data.ATCCF.tireTempRLO = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRLO"))), data.xtime);
data.ATCCF.tireTempRRI = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRRI"))), data.xtime);
data.ATCCF.tireTempRRM = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRRM"))), data.xtime);
data.ATCCF.tireTempRRO = timeseries( table2array(chData(:,find(string(chNames) == "ATCCR_tireTempRRO"))), data.xtime);

%% C50

data.C50.batteryVoltage = timeseries( table2array(chData(:,find(string(chNames) == "C50_batteryVoltage"))), data.xtime);
data.C50.ecuCoreTemp = timeseries( table2array(chData(:,find(string(chNames) == "C50_ecuCoreTemp"))), data.xtime);
data.C50.lapTrigger = timeseries( table2array(chData(:,find(string(chNames) == "C50_lapTrigger"))), data.xtime);
data.C50.markSwitch = timeseries( table2array(chData(:,find(string(chNames) == "C50_markSwitch"))), data.xtime);
data.C50.TCSet = timeseries( table2array(chData(:,find(string(chNames) == "C50_TCSet"))), data.xtime);

%% GPS

data.GPS.day = timeseries( table2array(chData(:,find(string(chNames) == "gps_day"))), data.xtime);
data.GPS.direction = timeseries( table2array(chData(:,find(string(chNames) == "gps_direction"))), data.xtime);
data.GPS.dist = timeseries( table2array(chData(:,find(string(chNames) == "gps_dist"))), data.xtime);
data.GPS.elv = timeseries( table2array(chData(:,find(string(chNames) == "gps_elv"))), data.xtime);
data.GPS.fix = timeseries( table2array(chData(:,find(string(chNames) == "gps_fix"))), data.xtime);
data.GPS.hour = timeseries( table2array(chData(:,find(string(chNames) == "gps_hour"))), data.xtime);
data.GPS.lat = timeseries( table2array(chData(:,find(string(chNames) == "gps_lat"))), data.xtime);
data.GPS.long = timeseries( table2array(chData(:,find(string(chNames) == "gps_long"))), data.xtime);
data.GPS.min = timeseries( table2array(chData(:,find(string(chNames) == "gps_min"))), data.xtime);
data.GPS.mon = timeseries( table2array(chData(:,find(string(chNames) == "gps_mon"))), data.xtime);
data.GPS.sec = timeseries( table2array(chData(:,find(string(chNames) == "gps_sec"))), data.xtime);
data.GPS.sig = timeseries( table2array(chData(:,find(string(chNames) == "gps_sig"))), data.xtime);
data.GPS.speed_km = timeseries( table2array(chData(:,find(string(chNames) == "gps_speed_km"))), data.xtime);
data.GPS.year = timeseries( table2array(chData(:,find(string(chNames) == "gps_year"))), data.xtime);

%% M400

data.M400.auxOut1DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut1DutyCycle_"))), data.xtime);
data.M400.auxOut2DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut2DutyCycle_"))), data.xtime);
data.M400.auxOut3DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut3DutyCycle_"))), data.xtime);
data.M400.auxOut4DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut4DutyCycle_"))), data.xtime);
data.M400.auxOut5DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut5DutyCycle_"))), data.xtime);
data.M400.auxOut6DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut6DutyCycle_"))), data.xtime);
data.M400.auxOut7DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut7DutyCycle_"))), data.xtime);
data.M400.auxOut8DutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_auxOut8DutyCycle_"))), data.xtime);
data.M400.batteryVoltage = timeseries( table2array(chData(:,find(string(chNames) == "M400_batteryVoltage"))), data.xtime);
data.M400.driveSpeed = timeseries( table2array(chData(:,find(string(chNames) == "M400_driveSpeed"))), data.xtime);
data.M400.driveSpeedLeft = timeseries( table2array(chData(:,find(string(chNames) == "M400_driveSpeedLeft"))), data.xtime);
data.M400.driveSpeedRight = timeseries( table2array(chData(:,find(string(chNames) == "M400_driveSpeedRight"))), data.xtime);
data.M400.ecuCpuUsage = timeseries( table2array(chData(:,find(string(chNames) == "M400_ecuCpuUsage_"))), data.xtime);
data.M400.ecuInternalTemp = timeseries( table2array(chData(:,find(string(chNames) == "M400_ecuInternalTemp"))), data.xtime);
data.M400.engineTemp = timeseries( table2array(chData(:,find(string(chNames) == "M400_engineTemp"))), data.xtime);
data.M400.exhaustGasTemp1 = timeseries( table2array(chData(:,find(string(chNames) == "M400_exhaustGasTemp1"))), data.xtime);
data.M400.exhaustGasTemp2 = timeseries( table2array(chData(:,find(string(chNames) == "M400_exhaustGasTemp2"))), data.xtime);
data.M400.exhaustGasTemp3 = timeseries( table2array(chData(:,find(string(chNames) == "M400_exhaustGasTemp3"))), data.xtime);
data.M400.exhaustGasTemp4 = timeseries( table2array(chData(:,find(string(chNames) == "M400_exhaustGasTemp4"))), data.xtime);
data.M400.fuel1IndivTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuel1IndivTrim_"))), data.xtime);
data.M400.fuel2IndivTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuel2IndivTrim_"))), data.xtime);
data.M400.fuel3IndivTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuel3IndivTrim_"))), data.xtime);
data.M400.fuel4IndivTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuel4IndivTrim_"))), data.xtime);
data.M400.fuelActualPulseW = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelActualPulseW"))), data.xtime);
data.M400.fuelAtComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelAtComp_"))), data.xtime);
data.M400.fuelComp1 = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelComp1_"))), data.xtime);
data.M400.fuelCutLevelTotal = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelCutLevelTotal_"))), data.xtime);
data.M400.fuelEtComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelEtComp_"))), data.xtime);
data.M400.fuelFpComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelFpComp_"))), data.xtime);
data.M400.fuelFtComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelFtComp_"))), data.xtime);
data.M400.fuelInjDutyCycle = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelInjDutyCycle_"))), data.xtime);
data.M400.fuelLambdaComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelLambdaComp_"))), data.xtime);
data.M400.fuelOverallTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelOverallTrim_"))), data.xtime);
data.M400.fuelPressure = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelPressure"))), data.xtime);
data.M400.fuelStartingComp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelStartingComp_"))), data.xtime);
data.M400.fuelTemp = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelTemp"))), data.xtime);
data.M400.fuelUsed = timeseries( table2array(chData(:,find(string(chNames) == "M400_fuelUsed"))), data.xtime);
data.M400.gear = timeseries( table2array(chData(:,find(string(chNames) == "M400_gear"))), data.xtime);
data.M400.gearDet = timeseries( table2array(chData(:,find(string(chNames) == "M400_gearDet"))), data.xtime);
data.M400.gearSensorVoltage = timeseries( table2array(chData(:,find(string(chNames) == "M400_gearSensorVoltage"))), data.xtime);
data.M400.groundSpeed = timeseries( table2array(chData(:,find(string(chNames) == "M400_groundSpeed"))), data.xtime);
data.M400.groundSpeedLeft = timeseries( table2array(chData(:,find(string(chNames) == "M400_groundSpeedLeft"))), data.xtime);
data.M400.groundSpeedRight = timeseries( table2array(chData(:,find(string(chNames) == "M400_groundSpeedRight"))), data.xtime);
data.M400.ign1Advance = timeseries( table2array(chData(:,find(string(chNames) == "M400_ign1Advance_"))), data.xtime);
data.M400.ign2Advance = timeseries( table2array(chData(:,find(string(chNames) == "M400_ign2Advance_"))), data.xtime);
data.M400.ign3Advance = timeseries( table2array(chData(:,find(string(chNames) == "M400_ign3Advance_"))), data.xtime);
data.M400.ign4Advance = timeseries( table2array(chData(:,find(string(chNames) == "M400_ign4Advance_"))), data.xtime);
data.M400.ignBaseAdvance = timeseries( table2array(chData(:,find(string(chNames) == "M400_ignBaseAdvance_"))), data.xtime);
data.M400.ignCutLevelTotal = timeseries( table2array(chData(:,find(string(chNames) == "M400_ignCutLevelTotal_"))), data.xtime);
data.M400.ignOverallTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_ignOverallTrim_"))), data.xtime);
data.M400.inletAirTemp = timeseries( table2array(chData(:,find(string(chNames) == "M400_inletAirTemp"))), data.xtime);
data.M400.la1AimValue = timeseries( table2array(chData(:,find(string(chNames) == "M400_la1AimValue"))), data.xtime);
data.M400.la1LongTermTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_la1LongTermTrim"))), data.xtime);
data.M400.la1ShortTermTrim = timeseries( table2array(chData(:,find(string(chNames) == "M400_la1ShortTermTrim"))), data.xtime);
data.M400.lambda1 = timeseries( table2array(chData(:,find(string(chNames) == "M400_lambda1"))), data.xtime);
data.M400.manifoldPressure = timeseries( table2array(chData(:,find(string(chNames) == "M400_manifoldPressure"))), data.xtime);
data.M400.oilPressure = timeseries( table2array(chData(:,find(string(chNames) == "M400_oilPressure"))), data.xtime);
data.M400.oilTemp = timeseries( table2array(chData(:,find(string(chNames) == "M400_oilTemp"))), data.xtime);
data.M400.rpm = timeseries( table2array(chData(:,find(string(chNames) == "M400_rpm"))), data.xtime);
data.M400.tcIgnretard = timeseries( table2array(chData(:,find(string(chNames) == "M400_tcIgnretard_"))), data.xtime);
data.M400.tcLaunchAimRPM = timeseries( table2array(chData(:,find(string(chNames) == "M400_tcLaunchAimRPM"))), data.xtime);
data.M400.tcPowerReduction = timeseries( table2array(chData(:,find(string(chNames) == "M400_tcPowerReduction_"))), data.xtime);
data.M400.tcSlipAimError = timeseries( table2array(chData(:,find(string(chNames) == "M400_tcSlipAimError"))), data.xtime);
data.M400.tcSlipAimValue = timeseries( table2array(chData(:,find(string(chNames) == "M400_tcSlipAimValue"))), data.xtime);
data.M400.throttlePosition = timeseries( table2array(chData(:,find(string(chNames) == "M400_throttlePosition"))), data.xtime);
data.M400.wheelSlip = timeseries( table2array(chData(:,find(string(chNames) == "M400_wheelSlip_"))), data.xtime);

%% MM5

data.MM5.Ax = timeseries( table2array(chData(:,find(string(chNames) == "MM5_Ax"))), data.xtime);
data.MM5.Ay = timeseries( table2array(chData(:,find(string(chNames) == "MM5_Ay"))), data.xtime);
data.MM5.Az = timeseries( table2array(chData(:,find(string(chNames) == "MM5_Az"))), data.xtime);
data.MM5.rollRate = timeseries( table2array(chData(:,find(string(chNames) == "MM5_rollRate"))), data.xtime);
data.MM5.yawRate = timeseries( table2array(chData(:,find(string(chNames) == "MM5_yawRate"))), data.xtime);

%%
end

