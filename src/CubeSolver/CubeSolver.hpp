#ifndef CUBESOLVER_H
#define CUBESOLVER_H

#include "Cube/Cube.hpp"
#include "Algorithm/Algorithm.hpp"

#include <span>

class CubeSolver
{
public:
    explicit CubeSolver(Cube& cube);

    auto Solve() -> void;

private:
    static const std::array<Algorithm, 7> s_2x2_OLLs;
    static const std::array<Algorithm, 6> s_2x2_PLLs;

private:
    auto _Solve2x2() -> void;
    auto _Solve3x3() -> void;

    auto _SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void;
    auto _SolveOLL(std::span<const Algorithm> OLLs, FaceColor faceColor) -> void;
    auto _SolvePLL(std::span<const Algorithm> PLLs) -> void;

    auto _MoveCornerToTop(PieceLocation location) -> PieceLocation;
    auto _MoveCornerOnTopToPosition(PieceLocation location, uint32_t x, uint32_t z) -> void;
    auto _InsertCornerToBottom(PieceLocation location, FaceColor bottomColor) -> void;

private:
    Cube& m_Cube;
};

#endif