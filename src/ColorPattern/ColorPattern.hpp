#ifndef COLORPATTERN_H
#define COLORPATTERN_H

#include "Cube/Cube.hpp"
#include "Face/FaceColor.hpp"

#include <vector>
#include <memory>

class ColorPattern
{
public:
    explicit ColorPattern(const std::vector<FaceColor>& colors)
        : m_CubeSize(static_cast<uint32_t>(colors.size() / 4)), m_Colors(colors) { }

    explicit ColorPattern(const std::string& colors);

    auto Match(const ColorPattern& other) const -> uint32_t;

    inline auto GetCubeSize() const -> uint32_t { return m_CubeSize; }
    inline auto GetColors() const -> const std::vector<FaceColor>& { return m_Colors; }

public:
    static auto CreateFromTopLayer(const Cube& cube) -> ColorPattern;
    static auto CreateFromTopLayerWithBaseColor(const Cube& cube, FaceColor baseColor) -> ColorPattern;

private:
    uint32_t m_CubeSize;
    std::vector<FaceColor> m_Colors;
};

#endif