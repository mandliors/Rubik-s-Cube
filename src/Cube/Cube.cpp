#include "Cube.hpp"

#include <raymath.h>

Cube::Cube(uint32_t layers, const Vector3& position, float size)
    : m_Layers(layers), m_Position(position), m_Size(size)
{
    float pieceSize = size / layers;
    Vector3 cornerPosition = position - Vector3 { 
        size / 2 - pieceSize / 2, 
        size / 2 - pieceSize / 2,
        size / 2 - pieceSize / 2
    };

    // create the pieces
    m_Pieces.reserve(layers * layers * layers);
    for (uint32_t z = 0; z < layers; z++)
        for (uint32_t y = 0; y < layers; y++)
            for (uint32_t x = 0; x < layers; x++)
            {
                m_Pieces.emplace_back(
                    cornerPosition + Vector3(x, y, z) * pieceSize, 
                    pieceSize * STICKER_SCALE
                );
            }

    // set the face colors of the pieces
    for (uint32_t z = 0; z < layers; z++)
        for (uint32_t y = 0; y < layers; y++)
            for (uint32_t x = 0; x < layers; x++)
            {
                Piece& piece = Get(x, y, z).value().get();
                if (x == 0)
                    piece.SetFaceColor(Face::Left, FaceColor::Orange);
                if (x == layers - 1)
                    piece.SetFaceColor(Face::Right, FaceColor::Red);
                if (y == 0)
                    piece.SetFaceColor(Face::Bottom, FaceColor::Yellow);
                if (y == layers - 1)
                    piece.SetFaceColor(Face::Top, FaceColor::White);
                if (z == 0)
                    piece.SetFaceColor(Face::Back, FaceColor::Black);
                if (z == layers - 1)
                    piece.SetFaceColor(Face::Front, FaceColor::Green);
            }
}

auto Cube::TurnSide(LayerType layerType, uint32_t layerIndex, bool clockwise) -> void
{
    (void)layerType;
    (void)layerIndex;
    (void)clockwise;  
}

auto Cube::Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>
{
    uint32_t index = z * m_Layers * m_Layers + y * m_Layers + x;
    if (index >= m_Pieces.size())
        return std::nullopt;
    
    return std::ref(m_Pieces[index]);
}

auto Cube::Set(uint32_t x, uint32_t y, uint32_t z, const Piece& piece) -> void
{
    uint32_t index = z * m_Layers * m_Layers + y * m_Layers + x;
    if (index >= m_Pieces.size())
        return;
    
    m_Pieces[index] = piece;
}

auto Cube::Draw() const -> void
{
    const float internalCubeSize = m_Size - 1.5f * m_Size / m_Layers * (1 - STICKER_SCALE);
    DrawCube(m_Position, internalCubeSize, internalCubeSize, internalCubeSize, BLACK);

    for (const auto& piece : m_Pieces)
        piece.Draw();
}