#ifndef __OUTPUT_HPP__
#define __OUTPUT_HPP__

#include "../game/BoardState.hpp"
#include <string>
#include <fstream>

using namespace std;

void printColoredBoard(const BoardState& state, char movedPiece = '\0');
string getMoveDirection(const unordered_map<char, Vehicle>& vehicles, char ID, int move);
extern ofstream solutionFile;
void initSolutionFile(const string& configPath);
void outputBoth(const string& text);

#endif
