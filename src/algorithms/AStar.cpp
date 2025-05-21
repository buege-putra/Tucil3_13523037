#include "AStar.hpp"

vector<AStarNode*> AStar::getNextStates(AStarNode* current) {
    vector<AStarNode*> nextStates;

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
            
            AStarNode* child = new AStarNode(
                nextState,
                current->cost + calculateNextCost(maxMove, move),
                calculateBlockingHeuristic(nextState),
                current,
                {id, move}
            );

            nextStates.push_back(child);
        }
    }
    
    return nextStates;
}

AStarNode* AStar::createStartNode(const BoardState& initial) {
    return new AStarNode(initial, 0, calculateBlockingHeuristic(initial), nullptr, {'\0', 0});
}
