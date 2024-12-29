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

auto Cube::MakeMove(Move move) -> void
{
    switch (move)
    {
    case Move::U:
        TurnSide(Direction::Horizontal, m_Layers - 1, true);
        break;
    case Move::U2:
        TurnSide(Direction::Horizontal, m_Layers - 1, true);
        TurnSide(Direction::Horizontal, m_Layers - 1, true);
        break;
    case Move::U_:
        TurnSide(Direction::Horizontal, m_Layers - 1, false);
        break;
    case Move::F:
        TurnSide(Direction::Depthical, m_Layers - 1, true);
        break;
    case Move::F2:
        TurnSide(Direction::Depthical, m_Layers - 1, true);
        TurnSide(Direction::Depthical, m_Layers - 1, true);
        break;
    case Move::F_:
        TurnSide(Direction::Depthical, m_Layers - 1, false);
        break;
    case Move::R:
        TurnSide(Direction::Vertical, m_Layers - 1, true);
        break;
    case Move::R2:
        TurnSide(Direction::Vertical, m_Layers - 1, true);
        TurnSide(Direction::Vertical, m_Layers - 1, true);
        break;
    case Move::R_:
        TurnSide(Direction::Vertical, m_Layers - 1, false);
        break;
    case Move::B:
        TurnSide(Direction::Depthical, 0, false);
        break;
    case Move::B2:
        TurnSide(Direction::Depthical, 0, false);
        TurnSide(Direction::Depthical, 0, false);
        break;
    case Move::B_:
        TurnSide(Direction::Depthical, 0, true);
        break;
    case Move::L:
        TurnSide(Direction::Vertical, 0, false);
        break;
    case Move::L2:
        TurnSide(Direction::Vertical, 0, false);
        TurnSide(Direction::Vertical, 0, false);
        break;
    case Move::L_:
        TurnSide(Direction::Vertical, 0, true);
        break;
    case Move::D:
        TurnSide(Direction::Horizontal, 0, false);
        break;
    case Move::D2:
        TurnSide(Direction::Horizontal, 0, false);
        TurnSide(Direction::Horizontal, 0, false);
        break;
    case Move::D_:
        TurnSide(Direction::Horizontal, 0, true);
        break;
    case Move::M:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Vertical, m_Layers / 2, false);
        break;
    case Move::M2:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Vertical, m_Layers / 2, false);
        TurnSide(Direction::Vertical, m_Layers / 2, false);
        break;
    case Move::M_:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Vertical, m_Layers / 2, true);
        break;
    case Move::E:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Horizontal, m_Layers / 2, false);
        break;
    case Move::E2:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Horizontal, m_Layers / 2, false);
        TurnSide(Direction::Horizontal, m_Layers / 2, false);
        break;
    case Move::E_:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Horizontal, m_Layers / 2, true);
        break;
    case Move::S:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Depthical, m_Layers / 2, true);
        break;
    case Move::S2:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Depthical, m_Layers / 2, true);
        TurnSide(Direction::Depthical, m_Layers / 2, true);
        break;
    case Move::S_:
        if (m_Layers % 2 == 0)
            return;

        TurnSide(Direction::Depthical, m_Layers / 2, false);
        break;
    case Move::x:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Vertical, i, true);

        break;
    case Move::x2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            TurnSide(Direction::Vertical, i, true);
            TurnSide(Direction::Vertical, i, true);
        }
        break;
    case Move::x_:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Vertical, i, false);

        break;
    case Move::y:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Horizontal, i, true);

        break;
    case Move::y2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            TurnSide(Direction::Horizontal, i, true);
            TurnSide(Direction::Horizontal, i, true);
        }
        break;
    case Move::y_:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Horizontal, i, false);

        break;
    case Move::z:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Depthical, i, true);

        break;
    case Move::z2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            TurnSide(Direction::Depthical, i, true);
            TurnSide(Direction::Depthical, i, true);
        }
        break;
    case Move::z_:
        for (uint32_t i = 0; i < m_Layers; i++)
            TurnSide(Direction::Depthical, i, false);

        break;
    }
}

auto Cube::MakeMoves(const std::string& moveString) -> void
{
    // split the string by spaces
    std::vector<std::string> moves;
    size_t start = 0;
    size_t end = 0;
    while ((end = moveString.find(' ', start)) != std::string::npos)
    {
        moves.push_back(moveString.substr(start, end - start));
        start = end + 1;
    }
    moves.push_back(moveString.substr(start));

    // make the moves
    for (const auto& move : moves)
    {
        if (move == "U")
            MakeMove(Move::U);
        else if (move == "U2")
            MakeMove(Move::U2);
        else if (move == "U'")
            MakeMove(Move::U_);
        else if (move == "F")
            MakeMove(Move::F);
        else if (move == "F2")
            MakeMove(Move::F2);
        else if (move == "F'")
            MakeMove(Move::F_);
        else if (move == "R")
            MakeMove(Move::R);
        else if (move == "R2")
            MakeMove(Move::R2);
        else if (move == "R'")
            MakeMove(Move::R_);
        else if (move == "B")
            MakeMove(Move::B);
        else if (move == "B2")
            MakeMove(Move::B2);
        else if (move == "B'")
            MakeMove(Move::B_);
        else if (move == "L")
            MakeMove(Move::L);
        else if (move == "L2")
            MakeMove(Move::L2);
        else if (move == "L'")
            MakeMove(Move::L_);
        else if (move == "D")
            MakeMove(Move::D);
        else if (move == "D2")
            MakeMove(Move::D2);
        else if (move == "D'")
            MakeMove(Move::D_);
        else if (move == "M")
            MakeMove(Move::M);
        else if (move == "M2")
            MakeMove(Move::M2);
        else if (move == "M'")
            MakeMove(Move::M_);
        else if (move == "E")
            MakeMove(Move::E);
        else if (move == "E2")
            MakeMove(Move::E2);
        else if (move == "E'")
            MakeMove(Move::E_);
        else if (move == "S")
            MakeMove(Move::S);
        else if (move == "S2")
            MakeMove(Move::S2);
        else if (move == "S'")
            MakeMove(Move::S_);
        else if (move == "x")
            MakeMove(Move::x);
        else if (move == "x2")
            MakeMove(Move::x2);
        else if (move == "x'")
            MakeMove(Move::x_);
        else if (move == "y")
            MakeMove(Move::y);
        else if (move == "y2")
            MakeMove(Move::y2);
        else if (move == "y'")
            MakeMove(Move::y_);
        else if (move == "z")
            MakeMove(Move::z);
        else if (move == "z2")
            MakeMove(Move::z2);
        else if (move == "z'")
            MakeMove(Move::z_);
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