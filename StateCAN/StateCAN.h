#ifndef STATE_CAN_H
#define STATE_CAN_H

#include <FlexCAN_T4.h> // this gives the error.

class StateCounter{
  private:
    unsigned int num_positions_ = 16; // the maximum number of positions to be sent, including 0, excluding the max.
    unsigned int current_position_ = 4294967294; // max value of unsigned int
  public:
    StateCounter() = default;
    StateCounter(unsigned int positions) : num_positions_(positions) {};

    // getter
    unsigned int value(); // returns the current value of the counter and increments
    unsigned int value_ghost(){return current_position_;} // returns the current value but does not increment

    // setter
    void set_max(unsigned int new_max){num_positions_ = new_max;}
    void increment(int positions){current_position_ += positions;} // why would you ever need this
};


class StateSignal{
  private:
    int bit_length_ = 16;
    unsigned long last_recieve_ = 0; // last recieved message (if applicable) in milliseconds
    float value_ = 0.00; // the actual, real value of the signal
    bool signed_ = true;
    const int inverse_factor_ = 1; // if the factor is 0.1 in the DBC, it should be 10 here. 0.01 -> 100
    const int offset_ = 0; // offset as in DBC
    int lower_bound_ = 0; // for bounds check
    int upper_bound_ = 0; // for bounds check
    bool valid_ = true; // if the signal is considered valid
    float secondary_value_ = 0.00; // secondary_value_ replaces value_ when this signal is not considered valid
    int timeout_delay_ = -1; // milliseconds delay before signal should become invalid. -1 means disabled


  public:
    //constructors
    StateSignal() = delete;
    StateSignal(int bl, bool s, int f, int o, int lb, int ub, float sv, int td = -1) : bit_length_(bl), signed_(s),
                inverse_factor_(f), offset_(o), lower_bound_(lb), upper_bound_(ub),
                secondary_value_(sv), timeout_delay_(td) {};

    // getters
    float value(); // returns value (takes validity into account)
    int can_value(); // returns an integer value ready to send over CAN
    float real_value(){return value_;} // always returns the normal value (don't use probably)

    // setters
    void set_can_value(int incoming); // used when an incoming CAN value is read and you finna update the real value.
    void set_validity(bool valid); // update the sensor's validity

    // helper function to check for timeout-based validity;
    bool timeout_check();

    // allow us to use the = operator to assign values to the Signal
    const int operator=(int);
    const int operator=(float);
    const int operator=(double);

    // implicit conversion to a int value
    operator int() const { return static_cast<int>(value_); }
    //implicit conversion to a float value
    operator float() const { return value_; }
};



#endif
