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
    static const std::array<Algorithm, 2> s_2x2_PLLs;

    static const std::array<Algorithm, 57> s_3x3_OLLs;
    static const std::array<Algorithm, 21> s_3x3_PLLs;

private:
    auto _Solve2x2() -> void;
    auto _Solve3x3() -> void;

    auto _SolveCorner(FaceColor color1, FaceColor color2, FaceColor color3, PieceLocation destLocation, FaceColor bottomColor) -> void;
    auto _SolveEdgeToBottom(FaceColor color1, FaceColor color2, PieceLocation destLocation, FaceColor bottomColor) -> void;
    auto _SolveEdgeToSecondLayer(FaceColor color1, FaceColor color2, PieceLocation destLocation) -> void;

    auto _SolveOLL(const std::span<const Algorithm>& OLLs, FaceColor faceColor) -> void;
    auto _SolvePLL(const std::span<const Algorithm>& PLLs) -> void;
    auto _SolveAUF() -> void;

    auto _SolveWhiteCenterToBottom() -> void;
    auto _SolveGreenCenterToFrontAfterWhiteCenter() -> void;

    auto _MoveCornerToTop(PieceLocation location) -> PieceLocation;
    auto _MoveCornerOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> PieceLocation;
    auto _InsertCornerToBottom(PieceLocation location, FaceColor bottomColor) -> PieceLocation;

    auto _MoveEdgeToTop(PieceLocation location) -> PieceLocation;
    auto _MoveInsertedEdgeToTop(PieceLocation location) -> PieceLocation;
    auto _MoveEdgeOnTopAboveCorrectSlot(PieceLocation location) -> PieceLocation;
    auto _MoveEdgeOnTopToPosition(PieceLocation location, uint32_t destX, uint32_t destZ) -> PieceLocation;
    auto _InsertEdgeToBottom(PieceLocation location, FaceColor bottomColor) -> PieceLocation;

    auto _InsertEdgeToSecondLayer(PieceLocation location, PieceLocation dest) -> PieceLocation;

private:
    Cube& m_Cube;
};

#endif