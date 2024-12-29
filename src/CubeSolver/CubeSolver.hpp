#ifndef CUBESOLVER_H
#define CUBESOLVER_H

#include "Cube/Cube.hpp"

class CubeSolver
{
public:
    CubeSolver(Cube& cube);

    auto Solve() -> void;

private:
    auto _Solve2x2() -> void;
    auto _Solve3x3() -> void;

private:
    Cube& m_Cube;
};

#endif