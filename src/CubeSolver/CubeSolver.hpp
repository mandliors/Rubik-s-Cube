#ifndef CUBESOLVER_H
#define CUBESOLVER_H

#include "Cube/Cube.hpp"

class CubeSolver
{
public:
    explicit CubeSolver(Cube& cube);

    auto Solve() -> void;

private:
    auto _Solve2x2() -> void;
    auto _Solve3x3() -> void;

    auto _SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void;

    auto _MoveCornerToTop(PieceLocation location) -> PieceLocation;
    auto _MoveCornerOnTopToPosition(PieceLocation location, uint32_t x, uint32_t z) -> void;
    auto _InsertCornerToBottom(PieceLocation location, FaceColor bottomColor) -> void;

private:
    Cube& m_Cube;
};

#endif