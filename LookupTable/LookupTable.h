#ifndef LOOKUP_H
#define LOOKUP_H

#include "Arduino.h" // for size_t

class LookupTable{
  private:
    int *table_;
    const int rows_;
    const int columns_;
  public:
    // constructors
    LookupTable() = delete;
    // this next constructor creates a 1d array that is much faster than a 2d array and uses less memory,
    // but it will require that the user indexes the table using an indexing function
    LookupTable(int rows, int columns) : rows_(rows), columns_(columns) { table_ = new int[rows_ * columns_];}

    // destructor (remember to destroy dynamically allocated table array)
    ~LookupTable() {delete [] table_;}

    // how to get the proper index for the table
    int index(int row, int column);

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

    template<typename Type, size_t Size> // this is needed so we don't have to pass the size of the array in manually
    void fill_table(const Type(&table)[Size]);
};

template<typename Type, size_t Size> // this is templated, so we've gotta keep it in the header file
void LookupTable::fill_table(const Type(&table)[Size]){
  for (int row = 0; row < this->rows_; ++row){ // iterate through the rows of the lookup table
    for (int column = 0; column < this->columns_; ++column){ // iterate through the columns of the lookup table
      this->set_index(row, column, table[row][column]);
    }
  }
}

#endif
