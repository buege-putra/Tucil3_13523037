#ifndef __BOARD_CONFIG_HPP__
#define __BOARD_CONFIG_HPP__

#include <utility>
using namespace std;

class BoardConfig {
public:
    static pair<int, int> dimension;  // rows, cols
    static pair<int, int> exitCoord;  // row, col
};

#endif
