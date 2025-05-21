#ifndef __BOARD_STATE_HPP__
#define __BOARD_STATE_HPP__

#include "BoardConfig.hpp"
#include "Vehicle.hpp"
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class BoardState : public BoardConfig {
    private:
        unordered_map<char, Vehicle> vehicles;
        vector<vector<char>> board;
        vector<string> debugBoard;
    
    public:
        BoardState() = default;
        BoardState(unordered_map<char, Vehicle> vehicles);

        const vector<vector<char>>& getBoard() const { return board; }
        const unordered_map<char, Vehicle>& getVehicles() const { return vehicles; }

        bool isGoal();

        bool operator==(const BoardState& other) const { return vehicles == other.vehicles; }
};

#endif