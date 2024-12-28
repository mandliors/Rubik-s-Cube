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

    m_Vertices[(int)PieceVertex::LBB] = position + Vector3 { -halfSize, -halfSize, -halfSize };
    m_Vertices[(int)PieceVertex::RBB] = position + Vector3 { +halfSize, -halfSize, -halfSize };
    m_Vertices[(int)PieceVertex::RTB] = position + Vector3 { +halfSize, +halfSize, -halfSize };
    m_Vertices[(int)PieceVertex::LTB] = position + Vector3 { -halfSize, +halfSize, -halfSize };
    m_Vertices[(int)PieceVertex::LBF] = position + Vector3 { -halfSize, -halfSize, +halfSize };
    m_Vertices[(int)PieceVertex::RBF] = position + Vector3 { +halfSize, -halfSize, +halfSize };
    m_Vertices[(int)PieceVertex::RTF] = position + Vector3 { +halfSize, +halfSize, +halfSize };
    m_Vertices[(int)PieceVertex::LTF] = position + Vector3 { -halfSize, +halfSize, +halfSize };

    m_StartingFaceColors[(int)Face::Top]    = m_CurrentFaceColors[(int)Face::Top]    = FaceColor::Black;
    m_StartingFaceColors[(int)Face::Front]  = m_CurrentFaceColors[(int)Face::Front]  = FaceColor::Black;
    m_StartingFaceColors[(int)Face::Right]  = m_CurrentFaceColors[(int)Face::Right]  = FaceColor::Black;
    m_StartingFaceColors[(int)Face::Back]   = m_CurrentFaceColors[(int)Face::Back]   = FaceColor::Black;
    m_StartingFaceColors[(int)Face::Left]   = m_CurrentFaceColors[(int)Face::Left]   = FaceColor::Black;
    m_StartingFaceColors[(int)Face::Bottom] = m_CurrentFaceColors[(int)Face::Bottom] = FaceColor::Black;
}

auto Piece::GetPosition() const -> Vector3
{
    Vector3 avaragePosition = Vector3{ 0, 0, 0 };
    for (const auto& vertex : m_Vertices)
        avaragePosition += vertex;
    avaragePosition /= 8;
    return avaragePosition;
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
        Face face = faceTransitionTensor[i][(int)direction][(int)clockwise ? 0 : 1];
        newFaceColors[(int)face] = m_CurrentFaceColors[i];
    }
    m_CurrentFaceColors = newFaceColors;
}

auto Piece::Draw(bool drawBlackFaces) const -> void
{
    // top face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Top] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::RTF],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Top]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::RTB],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Top]]
        );
    }

    // front face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Front] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RTF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Front]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::RTF],
            m_Vertices[(int)PieceVertex::LTF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Front]]
        );
    }

    // right face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Right] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Right]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::RTB],
            m_Vertices[(int)PieceVertex::RTF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Right]]
        );
    }

    // back face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Back] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Back]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::LTB],
            m_Vertices[(int)PieceVertex::RTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Back]]
        );
    }

    // left face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Left] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LBF],
            m_Vertices[(int)PieceVertex::LTF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Left]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::LTF],
            m_Vertices[(int)PieceVertex::LTB],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Left]]
        );
    }

    // bottom face
    if (drawBlackFaces || m_StartingFaceColors[(int)Face::Bottom] != FaceColor::Black) 
    {
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::RBB],
            m_Vertices[(int)PieceVertex::RBF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Bottom]]
        );
        DrawTriangle3D(
            m_Vertices[(int)PieceVertex::LBB],
            m_Vertices[(int)PieceVertex::RBF],
            m_Vertices[(int)PieceVertex::LBF],
            FaceColors[(int)m_StartingFaceColors[(int)Face::Bottom]]
        );
    }
}