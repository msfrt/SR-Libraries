#ifndef STATE_CAN_H
#define STATE_CAN_H

#include <FlexCAN_T4.h> // this gives the error.


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
    bool valid_ = true; // if the sensor is considered valid
    float secondary_value_ = 0.00; // secondary_value_ replaces value_ when this signal is not considered valid

  public:
    //constructors
    StateSignal() = delete;
    StateSignal(int bl, bool s, int f, int o, int lb, int ub, float sv) : bit_length_(bl), signed_(s),
                inverse_factor_(f), offset_(o), lower_bound_(lb), upper_bound_(ub), secondary_value_(sv) {};

    // getters
    float value() const; // returns real value
    int can_value() const; // returns an integer value ready to send over CAN

    // setters
    void set_can_value(int incoming); // used when an incoming CAN value is read and you finna update the real value.
    void set_validity(bool valid); // update the sensor's validity

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
