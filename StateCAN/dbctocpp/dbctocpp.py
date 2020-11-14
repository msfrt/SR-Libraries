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

        self._name = str(name)
        self._bit_length = int(bit_length)
        self._signed = bool(signed)
        self._factor = float(factor)
        self._offset = float(offset)

        try:
            self._lower_bound = int(lower_bound)
        except TypeError:
            self._lower_bound = 0

        try:
            self._upper_bound = int(upper_bound)
        except TypeError:
            self._upper_bound = 0

        try:
            self._secondary_value = float(secondary_value)
        except TypeError:
            self._secondary_value = 0.0

        try:
            self._timeout_delay = int(timeout_delay)
        except TypeError:
            self._timeout_delay = 0

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

#include <FlexCAN_T4.h>
#include <StateCAN.h>

""".format(header_guard, header_guard)

    fp_out.write(header)

    # signal definitions
    for msg in db.messages:
        fp_out.write("// Message: {} [0x{:x}]\n".format(msg.name, msg.frame_id))
        for sig in msg.signals:
            if not sig.is_multiplexer:
                ssig = StateSignal(sig.name, sig.length, sig.is_signed, sig.scale, sig.offset, sig.minimum, sig.maximum)
                fp_out.write("{};\n".format(ssig))
        fp_out.write("\n")


    fp_out.write("""\n\n\n/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/\n\n\n""")


    # message definitions
    for msg in db.messages:

        # function header
        fp_out.write("/*\n * Decode a CAN frame for the message {}\n * \\param imsg A reference to the incoming CAN message frame\n */".format(msg.name))

        fp_out.write("\nvoid read_{}(CAN_message_t &imsg) {{\n\n".format(msg.name))

        # is this message multiplexed? (it will have a signal tree)
        try:
            for mult_sig_name, mult_msg in msg.signal_tree[0].items():
                # multiplexed message processing here
                pass

        # message is not multiplexed
        except AttributeError:
            for sig in msg.signals:

                if sig.byte_order == 'little_endian':

                    start_byte = sig.start // 8
                    start_byte_offset = sig.start % 8
                    num_bytes = sig.length // 8
                    num_bytes_bit_extension = sig.length % 8

                    end_byte = start_byte + num_bytes
                    if num_bytes_bit_extension > 0:
                        end_byte += 1

                    fp_out.write("\t{}.set_can_value(".format(sig.name))

                    # if we will have to shift everything at the end, we need another open parenthesis
                    # start_byte_offset (part 1)
                    if start_byte_offset > 0:
                        fp_out.write("(")

                    bit_shift = 0
                    for byte_i in range(start_byte, end_byte):

                        # if the last byte is not a complete byte (part 1)
                        if (byte_i == (end_byte - 1)) and (num_bytes_bit_extension > 0):
                            fp_out.write("(")

                        fp_out.write("(imsg.buf[{}]".format(byte_i))

                        # if the last byte is not a complete byte (part 2)
                        if (byte_i == (end_byte - 1)) and (num_bytes_bit_extension > 0):
                            mask = construct_byte_mask(0, num_bytes_bit_extension)
                            fp_out.write(" && 0b{}) >> {}".format(mask, 8 - num_bytes_bit_extension))

                        # if there was start_byte_offset, we need to shift everything temporarily (part 2)
                        if (byte_i == start_byte) and (start_byte_offset > 0):
                            fp_out.write(") << {}".format(start_byte_offset))

                        # shift by the number of bits in the byte (for bytes after byte 0 only)
                        if byte_i != start_byte:
                            fp_out.write(" << {}".format(bit_shift))
                        bit_shift += 8

                        # done with the masking and shifting by this point
                        fp_out.write(")")

                        # there are more bytes to add, so bitwise OR
                        if byte_i != (end_byte - 1):
                            fp_out.write(" | ")

                    # if there was start_byte_offset, we need to shift everything (part 3)
                    if start_byte_offset > 0:
                        fp_out.write(") >> {}".format(start_byte_offset))

                    # okay, now we're done here :)
                    fp_out.write(");\n")

                    # print("sig.start: {}".format(sig.start))
                    # print("sig.length: {}".format(sig.length))
                    # print("start_byte = {}".format(sig.start // 8))
                    # print("start_byte_offset = {}".format(sig.start % 8))
                    # print("num_bytes = {}".format(sig.length // 8))
                    # print("num_bytes_bit_extension = {}".format(sig.length % 8))



        fp_out.write("\n}\n\n")


    # end of header guards and close the file
    fp_out.write("\n\n#endif\n")
    fp_out.close()



def construct_byte_mask(start_bit = 0, num_bits = 8):
    """
    Constructs a mask for end bytes that are not full bytes
    :param start_bit: The starting bit to KEEP
    :param num_bits: The number of bits to keep
    :return: a string representing the 8-bit mask
    """
    mask = ''
    for i in range(start_bit):
        mask += '0'
    for i in range(num_bits):
        mask += '1'
    for i in range(8 - (start_bit + num_bits)):
        mask += '0'

    return mask



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


