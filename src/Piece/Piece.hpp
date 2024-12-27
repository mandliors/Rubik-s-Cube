#ifndef PIECE_H
#define PIECE_H

#include "Face/Face.hpp"
#include "Face/FaceColor.hpp"

#include <raylib.h>
#include <raymath.h>

#include <array>

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

    inline auto SetFaceColor(Face face, FaceColor color) -> void
    {
        m_FaceColors[(int)face] = color;
    }

    inline auto GetPosition() const -> Vector3
    {
        Vector3 avaragePosition = Vector3{ 0, 0, 0 };
        for (const auto& vertex : m_Vertices)
            avaragePosition += vertex;
        avaragePosition /= 8;
        return avaragePosition;
    }

    auto Rotate(const Vector3& axis, float angle) -> void;
    auto Draw(bool drawBlackFaces = false) const -> void;

private:
    float m_Size;

    std::array<Vector3, 8> m_Vertices;
    std::array<FaceColor, 6> m_FaceColors;
};

#endif