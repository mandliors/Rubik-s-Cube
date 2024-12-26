#include "Piece.hpp"

#include <raylib.h>

Piece::Piece(const Vector3& position, float size)
    : m_Position(position), m_Size(size)
{
    const float halfSize = 0.5 * size;

    m_Vertices[(int)PieceVertex::LBB] = { position.x - halfSize, position.y - halfSize, position.z - halfSize };
    m_Vertices[(int)PieceVertex::RBB] = { position.x + halfSize, position.y - halfSize, position.z - halfSize };
    m_Vertices[(int)PieceVertex::RTB] = { position.x + halfSize, position.y + halfSize, position.z - halfSize };
    m_Vertices[(int)PieceVertex::LTB] = { position.x - halfSize, position.y + halfSize, position.z - halfSize };
    m_Vertices[(int)PieceVertex::LBF] = { position.x - halfSize, position.y - halfSize, position.z + halfSize };
    m_Vertices[(int)PieceVertex::RBF] = { position.x + halfSize, position.y - halfSize, position.z + halfSize };
    m_Vertices[(int)PieceVertex::RTF] = { position.x + halfSize, position.y + halfSize, position.z + halfSize };
    m_Vertices[(int)PieceVertex::LTF] = { position.x - halfSize, position.y + halfSize, position.z + halfSize };

    m_FaceColors[(int)Face::Top]    = FaceColor::Black;
    m_FaceColors[(int)Face::Front]  = FaceColor::Black;
    m_FaceColors[(int)Face::Right]  = FaceColor::Black;
    m_FaceColors[(int)Face::Back]   = FaceColor::Black;
    m_FaceColors[(int)Face::Left]   = FaceColor::Black;
    m_FaceColors[(int)Face::Bottom] = FaceColor::Black;
}

auto Piece::Draw(bool drawBlackFaces) const -> void
{
    // top face
    if (drawBlackFaces || m_FaceColors[(int)Face::Top] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::RTF],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_FaceColors[(int)Face::Top]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::RTB],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_FaceColors[(int)Face::Top]]
        );
    }

    // front face
    if (drawBlackFaces || m_FaceColors[(int)Face::Front] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RTF],
            FaceColors[(int)m_FaceColors[(int)Face::Front]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::RTF],
            m_Vertices[(int)PieceVertex::LTF],
            FaceColors[(int)m_FaceColors[(int)Face::Front]]
        );
    }

    // right face
    if (drawBlackFaces || m_FaceColors[(int)Face::Right] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_FaceColors[(int)Face::Right]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RTB],
            m_Vertices[(int)PieceVertex::RTF],
            FaceColors[(int)m_FaceColors[(int)Face::Right]]
        );
    }


    // back face
    if (drawBlackFaces || m_FaceColors[(int)Face::Back] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_FaceColors[(int)Face::Back]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::LTB],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_FaceColors[(int)Face::Back]]
        );
    }

    // left face
    if (drawBlackFaces || m_FaceColors[(int)Face::Left] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::LTF],
            FaceColors[(int)m_FaceColors[(int)Face::Left]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_FaceColors[(int)Face::Left]]
        );
    }

    // bottom face
    if (drawBlackFaces || m_FaceColors[(int)Face::Bottom] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::RBF],
            FaceColors[(int)m_FaceColors[(int)Face::Bottom]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::LBF],
            FaceColors[(int)m_FaceColors[(int)Face::Bottom]]
        );
    }
}