#ifndef PIECE_H
#define PIECE_H

#include "Face/Face.hpp"
#include "Face/FaceColor.hpp"
#include "Direction/Direction.hpp"

#include <raylib.h>
#include <raymath.h>

#include <array>
#include <memory>

class Piece
{
public:
    enum class PieceVertex /* (L)eft/(R)ight ; (B)ottom/(T)op ; (F)ront/(B)ack*/
    {
        LBB = 0,
        RBB,
        RTB,
        LTB,
        LBF,
        RBF,
        RTF,
        LTF
    };    

public:
    Piece(const Vector3& position, float size);

    inline auto SetFaceColor(Face face, FaceColor color, bool startingFaceToo = false) -> void
    {
        m_CurrentFaceColors[(int)face] = color;
        if (startingFaceToo)
            m_StartingFaceColors[(int)face] = color;
    }
    
    inline auto GetFaceByColor(FaceColor color, bool current = true) const -> Face
    {
        for (uint32_t i = 0; i < m_StartingFaceColors.size(); i++)
        {
            if (current && m_CurrentFaceColors[i] == color)
                return (Face)i;
            else if (!current && m_StartingFaceColors[i] == color)
                return (Face)i;
        }

        return Face::None;
    }
    auto GetPosition() const -> Vector3;

    auto Rotate(Direction direction, bool clockwise) -> void;
    auto Draw(bool drawBlackFaces = false) const -> void;

private:
    static std::array<std::array<std::array<Face, 2>, 3>, 6> faceTransitionTensor;

private:
    float m_Size;

    std::array<Vector3, 8> m_Vertices;
    std::array<FaceColor, 6> m_StartingFaceColors;
    std::array<FaceColor, 6> m_CurrentFaceColors;
};

#endif