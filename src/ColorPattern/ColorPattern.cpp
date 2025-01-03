#include "ColorPattern.hpp"


ColorPattern::ColorPattern(const std::string& colors)
{
    m_CubeSize = static_cast<uint32_t>(colors.size() / 4);
    m_Colors.reserve(colors.size());
    for (const char& color : colors)
    {
        switch (color)
        {
        case 'W':
            m_Colors.push_back(FaceColor::White);
            break;
        case 'Y':
            m_Colors.push_back(FaceColor::Yellow);
            break;
        case 'R':
            m_Colors.push_back(FaceColor::Red);
            break;
        case 'O':
            m_Colors.push_back(FaceColor::Orange);
            break;
        case 'G':
            m_Colors.push_back(FaceColor::Green);
            break;
        case 'B':
            m_Colors.push_back(FaceColor::Blue);
            break;
        default:
            m_Colors.push_back(FaceColor::None);
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

auto ColorPattern::CreateFromTopLayer(const Cube& cube) -> ColorPattern
{
    std::vector<FaceColor> colors;
    uint32_t size = cube.GetSize();
    colors.reserve(size * 4);

    // front face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ i, size - 1, size - 1 }).value().get()[Face::Front]);

    // right face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1, size - 1, size - 1 - i }).value().get()[Face::Right]);

    // back face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1 - i, size - 1, 0 }).value().get()[Face::Back]);

    // left face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ 0, size - 1, i }).value().get()[Face::Left]);

    return ColorPattern(colors);
}

auto ColorPattern::CreateFromTopLayerWithBaseColor(const Cube& cube, FaceColor baseColor) -> ColorPattern
{
    std::vector<FaceColor> colors;
    uint32_t size = cube.GetSize();
    colors.reserve(size * 4);

    // front face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ i, size - 1, size - 1 }).value().get()[Face::Front] == baseColor ? baseColor : FaceColor::None);

    // right face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1, size - 1, size - 1 - i }).value().get()[Face::Right] == baseColor ? baseColor : FaceColor::None);

    // back face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ size - 1 - i, size - 1, 0 }).value().get()[Face::Back] == baseColor ? baseColor : FaceColor::None);

    // left face
    for (uint32_t i = 0; i < size; i++)
        colors.push_back(cube.GetPieceColors({ 0, size - 1, i }).value().get()[Face::Left] == baseColor ? baseColor : FaceColor::None);

    return ColorPattern(colors);
}