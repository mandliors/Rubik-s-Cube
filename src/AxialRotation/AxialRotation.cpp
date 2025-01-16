#include "AxialRotation.hpp"

#include "Cube/Cube.hpp"

#include <utility>

auto AxialRotation::Update(float rotation) -> bool
{
    if (!m_Cube.has_value())
        return false;

    bool isDone = false;

    m_CurrentRotation += rotation;
    if (m_CurrentRotation >= PI / 2.0f)
    {
        m_CurrentRotation = PI / 2.0f;
        isDone = true;
    }

    for (auto& turn : m_Turns)
        for (auto& piece : m_Cube.value().get()._GetPiecesByIndices(m_Cube.value().get()._GetIndicesByTurn(turn)))
            piece.get().SetRotation(_GetRotationVector(turn), isDone);

    return isDone;
}

auto AxialRotation::_GetRotationVector(const Turn& turn) const -> Vector3
{
    switch (turn.LayerType)
    {
    case Direction::Horizontal:
        return Vector3 { 0.0f, (-2 * turn.Clockwise + 1) * m_CurrentRotation, 0.0f };
    case Direction::Vertical:
        return Vector3 { (-2 * turn.Clockwise + 1) * m_CurrentRotation, 0.0f, 0.0f };
    case Direction::Depthical:
        return Vector3 { 0.0f, 0.0f, (-2 * turn.Clockwise + 1) * m_CurrentRotation };
    }

    std::unreachable();
}