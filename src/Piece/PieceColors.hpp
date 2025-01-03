#ifndef PIECECOLORS_H
#define PIECECOLORS_H

#include "Face/Face.hpp"
#include "Face/FaceColor.hpp"
#include "Direction/Direction.hpp"

#include <array>
#include <memory>
#include <utility>

class PieceColors
{
public:
    PieceColors();
    explicit PieceColors(const std::array<FaceColor, 6>& colors)
        : m_Colors(colors) { }

    inline auto operator[](Face face) -> FaceColor& { return m_Colors[std::to_underlying(face)]; }
    inline auto operator[](Face face) const -> const FaceColor& { return m_Colors[std::to_underlying(face)]; }

    inline auto GetColors() const -> const std::array<FaceColor, 6>& { return m_Colors; }    
    inline auto GetFaceByColor(FaceColor color) const -> Face
    {
        for (uint32_t i = 0; i < m_Colors.size(); i++)
            if (m_Colors[i] == color)
                return (Face)i;

        return Face::None;
    }

    auto HandleRotation(Direction direction, bool clockwise) -> void;

private:
    static std::array<std::array<std::array<Face, 2>, 3>, 6> s_FaceTransitionTensor;

private:
    std::array<FaceColor, 6> m_Colors;
};

#endif