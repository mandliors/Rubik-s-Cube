#ifndef ROTATION_H
#define ROTATION_H

#include "Direction/Direction.hpp"

#include <raylib.h>

#include <utility>

class Rotation
{
public:
    Rotation() = default;
    Rotation(Direction direction, bool clockwise)
        : m_Direction(direction), m_Clockwise(clockwise), m_Rotation(0.0f) {}

    inline auto Update(float rotation) -> bool 
    {
        m_Rotation += rotation;
        if (m_Rotation >= PI / 2.0f)
        {
            m_Rotation = PI / 2.0f;
            return true;
        }
        return false;
    }
    inline auto GetRotationVector() const -> Vector3
    {
        switch (m_Direction)
        {
        case Direction::Horizontal:
            return Vector3 { 0.0f, m_Clockwise ? -m_Rotation : m_Rotation, 0.0f };
        case Direction::Vertical:
            return Vector3 { m_Clockwise ? -m_Rotation : m_Rotation, 0.0f, 0.0f };
        case Direction::Depthical:
            return Vector3 { 0.0f, 0.0f, m_Clockwise ? -m_Rotation : m_Rotation };
        }

        std::unreachable();
    }

private:
    Direction m_Direction;
    bool m_Clockwise;
    float m_Rotation;
};

#endif