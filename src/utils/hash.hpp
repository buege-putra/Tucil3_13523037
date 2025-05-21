#ifndef __HASH_HPP__
#define __HASH_HPP__

#include <functional>
#include "../game/BoardState.hpp"

namespace std {
    template<>
    struct hash<Vehicle> {
        size_t operator()(const Vehicle& v) const {
            const size_t prime = 0x9e3779cd;
            size_t seed = hash<char>()(v.getID());
            seed ^= hash<int>()(v.getRow()) + prime + (seed << 6) + (seed >> 2);
            seed ^= hash<int>()(v.getCol()) + prime + (seed << 6) + (seed >> 2);
            seed ^= hash<int>()(v.getLength()) + prime + (seed << 6) + (seed >> 2);
            seed ^= hash<bool>()(v.getOrientation() == HORIZONTAL) + prime + (seed << 6) + (seed >> 2);
            return seed;
        }
    };

    template<>
    struct hash<BoardState> {
        size_t operator()(const BoardState& state) const {
            const size_t prime = 0x9e3779cd;
            size_t seed = 0;
            for (const auto& [id, v] : state.getVehicles()) {
                size_t vehicle_hash = hash<Vehicle>()(v);
                seed ^= vehicle_hash + prime + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
}

#endif