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
import ntpath

DEBUG = False


class SignalMask:

    def __init__(self, sig, message_bytes):
        """
        Creates a signal mask object
        :param sig: the signal object to create a mask for
        :param message_bytes: the number of bytes in the message that this signal belongs to
        """

        self._start = sig.start
        self._bit_length = sig.length
        self._msg_bytes = message_bytes
        self._little_endian = sig.byte_order == "little_endian"
        self._byte_array_prefix = "imsg.buf"

        self._byte_array = [[0 for j in range(8)] for i in range(self._msg_bytes)]

        if self._little_endian:
            for bit_i in range(self._start, self._start + self._bit_length):
                # calculate the current byte and the current bit index
                byte = bit_i // 8
                bit = 7 - bit_i % 8

                # set the bit
                self._byte_array[byte][bit] = 1

        # big endian is pretty muffed up. Just look at the bit indices in DB++
        else:

            bit_i = (7 - self._start) % 8
            byte_i = self._start // 8

            for i in range(self._start, self._start + self._bit_length):

                # set the bit
                self._byte_array[byte_i][bit_i] = 1

                bit_i += 1
                if bit_i % 8 == 0:
                    bit_i = 0
                    byte_i += 1

    def byte_array_str(self):
        """
        constructs a matrix representation of this signal within the byte array
        :return: the string representation
        """

        # this constructs a matrix representation of the entire message buffer. Use this to help with debugging
        st = "byte order: "
        if self._little_endian:
            st += "little-endian\n"
        else:
            st += "big-endian\n"

        for byte_i in range(len(self._byte_array)):
            st += "{}: ".format(byte_i)
            byte = self._byte_array[byte_i]
            for bit in byte:
                st += "{} ".format(bit)
            st += '\n'
        return st

    def __str__(self):
        """
        Represent this mask as a string
        :return: the string C code mask
        """

        mask_str = ""

        if self._little_endian:

            byte_offset = 0  # used to shift each additional byte of the buffer
            shift_right_bits = 0  # if the first byte in this number is not a full byte, the end will shift right
            for byte_i in range(len(self._byte_array)):

                mask_sum = sum(self._byte_array[byte_i])

                # if the sum of the mask == 0, that means that the entire mask is 0b00000000.
                # in other words, we omit this byte
                if mask_sum == 0:
                    continue

                # if the mask sum is 8, the mask is 0b11111111, which means no masking is necessary
                elif mask_sum == 8:
                    mask_str += "({}[{}]".format(self._byte_array_prefix, byte_i)

                    if byte_offset != 0:
                        mask_str += " << {}".format(byte_offset * 8)

                    # we've added a byte, so we must increase the byte offset by one for the next iteration
                    byte_offset += 1
                    mask_str += ")"

                # if the mask sum was neither 0 nor 8, that means that there's some variable mask we need to do
                else:

                    # okay so this gets a little tricky. If this is the first byte, there's a possibility that it's
                    # shifted to the left too much. This occurs when there's a mask like 0b00110000, where the actual
                    # integer value needs to be 0b00000011. We would need to shift the entire thing by 4 bits at the
                    # very end of all of the masking, otherwise it could be off my many factors of two
                    if byte_offset == 0:
                        for i in range(7, -1, -1):  # start from 7 and go to 0
                            if self._byte_array[byte_i][i] == 0:
                                shift_right_bits += 1
                            else:
                                break

                    mask_str += "(({}[{}]".format(self._byte_array_prefix, byte_i)

                    # construct the 0b???????? mask based off of the bits in the byte
                    mask_bit_str = ""
                    for bit in self._byte_array[byte_i]:
                        mask_bit_str += str(bit)  # either is a 1 or a 0

                    # add the mask
                    mask_str += " & 0b{})".format(mask_bit_str)

                    if byte_offset != 0:
                        mask_str += " << {}".format(byte_offset * 8)

                    # we've added a byte, so we must increase the byte offset by one for the next iteration
                    byte_offset += 1
                    mask_str += ")"

                # look one iteration into the future to see if we need to add a bitwise OR to the mask
                try:
                    if (sum(self._byte_array[byte_i + 1])) != 0:
                        mask_str += " | "
                except IndexError:
                    pass

            # congrats! you've got a mask! (almost). If we need to shift the entire thing right some bits, we can
            # do it now that that main mask construction is complete
            if shift_right_bits > 0:
                # add an extra parenthesis to the beginning and do the shifts
                mask_str = "(" + mask_str + " >> {})".format(shift_right_bits)

        # big endian, so above, but in reverse
        else:

            byte_offset = 0  # used to shift each additional byte of the buffer
            shift_right_bits = 0  # if the first byte in this number is not a full byte, the end will shift right
            for byte_i in range(len(self._byte_array) - 1, -1, -1):
                
                mask_sum = sum(self._byte_array[byte_i])

                # if the sum of the mask == 0, that means that the entire mask is 0b00000000.
                # in other words, we omit this byte
                if mask_sum == 0:
                    continue

                # if the mask sum is 8, the mask is 0b11111111, which means no masking is necessary
                elif mask_sum == 8:
                    mask_str += "({}[{}]".format(self._byte_array_prefix, byte_i)

                    if byte_offset != 0:
                        mask_str += " << {}".format(byte_offset * 8)

                    # we've added a byte, so we must increase the byte offset by one for the next iteration
                    byte_offset += 1
                    mask_str += ")"

                # if the mask sum was neither 0 nor 8, that means that there's some variable mask we need to do
                else:

                    # okay so this gets a little tricky. If this is the first byte, there's a possibility that it's
                    # shifted to the left too much. This occurs when there's a mask like 0b00110000, where the actual
                    # integer value needs to be 0b00000011. We would need to shift the entire thing by 4 bits at the
                    # very end of all of the masking, otherwise it could be off my many factors of two
                    if byte_offset == 0:
                        for i in range(7, -1, -1):  # start from 7 and go to 0
                            if self._byte_array[byte_i][i] == 0:
                                shift_right_bits += 1
                            else:
                                break

                    mask_str += "(({}[{}]".format(self._byte_array_prefix, byte_i)

                    # construct the 0b???????? mask based off of the bits in the byte
                    mask_bit_str = ""
                    for bit in self._byte_array[byte_i]:
                        mask_bit_str += str(bit)  # either is a 1 or a 0

                    # add the mask
                    mask_str += " & 0b{})".format(mask_bit_str)

                    if byte_offset != 0:
                        mask_str += " << {}".format(byte_offset * 8)

                    # we've added a byte, so we must increase the byte offset by one for the next iteration
                    byte_offset += 1
                    mask_str += ")"

                # look one iteration into the future to see if we need to add a bitwise OR to the mask
                try:
                    if (sum(self._byte_array[byte_i - 1])) != 0:
                        mask_str += " | "
                except IndexError:
                    pass

            # congrats! you've got a mask! (almost). If we need to shift the entire thing right some bits, we can
            # do it now that that main mask construction is complete
            if shift_right_bits > 0:
                # add an extra parenthesis to the beginning and do the shifts
                mask_str = "(" + mask_str + " >> {})".format(shift_right_bits)

        return mask_str


class StateSignal:

    def __init__(self, name, bit_length, signed, factor, offset, lower_bound, upper_bound,
                 secondary_value=0, timeout_delay=0, frame_id=0):
        """
        Contructor
        :param name: the name of the signal
        :param bit_length: the bit length (unsigned integer)
        :param signed: if the signal is signed (true) or unsigned (false)
        :param factor: The inverse of the signal's factor (integer)
        :param offset: the offset of the signal (int)
        :param lower_bound: The lower bound of the signal (int)
        :param upper_bound: The upper bound of the signal (int)
        :param frame_id: The ID of the message that this signal belongs to
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

        try:
            self._frame_id = int(frame_id)
        except TypeError:
            self._frame_id = 0

    def __str__(self):
        return "StateSignal {}({}, {}, {}, {}, {}, {}, {}, {}, {})".format(self._name, self._bit_length,
                                                                       str(self._signed).lower(),
                                                                       int(1.0 / self._factor),
                                                                       self._offset, self._lower_bound,
                                                                       self._upper_bound, self._secondary_value,
                                                                       self._timeout_delay, self._frame_id)

    def __repr__(self):
        return self.__str__()


def find_signal_object(signals_list, signal_name_str):
    """
    Finds the signal object by signals name within a list of signal objects
    :param signals_list: the list of signal objects
    :param signal_name_str: the name of the signal
    :return: The signal object
    """

    for sig in signals_list:
        if sig.name == signal_name_str:
            return sig


def path_leaf(path):
    """
    Takes in a full filepath and returns just the filename
    """
    head, tail = ntpath.split(path)
    return tail or ntpath.basename(head)


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
    header_guard = output_file.upper().replace(".", "_").replace(" ", "_").replace("\\", "_").replace("/", "_")
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
                ssig = StateSignal(sig.name, sig.length, sig.is_signed, sig.scale, sig.offset, sig.minimum, sig.maximum,
                                   frame_id=msg.frame_id)
                fp_out.write("{};\n".format(ssig))
        fp_out.write("\n")

    fp_out.write("""\n\n\n/************************************************************************************
    
    Incoming CAN frame decoding functions

************************************************************************************/\n\n\n""")

    # message definitions
    for msg in db.messages:

        # function header
        fp_out.write(
            "/*\n * Decode a CAN frame for the message {}\n * \\param imsg A reference to the incoming CAN message "
            "frame\n */".format(
                msg.name))

        fp_out.write("\nvoid read_{}(const CAN_message_t &imsg) {{\n\n".format(msg.name))

        # for testing
        # if msg.name[0:4] != "TEST":
        #     continue

        # is this message multiplexed? (it will have a signal tree)
        try:
            for mult_sig_name, mult_msg in msg.signal_tree[0].items():
                # multiplexed message processing here

                fp_out.write("\t// multiplexer signal\n")
                fp_out.write("\tint {} = imsg.buf[0];\n\n".format(mult_sig_name))

                fp_out.write("\tswitch ({}) {{\n\n".format(mult_sig_name))

                for mult_id, signal_list in mult_msg.items():
                    fp_out.write("\t\tcase {}:\n".format(mult_id))

                    for sig_name_str in signal_list:
                        # this finds the actual signal object within the message's signals
                        sig_obj = find_signal_object(msg.signals, sig_name_str)

                        # create the mask
                        signal_bit_mask = SignalMask(sig_obj, msg.length)

                        # write to the file
                        fp_out.write("\t\t\t{}.set_can_value({});\n".format(sig_obj.name, signal_bit_mask))

                    # end switch
                    fp_out.write("\t\t\tbreak;\n\n".format(mult_id))

                # end switch statement
                fp_out.write("\t}\n")

        # the message exists, but has no signals
        except IndexError:
            pass

        # message is not multiplexed
        except AttributeError:
            for sig in msg.signals:

                little_endian_bool = sig.byte_order == 'little_endian'

                signal_bit_mask = SignalMask(sig, msg.length)

                if DEBUG:
                    print('\n')
                    print(msg.name)
                    print(sig.name)
                    print(signal_bit_mask.byte_array_str())
                    print(signal_bit_mask)

                fp_out.write("\t{}.set_can_value({});\n".format(sig.name, signal_bit_mask))

        fp_out.write("\n}\n\n")

    fp_out.write("""\n\n\n/************************************************************************************

    Distribute incoming messages to the correct decoding functions

************************************************************************************/\n\n\n""")

    input_filename_only = path_leaf(input_file)

    # function header
    fp_out.write("/*\n * Decode a CAN message for the bus captured in {}.\n * To more efficiently allocate "
                 "microcontroller resources, simply comment\n * out unnecessary messages that do not need to be "
                 "decoded.\n * \\param imsg A reference to the incoming CAN frame\n */\n".format(input_filename_only))

    # create a function that uses this filename as a bus name to distribute incoming frames to decode functions
    fp_out.write("void decode_{}(const CAN_message_t &imsg) {{\n\n".format(input_filename_only[:-4]))

    # switch based on message id
    fp_out.write("\tswitch (imsg.id) {\n\n")

    # map every message's read function (that was defined above) to the proper id
    for msg in db.messages:
        fp_out.write("\t\tcase {}:\n".format(msg.frame_id))
        fp_out.write("\t\t\tread_{}(imsg);\n".format(msg.name))
        fp_out.write("\t\t\tbreak;\n\n")

    # end switch statement
    fp_out.write("\t}\n")

    # end decode incoming function
    fp_out.write("}\n")

    # end of header guards and close the file
    fp_out.write("\n\n#endif\n")
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
