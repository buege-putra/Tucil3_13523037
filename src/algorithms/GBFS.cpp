#include "GBFS.hpp"

vector<GBFSNode*> GBFS::getNextStates(GBFSNode* current) {
    vector<GBFSNode*> nextStates;

    const auto& vehicles = current->state.getVehicles();
    for (const auto& [id, vehicle] : vehicles) {
        int maxMove = vehicle.getOrientation() == HORIZONTAL ? 
            BoardState::dimension.second - vehicle.getLength() :
            BoardState::dimension.first - vehicle.getLength();

        for (int move = -maxMove; move <= maxMove; ++move) {
            if (move == 0) continue;
            
            Vehicle moved = vehicle.moved(move, current->state.getBoard());
            if (moved == vehicle) continue;

            auto newVehicles = vehicles;
            newVehicles[id] = moved;
            BoardState nextState(newVehicles);
            
            GBFSNode* child = new GBFSNode(
                nextState,
                calculateBlockingHeuristic(nextState),
                current,
                {id, move}
            );

            nextStates.push_back(child);
        }
    }
    
    return nextStates;
}

GBFSNode* GBFS::createStartNode(const BoardState& initial) {
    return new GBFSNode(initial, calculateBlockingHeuristic(initial), nullptr, {'\0', 0});
}
