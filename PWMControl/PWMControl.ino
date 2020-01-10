// ino file for testing PWMControl library :-)

#include "PWMControl.h"

const int num_rows = 12;
const int num_cols = 14;

// PWMDevice(int output_pin, int table_rows, int table_columns, int pwm_min, int pwm_max, int soft_start_dur,
//           int pwm_control_freq, int pwm_normal_freq, int pwm_soft_start_freq)
PWMDevice test_device(5, num_rows, num_cols, 0, 255, 7500, 10, 40, 420);

LEDBlink onboard_led(13, 10);
EasyTimer print_timer(10);
EasyTimer read_timer(1);

int engine_temp_row = 0; // pot value
int battery_mv10_column = 0; // pot value

int engine_mode = 0; //engine state
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

  pinMode(23, INPUT); //pot1
  pinMode(22, INPUT); //pot2

  pinMode(18, INPUT_PULLUP); //buddon
  pinMode(16, INPUT_PULLUP); //buddon 2
}

void loop()
{
  onboard_led.run();//led blink


  if (!digitalRead(16)){
    pwm_override = 100;
  } else {
    pwm_override = -1;
  }


  // read the engine button, and go through engine state cycle
  if (!digitalRead(18)){
    engine_mode_timer = millis();
  }
  if (millis() - engine_mode_timer > 15000){
    engine_mode = 0; // off
  } else if (millis() - engine_mode_timer > 5000) {
    engine_mode = 3; // cooldown
  } else if (millis() - engine_mode_timer > 100){
    engine_mode = 2; // running
  } else {
    engine_mode = 1; //cranking
  }


  //read dem bois
  if (read_timer.isup()){
    engine_temp_row = map(analogRead(23), 0, 1023, 800, 1000);
    battery_mv10_column = map(analogRead(22), 0, 1023, 80000, 145000);
  }

  if (print_timer.isup()){
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.print(" Engine temp: "); Serial.println(engine_temp_row);
    Serial.print("Battery volt: "); Serial.println(battery_mv10_column);

    switch (engine_mode) {
      case 0:
        Serial.println("      Engine: OFF");
        break;
      case 1:
        Serial.println("      Engine: CRANKING");
        break;
      case 2:
        Serial.println("      Engine: ON");
        break;
      case 3:
        Serial.println("      Engine: COOLDOWN");
        break;
    }
  }

  test_device.set_pwm(engine_temp_row, battery_mv10_column, engine_mode, pwm_override);
}
