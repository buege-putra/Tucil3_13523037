#ifndef __TXT_PARSER_HPP__
#define __TXT_PARSER_HPP__

#include "../game/BoardState.hpp"
#include "../game/BoardConfig.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

BoardState parseConfig(const string& filename);

#endif