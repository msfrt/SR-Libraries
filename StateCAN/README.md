# StateCAN Library
This library provides an easy way to define and use signals that can be easily identified and used between modules. All signals that are present in the DBC can be loaded into a `StateSignal`, which provides useful functionality for sending over can, performing time-out operations, validity checks, and more. Additionally, a `StateCounter` may also be defined, which allows us to easily see lapses in data transmission externally.


## Define a Signal

```cpp
int bitl = 16; // bit length of the signal
bool signed = true; // if signal is signed or unsigned
int fact = 1; // inverse of the factor in the dbc. (example: .01 in DBC means 100 here)
int offset = 0; // offset like in the DBC (currently not enabled)
int min = -5; // minimum value (used for external checks if applicable)
int max = 100; // maximum value (used for external checks if applicable)
int secondary = -1; // secondary value (returned from value() when signal is invalid))
int timeout = 1000; // timeout delay in milliseconds (used for checks if applicable) (optional parameter)

StateSignal USER_fanOverride(bitl, signed, fact, offset, min, max, secondary, timeout);
```

## How to assign a value to the signal

This is really simple. For real values, you can simply use the `=` operator. Like, if I had a signal named `my_cignal`, and I wanted the new value to be 420.69, I would write `my_signal = 420.69`. However, this is not how you should assign values to the signals that are read off of the CAN bus. For that, you should use the `set_can_value` member function, which is listed below

## Member Functions

### value()

Returns the floating-point value associated with the signal. If the signal is invalid, it returns the secondary value.

### can_value()

Returns an integer that is scaled and ready to send over can (if > 1 byte, you must remember to bit shift in your message byte definitions

### real_value()

Always returns the real value. Disregards the secondary value. You probably shouldn't use this, but it's here if you need to.

### timeout_check()

If you would like to check for time-based validity, call this function. It will update the validity parameter to false if the timeout period has been expired, or keep it true otherwise. Furthermore, the validity boolean is returned. IF YOU PERFORM OTHER OBD FUNCTIONS THAT MODIFY VALIDITY, DO NOT USE THIS FUNCTION IN CONJUNCTION.

### set_can_value(int value)

Use this to assign the signal an incoming value from CAN.

### set_validity(bool new_validity)

Manually set the validity with the `new_validity` parameter.

### set_secondary_value(float new_value)

Updates the secondary value.

### is_valid()

Returns true if the signal is currently valid, false otherwise.

## Define a `StateCounter`

When sending can messages, a simple counter can help nodes on the network understand if they are receiving all intended messages. Or, perhaps, there could be a bug on the sending-end. Either way, you can define a counter by using `StateCounter my_counter(256)`. In this instance, `my_counter` is incrementally counts within 8 bits. A counter is initialized by default to have 16 positions and return the values 0-15.

To get the value of a counter, simply use `my_counter.value()`. This will increment the counter by one and return the new value - no need to increment on your own. Once it reaches the number before the maximum, it resets to 0.

For example, if I had code that looked like this...

```cpp
StateCounter my_counter;

while (true){
  Serial.println(my_counter.value());
}
```
The output would look like this...
```
0
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
0
1
2
3
... // you get the point
```
