#include "Piece.hpp"
#include "Direction/Direction.hpp"

#include <raymath.h>

#include <array>

Piece::Piece(const Vector3& position, float size)
{
    const float halfSize = 0.5f * size;

    m_Vertices[std::to_underlying(PieceVertex::LBB)] = position + Vector3 { -halfSize, -halfSize, -halfSize };
    m_Vertices[std::to_underlying(PieceVertex::RBB)] = position + Vector3 { +halfSize, -halfSize, -halfSize };
    m_Vertices[std::to_underlying(PieceVertex::RTB)] = position + Vector3 { +halfSize, +halfSize, -halfSize };
    m_Vertices[std::to_underlying(PieceVertex::LTB)] = position + Vector3 { -halfSize, +halfSize, -halfSize };
    m_Vertices[std::to_underlying(PieceVertex::LBF)] = position + Vector3 { -halfSize, -halfSize, +halfSize };
    m_Vertices[std::to_underlying(PieceVertex::RBF)] = position + Vector3 { +halfSize, -halfSize, +halfSize };
    m_Vertices[std::to_underlying(PieceVertex::RTF)] = position + Vector3 { +halfSize, +halfSize, +halfSize };
    m_Vertices[std::to_underlying(PieceVertex::LTF)] = position + Vector3 { -halfSize, +halfSize, +halfSize };

    m_Colors[Face::Top]    = FaceColor::None;
    m_Colors[Face::Front]  = FaceColor::None;
    m_Colors[Face::Right]  = FaceColor::None;
    m_Colors[Face::Back]   = FaceColor::None;
    m_Colors[Face::Left]   = FaceColor::None;
    m_Colors[Face::Bottom] = FaceColor::None;

    m_Rotating = false;
    m_RotationMatrix = MatrixIdentity();
}

auto Piece::SetRotation(Vector3 rotation, bool isDone) -> void
{
    m_Rotating = !isDone;
    m_CurrentRotation = rotation;
    
    if (isDone)
    {
        m_RotationMatrix = MatrixMultiply(
            m_RotationMatrix,
            MatrixRotateXYZ(m_CurrentRotation)
        );
    }
}
auto Piece::Draw(bool drawBlackFaces) const -> void
{
    std::array<Vector3, 8> m_TransformedVertices;
    for (int i = 0; i < 8; i++)
    {
        m_TransformedVertices[i] = Vector3Transform(m_Vertices[i], m_RotationMatrix);
        if (m_Rotating)
            m_TransformedVertices[i] = Vector3Transform(m_TransformedVertices[i], MatrixRotateXYZ(m_CurrentRotation));
    }

    // top face
    if (drawBlackFaces || m_Colors[Face::Top] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LTF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Top])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LTF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Top])]
        );
    }

    // front face
    if (drawBlackFaces || m_Colors[Face::Front] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTF)],
            FaceColors[std::to_underlying(m_Colors[Face::Front])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTF)],
            FaceColors[std::to_underlying(m_Colors[Face::Front])]
        );
    }

    // right face
    if (drawBlackFaces || m_Colors[Face::Right] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::RBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Right])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::RBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTF)],
            FaceColors[std::to_underlying(m_Colors[Face::Right])]
        );
    }

    // back face
    if (drawBlackFaces || m_Colors[Face::Back] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::RBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Back])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::RBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Back])]
        );
    }

    // left face
    if (drawBlackFaces || m_Colors[Face::Left] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTF)],
            FaceColors[std::to_underlying(m_Colors[Face::Left])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LTB)],
            FaceColors[std::to_underlying(m_Colors[Face::Left])]
        );
    }

    // bottom face
    if (drawBlackFaces || m_Colors[Face::Bottom] != FaceColor::None) 
    {
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RBF)],
            FaceColors[std::to_underlying(m_Colors[Face::Bottom])]
        );
        DrawTriangle3D(
            m_TransformedVertices[std::to_underlying(PieceVertex::LBB)],
            m_TransformedVertices[std::to_underlying(PieceVertex::RBF)],
            m_TransformedVertices[std::to_underlying(PieceVertex::LBF)],
            FaceColors[std::to_underlying(m_Colors[Face::Bottom])]
        );
    }
}