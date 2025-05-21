#include "heuristic.hpp"

int calculateNextCost(int maxMove, int move) {
    return 1 + maxMove - abs(move);
}


int calculateBlockingHeuristic(const BoardState& state) {
    const auto& vehicles = state.getVehicles();
    const Vehicle& player = vehicles.at(playerID);
    unordered_set<char> blocking;
    
    const auto& board = state.getBoard();
    
    if (player.getOrientation() == HORIZONTAL) {
        if (BoardState::exitCoord.second == BoardState::dimension.second) {
            for (int c = player.getCol() + player.getLength(); c < BoardState::dimension.second; c++) {
                if (board[player.getRow()][c] != '.') {
                    blocking.insert(board[player.getRow()][c]);
                }
            }
        }
        else if (BoardState::exitCoord.second == -1) {
            for (int c = 0; c < player.getCol(); c++) {
                if (board[player.getRow()][c] != '.') {
                    blocking.insert(board[player.getRow()][c]);
                }
            }
        }
    } else {
        if (BoardState::exitCoord.first == BoardState::dimension.first) {
            for (int r = player.getRow() + player.getLength(); r < BoardState::dimension.first; r++) {
                if (board[r][player.getCol()] != '.') {
                    blocking.insert(board[r][player.getCol()]);
                }
            }
        }
        else if (BoardState::exitCoord.first == -1) {
            for (int r = 0; r < player.getRow(); r++) {
                if (board[r][player.getCol()] != '.') {
                    blocking.insert(board[r][player.getCol()]);
                }
            }
        }
    }
    
    return blocking.size();
}
