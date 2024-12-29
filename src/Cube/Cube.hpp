#ifndef CUBE_H
#define CUBE_H

#include "Piece/Piece.hpp"
#include "Piece/PieceLocation.hpp"
#include "Direction/Direction.hpp"
#include "Move/Move.hpp"

#include <raylib.h>

#include <memory>
#include <vector>
#include <optional>

class Cube
{
public:
    Cube(uint32_t layers, const Vector3& position, float size);
    
    auto MakeMove(Move move) -> void;
    auto MakeMoves(const std::string& moveString) -> void;
    inline auto MakeMoves(Move move, auto... moves) -> void
    {
        MakeMove(move);
        (MakeMove(moves), ...);
    }
    
    auto Scramble() -> void;
    auto IsSolved() const -> bool;

    inline auto GetSize() -> uint32_t { return m_Layers; }

    auto Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>;
    auto Get(uint32_t x, uint32_t y, uint32_t z) const -> std::optional<std::reference_wrapper<const Piece>>;
    auto Set(uint32_t x, uint32_t y, uint32_t z, const Piece& piece) -> void;
    
    auto FindPieceByColors(FaceColor color, auto... colors) -> std::optional<std::reference_wrapper<const Piece>>
    {
        for (const auto& piece : m_Pieces) 
            if (((piece.GetFaceByColor(color) != Face::None) && ... && (piece.GetFaceByColor(colors) != Face::None)))
                return std::ref(piece);

        return std::nullopt;
    }
    auto GetPieceLocationByColors(FaceColor color, auto... colors) -> std::optional<PieceLocation>
    {
        for (uint32_t z = 0; z < m_Layers; z++)
            for (uint32_t y = 0; y < m_Layers; y++)
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    auto pieceOpt = Get(x, y, z);
                    if (!pieceOpt.has_value())
                        continue;

                    const auto& piece = pieceOpt.value().get();
                    if (((piece.GetFaceByColor(color) != Face::None) && ... && (piece.GetFaceByColor(colors) != Face::None)))
                        return PieceLocation { x, y, z };
                }
                
        return std::nullopt;
    }

    inline auto Rotate(float x, float y, float z) -> void
    {
        m_RotationMatrix = MatrixMultiply(m_RotationMatrix, MatrixRotateXYZ(Vector3{ x, y, z }));
    }

    auto Draw() const -> void;

    auto TurnSide(Direction layerType, uint32_t layerIndex, bool clockwise) -> void;

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