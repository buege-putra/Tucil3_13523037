#include "output.hpp"
#include <iostream>
#include <filesystem>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

void printColoredBoard(const BoardState& state, char movedVehicleID) {
    auto [rows, cols] = BoardConfig::dimension;
    auto [exitRow, exitCol] = BoardConfig::exitCoord;
    auto board = state.getBoard();
    
    bool isTop = exitRow == -1;
    bool isBottom = exitRow == rows;
    bool isLeft = exitCol == -1;
    bool isRight = exitCol == cols;

    if (isTop) {
        cout << endl;
        solutionFile << endl;
    }
    
    for (int i = 0; i < cols + 2; i++) {
        if (isTop && i == exitCol + 1) {
            cout << GREEN << 'K' << RESET << "  ";
            solutionFile << 'K' << "  ";
        } else {
            outputBoth(" " "  ");
        }
    }
    outputBoth("\n");
    
    for (int i = 0; i < rows; i++) {
        if (isLeft && i == exitRow) {
            cout << GREEN << 'K' << RESET << "  ";
            solutionFile << 'K' << "  ";
        } else {
            outputBoth(" " "  ");
        }
            
        for (int j = 0; j < cols; j++) {
            char cell = board[i][j];
            if (cell == 'P') {
                cout << RED << cell << RESET << "  ";
                solutionFile << cell << "  ";
            } else if (cell == movedVehicleID) {
                cout << YELLOW << cell << RESET << "  ";
                solutionFile << cell << "  ";
            } else {
                outputBoth(string(1, cell) + "  ");
            }
        }
        
        if (isRight && i == exitRow) {
            cout << GREEN << 'K' << RESET << "  \n";
            solutionFile << 'K' << "  \n";
        } else {
            outputBoth(" \n");
        }
    }
    
    for (int i = 0; i < cols + 2; i++) {
        if (isBottom && i == exitCol + 1) {
            cout << GREEN << 'K' << RESET << "  ";
            solutionFile << 'K' << "  ";
        } else {
            outputBoth(" " "  ");
        }
    }
    outputBoth("\n");
}

string getMoveDirection(const unordered_map<char, Vehicle>& vehicles, char ID, int move) {
    auto direction = vehicles.at(ID).getOrientation();
    if (direction == HORIZONTAL) {
        if (move < 0) return "left";
        else return "right";
    } else {
        if (move < 0) return "up";
        else return "down";
    }
}

ofstream solutionFile;

void initSolutionFile(const string& configPath) {
    filesystem::create_directories("test/solutions");
    string filename = filesystem::path(configPath).filename().string();
    solutionFile.open("test/solutions/" + filename);
}

void outputBoth(const string& text) {
    cout << text;
    if (solutionFile.is_open()) {
        solutionFile << text;
    }
}
