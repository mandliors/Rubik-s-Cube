#include "PieceColors.hpp"

std::array<std::array<std::array<Face, 2>, 3>, 6> PieceColors::s_FaceTransitionTensor = {{
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

PieceColors::PieceColors()
    : m_Colors({ FaceColor::None, FaceColor::None, FaceColor::None, FaceColor::None, FaceColor::None, FaceColor::None }) { }

auto PieceColors::HandleRotation(Direction direction, bool clockwise) -> void
{
    // rotate the face colors
    std::array<FaceColor, 6> newColors;
    for (int i = 0; i < 6; i++)
    {
        Face face = s_FaceTransitionTensor[i][std::to_underlying(direction)][clockwise ? 0 : 1];
        newColors[std::to_underlying(face)] = m_Colors[i];
    }
    m_Colors = newColors;
}