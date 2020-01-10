# PWM Control Library

Alright, this PWM control library makes it super easy to control the fans and water pump on the car via some crazy customizable lookup tables. It's jam-packed full of goodies like soft-start control, pwm overrides, cranking shutoff, and cooldown functionality. That's lit, brother!

## Define a PWMDevice
This is probably the hardest part about using this library, but I've got your back, don't worry. Just follow my instructions and you'll be set.

#### Step 1 - defining your table:

The first step is to define your lookup table as a 2D-array. This will contain all of your output percentages. Yes, I said percentages. Aside from the first value in every row and the top column (i.e. the X and Y axis), everything in your table should be an __integer between 0 and 100__. A proper lookup table definition looks like this:

```cpp
const int num_rows = 12;
const int num_cols = 14;

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
```

There are a few things to notice here. First, look at how I defined the number of rows and the number of columns as a `const int` before defining the table. Not only did I use those in the table definition itself, but they will be __crucial__ when defining our `PWMDevice`. Second, notice how the rows and columns are some funky units. In this example, rows are Cº × 10 and columns are battery mV × 10. Your row and column values can be whatever the frick you want, but they need to be of the type `int`!

---
#### Step 2 - defining your PWMDevice:

This is where is gets a little funky, and it might be easy to mess up. We now need to define our PWMDevice, as well as initialize most of the variables within it. Here's an example of doing so:

```cpp
int teensy_pwm_pin = 5;
int minimum_pwm = 0;
int maximum_pwm = 255;
int soft_start_duration = 5000;
int device_update_frequency = 10;
int pwm_frequency_normal = 40;
int pwm_frequency_soft_start = 420;
PWMDevice test_device(teensy_pwm_pin, num_rows, num_cols, minimum_pwm, maximum_pwm, soft_start_duration, device_update_frequency, pwm_frequency_normal, pwm_frequency_soft_start);
```

Yeah, so there's a lot to unpack there. Here's a little more info on each parameter.

* _`teensy_pwm_pin`_ - the pin on the microcontroller that will output the PWM
* _`num_rows`_ & _`num_cols`_ - remember these from above? Yeah, these are the same as what you should've constructed the table with.
* _`minimum_pwm`_ - this is the minimum PWM that the device will run. Essentially, when the output percentage is 1%, this is the PWM duty cycle that will be written
* _`maximum_pwm`_ - similarly to `minimum_pwm`, this is the output PWM that will be written at 100%. Normally, the maximum duty cycle that you can write on an Arduino-type microcontroller is 255 (the range is 0-255), however, on a Teensy, you can change this via the `analogWriteResolution()` function. If you decide to update the write resolution, you must also remember to calculate the maximum output PWM duty cycle, and use it as your `maximum_pwm` variable.
* _`soft_start_duration`_ - this is the duration in milliseconds for the soft-start mode. Soft start changes the write frequency of the PWM pin for a specified duration after the device turns on.
* _`device_update_frequency`_ - is the frequency at which the device should be updated. Broadly speaking, this is the frequency at which the PWM value should be changed. It should be an integer value ≥ 1.
* _`pwm_frequency_normal`_ - the frequency of PWM under normal operation.
* _`pwm_frequency_soft_start`_ - the frequency of PWM output during soft start. This is typically much higher than the normal frequency, but hey, if you want to set it lower, you do you.

#### Step 3 - Populating your PWMDevice table:

So if you noticed above, we never linked our `PWMDevice` to our lookup table. This is something that has to be done during runtime, because of the way I manipulate the table into a faster `LookupTable` object. Also, the way that you move 2d arrays around in C++ is kinda wack.

This is what you need to do:

```cpp
int *fan_table_ptr = fan_table[0]; // create the pointer
test_device.fill_table(fan_table_ptr); // pass the table ptr into the test_device
```

Essentially, we're creating a pointer to an int, which is the first row of the table. That's fine, because the compiler makes the array sequentially, and the `test_device` already knows the size. It's important that you denote the first row of the table by indexing `[0]`. If you don't do that, the function will improperly copy the contents of the table, and your code may crash.

You should write those lines of code in the `setup()`.

#### Step 4 - Use the PWMDevice

You've done all of the grunt work so far, and now it's time to let the `PWMDevice` do all of the rest. In the `loop()`, you should continuously run the following:

```cpp
test_device.set_pwm(row_value, column_value, engine_mode, pwm_override)
```

* _`row_value`_ - what row value to look for in the `LookupTable`
* _`column_value`_ - what column value to look for in the `LookupTable`
* _`engine_mode`_ - the mode of the engine, look below for details.
* _`pwm_override`_ - a percentage override. This will ignore all of the PWM control stuff and write that percent to the output pin (unless the engine is cranking). To enable the override, pass in any integer __0-100__. To disable the override and resume normal operation, pass in __-1__.

## Useful Informations

#### Engine Mode Parameter

There are 4 engine modes that this library accepts. They are integers 0-3, and here are their meanings:

| Mode  | Engine   | Description |
| ----- | -------- | ----------- |
| 0     | OFF      | `PWMDevice` will not run unless overridden |
| 1     | CRANKING | `PWMDevice` will not run |
| 2     | RUNNING  | `PWMDevice` functions as normal
| 3     | COOLDOWN | `PWMDevice` target PWM set to 0, and actual PWM will decrease until it reaches 0 or engine mode returns to OFF|

#### LookupTable Usage

This library makes extensive use of the LookupTable library. If you do not have that installed, you should do that. It is also located in the [SR-Libraries repository](..).

If you are interested in reading the LookupTable documentation and how values are mapped in-between defined values, you can do so [here](../LookupTable/).
