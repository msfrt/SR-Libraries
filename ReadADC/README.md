# ReadADC Library

The ReadADC library allows you to easily sample sensors that are read through an external analog-to-digital converter.

## Usage

### Declarations
Before the `setup()` and `loop()` functions, you should declare each sensor. You will do this using the one and only constructor for this class, with formatting as follows:

```cpp
ADCSensor my_sensor(int chip_select, int adc_channel, int sensor_zero_mV, int mV_per_sensor_unit);
```

* __chip_select__ is the teensy pin that the ADC is on
* __adc_channel__ is the channel of the ADC that the sensor is on (it should be between 0-7 on an 8-channel ADC)
* __sensor_zero_mV__ this is the zero-voltage of the sensor in milliVolts
* __mV_per_sensor_unit__ represents the voltage per sensor unit. For example, if my sensor was 30mV per ºC, this parameter would be set to 30.

### Initializations
It is __critical__ that you remember to initialize SPI communication, as this is how the Teensy communicates with the ADC. Do so by calling `SPI.begin();` in the `setup()` function, and don't forget to `#include <SPI.h>` at the top of your code as well.

The next step is to initialize the sensor and sensor pin. If I had a sensor object called `my_sensor`, I would initialize it by writing `my_sensor.begin();`.

### Usage

There are two main things you need to do to effectively use this library. The first is to sample a sensor, and the second is to actually get a value returned from the sensor object. Lucky, I've made these both pretty easy.

#### Sampling
Sampling of a sensor should happen at a much faster rate than what we care to send over CAN in order to minimize loss of data in-between messages. To sample a sensor called `my_sensor`, I would simply write `my_sensor.sample()`.


#### Reading a value
To read a value from the sensor, you have your choice of three member functions, `avg()`, `min()`, and `max()`. You can read one, two, or all three of them if you'd like. The sample values are automatically turned into sensor values, so no need to worry about confusing conversions. The average, minimum, and maximum values are the result of samples since the last time any of the `avg()`, `min()`, or `max()` member-functions were called. After they are called, the running-tally of samples is automatically reset.

For example, if I wanted to know the maximum value of the sensor, I would call `my_sensor.max()`. The return type is float.

## Full Example
```cpp
#include "ReadADC.h"
#include <EasyTimer.h>

// from left to right, 9 is the teensy pin connected to the ADC, 0 is the ADC pin that the sensor is on,
// 0 is the zero-value of the sensor in mV, 1000 is the mV per sensor unit,
ADCSensor my_sensor(9, 0, 0, 1000);

EasyTimer sample_timer(100); // 50hz timer from the EasyTimer library
EasyTimer print_timer(2); // 2Hz timer from the EasyTimer library

void setup(){
  // initialize serial communication for debugging purposes
  Serial.begin(112500);

  // initialize SPI:
  SPI.begin();

  // initialize sensor
  my_sensor.begin();
}

void loop(){

  if (sample_timer.isup()){
    my_sensor.sample(); // sample the ADC sensor at 50Hz
  }

  if (print_timer.isup()){ // get the values of the sensor every 2Hz
    Serial.print("Average value: ");
    Serial.println(my_sensor.avg());
    Serial.print("Minumum value: ");
    Serial.println(my_sensor.min());
    Serial.print("Maximum value: ");
    Serial.println(my_sensor.max());
    Serial.println();
  }

}
```
