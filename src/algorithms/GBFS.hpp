#ifndef __GBFS_HPP__
#define __GBFS_HPP__

#include "Search.hpp"
#include "SearchNodes.hpp"

class GBFS : public Search<GBFSNode> {
protected:
    vector<GBFSNode*> getNextStates(GBFSNode* current) override;
    GBFSNode* createStartNode(const BoardState& initial) override;
};

#endif
