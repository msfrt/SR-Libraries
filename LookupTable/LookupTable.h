#ifndef LOOKUP_H
#define LOOKUP_H

#include "Arduino.h" // for size_t

class LookupTable{
  private:
    int *table_;
    const int rows_;
    const int columns_;

    // how to get the proper index for the table
    int index(int row, int column);
  public:
    // constructors
    LookupTable() = delete;
    // this next constructor creates a 1d array that is much faster than a 2d array and uses less memory,
    // but it will require that the user indexes the table using an indexing function
    LookupTable(int rows, int columns) : rows_(rows), columns_(columns) { table_ = new int[rows_ * columns_];}

    // RULE OF THREE:
    // destructor (remember to destroy dynamically allocated table array)
    ~LookupTable() {delete [] table_;}
    // copy and copy-assignment constructor
    LookupTable(const LookupTable &old_table) = delete; // don't EVER copy unless implementing this function.
    LookupTable& operator=(const LookupTable& old_table) = delete; // same here, DON'T COPY!

    // getter - get the value at a certain index
    int at_index(int row, int column);
    int rows(){return rows_;}
    int columns(){return columns_;}
    int find(int row_val, int col_val); // the returns the value in the lookuptable if found, otherwise it calculates
                                        // one based off of the surrounding values

    // setter - set the value at a certain index
    int set_index(int row, int column, int value);

    // you can print the table for debugging purposes
    void print();

    // this takes a pointer to the first element of the 2d array
    void fill_table(int *first_element);
};


#endif
