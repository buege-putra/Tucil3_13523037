#ifndef __SEARCH_UTILS_HPP__
#define __SEARCH_UTILS_HPP__

#include "../game/BoardState.hpp"
#include "../utils/heuristic.hpp"

template<typename T>
struct SearchNode {
    BoardState state;
    T* parent;
    pair<char, int> move;

    SearchNode(BoardState state, T* parent, pair<char, int> move) 
        : state(state), parent(parent), move(move) {}
    virtual ~SearchNode() = default;
};

struct UCSNode : public SearchNode<UCSNode> {
    int cost;
    
    UCSNode(BoardState state, int cost, UCSNode* parent, pair<char, int> move)
        : SearchNode<UCSNode>(state, parent, move), cost(cost) {}

    struct Compare {
        bool operator()(const UCSNode* a, const UCSNode* b) const {
            return a->cost > b->cost;
        }
    };
};

struct GBFSNode : public SearchNode<GBFSNode> {
    int heuristic;
    
    GBFSNode(BoardState state, int heuristic, GBFSNode* parent, pair<char, int> move)
        : SearchNode<GBFSNode>(state, parent, move), heuristic(heuristic) {}

    struct Compare {
        bool operator()(const GBFSNode* a, const GBFSNode* b) const {
            return a->heuristic > b->heuristic;
        }
    };
};

struct AStarNode : public SearchNode<AStarNode> {
    int cost;
    int heuristic;
    
    AStarNode(BoardState state, int cost, int heuristic, AStarNode* parent, pair<char, int> move)
        : SearchNode<AStarNode>(state, parent, move), cost(cost), heuristic(heuristic) {}

    int getF() const { return cost + heuristic; }

    struct Compare {
        bool operator()(const AStarNode* a, const AStarNode* b) const {
            return a->getF() > b->getF();
        }
    };
};

#endif
