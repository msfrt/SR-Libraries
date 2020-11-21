# DBC to CPP
A nice little script that saves you hours of work every time you make or update a DBC.\
Dave Yonkers, 2020(ish)


## Purpose
To read can frames on an Arduino, or, in this case, a Teensy, you need to do a bit of maths to get the 64 (or more) 
ones and zeros within an incoming CAN frame lined up just right. Then, after everything is lined up, you need to do
plenty of bitwise operations to mask out and shift the signals contained within the frame before they can be used
as a C++ int (or whatever standard data structure is of your liking). 

This script will generate C++ code that takes in a [FlexCAN_T4](https://github.com/tonton81/FlexCAN_T4) message frame 
for any given bus, determine the correct message that
it belongs to, then finally decodes the bits contained in the can frame into actual numbers. This is done with the help
of the StateCAN library.


## Dependencies

This script relies on the usage of the [cantools](https://pypi.org/project/cantools/) package. This is not included
within the default python installation, so you may either need to use a virtual environment with it installed 
(preferred, but more advanced method), or simply install it in your root Python installation by running the
 following command:

```shell script
pip install cantools
```


## Usage

A complete and well-formatted DBC is required for use. If the execution is successful, a file will be created with 
the name supplied in the second command line argument. This file is formatted as a `.hpp` file, so you should probably 
save it as a `.hpp` file. Those seem to work nice with Arduino.

The python script is designed to be ran from the command line. To view command-line arguments and basic descriptions, 
simply run:
```shell script
python3 dbctocpp.py -h
```

A complete use case may look like this:

```shell script
python3 dbctocpp.py /path/to/my/can_bus.dbc /put/output/file/here.hpp
```

Or this:

```shell script
python3 dbctocpp.py my_bus.dbc output.hpp
```

## Notes

* Although it may be easy to just generate the CAN reading functions and stop there, it's probably pretty inefficient 
to read and decode every single CAN message. In the top-level decoding function (the function that starts 
with `void decode_<filename>`), you should comment out all of the cases in the switch statement that you are 
uninterested in. That way, only the signals that you care about are getting updated, which frees up resources for
operations elsewhere.


