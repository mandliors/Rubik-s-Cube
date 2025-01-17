#include "CubeSolver.hpp"
#include "ColorPattern/ColorPattern.hpp"

#include <utility>

const std::array<Algorithm, 7> CubeSolver::s_2x2_OLLs = {
    Algorithm {
        .Pattern = ColorPattern { "DBDBDDDB" },
        .Moves = "L' U2 L U L' U L"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDBDDDBD" },
        .Moves = "R U2 R' U' R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDDDDBDD" },
        .Moves = "R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBBDD" },
        .Moves = "R2 U2 R U2 R2"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDBDBB" },
        .Moves = "F R U R' U' R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDBD" },
        .Moves = "F' R U R' U' R' F R"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDDDDDBB" },
        .Moves = "F R U R' U' F'"
    }
};

const std::array<Algorithm, 2> CubeSolver::s_2x2_PLLs = {
    Algorithm {
        .Pattern = ColorPattern { "LOLOLOLO" },
        .Moves = "F R U' R' U' R U R' F' R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LLLOLLLS" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F'"
    }
};

const std::array<Algorithm, 57> CubeSolver::s_3x3_OLLs = {
    Algorithm {
        .Pattern = ColorPattern { "DBDBBBDBDBBB" },
        .Moves = "R U2 R2 F R F' U2 R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBDBBDBBB" },
        .Moves = "F R U R' U' S R U R' U' f'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBBDBDDBB" },
        .Moves = "F U R U' R' F' U F R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBDBBDBBD" },
        .Moves = "M U' r U2 r' U' R U' R' M'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBBDDDDDB" },
        .Moves = "l' U2 L U L' U l"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDBDDDDDBBD" },
        .Moves = "r U2 R' U' R U' r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBBDDBDDD" },
        .Moves = "r U R' U R U2 r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDDDBDDBBD" },
        .Moves = "l' U' L U' L' U2 l"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBDBDDBDD" },
        .Moves = "R U R' U' R' F R2 U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDBDBDDBBDDB" },
        .Moves = "R U R' U R' F R F' R U2 R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBDDDBDDB" },
        .Moves = "r U R' U R' F R F' R U2 r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDBDDBDDDBD" },
        .Moves = "M' R' U' R U' R' U2 R U' R r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDDBDBBDDD" },
        .Moves = "F U R U' R2 F' R U R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDDDBBDBDD" },
        .Moves = "R' F R U R' F' R F U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDDBDBDDDB" },
        .Moves = "l' U' l L' U' L U l' U l"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDBDDDBDBDD" },
        .Moves = "r U r' R U R' U' r U' r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBBDBDDBD" },
        .Moves = "F R' F' R2 r' U R U' R' U' M'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBBDBDDBDDBD" },
        .Moves = "r U R' U R U2 r r U' R U' R' U2 r"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDBBDDBDDBB" },
        .Moves = "r' R U R U R' U' M' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDBDDBDDBD" },
        .Moves = "r U R' U' M2 U R U' R' U' M'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDBDDDBDBDDD" },
        .Moves = "R U2 R' U' R U R' U' R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDBDDDBDDBDB" },
        .Moves = "R U2 R2 U' R2 U' R2 U2 R"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDDDDDBDBDDD" },
        .Moves = "R2 D' R U2 R' D R U2 R"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDDDDDDDBDDD" },
        .Moves = "r U R' U' r' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDBDDDDDDBDD" },
        .Moves = "F' r U R' U' r' F R"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDDBDDDDDBDD" },
        .Moves = "R U2 R' U' R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDBDDBDDBDDD" },
        .Moves = "R U R' U R U2 R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDBDDDDDDD" },
        .Moves = "r U R' U' r' R U R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBDDDBDDD" },
        .Moves = "R U R' U' R U' R' F' U' F R U R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDBBDDDBDD" },
        .Moves = "F R' F R2 U' R' U' R U R' F2"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDDDDDBDBD" },
        .Moves = "R' U' F U R U' R' F' R"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBDBDDDDD" },
        .Moves = "L U F' U' L' U L F L'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDDDDBBDDD" },
        .Moves = "R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDBDBDBDD" },
        .Moves = "R U R2 U' R' F R U R U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDDDDBDBDDBD" },
        .Moves = "R U2 R2 F R F' R U2 R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDBDDDBB" },
        .Moves = "L' U' L U' L' U L U L F' L' F"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDDBBDDDDDD" },
        .Moves = "F R' F' R U R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDBBDDDBDDD" },
        .Moves = "R U R' U R U' R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDBDDDBBDDD" },
        .Moves = "L F' L' U' L U F U' L'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDBBDDDB" },
        .Moves = "R' F R U R' U' F' U R"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDBDBDBDDD" },
        .Moves = "R U R' U R U2 R' F R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDBDBDDBDDDD" },
        .Moves = "R' U' R U' R' U2 R F R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDDDDBBB" },
        .Moves = "F' U' L' U L F"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDBBBDDDDDD" },
        .Moves = "F U R U' R' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDDBDBDB" },
        .Moves = "F R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDDBBBDDDDBD" },
        .Moves = "R' U' R' F R F' U R"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDBDBDDBDBD" },
        .Moves = "R' U' R' F R F' R' F R F' U R"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDBDBDDBDB" },
        .Moves = "F R U R' U' R U R' U' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBBDDDBDDBBB" },
        .Moves = "r U' r r U r r U r r U' r"
    },
    Algorithm {
        .Pattern = ColorPattern { "DDBDDDBBDBBB" },
        .Moves = "r' U r r U' r r U' r r U r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBDBDBDBBDDD" },
        .Moves = "F U R U' R' U R U' R' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BDDBBBDDBDBD" },
        .Moves = "R U R' U R U' B U' B' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBBDDDBDBDBD" },
        .Moves = "l' U2 L U L' U' L U L' U l"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBBDBDBDBDDD" },
        .Moves = "r U2 R' U' R U R' U' R U' r'"
    },
    Algorithm {
        .Pattern = ColorPattern { "BBBDDDBBBDDD" },
        .Moves = "R' F R U R U' R2 F' R2 U' R' U R U R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDBDBDBDBDB" },
        .Moves = "r' U' r U' R' U R U' R' U R r' U r"
    },
    Algorithm {
        .Pattern = ColorPattern { "DBDDDDDBDDDD" },
        .Moves = "R U R' U' M' U R U' r'"
    }
};

const std::array<Algorithm, 21> CubeSolver::s_3x3_PLLs = {
    Algorithm {
        .Pattern = ColorPattern { "LLSLSOLORLLR" },
        .Moves = "x L2 D2 L' U' L D2 L' U L' x'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LROLOSLSLLRL" },
        .Moves = "x' L2 D2 L U L' D2 L U' L x"
    },
    Algorithm {
        .Pattern = ColorPattern { "LORLRRLROLSS" },
        .Moves = "R' U' F' R U R' U' R' F R2 U' R' U' R U R' U R"
    },
    Algorithm {
        .Pattern = ColorPattern { "LLSLLLLROLRL" },
        .Moves = "R2 U R' U R' U' R U' R2 U' D R' U R D'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LORLOSLORLOO" },
        .Moves = "R' U' R U D' R2 U R' U R U' R U' R2 D"
    },
    Algorithm {
        .Pattern = ColorPattern { "LORLLLLSLLLR" },
        .Moves = "R2 U' R U' R U R' U R2 U D' R U' R' D"
    },
    Algorithm {
        .Pattern = ColorPattern { "LROLSOLROLOO" },
        .Moves = "R U R' U' D R2 U' R U' R' U R' U R2 D'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSLLSOLSLLSS" },
        .Moves = "x R2 F R F' R U2 r' U r U2 x'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LLSLOSLLSLSS" },
        .Moves = "R U R' F' R U R' U' R' F R2 U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSLLRRLORLRL" },
        .Moves = "R U' R' U' R U R D R' U' R D' R' U2 R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LROLRRLLSLLR" },
        .Moves = "R2 F R U R U' R' F' R U2 R' U2 R"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSLLLLLLSLOO" },
        .Moves = "R U R' U' R' F R2 U' R' U' R U R' F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LLLLRRLLLLRR" },
        .Moves = "x' L' U L D' L' U' L D L' U' L D' L' U L D x"
    },
    Algorithm {
        .Pattern = ColorPattern { "LOSLOSLOSLOS" },
        .Moves = "R U R' U R U R' F' R U R' U' R' F R2 U' R' U2 R U' R'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSOLSOLSOLSO" },
        .Moves = "R' U R U' R' F' U' F R U R' F R' F' R U' R"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSOLRRLRRLOS" },
        .Moves = "R' U R' U' y R' F' R2 U' R' U R' F R F y'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LSOLOSLLLLLL" },
        .Moves = "F R U' R' U' R U R' F' R U R' U' R' F R F'"
    },
    Algorithm {
        .Pattern = ColorPattern { "LOOLOOLOOLOO" },
        .Moves = "M2 U M2 U2 M2 U M2"
    },
    Algorithm {
        .Pattern = ColorPattern { "LLRLOOLSSLLR" },
        .Moves = "M2 U M U2 M' U M2"
    },
    Algorithm {
        .Pattern = ColorPattern { "LRLLRLLSSLOO" },
        .Moves = "M2 U' M U2 M' U' M2"
    },
    Algorithm {
        .Pattern = ColorPattern { "LRLLLRLRLLLR" },
        .Moves = "M' U M2 U M2 U M' U2 M2"
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
    _SolveAUF();
}
auto CubeSolver::_Solve3x3() -> void
{
    uint32_t lastLayerIndex = m_Cube.GetSize() - 1;

    _SolveWhiteCenterToBottom();
    _SolveGreenCenterToFrontAfterWhiteCenter();
    
    _SolveEdgeToBottom(FaceColor::White, FaceColor::Red, { 0, 0, 1 }, FaceColor::White);
    _SolveEdgeToBottom(FaceColor::White, FaceColor::Blue, { 1, 0, 0 }, FaceColor::White);
    _SolveEdgeToBottom(FaceColor::White, FaceColor::Orange, { lastLayerIndex, 0, 1 }, FaceColor::White);
    _SolveEdgeToBottom(FaceColor::White, FaceColor::Green, { 1, 0, lastLayerIndex }, FaceColor::White);

    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Green, { 0, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Green, { lastLayerIndex, 0, lastLayerIndex }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Orange, FaceColor::Blue, { lastLayerIndex, 0, 0 }, FaceColor::White);
    _SolveCorner(FaceColor::White, FaceColor::Red, FaceColor::Blue, { 0, 0, 0 }, FaceColor::White);

    _SolveEdgeToSecondLayer(FaceColor::Red, FaceColor::Blue, { 0, 1, 0 });
    _SolveEdgeToSecondLayer(FaceColor::Blue, FaceColor::Orange, { lastLayerIndex, 1, 0 });
    _SolveEdgeToSecondLayer(FaceColor::Orange, FaceColor::Green, { lastLayerIndex, 1, lastLayerIndex });
    _SolveEdgeToSecondLayer(FaceColor::Red, FaceColor::Green, { 0, 1, lastLayerIndex });

    _SolveOLL(s_3x3_OLLs, FaceColor::Yellow);
    _SolvePLL(s_3x3_PLLs);
    _SolveAUF();
}


auto CubeSolver::_SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void
{
    PieceLocation cornerLocation = m_Cube.GetPieceLocationByExactColors(color1, color2, color3).value();
    
    // already solved
    if (cornerLocation == destLocation && m_Cube.GetPieceColors(destLocation).value().get()[Face::Bottom] == bottomColor)
        return;

    // move the corner to the top layer, then above the destination, and finally insert it to the destination
    _InsertCornerToBottom(
        _MoveCornerOnTopToPosition(
            _MoveCornerToTop(cornerLocation),
            destLocation.X, destLocation.Z
        ),
        bottomColor
    );
}
auto CubeSolver::_SolveEdgeToBottom(FaceColor color1, FaceColor color2, PieceLocation destLocation, FaceColor bottomColor) -> void
{
    PieceLocation edgeLocation = m_Cube.GetPieceLocationByExactColors(color1, color2).value();
    
    // already solved
    if (edgeLocation == destLocation && m_Cube.GetPieceColors(destLocation).value().get()[Face::Bottom] == bottomColor)
        return;
        
    // move the edge to the top layer, then above the destination, and finally insert it to the destination
    _InsertEdgeToBottom(
        _MoveEdgeOnTopToPosition(
            _MoveEdgeToTop(edgeLocation),
            destLocation.X, destLocation.Z
        ), 
        bottomColor
    );
}
auto CubeSolver::_SolveEdgeToSecondLayer(FaceColor color1, FaceColor color2, PieceLocation destLocation) -> void
{
    PieceLocation edgeLocation = m_Cube.GetPieceLocationByExactColors(color1, color2).value();
    
    // already solved
    if (edgeLocation == destLocation && (
        m_Cube.GetPieceColors(destLocation).value().get()[Face::Left] == FaceColor::Red ||
        m_Cube.GetPieceColors(destLocation).value().get()[Face::Back] == FaceColor::Blue ||
        m_Cube.GetPieceColors(destLocation).value().get()[Face::Right] == FaceColor::Orange ||
        m_Cube.GetPieceColors(destLocation).value().get()[Face::Front] == FaceColor::Green
    )) return;

    // move the edge to the top layer, then close to the destination, and finally insert it to the destination
    _InsertEdgeToSecondLayer(
        _MoveEdgeOnTopAboveCorrectSlot(
            _MoveInsertedEdgeToTop(edgeLocation)
        ),
        destLocation
    );
}
auto CubeSolver::_SolveOLL(const std::span<const Algorithm>& OLLs, FaceColor faceColor) -> void
{
    ColorPattern OLLPattern = ColorPattern::CreateOLLPatternFromTopLayer(m_Cube, faceColor);
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
    ColorPattern PLLPattern = ColorPattern::CreatePLLPatternFromTopLayer(m_Cube);
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
auto CubeSolver::_SolveAUF() -> void
{
    uint32_t last = m_Cube.GetSize() - 1;
    uint32_t half = last / 2;

    FaceColor topCol = m_Cube.GetPieceColors({ half, last, last }).value().get()[Face::Front];
    FaceColor faceCol = m_Cube.GetPieceColors({ half, half, last }).value().get()[Face::Front];

    ColorPattern::ColorDescriptor desc = ColorPattern::CreateDescriptorFromTwoColors(topCol, faceCol);

    switch (desc)
    {
    case ColorPattern::ColorDescriptor::LEFT_NEIGHBOR:
        m_Cube.MakeMove(Move::U);
        break;
    case ColorPattern::ColorDescriptor::RIGHT_NEIGHBOR:
        m_Cube.MakeMove(Move::U_);
        break;
    case ColorPattern::ColorDescriptor::OPPOSITE:
        m_Cube.MakeMove(Move::U2);
        break;
    
    default:
        break;
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
auto CubeSolver::_MoveCornerOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> PieceLocation
{
    // already in the correct position
    if (location.X == destX && location.Z == destZ)
        return { destX, m_Cube.GetSize() - 1, destZ };

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

    return { destX, m_Cube.GetSize() - 1, destZ };
}
auto CubeSolver::_InsertCornerToBottom(PieceLocation location, FaceColor bottomColor) -> PieceLocation
{
    // get the bottomColor colored face
    Face bottomColorFace = m_Cube
        .GetPieceColors(location)
        .value().get()
        .GetFaceByColor(bottomColor);

    // top left back
    if (location.X == 0 && location.Z == 0)
    {
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves("B' U' B");
            break;
        case Face::Left:
            m_Cube.MakeMoves("L U L'");
            break;
        case Face::Top:
            m_Cube.MakeMoves("L U2 L' U' L U L'");
            break;
        
        default:
            std::unreachable();
        }
    }
    // top right back
    else if (location.X != 0 && location.Z == 0)
    {
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves("B U B'");
            break;
        case Face::Right:
            m_Cube.MakeMoves("R' U' R");
            break;
        case Face::Top:
            m_Cube.MakeMoves("R' U2 R U R' U' R");
            break;
        
        default:
            std::unreachable();
        }
    }
    // top right front
    else if (location.X != 0 && location.Z != 0)
    {        
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves("F' U' F");
            break;
        case Face::Right:
            m_Cube.MakeMoves("R U R'");
            break;
        case Face::Top:
            m_Cube.MakeMoves("R U2 R' U' R U R'");
            break;
        
        default:
            std::unreachable();
        }
    }
    // top left front
    else if (location.X == 0 && location.Z != 0)
    {       
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves("F U F'");
            break;
        case Face::Left:
            m_Cube.MakeMoves("L' U' L");
            break;
        case Face::Top:
            m_Cube.MakeMoves("L' U2 L U L' U' L");
            break;
        
        default:
            std::unreachable();
        }
    }

    return { location.X, 0, location.Z };
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
auto CubeSolver::_MoveInsertedEdgeToTop(PieceLocation location) -> PieceLocation
{
    // already on top
    if (location.Y == m_Cube.GetSize() - 1)
        return location;

    // left
    if (location.X == 0)
    {
        _InsertEdgeToSecondLayer({ 0, m_Cube.GetSize() - 1, 1 }, location);
        return { m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, 1 };
    }
    // right
    if (location.X == m_Cube.GetSize() - 1)
    {
        _InsertEdgeToSecondLayer({ m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, 1 }, location);
        return { 0, m_Cube.GetSize() - 1, 1 };
    }

    std::unreachable();
}
auto CubeSolver::_MoveEdgeOnTopAboveCorrectSlot(PieceLocation location) -> PieceLocation
{
    PieceColors& edgeColors = m_Cube.GetPieceColors(location).value().get();

    // get the side color
    FaceColor sideColor;
    if (edgeColors[Face::Left] != FaceColor::None)
        sideColor = edgeColors[Face::Left];
    else if (edgeColors[Face::Back] != FaceColor::None)
        sideColor = edgeColors[Face::Back];
    else if (edgeColors[Face::Right] != FaceColor::None)
        sideColor = edgeColors[Face::Right];
    else if (edgeColors[Face::Front] != FaceColor::None)
        sideColor = edgeColors[Face::Front];

    uint32_t destX, destZ;
    switch (sideColor)
    {
    case FaceColor::Red:
        destX = 0;
        destZ = 1;
        break;
    case FaceColor::Blue:
        destX = 1;
        destZ = 0;
        break;
    case FaceColor::Orange:
        destX = 2;
        destZ = 1;
        break;
    case FaceColor::Green:
        destX = 1;
        destZ = 2;
        break;
    
    default:
        std::unreachable();
    }

    return _MoveEdgeOnTopToPosition(location, destX, destZ);
}
auto CubeSolver::_MoveEdgeOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> PieceLocation
{
    // already in the correct position
    if (location.X == destX && location.Z == destZ)
        return { destX, m_Cube.GetSize() - 1, destZ };

    // make a U2
    if (location.X == destX || location.Z == destZ)
        m_Cube.MakeMove(Move::U2);
    // make one U or U'
    else
    {
        // clockwise cases
        if ((location.X == 0 && destZ == 0) || (location.X == m_Cube.GetSize() - 1 && destZ == m_Cube.GetSize() - 1))
            m_Cube.MakeMove(Move::U);
        // clockwise cases #2
        else if ((location.Z == 0 && destX == m_Cube.GetSize() - 1) || (location.Z == m_Cube.GetSize() - 1 && destX == 0))
            m_Cube.MakeMove(Move::U);

        // counter-clockwise cases
        else if ((location.X == 0 && destZ == m_Cube.GetSize() - 1) || (location.X == m_Cube.GetSize() - 1 && destZ == 0))
            m_Cube.MakeMove(Move::U_);
        // counter-clockwise cases #2
        else if ((location.Z == 0 && destX == 0) || (location.Z == m_Cube.GetSize() - 1 && destX == m_Cube.GetSize() - 1))
            m_Cube.MakeMove(Move::U_);
    }

    return { destX, m_Cube.GetSize() - 1, destZ };
}
auto CubeSolver::_InsertEdgeToBottom(PieceLocation location, FaceColor bottomColor) -> PieceLocation
{
    // get the bottomColor colored face
    Face bottomColorFace = m_Cube
        .GetPieceColors(location)
        .value().get()
        .GetFaceByColor(bottomColor);

    // left
    if (location.X == 0)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
            m_Cube.MakeMoves("S U2 S'");
        // bottomColor on side
        if (bottomColorFace == Face::Left)
            m_Cube.MakeMoves("U S U' S'");
    }
    // back
    else if (location.Z == 0)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
            m_Cube.MakeMoves("M U2 M'");
        // bottomColor on side
        if (bottomColorFace == Face::Back)
            m_Cube.MakeMoves("U' M U M'");
    }
    // right
    else if (location.X == m_Cube.GetSize() - 1)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
            m_Cube.MakeMoves("S' U2 S");
        // bottomColor on side
        if (bottomColorFace == Face::Right)
            m_Cube.MakeMoves("U' S' U S");
    }
    // front
    else if (location.Z == m_Cube.GetSize() - 1)
    {
        // bottomColor on top
        if (bottomColorFace == Face::Top)
            m_Cube.MakeMoves("M' U2 M");
        // bottomColor on side
        if (bottomColorFace == Face::Front)
            m_Cube.MakeMoves("U M' U' M");
    }

    return { location.X, 0, location.Z };
}

auto CubeSolver::_InsertEdgeToSecondLayer(PieceLocation location, PieceLocation dest) -> PieceLocation
{
    // left
    if (location.X == 0)
    {
        // back
        if (dest.Z == 0)
            m_Cube.MakeMoves("U' B' U B U L U' L'");
        // front
        else if (dest.Z == m_Cube.GetSize() - 1)
            m_Cube.MakeMoves("U F U' F' U' L' U L");
    }
    // right
    else if (location.X == m_Cube.GetSize() - 1)
    {
        // back
        if (dest.Z == 0)
            m_Cube.MakeMoves("U B U' B' U' R' U R");
        // front
        else if (dest.Z == m_Cube.GetSize() - 1)
            m_Cube.MakeMoves("U' F' U F U R U' R'");
    }
    // back
    else if (location.Z == 0)
    {
        // left
        if (dest.X == 0)
            m_Cube.MakeMoves("U L U' L' U' B' U B");
        // right
        else if (dest.X == m_Cube.GetSize() - 1)
            m_Cube.MakeMoves("U' R' U R U B U' B'");
    }
    // front
    else if (location.Z == m_Cube.GetSize() - 1)
    {
        // left
        if (dest.X == 0)
            m_Cube.MakeMoves("U' L' U L U F U' F'");
        // right
        else if (dest.X == m_Cube.GetSize() - 1)
            m_Cube.MakeMoves("U R U' R' U' F' U F");
    }

    return dest;
}