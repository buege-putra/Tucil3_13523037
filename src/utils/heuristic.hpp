#ifndef __HEURISTIC_HPP__
#define __HEURISTIC_HPP__

#include "../game/BoardState.hpp"
#include <unordered_set>

int calculateNextCost(int maxMove, int move);
int calculateBlockingHeuristic(const BoardState& state);

#endif
