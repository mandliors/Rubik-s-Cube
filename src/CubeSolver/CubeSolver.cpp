#include "CubeSolver.hpp"

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
    PieceLocation wrg = m_Cube.GetPieceLocationByColors(FaceColor::White, FaceColor::Red, FaceColor::Green).value();

    if (wrg.X == 0 && wrg.Y == 0 && wrg.Z == 0)
    {
        m_Cube.TurnD();
    }
    else if (wrg.X == 0 && wrg.Y == 0 && wrg.Z == 1)   
    {
        ;
    }
    else if (wrg.X == 0 && wrg.Y == 1 && wrg.Z == 0)
    {
        m_Cube.TurnB();
        m_Cube.TurnD();
    }
    else if (wrg.X == 0 && wrg.Y == 1 && wrg.Z == 1)
    {
        m_Cube.TurnL();
    }
    else if (wrg.X == 1 && wrg.Y == 0 && wrg.Z == 0)
    {
        m_Cube.TurnD();
        m_Cube.TurnD();
    }
    else if (wrg.X == 1 && wrg.Y == 0 && wrg.Z == 1)
    {
        m_Cube.TurnD(false);
    }
    else if (wrg.X == 1 && wrg.Y == 1 && wrg.Z == 0)
    {
        m_Cube.TurnR();
        m_Cube.TurnD();
        m_Cube.TurnD();
    }
    else if (wrg.X == 1 && wrg.Y == 1 && wrg.Z == 1)
    {
        m_Cube.TurnF();
        m_Cube.TurnF();
    }
}
auto CubeSolver::_Solve3x3() -> void
{
    return;
}