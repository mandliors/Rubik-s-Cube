#include "Cube.hpp"

#include <raymath.h>
#include <rlgl.h>

Cube::Cube(uint32_t layers, const Vector3& position, float size)
    : m_Layers(layers), m_Position(position), m_Size(size), m_Animations(true), m_AnimationSpeed(10.0f)
{
    Reset();
}

auto Cube::MakeMove(Move move) -> void
{
    switch (move)
    {
    case Move::U:
        MakeTurn({ Direction::Horizontal, m_Layers - 1, true });
        break;
    case Move::U2:
        MakeTurn({ Direction::Horizontal, m_Layers - 1, true });
        MakeTurn({ Direction::Horizontal, m_Layers - 1, true });
        break;
    case Move::U_:
        MakeTurn({ Direction::Horizontal, m_Layers - 1, false });
        break;
    case Move::u:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Horizontal, m_Layers - 1, true });
        MakeTurn({ Direction::Horizontal, m_Layers - 2, true });
        break;
    case Move::u_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Horizontal, m_Layers - 1, false });
        MakeTurn({ Direction::Horizontal, m_Layers - 2, false });
        break;
    case Move::F:
        MakeTurn({ Direction::Depthical, m_Layers - 1, true });
        break;
    case Move::F2:
        MakeTurn({ Direction::Depthical, m_Layers - 1, true });
        MakeTurn({ Direction::Depthical, m_Layers - 1, true });
        break;
    case Move::F_:
        MakeTurn({ Direction::Depthical, m_Layers - 1, false });
        break;
    case Move::f:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Depthical, m_Layers - 1, true });
        MakeTurn({ Direction::Depthical, m_Layers - 2, true });
        break;
    case Move::f_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Depthical, m_Layers - 1, false });
        MakeTurn({ Direction::Depthical, m_Layers - 2, false });
        break;
    case Move::R:
        MakeTurn({ Direction::Vertical, m_Layers - 1, true });
        break;
    case Move::R2:
        MakeTurn({ Direction::Vertical, m_Layers - 1, true });
        MakeTurn({ Direction::Vertical, m_Layers - 1, true });
        break;
    case Move::R_:
        MakeTurn({ Direction::Vertical, m_Layers - 1, false });
        break;
    case Move::r:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Vertical, m_Layers - 1, true });
        MakeTurn({ Direction::Vertical, m_Layers - 2, true });
        break;
    case Move::r_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Vertical, m_Layers - 1, false });
        MakeTurn({ Direction::Vertical, m_Layers - 2, false });
        break;
    case Move::B:
        MakeTurn({ Direction::Depthical, 0, false });
        break;
    case Move::B2:
        MakeTurn({ Direction::Depthical, 0, false });
        MakeTurn({ Direction::Depthical, 0, false });
        break;
    case Move::B_:
        MakeTurn({ Direction::Depthical, 0, true });
        break;
    case Move::b:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Depthical, 0, false });
        MakeTurn({ Direction::Depthical, 1, false });
        break;
    case Move::b_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Depthical, 0, true });
        MakeTurn({ Direction::Depthical, 1, true });
        break;
    case Move::L:
        MakeTurn({ Direction::Vertical, 0, false });
        break;
    case Move::L2:
        MakeTurn({ Direction::Vertical, 0, false });
        MakeTurn({ Direction::Vertical, 0, false });
        break;
    case Move::L_:
        MakeTurn({ Direction::Vertical, 0, true });
        break;
    case Move::l:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Vertical, 0, false });
        MakeTurn({ Direction::Vertical, 1, false });
        break;
    case Move::l_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Vertical, 0, true });
        MakeTurn({ Direction::Vertical, 1, true });
        break;
    case Move::D:
        MakeTurn({ Direction::Horizontal, 0, false });
        break;
    case Move::D2:
        MakeTurn({ Direction::Horizontal, 0, false });
        MakeTurn({ Direction::Horizontal, 0, false });
        break;
    case Move::D_:
        MakeTurn({ Direction::Horizontal, 0, true });
        break;
    case Move::d:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Horizontal, 0, false });
        MakeTurn({ Direction::Horizontal, 1, false });
        break;
    case Move::d_:
        if (m_Layers < 3)
            break;

        MakeTurn({ Direction::Horizontal, 0, true });
        MakeTurn({ Direction::Horizontal, 1, true });
        break;
    case Move::M:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Vertical, m_Layers / 2, false });
        break;
    case Move::M2:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Vertical, m_Layers / 2, false });
        MakeTurn({ Direction::Vertical, m_Layers / 2, false });
        break;
    case Move::M_:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Vertical, m_Layers / 2, true });
        break;
    case Move::E:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Horizontal, m_Layers / 2, false });
        break;
    case Move::E2:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Horizontal, m_Layers / 2, false });
        MakeTurn({ Direction::Horizontal, m_Layers / 2, false });
        break;
    case Move::E_:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Horizontal, m_Layers / 2, true });
        break;
    case Move::S:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Depthical, m_Layers / 2, true });
        break;
    case Move::S2:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Depthical, m_Layers / 2, true });
        MakeTurn({ Direction::Depthical, m_Layers / 2, true });
        break;
    case Move::S_:
        if (m_Layers % 2 == 0)
            return;

        MakeTurn({ Direction::Depthical, m_Layers / 2, false });
        break;
    case Move::x:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Vertical, i, true });

        break;
    case Move::x2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            MakeTurn({ Direction::Vertical, i, true });
            MakeTurn({ Direction::Vertical, i, true });
        }
        break;
    case Move::x_:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Vertical, i, false });

        break;
    case Move::y:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Horizontal, i, true });

        break;
    case Move::y2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            MakeTurn({ Direction::Horizontal, i, true });
            MakeTurn({ Direction::Horizontal, i, true });
        }
        break;
    case Move::y_:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Horizontal, i, false });

        break;
    case Move::z:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Depthical, i, true });

        break;
    case Move::z2:
        for (uint32_t i = 0; i < m_Layers; i++)
        {
            MakeTurn({ Direction::Depthical, i, true });
            MakeTurn({ Direction::Depthical, i, true });
        }
        break;
    case Move::z_:
        for (uint32_t i = 0; i < m_Layers; i++)
            MakeTurn({ Direction::Depthical, i, false });

        break;
    }
}

auto Cube::MakeMoves(std::string_view moveString) -> void
{
    // split the string by spaces
    std::vector<std::string_view> moves;
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
        else if (move == "u")
            MakeMove(Move::u);
        else if (move == "u'")
            MakeMove(Move::u_);
        else if (move == "F")
            MakeMove(Move::F);
        else if (move == "F2")
            MakeMove(Move::F2);
        else if (move == "F'")
            MakeMove(Move::F_);
        else if (move == "f")
            MakeMove(Move::f);
        else if (move == "f'")
            MakeMove(Move::f_);
        else if (move == "R")
            MakeMove(Move::R);
        else if (move == "R2")
            MakeMove(Move::R2);
        else if (move == "R'")
            MakeMove(Move::R_);
        else if (move == "r")
            MakeMove(Move::r);
        else if (move == "r'")
            MakeMove(Move::r_);
        else if (move == "B")
            MakeMove(Move::B);
        else if (move == "B2")
            MakeMove(Move::B2);
        else if (move == "B'")
            MakeMove(Move::B_);
        else if (move == "b")
            MakeMove(Move::b);
        else if (move == "b'")
            MakeMove(Move::b_);
        else if (move == "L")
            MakeMove(Move::L);
        else if (move == "L2")
            MakeMove(Move::L2);
        else if (move == "L'")
            MakeMove(Move::L_);
        else if (move == "l")
            MakeMove(Move::l);
        else if (move == "l'")
            MakeMove(Move::l_);
        else if (move == "D")
            MakeMove(Move::D);
        else if (move == "D2")
            MakeMove(Move::D2);
        else if (move == "D'")
            MakeMove(Move::D_);
        else if (move == "d")
            MakeMove(Move::d);
        else if (move == "d'")
            MakeMove(Move::d_);
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
        MakeTurn({
            .LayerType = static_cast<Direction>(GetRandomValue(0, 2)),
            .LayerIndex = static_cast<uint32_t>(GetRandomValue(0, m_Layers - 1)),
            .Clockwise = static_cast<bool>(GetRandomValue(0, 1))
        });
}
auto Cube::IsSolved() const -> bool
{
    // if still animating, return false
    if (!m_Rotations.empty())
        return false;

    FaceColor color;

    // check the colors of the back face
    color = GetPieceColors({ 0, 0, 0 }).value().get()[Face::Back];
    for (uint32_t y = 0; y < m_Layers; y++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (GetPieceColors({ x, y, 0 }).value().get()[Face::Back] != color)
                return false;

    // check the colors of the bottom face
    color = GetPieceColors({ 0, 0, 0 }).value().get()[Face::Bottom];
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (GetPieceColors({ x, 0, z }).value().get()[Face::Bottom] != color)
                return false;
    
    // check the colors of the left face
    color = GetPieceColors({ 0, 0, 0 }).value().get()[Face::Left];
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t y = 0; y < m_Layers; y++)
            if (GetPieceColors({ 0, y, z }).value().get()[Face::Left] != color)
                return false;

    // check the colors of the front face
    color = GetPieceColors({ m_Layers - 1, m_Layers - 1, m_Layers - 1 }).value().get()[Face::Front];
    for (uint32_t y = 0; y < m_Layers; y++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (GetPieceColors({ x, y, m_Layers - 1 }).value().get()[Face::Front] != color)
                return false;

    // check the colors of the top face
    color = GetPieceColors({ m_Layers - 1, m_Layers - 1, m_Layers - 1 }).value().get()[Face::Top];
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t x = 0; x < m_Layers; x++)
            if (GetPieceColors({ x, m_Layers - 1, z }).value().get()[Face::Top] != color)
                return false;

    // check the colors of the right face
    color = GetPieceColors({ m_Layers - 1, m_Layers - 1, m_Layers - 1 }).value().get()[Face::Right];
    for (uint32_t z = 0; z < m_Layers; z++)
        for (uint32_t y = 0; y < m_Layers; y++)
            if (GetPieceColors({ m_Layers - 1, y, z }).value().get()[Face::Right] != color)
                return false;
        
    return true;
}

auto Cube::Reset() -> void
{
    // empty the move queue
    while (!m_Rotations.empty())
        m_Rotations.pop();

    // calculate helper variables
    float pieceSize = m_Size / static_cast<float>(m_Layers);
    Vector3 cornerPosition = m_Position - Vector3 { 
        m_Size * 0.5f - pieceSize * 0.5f, 
        m_Size * 0.5f - pieceSize * 0.5f,
        m_Size * 0.5f - pieceSize * 0.5f
    };

    // create the pieces and the piece colors
    m_Pieces.clear();
    m_Pieces.reserve(m_Layers * m_Layers * m_Layers);
    m_CurrentPieceColors.clear();
    m_CurrentPieceColors.reserve(m_Layers * m_Layers * m_Layers);
    for (uint32_t z = 0; z < m_Layers; z++)
    {
        for (uint32_t y = 0; y < m_Layers; y++)
        {
            for (uint32_t x = 0; x < m_Layers; x++)
            {
                m_Pieces.emplace_back(
                    cornerPosition + Vector3(x, y, z) * pieceSize, 
                    pieceSize * STICKER_SCALE
                );
                m_CurrentPieceColors.emplace_back(std::array<FaceColor, 6>{
                    FaceColor::None, 
                    FaceColor::None, 
                    FaceColor::None,
                    FaceColor::None,
                    FaceColor::None,
                    FaceColor::None
                });
            }
        }
    }

    // set the face colors of the pieces
    for (uint32_t z = 0; z < m_Layers; z++)
    {
        for (uint32_t y = 0; y < m_Layers; y++)
        {
            for (uint32_t x = 0; x < m_Layers; x++)
            {
                PieceColors& pieceColors = GetPieceColors({ x, y, z }).value().get();
                Piece& piece = _GetPiece({ x, y, z }).value().get();
                if (x == 0)
                {
                    pieceColors[Face::Left] = FaceColor::Orange;
                    piece.SetFaceColor(Face::Left, FaceColor::Orange);
                }
                if (x == m_Layers - 1)
                {
                    pieceColors[Face::Right] = FaceColor::Red;
                    piece.SetFaceColor(Face::Right, FaceColor::Red);
                }
                if (y == 0)
                {
                    pieceColors[Face::Bottom] = FaceColor::Yellow;
                    piece.SetFaceColor(Face::Bottom, FaceColor::Yellow);
                }
                if (y == m_Layers - 1)
                {
                    pieceColors[Face::Top] = FaceColor::White;
                    piece.SetFaceColor(Face::Top, FaceColor::White);
                }
                if (z == 0)
                {
                    pieceColors[Face::Back] = FaceColor::Blue;
                    piece.SetFaceColor(Face::Back, FaceColor::Blue);
                }
                if (z == m_Layers - 1)
                {
                    pieceColors[Face::Front] = FaceColor::Green;
                    piece.SetFaceColor(Face::Front, FaceColor::Green);
                }
            }
        }
    }

    // initialize the rotation matrix
    m_RotationMatrix = MatrixIdentity();
}

auto Cube::Update(float deltaTime) -> void
{
    if (m_Rotations.empty())
        return;

    // update the rotation (do all rotations if animations are disabled)
    float rotationAngle = m_Animations ? m_AnimationSpeed * deltaTime : PI;
    do
    {
        AxialRotation& rotation = m_Rotations.front();
        auto indices = _GetIndicesByTurn(rotation.GetTurn());
        if (rotation.Update(rotationAngle, _GetPiecesByIndices(indices)))
        {
            auto newPieces = _GetPieceClonesByIndices(_GetIndicesByTurnInversed(rotation.GetTurn()));
            _SetPiecesByIndices(indices, newPieces);

            m_Rotations.pop();
        }
    }
    while (!m_Animations && !m_Rotations.empty());
}
auto Cube::Draw() const -> void
{
    rlPushMatrix();
    rlMultMatrixf(MatrixToFloat(m_RotationMatrix));

    for (const auto& piece : m_Pieces)
        piece.Draw();

    rlPopMatrix();
}

auto Cube::MakeTurn(const Turn& turn) -> void
{
    auto indices = _GetIndicesByTurn(turn);
    auto indicesInversed = _GetIndicesByTurnInversed(turn);

    auto newPieceColors = _GetPieceColorsClonesByIndices(indicesInversed);
    for (auto& colors : newPieceColors)
        colors.HandleRotation(turn.LayerType, turn.Clockwise);

    _SetPieceColorsByIndices(indices, newPieceColors);

    m_Rotations.emplace(turn);
}

auto Cube::_GetIndicesByTurn(const Turn& turn) const -> std::vector<PieceLocation>
{
    switch (turn.LayerType)
    {
        case Direction::Horizontal:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t x = 0; x < m_Layers; x++)
                    indices.emplace_back(x, turn.LayerIndex, z);

            return indices;
        }
    
        case Direction::Vertical:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
                for (uint32_t y = 0; y < m_Layers; y++)
                    indices.emplace_back(turn.LayerIndex, y, z);

            return indices;
        }

        case Direction::Depthical:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t y = 0; y < m_Layers; y++)
                for (uint32_t x = 0; x < m_Layers; x++)
                    indices.emplace_back(x, y, turn.LayerIndex);

            return indices;
        }
    }

    std::unreachable();
}
auto Cube::_GetIndicesByTurnInversed(const Turn& turn) const -> std::vector<PieceLocation>
{
    switch (turn.LayerType)
    {
        case Direction::Horizontal:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
            {
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    if (turn.Clockwise)
                        indices.emplace_back(z, turn.LayerIndex, m_Layers - 1 - x);
                    else
                        indices.emplace_back( m_Layers - 1 - z, turn.LayerIndex, x);
                   
                }
            }

            return indices;
        }
    
        case Direction::Vertical:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t z = 0; z < m_Layers; z++)
            {
                for (uint32_t y = 0; y < m_Layers; y++)
                {
                    if (turn.Clockwise)
                        indices.emplace_back(turn.LayerIndex, m_Layers - 1 - z, y);
                    else
                        indices.emplace_back(turn.LayerIndex, z, m_Layers - 1 - y);
                }
            }

            return indices;
        }

        case Direction::Depthical:
        {
            std::vector<PieceLocation> indices;
            indices.reserve(m_Layers);
            for (uint32_t y = 0; y < m_Layers; y++)
            {
                for (uint32_t x = 0; x < m_Layers; x++)
                {
                    if (turn.Clockwise)
                        indices.emplace_back(m_Layers - 1 - y, x, turn.LayerIndex);
                    else
                        indices.emplace_back(y, m_Layers - 1 - x, turn.LayerIndex);
                }
            }

            return indices;
        }
    }

    std::unreachable();
}

auto Cube::_GetPieceColorsClonesByIndices(const std::vector<PieceLocation>& indices) const -> std::vector<PieceColors>
{
    std::vector<PieceColors> pieceColors;
    pieceColors.reserve(indices.size());
    for (const auto& index : indices)
    {
        auto colors = GetPieceColors(index);
        if (colors.has_value())
            pieceColors.push_back(colors.value().get());
    }

    return pieceColors;
}
auto Cube::_SetPieceColorsByIndices(const std::vector<PieceLocation>& indices, const std::vector<PieceColors>& pieceColors) -> void
{
    for (uint32_t i = 0; i < indices.size(); i++)
        SetPieceColors(indices[i], pieceColors[i]);
}

auto Cube::_GetPiecesByIndices(const std::vector<PieceLocation>& indices) -> std::vector<std::reference_wrapper<Piece>>
{
    std::vector<std::reference_wrapper<Piece>> pieces;
    pieces.reserve(indices.size());
    for (const auto& index : indices)
    {
        auto piece = _GetPiece(index);
        if (piece.has_value())
            pieces.push_back(piece.value());
    }

    return pieces;
}
auto Cube::_GetPieceClonesByIndices(const std::vector<PieceLocation>& indices) const -> std::vector<Piece>
{
    std::vector<Piece> pieces;
    pieces.reserve(indices.size());
    for (const auto& index : indices)
    {
        auto piece = _GetPiece(index);
        if (piece.has_value())
            pieces.push_back(piece.value().get());
    }

    return pieces;
}
auto Cube::_SetPiecesByIndices(const std::vector<PieceLocation>& indices, const std::vector<Piece>& pieces) -> void
{
    for (uint32_t i = 0; i < indices.size(); i++)
        _SetPiece(indices[i], pieces[i]);
}