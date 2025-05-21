#ifndef __UCS_HPP__
#define __UCS_HPP__

#include "Search.hpp"
#include "SearchNodes.hpp"

class UCS : public Search<UCSNode> {
protected:
    vector<UCSNode*> getNextStates(UCSNode* current) override;
    UCSNode* createStartNode(const BoardState& initial) override;
};

#endif
