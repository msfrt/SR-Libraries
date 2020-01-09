#include "PWMControl.h"

const int num_rows = 12;
const int num_cols = 14;

// PwmDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
// int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq)
PwmDevice test_device(1, num_rows, num_cols, 0, 255, 2500, 10, 40, 100);

LEDBlink onboard_led(13, 10);
EasyTimer print_timer(1);

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
}

void loop()
{
  onboard_led.run();

  if (print_timer.isup()){
    test_device.table().print();
  }
}
