# EasyTimer Library

EasyTimer is a library for creating frequency-based timers that avoid the Arduino `delay()` function. `delay()` temporarily halts all code execution for a specified duration of milliseconds.

To get around the halting, non-destructive timers were previously created like this:

```cpp
unsigned long my_timer = 0;
const unsigned long my_timer_delay = 0;

if (my_timer - millis() >= my_timer_delay){
  my_timer = millis();

  // code to run would be placed here
}
```
As you can imagine, it gets a bit messy when 20+ timers are involved in a program. That's 40+ variables to keep track of. Yuck.

I solved this problem by creating a c++ class called EasyTimer. Here's an example of a use case:

```cpp
EasyTimer my_timer(10);

if (my_timer.isup()){
  // code to run goes here
}
```

Wow! This makes things much more simple! Here's a breakdown of how to use the class...

### Defining a timer

Like above, you should always initialize an instance of EasyTimer with a frequency (in Hz). Currently, there is no meaningful default constructor. If you try to initialize an EasyTimer without a frequency parameter, you may get undefined and undesired behavior. The frequency parameter should be a positive integer.

```cpp
EasyTimer my_timer(20); // initialize a timer to 20Hz
```

### Checking if a timer is up

This one's pretty simple. There are two functions to do this and they both do the exact same thing. To check if a timer is up, you can either use the member function `check()` or `isup()`. These functions accept no parameters and return a boolean - true if the timer is up, false otherwise.

```cpp
if (my_timer.isup()){
  // code to run goes here
}
```

### Dynamically changing the timer delay

This is some pretty cool functionality that wasn't easily possible before. You can change the delay of a timer by assigning a new frequency with `set_frequency()` or a new delay in milliseconds with `set_delay` This automatically updates the statements that use `isup()` and `check()`.

```cpp
my_timer.set_frequency(100); // changes EasyTimer to 100Hz
my_timer.set_delay(20); // sets delay to 20ms (equivalent to 50Hz)
```
