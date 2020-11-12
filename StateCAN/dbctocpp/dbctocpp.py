########################################################################################################################
#
# dbctocpp.py
#
# Author: Dave Yonkers
# Maintainer: Dave Yonkers
#
# A script to read in regular DBC files, make sense of them, then output them as messages and signals that the StateCAN
# library can make sense of.
#
########################################################################################################################

import cantools
import argparse


class StateSignal:

    def __init__(self, name, bit_length, signed, factor, offset, lower_bound, upper_bound,
                 secondary_value=0, timeout_delay=0):
        """
        Contructor
        :param name: the name of the signal
        :param bit_length: the bit length (unsigned integer)
        :param signed: if the signal is signed (true) or unsigned (false)
        :param factor: The inverse of the signal's factor (integer)
        :param offset: the offset of the signal (int)
        :param lower_bound: The lower bound of the signal (int)
        :param upper_bound: The upper bound of the signal (int)
        :param secondary_value: The secondary value when the signal is invalid
        :param timeout_delay: The timeout delay for the signal in milliseconds
        """

        self._name = name
        self._bit_length = bit_length
        self._signed = signed
        self._factor = factor
        self._offset = offset
        self._lower_bound = lower_bound
        self._upper_bound = upper_bound
        self._secondary_value = secondary_value
        self._timeout_delay = timeout_delay

    def __str__(self):
        return "StateSignal {}({}, {}, {}, {}, {}, {}, {}, {})".format(self._name, self._bit_length,
                                                                       str(self._signed).lower(),
                                                                       int(1.0 / self._factor),
                                                                       self._offset, self._lower_bound,
                                                                       self._upper_bound, self._secondary_value,
                                                                       self._timeout_delay)

    def __repr__(self):
        return self.__str__()



def dbctocpp(input_file, output_file):
    """
    This function reads in regular DBC files, makes sense of them using the cantools library, then outputs them
    as messages in a .hpp that the StateCAN library can make sense of.
    :param input_file: The name/path of the input DBC file (ex. my_DBC1.dbc)
    :param output_file: The name/path of the output file. A typical extension would be ".hpp" but it's just a text file.
    :return: True if success, False is failure
    """

    db = cantools.database.load_file(input_file)

    # open the output file and write a few basic lines
    fp_out = open(output_file, "w")
    header_guard = output_file.upper().replace(".", "_").replace(" ", "_")
    header = """/******************************************************************************
    
    This file was generated automatically from a DBC file by the dbctocpp 
    utility, which is part of the StateCAN library, 
    a component of SR-Libraries.

    https://github.com/msfrt/SR-Libraries
    
******************************************************************************/

#ifndef {}
#define {}

#include <StateCAN.h>

""".format(header_guard, header_guard)

    fp_out.write(header)

    for msg in db.messages:
        fp_out.write("// Message: {} [0x{:x}]\n".format(msg.name, msg.frame_id))
        for sig in msg.signals:
            if not sig.is_multiplexer:
                ssig = StateSignal(sig.name, sig.length, sig.is_signed, sig.scale, sig.offset, sig.minimum, sig.maximum)
                fp_out.write("{};\n".format(ssig))
        fp_out.write("\n")



    # end of header guards and close the file
    fp_out.write("#endif\n")
    fp_out.close()



def main():
    """
    The main function reads command line inputs and calls the dbctocpp function
    :return:
    """

    parser = argparse.ArgumentParser(description='Turn a .dbc file into a file that StateCAN can understand')
    parser.add_argument('input_file', type=str,
                        help='The filename (and path if necessary) of the input .dbc file. (Ex. "my_DBC.dbc")')
    parser.add_argument('output_file', type=str,
                        help='The filename (and path if necessary) of the output file. (Ex. "bus1_messages.hpp")')

    args = parser.parse_args()

    dbctocpp(args.input_file, args.output_file)


if __name__ == "__main__":
    main()


