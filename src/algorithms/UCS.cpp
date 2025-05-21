#include "UCS.hpp"

vector<UCSNode*> UCS::getNextStates(UCSNode* current) {
    vector<UCSNode*> nextStates;

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
            
            UCSNode* child = new UCSNode(
                BoardState(newVehicles),
                current->cost + calculateNextCost(maxMove, move),
                current,
                {id, move}
            );

            nextStates.push_back(child);
        }
    }
    
    return nextStates;
}

UCSNode* UCS::createStartNode(const BoardState& initial) {
    return new UCSNode(initial, 0, nullptr, {'\0', 0});
}
