#include <iostream>
#include <fstream>
#include <chrono>
#include "game/BoardState.hpp"
#include "algorithms/UCS.hpp"
#include "algorithms/GBFS.hpp"
#include "algorithms/AStar.hpp"
#include "utils/output.hpp"
#include "utils/txt_parser.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <config_file>" << endl;
        return 1;
    }

    BoardState initial;
    try {
        initial = parseConfig(argv[1]);
        initSolutionFile(argv[1]);
        outputBoth("\n");
    } catch (const exception& e) {
        cout << e.what() << endl << endl;
        return 1;
    }

    outputBoth("Choose algorithm:\n");
    outputBoth("1. UCS (Uniform Cost Search)\n");
    outputBoth("2. GBFS (Greedy Best-First Search)\n");
    outputBoth("3. A* Search\n");

    int choice;
    do {
        cout << "Choice: ";
        cin >> choice;
        solutionFile << "Choice: " << choice << "\n";
        if (choice < 1 || choice > 3) {
            cout << "Invalid choice. Please try again." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (choice < 1 || choice > 3);
    
    outputBoth("\nInitial board:\n");
    printColoredBoard(initial);
    outputBoth("\n");

    system_clock::time_point start, end;
    vector<pair<char, int>> solution;
    int nodesVisited;

    UCS ucs;
    GBFS gbfs;
    AStar astar;

    if (choice == 1) {
        start = high_resolution_clock::now();
        solution = ucs.solve(initial);
        end = high_resolution_clock::now();
        nodesVisited = ucs.getNodesVisited();
    } else if (choice == 2) {
        start = high_resolution_clock::now();
        solution = gbfs.solve(initial);
        end = high_resolution_clock::now();
        nodesVisited = gbfs.getNodesVisited();
    } else {
        start = high_resolution_clock::now();
        solution = astar.solve(initial);
        end = high_resolution_clock::now();
        nodesVisited = astar.getNodesVisited();
    }

    if (solution.empty()) {
        outputBoth("No solution found :(\n");
        return 0;
    }

    // Replay solution
    BoardState current = initial;
    auto vehicles = current.getVehicles();

    for (size_t i = 0; i < solution.size(); i++) {
        const auto& [ID, move] = solution[i];
        outputBoth("Move " + to_string(i+1) + ": " + ID + "-" + 
                  getMoveDirection(vehicles, ID, move) + "\n");
        
        if (i == solution.size() - 1) vehicles.erase(playerID);
        else vehicles[ID] = vehicles[ID].moved(move, current.getBoard());
        current = BoardState(vehicles);
        
        printColoredBoard(current, ID);
        outputBoth("\n");
    }

    auto duration = duration_cast<milliseconds>(end - start);
    outputBoth("Nodes visited: " + to_string(nodesVisited) + "\n");
    outputBoth("Execution time: " + to_string(duration.count()) + "ms\n");

    solutionFile.close();
    return 0;
}