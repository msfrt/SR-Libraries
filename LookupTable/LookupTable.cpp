#include "LookupTable.h"

int LookupTable::index(int row, int column){
  if (row < 0){row = 0;} // snap to row 0
  if (row > (rows_ - 1)){row = rows_ - 1;} // snap to maximum row
  if (column < 0){column = 0;} // snap to column 0
  if (column > columns_ - 1){column = columns_ - 1;} // snap to maximum column

  // so, columns_ is essentiall the width of the table. To skip however many rows desired, we multiply the
  // rows variable by the width (columns_), and then add the desired column to get at
  return row * columns_ + column;
}

int LookupTable::at_index(int row, int column){
  return table_[this->index(row, column)];
}

int LookupTable::set_index(int row, int column, int value){
  table_[this->index(row, column)] = value;
  return value;
}

// iterates through the table and prints it
void LookupTable::print(){
  for (int row = 0; row < this->rows_; ++row){
    for (int column = 0; column < this->columns_; ++column){
      Serial.print(this->at_index(row, column));
      Serial.print(", ");
    }
    Serial.println();
  }
}

int LookupTable::find(int find_row_val, int find_col_val){
  int row_lesser=0;
  int row_greater=0;
  int col_lesser=0;
  int col_greater=0;

  int current_val=0;

  // check to see if the desired row values is above the upper bound
  if (find_row_val >= this->at_index(rows_ - 1, 0)){
    row_lesser = rows_ - 1;
    row_greater = rows_ - 1;

  // check to see if the desired row value is below the lower bound
  } else if (find_row_val <= this->at_index(1, 0)){
    row_lesser = 1;
    row_greater = 1;

  // the desired value is neither below the min, or above the max, so continue...
  } else {
    for (int row = 1; row < rows_; ++row){ // start at 1, becase 0th index is column labels
      current_val = this->at_index(row, 0);

      if (current_val == find_row_val){ // if the row value that we're looking for is already in the table...
        row_lesser = row;
        row_greater = row;
        break; // we've found our row values
      } else if (current_val > find_row_val){ // if the row value we're looking for is in between some other values...
        row_lesser = row - 1; // the next lower value was the previous value
        row_greater = row;
        break;
      }
    }
  }


  // this next for loop is the same as above, but for columns
  if (find_col_val >= this->at_index(0, columns_ - 1)){ // max bound
    col_lesser = columns_ - 1;
    col_greater = columns_ - 1;

  } else if (find_col_val <= this->at_index(0, 1)){ // min bound
    col_lesser = 1;
    col_greater = 1;

  } else {
    // iterate through the columns
    for (int column = 1; column < columns_; ++column){
      current_val = this->at_index(0, column);

      if (current_val == find_col_val){
        col_lesser = column;
        col_greater = column;
        break;
      } else if (current_val > find_col_val){
        col_lesser = column - 1;
        col_greater = column;
        break;
      }
    }
  }

  Serial.println(row_lesser);
  Serial.println(row_greater);
  Serial.println(col_lesser);
  Serial.println(col_greater);


  // now that we have the greater and lesser values, we need to do the mapping.
  int row_map1 = map(find_row_val, this->at_index(row_lesser, 0), this->at_index(row_greater, 0),
                     this->at_index(row_lesser, col_lesser), this->at_index(row_greater, col_lesser));

  int row_map2 = map(find_row_val, this->at_index(row_lesser, 0), this->at_index(row_greater, 0),
                     this->at_index(row_lesser, col_greater), this->at_index(row_greater, col_greater));

  // this map uses the column values to map between the two row maps
  return map(find_col_val, this->at_index(0, col_lesser), this->at_index(0, col_greater), row_map1, row_map2);
}
