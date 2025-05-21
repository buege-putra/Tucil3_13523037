#include "Vehicle.hpp"

Vehicle Vehicle::moved(int move, const vector<vector<char>>& board) const {
    if (orientation == HORIZONTAL) {
        int newCol = col + move;
        if (newCol < 0 || newCol + length - 1 >= BoardConfig::dimension.second) {
            return *this;
        }
        
        // check collision
        if (move < 0) {
            for (int c = col - 1; c >= col + move; c--) {
                char cell = board[row][c];
                if (cell != '.') return *this;
            }
        } else {
            for (int c = col + length; c <= col + length + move - 1; c++) {
                char cell = board[row][c];
                if (cell != '.') return *this;
            }
        }
        
        return Vehicle(ID, row, newCol, length, orientation);
    } else {
        int newRow = row + move;
        if (newRow < 0 || newRow + length - 1 >= BoardConfig::dimension.first) {
            return *this;
        }
        
        // check collision
        if (move < 0) {
            for (int r = row - 1; r >= row + move; r--) {
                char cell = board[r][col];
                if (cell != '.') return *this;
            }
        } else {
            for (int r = row + length; r <= row + length + move - 1; r++) {
                char cell = board[r][col];
                if (cell != '.') return *this;
            }
        }
        
        return Vehicle(ID, newRow, col, length, orientation);
    }
}

bool Vehicle::operator==(const Vehicle& other) const {
    return ID == other.ID &&
           row == other.row &&
           col == other.col &&
           length == other.length &&
           orientation == other.orientation;
}