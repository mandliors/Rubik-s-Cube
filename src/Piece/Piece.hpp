#ifndef PIECE_H
#define PIECE_H

#include "Face/Face.hpp"
#include "Face/FaceColor.hpp"

#include <raylib.h>

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
    auto Draw(bool drawBlackFaces = false) const -> void;

private:
    Vector3 m_Position;
    float m_Size;

    std::array<Vector3, 8> m_Vertices;
    std::array<FaceColor, 6> m_FaceColors;
};

#endif