#ifndef PIECELOCATION_H
#define PIECELOCATION_H

#include <memory>

struct PieceLocation
{
    uint32_t X;
    uint32_t Y;
    uint32_t Z;

    auto operator==(const PieceLocation& other) const -> bool
    {
        return X == other.X && Y == other.Y && Z == other.Z;
    }
};

#endif