#ifndef CUBE_H
#define CUBE_H

#include "Piece/Piece.hpp"

#include <raylib.h>

#include <memory>
#include <vector>
#include <optional>

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
    
    inline auto TurnU(bool prime) -> void { TurnSide(Cube::LayerType::Horizontal, m_Layers - 1, !prime); }
    inline auto TurnF(bool prime) -> void { TurnSide(Cube::LayerType::Depthical, m_Layers - 1, !prime); }
    inline auto TurnR(bool prime) -> void { TurnSide(Cube::LayerType::Vertical, m_Layers - 1, !prime); }
    inline auto TurnB(bool prime) -> void { TurnSide(Cube::LayerType::Depthical, 0, prime); }
    inline auto TurnL(bool prime) -> void { TurnSide(Cube::LayerType::Vertical, 0, prime); }
    inline auto TurnD(bool prime) -> void { TurnSide(Cube::LayerType::Horizontal, 0, prime); }
    inline auto TurnM(bool prime) -> void 
    {
        if (m_Layers % 2 == 0)
            return;

        for (uint32_t x = 1; x < m_Layers - 1; x++)
            TurnSide(Cube::LayerType::Vertical, x, !prime);
    }

    inline auto GetSize() -> uint32_t { return m_Layers; }
    
    auto Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>;
    auto Get(uint32_t x, uint32_t y, uint32_t z) const -> std::optional<std::reference_wrapper<const Piece>>;
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