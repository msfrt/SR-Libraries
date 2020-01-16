// ino file for testing PWMControl library :-)

#include "PWMControl.h"
#include "StateCAN.h"

StateSignal test_row_sig(16, false, 1, 0, 0, 0, 100);
StateSignal test_col_sig(16, false, 1, 0, 0, 0, -12);
StateSignal test_override(16, false, 1, 0, 0, 0, -1, 1500);

const int num_rows = 12;
const int num_cols = 14;

// PWMDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
//           int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq)
PWMDevice test_device(5, num_rows, num_cols, 10, 10000, test_row_sig, test_col_sig, test_override, 0, 255, 2500, 10, 40, 420);

LEDBlink onboard_led(13, 10);
EasyTimer print_timer(10);
EasyTimer read_timer(1);

int engine_temp_row = 0; // pot value
int battery_mv10_column = 0; // pot value

int engine_mode = 2; //engine state
unsigned long engine_mode_timer = 0;
int pwm_override = -1;


void setup()
{
  Serial.begin(115200);

  int fan_table[num_rows][num_cols] =
  {
   {    0, 80000, 90000, 100000, 105000, 110000, 119000, 120000, 130000, 137000, 138000, 139000, 142000, 145000},
   {    0,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0},
   {  700,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0},
   {  850,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,     25},
   {  855,    15,    15,     15,     15,     15,     15,     15,     15,     15,     30,     30,     30,     30},
   {  920,    15,    15,     15,     15,     15,     15,     15,     15,     15,     50,     50,     50,     50},
   {  921,    15,    15,     15,     15,     25,     25,     25,     25,     25,     65,     65,     65,     65},
   {  950,    75,    75,     75,     75,     75,     75,     75,     75,     75,     75,     75,     75,     75},
   {  951,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
   { 1000,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
   { 1001,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
   { 1500,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
  };
  int *fan_table_ptr = fan_table[0];
  test_device.fill_table(fan_table_ptr);

  test_row_sig = 95.0;
  test_col_sig = 13.5;
  test_override = -1;

  pinMode(23, INPUT); //pot1
  pinMode(22, INPUT); //pot2

  pinMode(18, INPUT_PULLUP); //buddon
  pinMode(16, INPUT_PULLUP); //buddon 2
}

void loop()
{
  onboard_led.run();//led blink


  if(test_device.set_pwm(engine_mode)){
    Serial.println();
    Serial.print("Target: "); Serial.println(test_device.target());
    Serial.print("Actual: "); Serial.println(test_device.actual());
    Serial.print("  Freq: "); Serial.println(test_device.freq());
    Serial.print("   ENG: "); Serial.println(engine_mode);
  }

  if (millis() > 10000 && millis() < 10020){
    test_override = 69;
  }

  test_override.timeout_check();


}
