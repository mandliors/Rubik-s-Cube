#ifndef TURN_H
#define TURN_H

#include "Direction/Direction.hpp"

#include <memory>

struct Turn
{
    Direction LayerType;
    uint32_t LayerIndex;
    bool Clockwise;
};

#endif