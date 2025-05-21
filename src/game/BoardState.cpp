#include "BoardState.hpp"

BoardState::BoardState(unordered_map<char, Vehicle> vehicles) : vehicles(vehicles) {
    board = vector<vector<char>>(dimension.first, vector<char>(dimension.second, '.'));
    for (const auto& [id, vehicle] : vehicles) {
        for (int i = 0; i < vehicle.getLength(); ++i) {
            int r = vehicle.getRow() + (vehicle.getOrientation() == VERTICAL ? i : 0);
            int c = vehicle.getCol() + (vehicle.getOrientation() == HORIZONTAL ? i : 0);
            board[r][c] = id;
        }
    }

    debugBoard = vector<string>(dimension.first);
    for (int i = 0; i < dimension.first; ++i) {
        debugBoard[i] = string(board[i].begin(), board[i].end());
    }
}

bool BoardState::isGoal() {
    const auto& player = vehicles.at(playerID);
    if (player.getOrientation() == HORIZONTAL) {
        // right
        if (player.getCol() + player.getLength() == BoardState::dimension.second &&
            BoardState::exitCoord.second == BoardState::dimension.second &&
            player.getRow() == BoardState::exitCoord.first) {
            return true;
        }
        // left
        if (player.getCol() == 0 &&
            BoardState::exitCoord.second == -1 &&
            player.getRow() == BoardState::exitCoord.first) {
            return true;
        }
    } else {
        // bottom
        if (player.getRow() + player.getLength() == BoardState::dimension.first &&
            BoardState::exitCoord.first == BoardState::dimension.first &&
            player.getCol() == BoardState::exitCoord.second) {
            return true;
        }
        // top
        if (player.getRow() == 0 &&
            BoardState::exitCoord.first == -1 &&
            player.getCol() == BoardState::exitCoord.second) {
            return true;
        }
    }

    return false;
}