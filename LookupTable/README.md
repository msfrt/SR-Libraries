# LookupTable Library

This library makes creating and using lookup tables a breeze. This library also proves faster lookup for tables. Using an array of arrays (2d array) is actually pretty resource intensive. LookupTable creates a single array that acts as a 2d array, so lookup is less processor intensive and memory management is better. However, that's behind the scenes, so you need not worry!

## Usage

### Declaration.

Unfortunately, you must still define an old and slow 2d array that has the contents of your lookup table. No worries, we'll fill our faster lookup table with these values in a minute. An example of a 2d array lookup table is seen below:

```cpp
//    rows: temp in degrees celcius * 10
// columns: battery voltage in mV * 10
const int right_fan_num_rows = 12;
const int right_fan_num_cols = 14;
int right_fan_array[right_fan_num_rows][right_fan_num_cols] =
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
```
You can define this array as a global variable, but understand that it will take up a bit of memory. A better solution would be to define this array in the `setup()` function, or similar, so that the array is deleted when it falls out of scope.

Okay, now that you've made a 2d array, we need to create a LookupTable object. You need to have the same number of rows and columns as your 2d-array as defined above.

```cpp
// we need to tell the LookupTable object how big it will be!
LookupTable fanr_table(right_fan_num_rows, right_fan_num_cols);
```

### Initialization

Okay, technically our LookupTable is already initialized, however it doesn't have the values that we want to use. We need to fill our LookupTable with the 2d array that was created earlier. C++ is kinda stupid in that you can't pass an array into a function. It gets even worse when we try to pass in a 2d array. However, since our LookupTable object already has the size information, we're almost there. We simply need to feed it a pointer to the first row of the 2d array, which is technically a pointer to an array of ints. The `fill_table()` function does the rest!

```cpp
// create a pointer to the first row of data in the table
int *right_fan_array_row_zero_ptr = right_fan_array[0];

// copy the contents of the array into the lookup table
fanr_table.fill_table(right_fan_array_row_zero_ptr);
```
### Usage

#### `LookupTable::find(int row_value, int column_value)`
The `find()` function is the bread and butter of this library. Given two inputs for the desired row value and desired column value, `find` finds the associated output value if the row value and column value are present. If the row value and column value are _not_ present, the function automatically maps the input row and column to an output that is in between already defined outputs in the table. The "mesh" that is created in-between defined values is planar.

#### `LookupTable::fill_table(int **2d_array)`
Usage for this member function is described in the initialization section.

#### `LookupTable::print()`
This is useful for debugging purposes only. It prints the contents of your table to the serial output. Be sure that you have already initialized the
Serial stream before calling this function.

#### `LookupTable::rows()`
Getter - this returns an integer that is the number of rows in the LookupTable.

#### `LookupTable::columns()`
Getter - this returns an integer that is the number of columns in the LookupTable.

#### `LookupTable::at_index(int row_index, int column_index)`
Getter - this returns the value in a table at a certain index. You shouldn't really every have to use this function, but is here if desired. You should probably be using `find()`.

#### `LookupTable::set_index(int row_index, int column_index, int value)`
Setter - given a table index, this functions updates the value at that index.

### Declaration and Initialization

```cpp
#include "LookupTable.h"

const int num_rows = 12; // define row count
const int num_columns = 14; // define column count
LookupTable fanr_table(num_rows, num_columns); // create a LookupTable with the number of rows and columns
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
int *right_fan_array_row_zero_ptr = right_fan_array[0]; // create a pointer to the first row

void setup(){
  fanr_table.fill_table(right_fan_array_row_zero_ptr); // fill the LookupTable object table
}
```
