#ifndef CUBE_H
#define CUBE_H

#include "Piece/Piece.hpp"

#include <raylib.h>

#include <memory>
#include <vector>
#include <optional>

struct Vector3;

class Cube
{
public:
    enum class LayerType
    {
        Horizontal = 0,
        Vertical,
        Depthical
    };

public:
    Cube(uint32_t layers, const Vector3& position, float size);
    
    auto TurnSide(LayerType layerType, uint32_t layerIndex, bool clockwise) -> void;
    
    auto Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>;
    auto Set(uint32_t x, uint32_t y, uint32_t z, const Piece& piece) -> void;

    auto Draw() const -> void;

private:
    static constexpr float STICKER_SCALE = 0.9f;

private:
    uint32_t m_Layers;
    Vector3 m_Position;
    float m_Size;

    std::vector<Piece> m_Pieces;
};

#endif