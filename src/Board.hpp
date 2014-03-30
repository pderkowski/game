/* Copyright 2014 <Piotr Derkowski> */

#ifndef BOARD_H_
#define BOARD_H_

#include <vector>

class Board {
public:
    Board(int rowsNo, int columnsNo);

    void toggleSelection(int row, int column);
    bool isSelected(int row, int column) const;

    int getRowsNo() const;
    int getColumnsNo() const;

private:
    int rowsNo_;
    int columnsNo_;
    std::vector<std::vector<bool>> tiles_;
};

#endif  // BOARD_H_
