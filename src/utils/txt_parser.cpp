#include "txt_parser.hpp"

BoardState parseConfig(const string& filename) {
    cout << "\nLoading " << filename << " ..." << endl;

    // open file
    ifstream configFile(filename);
    if (!configFile.is_open()) throw runtime_error("Cannot open " + filename);

    // take rows and cols
    int rows, cols;
    configFile >> rows >> cols;

    if (rows <= 0 || cols <= 0 || rows * cols < 2) {
        throw runtime_error("Invalid board dimension.\nBoard dimension must be at least 2x1 or 1x2.");
    }

    // take num of pieces
    int numPieces;
    configFile >> numPieces;

    vector<string> board;
    string line;
    while (getline(configFile, line)) {
        if (line == "" || line == "\r") continue;
        board.emplace_back(line);
    }

    unordered_map<char, vector<pair<int, int>>> positions;
    pair<int, int> exitCoord(-2, -2);
    pair<int, int> topLeft, bottomRight;
    bool hasTopLeft = false;

    // take positions data
    for (size_t r = 0; r < board.size(); ++r) {
        for (size_t c = 0; c < board[r].size(); ++c) {
            char ch = board[r][c];

            if (ch == 'K') {
                exitCoord = {r, c};
                continue;
            }

            if (!('A' <= ch && ch <= 'Z') && ch != '.') {
                continue;
            }

            if (hasTopLeft) {
                bottomRight = {static_cast<int>(r), static_cast<int>(c)};
            } else {
                topLeft = {static_cast<int>(r), static_cast<int>(c)};
                hasTopLeft = true;
            }

            if (ch != '.') {
                positions[ch].emplace_back(r, c);
            }
        }
    }

    if (bottomRight.first - topLeft.first + 1 != rows || bottomRight.second - topLeft.second + 1 != cols) {
        throw runtime_error("The board dimension does not match the stated number.");
    }

    if (exitCoord.first == -2 && exitCoord.second == -2) {
        throw runtime_error("There is no exit on the board.");
    }

    // calculate offset caused by exit (if on top or left)
    pair<int, int> exitOffset(0, 0);

    if (exitCoord.first == 0 && static_cast<size_t>(rows) < board.size()) { // top
        exitOffset = {-1, 0};
        exitCoord.first -= 1;
    } else if (exitCoord.second == 0 && static_cast<size_t>(rows) == board.size()) { // left
        exitOffset = {0, -1};
        exitCoord.second -= 1;
    }

    // process position data into vehicles
    unordered_map<char, Vehicle> vehicles;

    for (const auto& [id, cells] : positions) {
        int r0 = cells[0].first, c0 = cells[0].second;
        int length = cells.size();
        Orientation orientation = HORIZONTAL;
        if (cells[1].first != r0) orientation = VERTICAL;

        vehicles[id] = Vehicle(id, r0 + exitOffset.first, c0 + exitOffset.second, length, orientation);
    }

    if (static_cast<size_t>(numPieces) != vehicles.size() - 1) {
        throw runtime_error(string("The number of pieces on the board does not match the stated number. Found ") + to_string(vehicles.size() - 1) + " pieces.");
    }

    if (vehicles.find('P') == vehicles.end()) {
        throw runtime_error("There is no primary piece on the board.");
    }

    if (exitCoord.first != vehicles[playerID].getRow() && exitCoord.second != vehicles[playerID].getCol()) {
        throw runtime_error("Impossible board. Primary piece is not aligned with exit cell.");
    }

    // set config and return
    BoardConfig::dimension = {rows, cols};
    BoardConfig::exitCoord = exitCoord;

    return BoardState(vehicles);
}