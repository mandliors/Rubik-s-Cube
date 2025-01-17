#include "ColorPattern.hpp"


ColorPattern::ColorPattern(const std::string& colors)
{
    m_CubeSize = static_cast<uint32_t>(colors.size() / 4);
    m_Colors.reserve(colors.size());
    for (const char& color : colors)
    {
        switch (color)
        {
        case 'D':
            m_Colors.push_back(ColorDescriptor::DONT_CARE);
            break;
        case 'B':
            m_Colors.push_back(ColorDescriptor::BASE_COLOR);
            break;
        case 'S':
            m_Colors.push_back(ColorDescriptor::SAME);
            break;
        case 'L':
            m_Colors.push_back(ColorDescriptor::LEFT_NEIGHBOR);
            break;
        case 'R':
            m_Colors.push_back(ColorDescriptor::RIGHT_NEIGHBOR);
            break;
        case 'O':
            m_Colors.push_back(ColorDescriptor::OPPOSITE);
            break;
        }
    }
}

auto ColorPattern::Match(const ColorPattern& other) const -> uint32_t
{
    if (m_CubeSize != other.GetCubeSize())
        return false;

    // check of the patterns match in any of the 4 rotations
    bool match;
    int idx;
    for (uint32_t i = 0; i < 4; i++)
    {
        match = true;
        for (uint32_t j = 0; j < m_Colors.size(); j++)
        {
            idx = (m_CubeSize * i + j) % m_Colors.size();
            if (m_Colors[j] != other.GetColors()[idx])
            {
                match = false;
                break;
            }
        }
        // return how many rotations are needed to match the pattern
        if (match)
            return i;
    }

    // they don't match
    return 5;
}

auto ColorPattern::CreateOLLPatternFromTopLayer(const Cube& cube, FaceColor OLLColor) -> ColorPattern
{
    std::vector<ColorDescriptor> colors;
    uint32_t size = cube.GetSize();
    colors.reserve(size * 4);

    // front face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ i, size - 1, size - 1 }).value().get()[Face::Front] == OLLColor ? ColorDescriptor::BASE_COLOR : ColorDescriptor::DONT_CARE);

    // right face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1, size - 1, size - 1 - i }).value().get()[Face::Right] == OLLColor ? ColorDescriptor::BASE_COLOR : ColorDescriptor::DONT_CARE);

    // back face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1 - i, size - 1, 0 }).value().get()[Face::Back] == OLLColor ? ColorDescriptor::BASE_COLOR : ColorDescriptor::DONT_CARE);

    // left face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ 0, size - 1, i }).value().get()[Face::Left] == OLLColor ? ColorDescriptor::BASE_COLOR : ColorDescriptor::DONT_CARE);

    return ColorPattern{ colors };
}

auto ColorPattern::CreatePLLPatternFromTopLayer(const Cube& cube) -> ColorPattern
{
    std::vector<ColorDescriptor> colors;
    uint32_t size = cube.GetSize();
    colors.reserve(size * 4);

    // front face
    colors.push_back(
        CreateDescriptorFromTwoColors(
            cube.GetPieceColors({ 0, size - 1, size - 1 }).value().get()[Face::Left],
            cube.GetPieceColors({ 0, size - 1, size - 1 }).value().get()[Face::Front]
        )
    );
    for (uint32_t i = 1; i < size; i++)
    {
        colors.push_back(
            CreateDescriptorFromTwoColors(
                cube.GetPieceColors({ i - 1, size - 1, size - 1 }).value().get()[Face::Front],
                cube.GetPieceColors({ i    , size - 1, size - 1 }).value().get()[Face::Front]
            )
        );
    }

    // right face
    colors.push_back(
        CreateDescriptorFromTwoColors(
            cube.GetPieceColors({ size - 1, size - 1, size - 1 }).value().get()[Face::Front],
            cube.GetPieceColors({ size - 1, size - 1, size - 1 }).value().get()[Face::Right]
        )
    );
    for (uint32_t i = 1; i < size; i++)
    {
        colors.push_back(
            CreateDescriptorFromTwoColors(
                cube.GetPieceColors({ size - 1, size - 1, size - 1 - i + 1 }).value().get()[Face::Right],
                cube.GetPieceColors({ size - 1, size - 1, size - 1 - i     }).value().get()[Face::Right]
            )
        );
    }

    // back face
    colors.push_back(
        CreateDescriptorFromTwoColors(
            cube.GetPieceColors({ size - 1, size - 1, 0 }).value().get()[Face::Right],
            cube.GetPieceColors({ size - 1, size - 1, 0 }).value().get()[Face::Back]
        )
    );
    for (uint32_t i = 1; i < size; i++)
    {
        colors.push_back(
            CreateDescriptorFromTwoColors(
                cube.GetPieceColors({ size - 1 - i + 1, size - 1, 0 }).value().get()[Face::Back],
                cube.GetPieceColors({ size - 1 - i    , size - 1, 0 }).value().get()[Face::Back]
            )
        );
    }

    // left face
    colors.push_back(
        CreateDescriptorFromTwoColors(
            cube.GetPieceColors({ 0, size - 1, 0 }).value().get()[Face::Back],
            cube.GetPieceColors({ 0, size - 1, 0 }).value().get()[Face::Left]
        )
    );
    for (uint32_t i = 1; i < size; i++)
    {
        colors.push_back(
            CreateDescriptorFromTwoColors(
                cube.GetPieceColors({ 0, size - 1, i - 1 }).value().get()[Face::Left],
                cube.GetPieceColors({ 0, size - 1, i     }).value().get()[Face::Left]
            )
        );
    }

    return ColorPattern{ colors };
}

auto ColorPattern::CreateDescriptorFromTwoColors(FaceColor left, FaceColor right) -> ColorDescriptor
{
    switch (left)
    {
    case FaceColor::Green:
        switch (right)
        {
        case FaceColor::Green:
            return ColorDescriptor::SAME;
        case FaceColor::Red:
            return ColorDescriptor::RIGHT_NEIGHBOR;
        case FaceColor::Blue:
            return ColorDescriptor::OPPOSITE;
        case FaceColor::Orange:
            return ColorDescriptor::LEFT_NEIGHBOR;
        
        default:
            return ColorDescriptor::DONT_CARE;
        }
        break;

    case FaceColor::Red:
        switch (right)
        {
        case FaceColor::Green:
            return ColorDescriptor::LEFT_NEIGHBOR;
        case FaceColor::Red:
            return ColorDescriptor::SAME;
        case FaceColor::Blue:
            return ColorDescriptor::RIGHT_NEIGHBOR;
        case FaceColor::Orange:
            return ColorDescriptor::OPPOSITE;
        
        default:
            return ColorDescriptor::DONT_CARE;
        }
        break;

    case FaceColor::Blue:
        switch (right)
        {
        case FaceColor::Green:
            return ColorDescriptor::OPPOSITE;
        case FaceColor::Red:
            return ColorDescriptor::LEFT_NEIGHBOR;
        case FaceColor::Blue:
            return ColorDescriptor::SAME;
        case FaceColor::Orange:
            return ColorDescriptor::RIGHT_NEIGHBOR;
        
        default:
            return ColorDescriptor::DONT_CARE;
        }
        break;

    case FaceColor::Orange:
        switch (right)
        {
        case FaceColor::Green:
            return ColorDescriptor::RIGHT_NEIGHBOR;
        case FaceColor::Red:
            return ColorDescriptor::OPPOSITE;
        case FaceColor::Blue:
            return ColorDescriptor::LEFT_NEIGHBOR;
        case FaceColor::Orange:
            return ColorDescriptor::SAME;
        
        default:
            return ColorDescriptor::DONT_CARE;
        }
        break;

    case FaceColor::White:
    case FaceColor::Yellow:
    case FaceColor::None:
        return ColorDescriptor::DONT_CARE;
    }

    std::unreachable();
}