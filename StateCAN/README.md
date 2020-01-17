# StateCAN Library

## Define a Signal

```cpp
int bitl = 16; // bit length of the signal
bool signed = true; // if signal is signed or unsigned
int fact = 1; // inverse of the factor in the dbc. (example: .01 in DBC means 100 here)
int offset = 0; // offset like in the DBC (currently not enabled)
int min = -5; // minimum value (used for external checks if applicable)
int max = 100; // maximum value (used for external checks if applicable)
int secondary = -1; // secondary value (returned from value() when signal is invalid))
int timeout = 1000; // timeout delay in milliseconds (used for checks if applicable)

StateSignal StateSignal USER_fanOverride(bitl, signed, fact, offset, -5, 100, -1, 1000);
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

If you would like to check for time-based validity, call this function. It will update the validity parameter to false if the timeout period has been expired, or keep it true otherwise.

### set_can_value(int value)

Use this to assign the signal an incoming value from CAN.

### set_validity(bool new_validity)

Manually set the validity with the `new_validity` parameter.


