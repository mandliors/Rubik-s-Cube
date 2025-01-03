#ifndef AXIALROTATION_H
#define AXIALROTATION_H

#include "Piece/Piece.hpp"
#include "Direction/Direction.hpp"
#include "Turn/Turn.hpp"

#include <raylib.h>

#include <utility>
#include <vector>

class AxialRotation
{
public:
    explicit AxialRotation() = default;
    AxialRotation(const Turn& turn)
        : m_Turn(turn), m_CurrentRotation(0.0f) { }

    inline auto GetTurn() const -> const Turn& { return m_Turn; }
    inline auto GetRotationVector() const -> Vector3
    {
        switch (m_Turn.LayerType)
        {
        case Direction::Horizontal:
            return Vector3 { 0.0f, (-2 * m_Turn.Clockwise + 1) * m_CurrentRotation, 0.0f };
        case Direction::Vertical:
            return Vector3 { (-2 * m_Turn.Clockwise + 1) * m_CurrentRotation, 0.0f, 0.0f };
        case Direction::Depthical:
            return Vector3 { 0.0f, 0.0f, (-2 * m_Turn.Clockwise + 1) * m_CurrentRotation };
        }

        std::unreachable();
    }

    inline auto Update(float rotation, const std::vector<std::reference_wrapper<Piece>> rotatedPieces) -> bool
    {
        bool isDone = false;
        m_CurrentRotation += rotation;

        if (m_CurrentRotation >= PI / 2.0f)
        {
            m_CurrentRotation = PI / 2.0f;
            isDone = true;
        }
        
        for (auto& piece : rotatedPieces)
            piece.get().SetRotation(GetRotationVector(), isDone);

        return isDone;
    }

private:
    Turn m_Turn;
    float m_CurrentRotation;
};

#endif