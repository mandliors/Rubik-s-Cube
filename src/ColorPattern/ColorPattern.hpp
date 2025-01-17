#ifndef COLORPATTERN_H
#define COLORPATTERN_H

#include "Cube/Cube.hpp"
#include "Face/FaceColor.hpp"

#include <vector>
#include <memory>

class ColorPattern
{
public:
    enum class ColorDescriptor
    {
        // for OLL patterns
        DONT_CARE = 0,
        BASE_COLOR,

        // for PLL patterns
        SAME,
        LEFT_NEIGHBOR,
        RIGHT_NEIGHBOR,
        OPPOSITE
    };

public:
    explicit ColorPattern(const std::vector<ColorDescriptor>& colors)
        : m_CubeSize(static_cast<uint32_t>(colors.size() / 4)), m_Colors(colors) { }

    explicit ColorPattern(const std::string& colors);

    auto Match(const ColorPattern& other) const -> uint32_t;

    inline auto GetCubeSize() const -> uint32_t { return m_CubeSize; }
    inline auto GetColors() const -> const std::vector<ColorDescriptor>& { return m_Colors; }

public:
    static auto CreateOLLPatternFromTopLayer(const Cube& cube, FaceColor OLLColor) -> ColorPattern;
    static auto CreatePLLPatternFromTopLayer(const Cube& cube) -> ColorPattern;

    static auto CreateDescriptorFromTwoColors(FaceColor left, FaceColor right) -> ColorDescriptor;

private:
    uint32_t m_CubeSize;
    std::vector<ColorDescriptor> m_Colors;
};

#endif