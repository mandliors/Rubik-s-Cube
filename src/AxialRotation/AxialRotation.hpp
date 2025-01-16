#ifndef AXIALROTATION_H
#define AXIALROTATION_H

#include "Piece/Piece.hpp"
#include "Direction/Direction.hpp"
#include "Turn/Turn.hpp"

#include <raylib.h>

#include <vector>
#include <optional>

class Cube;

class AxialRotation
{
public:
    AxialRotation(Cube& cube, const std::vector<Turn>& turns)
        : m_Cube(cube), m_Turns(turns) { m_CurrentRotation = 0.0f; }

    inline auto GetTurns() const -> const std::vector<Turn>& { return m_Turns; }

    auto Update(float rotation) -> bool;

private:
    auto _GetRotationVector(const Turn& turn) const -> Vector3;

private:
    std::optional<std::reference_wrapper<Cube>> m_Cube;
    std::vector<Turn> m_Turns;
    float m_CurrentRotation;
};

#endif