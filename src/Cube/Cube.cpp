#include "Cube.hpp"

#include <raymath.h>
#include <rlgl.h>

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
                    piece.SetFaceColor(Face::Left, FaceColor::Orange, true);
                if (x == layers - 1)
                    piece.SetFaceColor(Face::Right, FaceColor::Red, true);
                if (y == 0)
                    piece.SetFaceColor(Face::Bottom, FaceColor::Yellow, true);
                if (y == layers - 1)
                    piece.SetFaceColor(Face::Top, FaceColor::White, true);
                if (z == 0)
                    piece.SetFaceColor(Face::Back, FaceColor::Blue, true);
                if (z == layers - 1)
                    piece.SetFaceColor(Face::Front, FaceColor::Green, true);
            }

    // initialize the rotation matrix
    m_RotationMatrix = MatrixIdentity();
}

auto Cube::TurnSide(Direction direction, uint32_t layerIndex, bool clockwise) -> void
{
    switch (direction)
    {
        case Direction::Horizontal:
        {
            // rotate the pieces phisically
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    auto piece = Get(x, layerIndex, z);
                    if (!piece.has_value())
                        continue;

                    piece.value().get().Rotate(direction, clockwise);
                }

            // caluculate the new piece for each slot
            std::vector<Piece> newPieces;
            newPieces.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    if (clockwise)
                        newPieces.push_back(Get(z, layerIndex, m_Layers - 1 - x).value().get());
                    else
                        newPieces.push_back(Get(m_Layers - 1 - z, layerIndex, x).value().get());
                }
            
            // set the new pieces to their new slots
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t x = 0; x < m_Layers; x++)
                    Set(x, layerIndex, z, newPieces[z * m_Layers + x]);

            break;
        }
    
        case Direction::Vertical:
        {
            // rotate the pieces phisically
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t y = 0; y < m_Layers; y++)
                {
                    auto piece = Get(layerIndex, y, z);
                    if (!piece.has_value())
                        continue;

                    piece.value().get().Rotate(direction, clockwise);
                }

            // caluculate the new piece for each slot
            std::vector<Piece> newPieces;
            newPieces.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t y = 0; y < m_Layers; y++)
                {
                    if (clockwise)
                        newPieces.push_back(Get(layerIndex, m_Layers - 1 - z, y).value().get());
                    else
                        newPieces.push_back(Get(layerIndex, z, m_Layers - 1 - y).value().get());
                }

            // set the new pieces to their new slots
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t y = 0; y < m_Layers; y++)
                    Set(layerIndex, y, z, newPieces[z * m_Layers + y]);

            break;
        }

        case Direction::Depthical:
        {
            // rotate the pieces phisically
            for (uint32_t y = 0; y < m_Layers; y++)
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    auto piece = Get(x, y, layerIndex);
                    if (!piece.has_value())
                        continue;

                    piece.value().get().Rotate(direction, clockwise);
                }

            // caluculate the new piece for each slot
            std::vector<Piece> newPieces;
            newPieces.reserve(m_Layers);
            for (uint32_t y = 0; y < m_Layers; y++)
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    if (clockwise)
                        newPieces.push_back(Get(m_Layers - 1 - y, x, layerIndex).value().get());
                    else
                        newPieces.push_back(Get(y, m_Layers - 1 - x, layerIndex).value().get());
                }
            
            // set the new pieces to their new slots
            for (uint32_t y = 0; y < m_Layers; y++)
                for (uint32_t x = 0; x < m_Layers; x++)
                    Set(x, y, layerIndex, newPieces[y * m_Layers + x]);

            break;
        }
    }
}

auto Cube::Scramble() -> void
{
    for (uint32_t i = 0; i < static_cast<uint32_t>(sqrt(m_Layers) * 20); i++)
        TurnSide(
            static_cast<Direction>(GetRandomValue(0, 2)),
            GetRandomValue(0, m_Layers - 1),
            GetRandomValue(0, 1)
        );
}
auto Cube::IsSolved() const -> bool
{
    FaceColor color;

    // check the colors of the back face
    color = Get(0, 0, 0).value().get().GetFaceColor(Face::Back);
    for (uint32_t y = 0; y < m_Layers; y++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (Get(x, y, 0).value().get().GetFaceColor(Face::Back) != color)
                return false;

    // check the colors of the bottom face
    color = Get(0, 0, 0).value().get().GetFaceColor(Face::Bottom);
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (Get(x, 0, z).value().get().GetFaceColor(Face::Bottom) != color)
                return false;
    
    // check the colors of the left face
    color = Get(0, 0, 0).value().get().GetFaceColor(Face::Left);
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t y = 0; y < m_Layers; y++)
            if (Get(0, y, z).value().get().GetFaceColor(Face::Left) != color)
                return false;

    // check the colors of the front face
    color = Get(m_Layers - 1, m_Layers - 1, m_Layers - 1).value().get().GetFaceColor(Face::Front);
    for (uint32_t y = 0; y < m_Layers; y++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (Get(x, y, m_Layers - 1).value().get().GetFaceColor(Face::Front) != color)
                return false;

    // check the colors of the top face
    color = Get(m_Layers - 1, m_Layers - 1, m_Layers - 1).value().get().GetFaceColor(Face::Top);
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (Get(x, m_Layers - 1, z).value().get().GetFaceColor(Face::Top) != color)
                return false;

    // check the colors of the right face
    color = Get(m_Layers - 1, m_Layers - 1, m_Layers - 1).value().get().GetFaceColor(Face::Right);
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t y = 0; y < m_Layers; y++)
            if (Get(m_Layers - 1, y, z).value().get().GetFaceColor(Face::Right) != color)
                return false;
        
    return true;
}

auto Cube::Get(uint32_t x, uint32_t y, uint32_t z) -> std::optional<std::reference_wrapper<Piece>>
{
    uint32_t index = z * m_Layers * m_Layers + y * m_Layers + x;
    if (index >= m_Pieces.size())
        return std::nullopt;
    
    return std::ref(m_Pieces[index]);
}

auto Cube::Get(uint32_t x, uint32_t y, uint32_t z) const -> std::optional<std::reference_wrapper<const Piece>>
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
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(m_RotationMatrix));

    const float internalCubeSize = m_Size - 1.5f * m_Size / m_Layers * (1 - STICKER_SCALE);
    //DrawCube(m_Position, internalCubeSize, internalCubeSize, internalCubeSize, BLACK);

    for (const auto& piece : m_Pieces)
        piece.Draw();

    rlPopMatrix();
}