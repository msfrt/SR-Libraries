# ReadADC Library

It's never been easier to sample your favorite ADC128S022 analog-to-digital converter over SPI.

## Usage

### Declarations
Before the `setup()` and `loop()` functions, you should declare each sensor and each ADC chip. The ADC sensor constructor has parameters as follows:

```cpp
ADCSensor my_sensor(int adc_channel, int sensor_zero_mV, int mV_per_sensor_unit);
```

* __adc_channel__ is the channel of the ADC that the sensor is on (it should be between 0-7 on an 8-channel ADC)
* __sensor_zero_mV__ this is the zero-voltage of the sensor in milliVolts
* __mV_per_sensor_unit__ represents the voltage per sensor unit. For example, if my sensor was 30mV per ºC, this parameter would be set to 30.

The ADC chip has a constructor with only one parameter.

```cpp
ADCChip my_chip(int chip_select);
```

* __chip_select__ is the pin number that controls the chip select for the ADC chip on the SPI bus.

### Initializations
It is __critical__ that you remember to initialize SPI communication, as this is how the Teensy communicates with the ADC. Do so by calling `SPI.begin();` in the `setup()` function, and don't forget to `#include <SPI.h>` at the top of your code as well.

The next step is to initialize the chip and chip select pin. If I had a sensor object called `my_chip`, I would initialize it by writing `my_chip.begin();`.

### Usage

There are two main things you need to do to effectively use this library. The first is to sample a sensor, and the second is to actually get a value returned from the sensor object. Lucky, I've made these both pretty easy.

#### Sampling
Sampling of a sensor should happen at a much faster rate than what we care to send over CAN in order to minimize loss of data in-between messages. To sample a sensor called `my_sensor` that's located on a chip called `my_chip`, I'd simply call `my_chip.sample(my_sensor)`. The sensor is passed by reference, so the values within `my_sensor` are automatically updated.

Let's talk about efficiency. A single ADC sample requires two SPI transactions: one to tell the ADC what channel number to sample, and another to get the return value. That's two transactions, but the second transaction takes the pin ID of the next channel to sensor. This means you can effectively daisy-chain sensor readings to reduce wasted transactions (i.e. 1 sensor takes 2 transactions, 2 sensors take 3 transactions, 3 sensors take 4, etc.). As of October 2020, you can chain up to 8 sensor readings in this library. A chained sample can look like `my_adc.sample(sensor1, sensor2)`, or even `my_adc.sample(sensor1, sensor1, sensor1)`, all they way up to 8 sensors per chip sample.


#### Reading a value
To read a value from the sensor, you have your choice of three member functions, `avg()`, `min()`, and `max()`. You can read one, two, or all three of them if you'd like. The sample values are automatically turned into sensor values, so no need to worry about confusing conversions. The average, minimum, and maximum values are the result of samples since the last time any of the `avg()`, `min()`, or `max()` member-functions were called. After they are called, the running-tally of samples is automatically reset.

For example, if I wanted to know the maximum value of the sensor, I would call `my_sensor.max()`. The return type is float.

## Full Example
```cpp
#include "ReadADC.h"
#include <EasyTimer.h>

// from left to right, 1 is the ADC channel that the sensor is on (0-7 possible),
// 0 is the zero-value of the sensor in mV, 1000 is the mV per sensor unit,
ADCSensor my_sensor1(1, 0, 1000);
ADCSensor my_sensor2(2, 0, 1000);

// 10 is the teensy pin that the ADC's chip select is connected to
ADCChip my_chip(10);

EasyTimer sample_timer(100); // 50hz timer from the EasyTimer library
EasyTimer print_timer(2); // 2Hz timer from the EasyTimer library

void setup(){
  // initialize serial communication for debugging purposes
  Serial.begin(112500);

  // initialize SPI:
  SPI.begin();

  // initialize chip
  my_chip.begin();
}

void loop(){

  if (sample_timer.isup()){
    my_chip.sample(my_sensor1, my_sensor2); // sample the ADC sensors at 50Hz
  }

  if (print_timer.isup()){ // get the values of the sensor every 2Hz
    Serial.print("Average value: ");
    Serial.println(my_sensor1.avg());
    Serial.print("Minumum value: ");
    Serial.println(my_sensor1.min());
    Serial.print("Maximum value: ");
    Serial.println(my_sensor1.max());
    Serial.println();
  }

}
```
