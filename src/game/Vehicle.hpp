#ifndef __VEHICLE_HPP__
#define __VEHICLE_HPP__

#include <string>
#include <vector>
#include <stdexcept>
#include "BoardConfig.hpp"

using namespace std;

enum Orientation {
    HORIZONTAL,
    VERTICAL
};

const char playerID = 'P';
const char exitID = 'K';

class Vehicle {
    private:
        char ID;
        int row, col; // top left coordinate
        int length;
        Orientation orientation;
    
    public:
        Vehicle() : ID('\0'), row(0), col(0), length(0), orientation(HORIZONTAL) {};

        Vehicle(const char ID, int row, int col, int length, Orientation orientation) : 
            ID(ID), row(row), col(col), length(length), orientation(orientation) {};

        char getID() const { return ID; }
        int getRow() const { return row; }
        int getCol() const { return col; }
        int getLength() const { return length; }
        Orientation getOrientation() const { return orientation; }

        Vehicle moved(int move, const vector<vector<char>>& board) const;

        bool operator==(const Vehicle& other) const;
};

#endif