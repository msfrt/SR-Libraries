# Diode-based Board Temperature

An easy and low-cost way to measure Centigrade temperature with a diode. This support library makes it easy.

## Define a board-temp sensor

Constructor:
```cpp
BoardTempDiode(int pin, int read_resolution, float temp_cal, float mV_cal)
```
* `pin` - the microcontroller pin that the voltage reading will be sampled from
* `read_resolution` - the number of bits of resolution that your microcontroller is sampling. 10 is the default on most μCs. The teensy 4.0 can go up to 12 (or so I've read). This parameter doesn't actually change the read resolution of your board. To do that, you must call `analogReadResolution(num_bits)`.
* `temp_cal` - the temperature (Centrigrade) reading at the time of calibration. This must be taken with an external temperature sensor that has already been calibrated (like an IR gun, or something).
* `mV_cal` - the milliVoltage reading at the time of calibration. The member function `.get_mV()` returns the last calculated mV, so it's easy to spit this out on a serial print statement during calibration. Just be sure that you are also calling the `.value()` member function, as the last milliVoltage is calculated only in that function call.

## Sample a sensor

You can sample the board temp diode with `.sample()`, and get the average value of the samples during the last sampling period with `.value()`. You'll probably want to sample the diode at a higher rate than you use the value, although this is temperature, so it shouldn't really change too fast.

## Update microcontroller voltage

By default, the temperature calculations are done off of a max reading of 3300mV. If you are using a 5V microcontroller, you will want to also update that voltage. You can do so by using `set_uC_mV()`. For example, if I were to use a 5V microcontroller with a sensor called `board_temp`, I'd call `board_temp.set_uC_mV(5000)`.

## Complete example

```cpp
#include <BoardTemp.h>
#include <EasyTimer.h>

// parameters and calibrations
const int pin = 19;
const int read_resolution_bits = 12;
const float temp_cal = 26.2;
const float mV_cal = 580;

// define a BoardTempDiode object
BoardTempDiode board_temp(pin, read_resolution_bits, temp_cal, mV_cal)

// define an EasyTimer for sampling, and one for printing
EasyTimer sample_timer(100);  // 100Hz
EasyTimer print_timer(10);  // 10Hz


void setup(){

  Serial.begin(115200);

  // you must call this, otherwise your sensor calculations will not work
  board_temp.begin()

}


void loop(){

  if (sample_timer.isup())
    board_temp.sample();

  if (print_timer.isup())
    Serial.println( board_temp.value() );

  // To print out the millivoltage reading during calibration, you can call:
  // Serial.println( board_temp.get_mV() );
}
```
