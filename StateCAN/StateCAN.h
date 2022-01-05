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
    unsigned int msg_id_ = 0;  // the id of the message that this signal belongs to (useful for CAN filtering purposes)
    bool updated_ = false;


  public:
    //constructors
    StateSignal() = delete;
    StateSignal(int bl, bool s, int f, int o, int lb, int ub, float sv, int td = -1, unsigned int msg_id = 0) : bit_length_(bl), signed_(s),
                inverse_factor_(f), offset_(o), lower_bound_(lb), upper_bound_(ub),
                secondary_value_(sv), timeout_delay_(td), msg_id_(msg_id) {};

    // getters
    float value(); // returns value (takes validity into account)
    int can_value(); // returns an integer value ready to send over CAN
    float real_value(){return value_;} // always returns the normal value (don't use probably)
    float secondary_value(){return secondary_value_;} // always returns the secondary value (useful for OBD debugging)
    float lower_bound() const {return lower_bound_;}
    float upper_bound() const {return upper_bound_;}
    bool is_valid() const {return valid_;}
    unsigned int get_msg_id() const {return msg_id_;}  // returns the message id of this signal. Be aware that the default value is 0
    bool is_updated() const {return updated_;}

    // setters
    void set_can_value(int incoming); // used when an incoming CAN value is read and you finna update the real value.
    void set_validity(bool valid); // update the sensor's validity
    void set_secondary_value(float new_val){secondary_value_ = new_val;} // set the secondary value
    void set_msg_id(unsigned int id){msg_id_ = id;}
  
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
