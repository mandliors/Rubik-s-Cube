#ifndef CUBE_H
#define CUBE_H

#include "Piece/Piece.hpp"
#include "Piece/PieceLocation.hpp"
#include "AxialRotation/AxialRotation.hpp"
#include "Move/Move.hpp"
#include "Turn/Turn.hpp"

#include <raylib.h>

#include <memory>
#include <vector>
#include <queue>
#include <optional>
#include <algorithm>

class Cube
{
public:
    Cube(uint32_t layers, const Vector3& position, float size);
    
    auto MakeMove(Move move) -> void;
    auto MakeMoves(std::string_view moveString) -> void;
    inline auto MakeMoves(Move move, auto... moves) -> void
    {
        MakeMove(move);
        (MakeMove(moves), ...);
    }
    
    auto Scramble() -> void;
    auto IsSolved() const -> bool;

    inline auto GetSize() const -> uint32_t { return m_Layers; }
    inline auto GetPieceColors(const PieceLocation& location) const -> std::optional<std::reference_wrapper<const PieceColors>>
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return std::nullopt;
        
        return std::ref(m_CurrentPieceColors[index]);
    }
    inline auto GetPieceColors(const PieceLocation& location) -> std::optional<std::reference_wrapper<PieceColors>>
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return std::nullopt;
        
        return std::ref(m_CurrentPieceColors[index]);
    }
    inline auto SetPieceColors(const PieceLocation& location, const PieceColors& pieceColors) -> void
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return;
        
        m_CurrentPieceColors[index] = pieceColors;
    }
    auto GetPieceLocationByExactColors(FaceColor color, auto... colors) -> std::optional<PieceLocation>
    {
        std::array<FaceColor, sizeof...(colors) + 1> searchColors = { color, colors... };

        for (uint32_t z = 0; z < m_Layers; z++)
        {
            for (uint32_t y = 0; y < m_Layers; y++)
            {
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    auto pieceOpt = GetPieceColors({ x, y, z });
                    if (!pieceOpt.has_value())
                        continue;

                    const auto& piece = pieceOpt.value().get();
                    const auto& pieceColors = piece.GetColors();

                    if (pieceColors.size() != searchColors.size())
                        continue;

                    bool allColorsMatch = std::ranges::all_of(searchColors, 
                        [&pieceColors](FaceColor col) {
                            return col == FaceColor::None || std::ranges::find(pieceColors, col) != pieceColors.end();
                        });

                    if (allColorsMatch)
                        return PieceLocation { x, y, z };
                }
            }
        }

        return std::nullopt;
    }
    auto GetPieceLocationsByColors(FaceColor color, auto... colors) -> std::vector<PieceLocation>
    {
        std::vector<PieceLocation> locations;
        for (uint32_t z = 0; z < m_Layers; z++)
        {
            for (uint32_t y = 0; y < m_Layers; y++)
            {
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    auto pieceOpt = GetPieceColors({ x, y, z });
                    if (!pieceOpt.has_value())
                        continue;

                    // check if the piece has the colors
                    const auto& piece = pieceOpt.value().get();
                    if (((piece.GetFaceByColor(color) != Face::None) && ... && (piece.GetFaceByColor(colors) != Face::None)))
                        locations.emplace_back(x, y, z);
                }
            }
        }

        return locations;
    }
    

    inline auto Rotate(float x, float y, float z) -> void
    {
        m_RotationMatrix = MatrixMultiply(
            m_RotationMatrix,
            MatrixRotateXYZ(Vector3 { x, y, z })
        );
    }

    inline auto SetAnimationsEnabled(bool animations) -> void { m_Animations = animations; }
    inline auto GetAnimationsEnabled() const -> bool { return m_Animations; }

    inline auto SetAnimationSpeed(float speed) -> void { m_AnimationSpeed = speed; }
    inline auto GetAnimationSpeed() const -> float { return m_AnimationSpeed; }

    auto Reset() -> void;
    auto Update(float deltaTime) -> void;
    auto Draw() const -> void;

    auto MakeTurn(const Turn& turn) -> void;

private:
    static constexpr float STICKER_SCALE = 0.9f;

private:
    inline auto _GetPiece(const PieceLocation& location) -> std::optional<std::reference_wrapper<Piece>>
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return std::nullopt;
        
        return std::ref(m_Pieces[index]);
    }
    inline auto _GetPiece(const PieceLocation& location) const -> std::optional<std::reference_wrapper<const Piece>>
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return std::nullopt;
        
        return std::ref(m_Pieces[index]);
    }
    inline auto _SetPiece(const PieceLocation& location, const Piece& piece) -> void
    {
        uint32_t index = location.Z * m_Layers * m_Layers + location.Y * m_Layers + location.X;
        if (index >= m_Pieces.size())
            return;
        
        m_Pieces[index] = piece;
    }

    auto _GetIndicesByTurn(const Turn& turn) const -> std::vector<PieceLocation>;
    auto _GetIndicesByTurnInversed(const Turn& turn) const -> std::vector<PieceLocation>;

    auto _GetPieceColorsClonesByIndices(const std::vector<PieceLocation>& indices) const -> std::vector<PieceColors>;
    auto _SetPieceColorsByIndices(const std::vector<PieceLocation>& indices, const std::vector<PieceColors>& pieceColors) -> void;

    auto _GetPiecesByIndices(const std::vector<PieceLocation>& indices) -> std::vector<std::reference_wrapper<Piece>>;
    auto _GetPieceClonesByIndices(const std::vector<PieceLocation>& indices) const -> std::vector<Piece>;
    auto _SetPiecesByIndices(const std::vector<PieceLocation>& indices, const std::vector<Piece>& pieces) -> void;

private:
    uint32_t m_Layers;
    Vector3 m_Position;
    float m_Size;
    
    bool m_Animations;
    float m_AnimationSpeed;

    std::vector<PieceColors> m_CurrentPieceColors;
    std::vector<Piece> m_Pieces;

    std::queue<AxialRotation> m_Rotations;

    Matrix m_RotationMatrix;
};

#endif