#include "LookupTable.h"

const int num_rows = 12;
const int num_columns = 14;
int right_fan_array[num_rows][num_columns] =
{
  {    0, 80000, 90000, 100000, 105000, 110000, 119000, 120000, 130000, 137000, 138000, 139000, 142000, 145000},
  {    0,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0},
  {  700,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0},
  {  850,     0,     0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,     25},
  {  851,    15,    15,     15,     15,     15,     15,     15,     15,     15,     30,     30,     30,     30},
  {  920,    15,    15,     15,     15,     15,     15,     15,     15,     15,     50,     50,     50,     50},
  {  921,    15,    15,     15,     15,     25,     25,     25,     25,     25,     65,     65,     65,     65},
  {  950,    75,    75,     75,     75,     75,     75,     75,     75,     75,     75,     75,     75,     75},
  {  951,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
  { 1000,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
  { 1001,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100},
  { 1500,   100,   100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100,    100}
};
LookupTable fanr_table(num_rows, num_columns);
int *right_fan_array_row_zero_ptr = right_fan_array[0];


void setup() {


  Serial.begin(9600);
  delay(2000);
  Serial.println("test");


  fanr_table.fill_table(right_fan_array_row_zero_ptr);


}

void loop() {




  Serial.println(fanr_table.find(930, 119000));
  Serial.println(fanr_table.find(0, 110000));
  Serial.println(fanr_table.find(0, 0));
  Serial.println(fanr_table.find(1000, 500));
  Serial.println();

  delay(2000);


}
