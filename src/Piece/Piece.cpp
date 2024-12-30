#include "Piece.hpp"
#include "Direction/Direction.hpp"

#include <raymath.h>

#include <array>

std::array<std::array<std::array<Face, 2>, 3>, 6> Piece::faceTransitionTensor = {{
    //   [Clockwise], [Counterclockwise]    
    // top
    { { { Face::Top,   Face::Top     },     // horizontal
        { Face::Back,  Face::Front   },     // vertical
        { Face::Right, Face::Left    } } }, // depthical
    // front
    { { { Face::Left,  Face::Right   },     // horizontal
        { Face::Top,   Face::Bottom  },     // vertical
        { Face::Front, Face::Front   } } }, // depthical
    // right
    { { { Face::Front, Face::Back    },     // horizontal
        { Face::Right, Face::Right   },     // vertical
        { Face::Bottom, Face::Top    } } }, // depthical
    // back
    { { { Face::Right,  Face::Left   },     // horizontal
        { Face::Bottom, Face::Top    },     // vertical
        { Face::Back,   Face::Back   } } }, // depthical
    // left
    { { { Face::Back, Face::Front    },     // horizontal
        { Face::Left, Face::Left     },     // vertical
        { Face::Top,  Face::Bottom   } } }, // depthical
    // bottom
    { { { Face::Bottom, Face::Bottom },     // horizontal
        { Face::Front,  Face::Back   },     // vertical
        { Face::Left,   Face::Right  } } }  // depthical
}};


Piece::Piece(const Vector3& position, float size)
    : m_Size(size)
{
    const float halfSize = 0.5 * size;

    m_Vertices[static_cast<int>(PieceVertex::LBB)] = position + Vector3 { -halfSize, -halfSize, -halfSize };
    m_Vertices[static_cast<int>(PieceVertex::RBB)] = position + Vector3 { +halfSize, -halfSize, -halfSize };
    m_Vertices[static_cast<int>(PieceVertex::RTB)] = position + Vector3 { +halfSize, +halfSize, -halfSize };
    m_Vertices[static_cast<int>(PieceVertex::LTB)] = position + Vector3 { -halfSize, +halfSize, -halfSize };
    m_Vertices[static_cast<int>(PieceVertex::LBF)] = position + Vector3 { -halfSize, -halfSize, +halfSize };
    m_Vertices[static_cast<int>(PieceVertex::RBF)] = position + Vector3 { +halfSize, -halfSize, +halfSize };
    m_Vertices[static_cast<int>(PieceVertex::RTF)] = position + Vector3 { +halfSize, +halfSize, +halfSize };
    m_Vertices[static_cast<int>(PieceVertex::LTF)] = position + Vector3 { -halfSize, +halfSize, +halfSize };

    m_StartingFaceColors[static_cast<int>(Face::Top)]    = m_CurrentFaceColors[static_cast<int>(Face::Top)]    = FaceColor::NONE;
    m_StartingFaceColors[static_cast<int>(Face::Front)]  = m_CurrentFaceColors[static_cast<int>(Face::Front)]  = FaceColor::NONE;
    m_StartingFaceColors[static_cast<int>(Face::Right)]  = m_CurrentFaceColors[static_cast<int>(Face::Right)]  = FaceColor::NONE;
    m_StartingFaceColors[static_cast<int>(Face::Back)]   = m_CurrentFaceColors[static_cast<int>(Face::Back)]   = FaceColor::NONE;
    m_StartingFaceColors[static_cast<int>(Face::Left)]   = m_CurrentFaceColors[static_cast<int>(Face::Left)]   = FaceColor::NONE;
    m_StartingFaceColors[static_cast<int>(Face::Bottom)] = m_CurrentFaceColors[static_cast<int>(Face::Bottom)] = FaceColor::NONE;
}

auto Piece::Rotate(Direction direction, bool clockwise) -> void
{
    // get the rotation axis
    Vector3 axis;
    switch (direction)
    {
    case Direction::Horizontal:
        axis = Vector3{ 0, 1, 0 };
        break;
    case Direction::Vertical:
        axis = Vector3{ 1, 0, 0 };
        break;
    case Direction::Depthical:
        axis = Vector3{ 0, 0, 1 };
        break;
    }

    // rotate the vertices
    Quaternion rotation = QuaternionFromAxisAngle(axis, clockwise ? -PI / 2 : PI / 2);
    for (int i = 0; i < 8; i++)
    {
        m_Vertices[i] = Vector3RotateByQuaternion(
            m_Vertices[i],
            rotation
        );
    }

    // rotate the face colors
    std::array<FaceColor, 6> newFaceColors;
    for (int i = 0; i < 6; i++)
    {
        Face face = faceTransitionTensor[i][static_cast<int>(direction)][clockwise ? 0 : 1];
        newFaceColors[static_cast<int>(face)] = m_CurrentFaceColors[i];
    }
    m_CurrentFaceColors = newFaceColors;
}

auto Piece::Draw(bool drawBlackFaces) const -> void
{
    // top face
    if (drawBlackFaces || m_StartingFaceColors[static_cast<int>(Face::Top)] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LTF)],
            m_Vertices[static_cast<int>(PieceVertex::RTF)],
            m_Vertices[static_cast<int>(PieceVertex::RTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Top)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LTF)],
            m_Vertices[static_cast<int>(PieceVertex::RTB)],
            m_Vertices[static_cast<int>(PieceVertex::LTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Top)])]
        );
    }

    // front face
    if (drawBlackFaces || m_StartingFaceColors[static_cast<int>(Face::Front)] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBF)],
            m_Vertices[static_cast<int>(PieceVertex::RBF)],
            m_Vertices[static_cast<int>(PieceVertex::RTF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Front)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBF)],
            m_Vertices[static_cast<int>(PieceVertex::RTF)],
            m_Vertices[static_cast<int>(PieceVertex::LTF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Front)])]
        );
    }

    // right face
    if (drawBlackFaces || m_StartingFaceColors[static_cast<int>(Face::Right)] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::RBF)],
            m_Vertices[static_cast<int>(PieceVertex::RBB)],
            m_Vertices[static_cast<int>(PieceVertex::RTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Right)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::RBF)],
            m_Vertices[static_cast<int>(PieceVertex::RTB)],
            m_Vertices[static_cast<int>(PieceVertex::RTF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Right)])]
        );
    }

    // back face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Back] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::RBB)],
            m_Vertices[static_cast<int>(PieceVertex::LBB)],
            m_Vertices[static_cast<int>(PieceVertex::LTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Back)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::RBB)],
            m_Vertices[static_cast<int>(PieceVertex::LTB)],
            m_Vertices[static_cast<int>(PieceVertex::RTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Back)])]
        );
    }

    // left face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Left] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBB)],
            m_Vertices[static_cast<int>(PieceVertex::LBF)],
            m_Vertices[static_cast<int>(PieceVertex::LTF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Left)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBB)],
            m_Vertices[static_cast<int>(PieceVertex::LTF)],
            m_Vertices[static_cast<int>(PieceVertex::LTB)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Left)])]
        );
    }

    // bottom face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Bottom] != FaceColor::NONE) 
    {
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBB)],
            m_Vertices[static_cast<int>(PieceVertex::RBB)],
            m_Vertices[static_cast<int>(PieceVertex::RBF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Bottom)])]
        );
        DrawTriangle3D(
            m_Vertices[static_cast<int>(PieceVertex::LBB)],
            m_Vertices[static_cast<int>(PieceVertex::RBF)],
            m_Vertices[static_cast<int>(PieceVertex::LBF)],
            FaceColors[static_cast<int>(m_StartingFaceColors[static_cast<int>(Face::Bottom)])]
        );
    }
}