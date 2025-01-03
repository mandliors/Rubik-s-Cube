#ifndef PIECE_H
#define PIECE_H

#include "Face/Face.hpp"
#include "Face/FaceColor.hpp"
#include "Piece/PieceColors.hpp"
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

    inline auto SetFaceColor(Face face, FaceColor color) -> void { m_Colors[face] = color; }

    auto SetRotation(Vector3 rotation, bool isDone) -> void;
    auto Draw(bool drawBlackFaces = true) const -> void;

private:
    std::array<Vector3, 8> m_Vertices;
    PieceColors m_Colors;

    bool m_Rotating;
    Vector3 m_CurrentRotation;
    Matrix m_RotationMatrix;
};

#endif