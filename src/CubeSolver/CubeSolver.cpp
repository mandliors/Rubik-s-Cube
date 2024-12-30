#include "CubeSolver.hpp"

#include <utility>

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
}
auto CubeSolver::_Solve3x3() -> void
{
    m_Cube.MakeMove(Move::z2);
    // ...
}


auto CubeSolver::_SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void
{
    PieceLocation cornerLocation = m_Cube.GetPieceLocationByColors(color1, color2, color3).value();
    
    // already solved
    if (cornerLocation == destLocation && m_Cube.Get(destLocation).value().get().GetFaceColor(Face::Bottom) == bottomColor)
        return;

    // if on the bottom layer
    if (cornerLocation.Y == 0)
        cornerLocation = _MoveCornerToTop(cornerLocation);

    // move the corner above the destination
    _MoveCornerOnTopToPosition(cornerLocation, destLocation.X, destLocation.Z);

    // insert the corner to the destination (right below the current position)
    _InsertCornerToBottom({ destLocation.X, m_Cube.GetSize() - 1, destLocation.Z }, bottomColor);
}

auto CubeSolver::_MoveCornerToTop(PieceLocation location) -> PieceLocation
{
    // bottom left back
    if (location.X == 0 && location.Z == 0)
    {
        m_Cube.MakeMoves(Move::L, Move::U, Move::L_);
        return { m_Cube.GetSize() - 1, m_Cube.GetSize() - 1, 0 };
    }
    // bottom right back
    if (location.X == m_Cube.GetSize() - 1 && location.Z == 0)
    {
        m_Cube.MakeMoves(Move::R_, Move::U_, Move::R);
        return { 0, m_Cube.GetSize() - 1, 0 };
    }
    // bottom right front
    if (location.X == m_Cube.GetSize() - 1 && location.Z == m_Cube.GetSize() - 1)
    {
        m_Cube.MakeMoves(Move::R, Move::U, Move::R_);
        return { 0, m_Cube.GetSize() - 1, m_Cube.GetSize() - 1 };
    }
    // bottom left front
    if (location.X == 0 && location.Z == m_Cube.GetSize() - 1)
    {
        m_Cube.MakeMoves(Move::L_, Move::U_, Move::L);
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
    // top left back
    if (location.X == 0 && location.Z == 0)
    {
        Face bottomColorFace = m_Cube
            .Get({ location.X, location.Y, location.Z })
            .value().get()
            .GetFaceByColor(bottomColor);
        
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves(Move::B_, Move::U_, Move::B);
            return;
        case Face::Left:
            m_Cube.MakeMoves(Move::L, Move::U, Move::L_);
            return;
        case Face::Top:
            m_Cube.MakeMoves(Move::L, Move::U2, Move::L_, Move::U_, Move::L, Move::U, Move::L_);        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top right back
    if (location.X != 0 && location.Z == 0)
    {
        Face bottomColorFace = m_Cube
            .Get({ location.X, location.Y, location.Z })
            .value().get()
            .GetFaceByColor(bottomColor);
        
        switch (bottomColorFace)
        {
        case Face::Back:
            m_Cube.MakeMoves(Move::B, Move::U, Move::B_);
            return;
        case Face::Right:
            m_Cube.MakeMoves(Move::R_, Move::U_, Move::R);
            return;
        case Face::Top:
            m_Cube.MakeMoves(Move::R_, Move::U2, Move::R, Move::U, Move::R_, Move::U_, Move::R);        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top right front
    if (location.X != 0 && location.Z != 0)
    {
        Face bottomColorFace = m_Cube
            .Get({ location.X, location.Y, location.Z })
            .value().get()
            .GetFaceByColor(bottomColor);
        
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves(Move::F_, Move::U_, Move::F);
            return;
        case Face::Right:
            m_Cube.MakeMoves(Move::R, Move::U, Move::R_);
            return;
        case Face::Top:
            m_Cube.MakeMoves(Move::R, Move::U2, Move::R_, Move::U_, Move::R, Move::U, Move::R_);        
            return;
        
        default:
            std::unreachable();
        }
    }
    // top left front
    if (location.X == 0 && location.Z != 0)
    {
        Face bottomColorFace = m_Cube
            .Get({ location.X, location.Y, location.Z })
            .value().get()
            .GetFaceByColor(bottomColor);
        
        switch (bottomColorFace)
        {
        case Face::Front:
            m_Cube.MakeMoves(Move::F, Move::U, Move::F_);
            return;
        case Face::Left:
            m_Cube.MakeMoves(Move::L_, Move::U_, Move::L);
            return;
        case Face::Top:
            m_Cube.MakeMoves(Move::L_, Move::U2, Move::L, Move::U, Move::L_, Move::U_, Move::L);        
            return;
        
        default:
            std::unreachable();
        }
    }

    std::unreachable();
}