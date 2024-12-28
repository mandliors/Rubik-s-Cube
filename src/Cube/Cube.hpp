#ifndef CUBE_H
#define CUBE_H

#include "Piece/Piece.hpp"
#include "Direction/Direction.hpp"

#include <raylib.h>

#include <memory>
#include <vector>
#include <optional>

class Cube
{
public:
    Cube(uint32_t layers, const Vector3& position, float size);
    
    auto TurnSide(Direction layerType, uint32_t layerIndex, bool clockwise) -> void;
    
    inline auto TurnU(bool prime) -> void { TurnSide(Direction::Horizontal, m_Layers - 1, !prime); }
    inline auto TurnF(bool prime) -> void { TurnSide(Direction::Depthical, m_Layers - 1, !prime); }
    inline auto TurnR(bool prime) -> void { TurnSide(Direction::Vertical, m_Layers - 1, !prime); }
    inline auto TurnB(bool prime) -> void { TurnSide(Direction::Depthical, 0, prime); }
    inline auto TurnL(bool prime) -> void { TurnSide(Direction::Vertical, 0, prime); }
    inline auto TurnD(bool prime) -> void { TurnSide(Direction::Horizontal, 0, prime); }
    inline auto TurnM(bool prime) -> void 
    {
        if (m_Layers % 2 == 0)
            return;

        for (uint32_t x = 1; x < m_Layers - 1; x++)
            TurnSide(Direction::Vertical, x, !prime);
    }

    inline auto GetSize() -> uint32_t { return m_Layers; }
    
    auto Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>;
    auto Get(uint32_t x, uint32_t y, uint32_t z) const -> std::optional<std::reference_wrapper<const Piece>>;
    auto Set(uint32_t x, uint32_t y, uint32_t z, const Piece& piece) -> void;

    inline auto Rotate(float x, float y, float z) -> void
    {
        m_RotationMatrix = MatrixMultiply(m_RotationMatrix, MatrixRotateXYZ(Vector3{ x, y, z }));
    }

    auto Draw() const -> void;

private:
    static constexpr float STICKER_SCALE = 0.9f;

private:
    uint32_t m_Layers;
    Vector3 m_Position;
    float m_Size;

    std::vector<Piece> m_Pieces;

    Matrix m_RotationMatrix;
};

#endif