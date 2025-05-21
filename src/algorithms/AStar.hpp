#ifndef __A_STAR_HPP__
#define __A_STAR_HPP__

#include "Search.hpp"
#include "SearchNodes.hpp"

class AStar : public Search<AStarNode> {
protected:
    vector<AStarNode*> getNextStates(AStarNode* current) override;
    AStarNode* createStartNode(const BoardState& initial) override;
};

#endif
