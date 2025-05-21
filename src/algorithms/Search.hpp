#ifndef __SEARCH_HPP__
#define __SEARCH_HPP__

#include <algorithm>
#include <queue>
#include <unordered_set>
#include <vector>
#include "../game/BoardState.hpp"
#include "../utils/hash.hpp"

template<typename NodeType>
class Search {
protected:
    int nodesVisited = 0;
    vector<NodeType*> allNodes;
    priority_queue<NodeType*, vector<NodeType*>, typename NodeType::Compare> queue;
    unordered_set<BoardState> explored;

    vector<pair<char, int>> reconstructPath(NodeType* goal) {
        vector<pair<char, int>> path;
        NodeType* n = goal;
        while (n->parent != nullptr) {
            path.push_back(n->move);
            n = n->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void cleanupQueue(priority_queue<NodeType*, vector<NodeType*>, typename NodeType::Compare>& queue) {
        while (!queue.empty()) {
            delete queue.top();
            queue.pop();
        }
    }

    virtual vector<NodeType*> getNextStates(NodeType* current) = 0;
    virtual NodeType* createStartNode(const BoardState& initial) = 0;
    
public:
    int getNodesVisited() const { return nodesVisited; }

    vector<pair<char, int>> solve(const BoardState& initial) {
        NodeType* start = createStartNode(initial);
        queue.push(start);
        allNodes.push_back(start);

        while (!queue.empty()) {
            nodesVisited++;
            NodeType* current = queue.top();
            queue.pop();

            if (explored.find(current->state) != explored.end()) {
                continue;
            }

            explored.insert(current->state);

            if (current->state.isGoal()) {
                return reconstructPath(current);
            }

            vector<NodeType*> children = getNextStates(current);
            for (auto nextState : children) {
                if (explored.find(nextState->state) != explored.end()) {
                    delete nextState;
                    continue;
                }
                queue.push(nextState);
                allNodes.push_back(nextState);
            }
        }
        return {};
    }

    virtual ~Search() {
        for (auto node : allNodes) {
            delete node;
        }
    }
};

#endif
