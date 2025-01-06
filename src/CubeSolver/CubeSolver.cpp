#include "CubeSolver.hpp"
#include "ColorPattern/ColorPattern.hpp"

#include <utility>

const std::array<Algorithm, 7> CubeSolver::s_2x2_OLLs = {
    Algorithm {
        .Pattern = ColorPattern { "NYNYNNNY" },
        .Moves = "L' U2 L U L' U L"
    },
    Algorithm {
        .Pattern = ColorPattern { "YNYNNNYN" },
        .Moves = "R U2 R' U' R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "YNNNNYNN" },
        .Moves = "R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "YYNNYYNN" },
        .Moves = "R2 U2 R U2 R2"
    },
    Algorithm {
        .Pattern = ColorPattern { "NYNNYNYY" },
        .Moves = "F R U R' U' R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "NYNNNNYN" },
        .Moves = "F' R U R' U' R' F R"
    },
    Algorithm {
        .Pattern = ColorPattern { "NNNNNNYY" },
        .Moves = "F R U R' U' F'"
    }
};

const std::array<Algorithm, 6> CubeSolver::s_2x2_PLLs = {
    Algorithm {
        .Pattern = ColorPattern { "GBROBGOR" },
        .Moves = "F R U' R' U' R U R' F' R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "GOBGOBRR" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "OBROBRGG" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F' U'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BRGBRGOO" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F' U2"
    },
    Algorithm {
        .Pattern = ColorPattern { "RGORGOBB" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F' U"
    },
    Algorithm {
        .Pattern = ColorPattern { "GGOOBBRR" },
        .Moves = ""
    }
};

CubeSolver::CubeSolver(Cube& cube)
    : m_Cube(cube) { }

auto CubeSolver::Solve() -> void
{
    if (m_Cube.IsSolved())
        return;

    if (m_Cube.GetSize() == 2)
        _Solve2x2();
    else if (m_Cube.GetSize() == 3)
        _Solve3x3();
    else
        return;
}

auto CubeSolver::_Solve2x2() -> void
{
    uint32_t lastLayerIndex = m_Cube.GetSize() - 1;

    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Green, { 0, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Green, { lastLayerIndex, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Blue, { lastLayerIndex, 0, 0 }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Blue, { 0, 0, 0 }, FaceColor::White);

    _SolveOLL(s_2x2_OLLs, FaceColor::Yellow);

    _SolvePLL(s_2x2_PLLs);
}
auto CubeSolver::_Solve3x3() -> void
{
    uint32_t lastLayerIndex = m_Cube.GetSize() - 1;

    _SolveWhiteCenterToBottom();
    _SolveGreenCenterToFrontAfterWhiteCenter();
    
    _SolveEdge(FaceColor::White, FaceColor::Red, { 0, 0, 1 }, FaceColor::White);
    _SolveEdge(FaceColor::White, FaceColor::Blue, { 1, 0, 0 }, FaceColor::White);
    _SolveEdge(FaceColor::White, FaceColor::Orange, { lastLayerIndex, 0, 1 }, FaceColor::White);
    _SolveEdge(FaceColor::White, FaceColor::Green, { 1, 0, lastLayerIndex }, FaceColor::White);

    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Green, { 0, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Green, { lastLayerIndex, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Blue, { lastLayerIndex, 0, 0 }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Blue, { 0, 0, 0 }, FaceColor::White);
}


auto CubeSolver::_SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void
{
    PieceLocation cornerLocation = m_Cube.GetPieceLocationByExactColors(color1, color2, color3).value();
    
    // already solved
    if (cornerLocation == destLocation && m_Cube.GetPieceColors(destLocation).value().get()[Face::Bottom] == bottomColor)
        return;

    // move the corner to the top layer
    cornerLocation = _MoveCornerToTop(cornerLocation);

    // move the corner above the destination
    _MoveCornerOnTopToPosition(cornerLocation, destLocation.X, destLocation.Z);

    // insert the corner to the destination (right below the current position)
    _InsertCornerToBottom({ destLocation.X, m_Cube.GetSize() - 1, destLocation.Z }, bottomColor);
}
auto CubeSolver::_SolveEdge(FaceColor color1, FaceColor color2, PieceLocation destLocation, FaceColor bottomColor) -> void
{
    PieceLocation edgeLocation = m_Cube.GetPieceLocationByExactColors(color1, color2).value();
    
    // already solved
    if (edgeLocation == destLocation && m_Cube.GetPieceColors(destLocation).value().get()[Face::Bottom] == bottomColor)
        return;

    // move the edge to the top layer
    edgeLocation = _MoveEdgeToTop(edgeLocation);

    // move the edge above the destination
    _MoveEdgeOnTopToPosition(edgeLocation, destLocation.X, destLocation.Z);

    // insert the edge to the destination (right below the current position)
    _InsertEdgeToBottom({ destLocation.X, m_Cube.GetSize() - 1, destLocation.Z }, bottomColor);
}
auto CubeSolver::_SolveOLL(const std::span<const Algorithm>& OLLs, FaceColor faceColor) -> void
{
    ColorPattern OLLPattern = ColorPattern::CreateFromTopLayerWithBaseColor(m_Cube, faceColor);
    for (const auto& OLL : OLLs)
    {
        uint32_t match = OLLPattern.Match(OLL.Pattern);
        if (match != 5)
        {
            // align the OLL pattern
            for (uint32_t i = 0; i < match; i++)
                m_Cube.MakeMove(Move::U_);

            m_Cube.MakeMoves(OLL.Moves);
            break;
        }
    }
}
auto CubeSolver::_SolvePLL(const std::span<const Algorithm>& PLLs) -> void
{
    ColorPattern PLLPattern = ColorPattern::CreateFromTopLayer(m_Cube);
    for (const auto& PLL : PLLs)
    {
        uint32_t match = PLLPattern.Match(PLL.Pattern);
        if (match != 5)
        {
            // align the OLL pattern
            for (uint32_t i = 0; i < match; i++)
                m_Cube.MakeMove(Move::U_);

            m_Cube.MakeMoves(PLL.Moves);
            break;
        }
    }
}

auto CubeSolver::_SolveWhiteCenterToBottom() -> void
{
    // get the white center location
    PieceLocation whiteCenter = m_Cube.GetPieceLocationByExactColors(FaceColor::White).value();

    if (whiteCenter.Y == 0) // already solved
        return;
    else if (whiteCenter.Y == m_Cube.GetSize() - 1) // on the top
        m_Cube.MakeMove(Move::M2);
    else if (whiteCenter.X == 0) // on the left
        m_Cube.MakeMove(Move::S_);
    else if (whiteCenter.X == m_Cube.GetSize() - 1) // on the right
        m_Cube.MakeMove(Move::S);
    else if (whiteCenter.Z == 0) // in the back
        m_Cube.MakeMove(Move::M_);
    else if (whiteCenter.Z == m_Cube.GetSize() - 1) // in the front
        m_Cube.MakeMove(Move::M);
    else
        std::unreachable();
}
auto CubeSolver::_SolveGreenCenterToFrontAfterWhiteCenter() -> void
{
    // get the green center location
    PieceLocation greenCenter = m_Cube.GetPieceLocationByExactColors(FaceColor::Green).value();

    if (greenCenter.Z == m_Cube.GetSize() - 1) // already solved
        return;
    else if (greenCenter.X == 0) // on the left
        m_Cube.MakeMove(Move::E);
    else if (greenCenter.X == m_Cube.GetSize() - 1) // on the right
        m_Cube.MakeMove(Move::E_);
    else if (greenCenter.Z == 0) // in the back
        m_Cube.MakeMove(Move::E2);
    else
        std::unreachable();
}

auto CubeSolver::_MoveCornerToTop(PieceLocation location) -> PieceLocation
{
    // already on top
    if (location.Y == m_Cube.GetSize() - 1)
        return location;
    
    // bottom left back
    if (location.X == 0 && location.Z == 0)
    {
        m_Cube.MakeMoves("L U L'");
        return { m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, 0 };
    }
    // bottom right back
    if (location.X == m_Cube.GetSize() - 1 && location.Z == 0)
    {
        m_Cube.MakeMoves("R' U' R");
        return { 0, m_Cube.GetSize() - 1, 0 };
    }
    // bottom right front
    if (location.X == m_Cube.GetSize() - 1 && location.Z == m_Cube.GetSize() - 1)
    {
        m_Cube.MakeMoves("R U R'");
        return { 0, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
    }
    // bottom left front
    if (location.X == 0 && location.Z == m_Cube.GetSize() - 1)
    {
        m_Cube.MakeMoves("L' U' L");
        return { m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
    }

    std::unreachable();
}
auto CubeSolver::_MoveCornerOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> void
{
    // already in the correct position
    if (location.X == destX && location.Z == destZ)
        return;

    // make one U or U'
    if (location.X == destX)
    {
        // left ot right side
        if (location.X == 0)
            m_Cube.MakeMove(location.Z > destZ ? Move::U : Move::U_);
        else
            m_Cube.MakeMove(location.Z < destZ ? Move::U : Move::U_);
    }
    else if (location.Z == destZ)
    {
        // front or back side
        if (location.Z == 0)
            m_Cube.MakeMove(location.X < destX ? Move::U : Move::U_);
        else
            m_Cube.MakeMove(location.X > destX ? Move::U : Move::U_);
    }
    // make a U2
    else
        m_Cube.MakeMove(Move::U2);
}
auto CubeSolver::_InsertCornerToBottom(PieceLocation location, FaceColor bottomColor) -> void
{
    // get the bottomColor colored face
    Face bottomColorFace = m_Cube
        .GetPieceColors({ location.X, location.Y, location.Z })
        .value().get()
        .GetFaceByColor(bottomColor);

    // top left back
    if (location.X == 0 && location.Z == 0)
    {
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves("B' U' B");
            return;
        case Face::Left:
            m_Cube.MakeMoves("L U L'");
            return;
        case Face::Top:
            m_Cube.MakeMoves("L U2 L' U' L U L'");        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top right back
    if (location.X != 0 && location.Z == 0)
    {
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves("B U B'");
            return;
        case Face::Right:
            m_Cube.MakeMoves("R' U' R");
            return;
        case Face::Top:
            m_Cube.MakeMoves("R' U2 R U R' U' R");        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top right front
    if (location.X != 0 && location.Z != 0)
    {        
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves("F' U' F");
            return;
        case Face::Right:
            m_Cube.MakeMoves("R U R'");
            return;
        case Face::Top:
            m_Cube.MakeMoves("R U2 R' U' R U R'");        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top left front
    if (location.X == 0 && location.Z != 0)
    {       
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves("F U F'");
            return;
        case Face::Left:
            m_Cube.MakeMoves("L' U' L");
            return;
        case Face::Top:
            m_Cube.MakeMoves("L' U2 L U L' U' L");        
            return;
        
        default:
            std::unreachable();
        }
    }

    std::unreachable();
}

auto CubeSolver::_MoveEdgeToTop(PieceLocation location) -> PieceLocation
{
    // already on top
    if (location.Y == m_Cube.GetSize() - 1)
        return location;

    // left
    if (location.X == 0)
    {
        // bottom
        if (location.Y == 0)
        {
            m_Cube.MakeMove(Move::L2);
            return { 0, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 - location.Z };
        }
        // inner
        else
        {
            // back
            if (location.Z == 0)
            {
                m_Cube.MakeMoves("L U' L'");
                return { location.Y, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
            }
            // front
            else
            {
                m_Cube.MakeMoves("L' U' L");
                return { m_Cube.GetSize() - 1 - location.Y, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
            }
        }
    }
    // right
    if (location.X == m_Cube.GetSize() - 1)
    {
        // bottom
        if (location.Y == 0)
        {
            m_Cube.MakeMove(Move::R2);
            return { m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 - location.Z };
        }
        // inner
        else
        {
            // back
            if (location.Z == 0)
            {
                m_Cube.MakeMoves("R' U R");
                return { m_Cube.GetSize() - 1 - location.Y, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
            }
            // front
            else
            {
                m_Cube.MakeMoves("R U R'");
                return { location.Y, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
            }
        }
    }
    // bottom back
    if (location.Z == 0)
    {
        m_Cube.MakeMove(Move::B2);
        return { m_Cube.GetSize() - 1 - location.X, m_Cube.GetSize() - 1, 0 };
    }
    // bottom front
    if (location.Z == m_Cube.GetSize() - 1)
    {
        m_Cube.MakeMove(Move::F2);
        return { m_Cube.GetSize() - 1 - location.X, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
    }

    std::unreachable();
}
auto CubeSolver::_MoveEdgeOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> void
{
    // already in the correct position
    if (location.X == destX && location.Z == destZ)
        return;

    // make a U2
    if (location.X == destX || location.Z == destZ)
    {
        m_Cube.MakeMove(Move::U2);
        return;
    }
    // make one U or U'
    else
    {
        // clockwise cases
        if ((location.X == 0 && destZ == 0) || (location.X == m_Cube.GetSize() - 1 && destZ == m_Cube.GetSize() - 1))
        {
            m_Cube.MakeMove(Move::U);
            return;
        }
        // clockwise cases #2
        if ((location.Z == 0 && destX == m_Cube.GetSize() - 1) || (location.Z == m_Cube.GetSize() - 1 && destX == 0))
        {
            m_Cube.MakeMove(Move::U);
            return;
        }

        // counter.clockwise cases
        if ((location.X == 0 && destZ == m_Cube.GetSize() - 1) || (location.X == m_Cube.GetSize() - 1 && destZ == 0))
        {
            m_Cube.MakeMove(Move::U_);
            return;
        }
        // counter.clockwise cases #2
        if ((location.Z == 0 && destX == 0) || (location.Z == m_Cube.GetSize() - 1 && destX == m_Cube.GetSize() - 1))
        {
            m_Cube.MakeMove(Move::U_);
            return;
        }

        std::unreachable();
    }
}
auto CubeSolver::_InsertEdgeToBottom(PieceLocation location, FaceColor bottomColor) -> void
{
    // get the bottomColor colored face
    Face bottomColorFace = m_Cube
        .GetPieceColors({ location.X, location.Y, location.Z })
        .value().get()
        .GetFaceByColor(bottomColor);

    // left
    if (location.X == 0)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
        {
            m_Cube.MakeMoves("S U2 S'");
            return;
        }
        // bottomColor on side
        if (bottomColorFace == Face::Left)
        {
            m_Cube.MakeMoves("U S U' S'");
            return;
        }
    }
    // back
    if (location.Z == 0)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
        {
            m_Cube.MakeMoves("M U2 M'");
            return;
        }
        // bottomColor on side
        if (bottomColorFace == Face::Back)
        {
            m_Cube.MakeMoves("U' M U M'");
            return;
        }
    }
    // right
    if (location.X == m_Cube.GetSize() - 1)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
        {
            m_Cube.MakeMoves("S' U2 S");
            return;
        }
        // bottomColor on side
        if (bottomColorFace == Face::Right)
        {
            m_Cube.MakeMoves("U' S' U S");
            return;
        }
    }
    // front
    if (location.Z == m_Cube.GetSize() - 1)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
        {
            m_Cube.MakeMoves("M' U2 M");
            return;
        }
        // bottomColor on side
        if (bottomColorFace == Face::Front)
        {
            m_Cube.MakeMoves("U M' U' M");
            return;
        }
    }

    std::unreachable();
}