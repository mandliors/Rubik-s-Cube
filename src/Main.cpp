#include "Cube/Cube.hpp"
#include "CubeSolver/CubeSolver.hpp"

#include <raylib.h>

#include <iostream>

auto CheckMoves(Cube& cube) -> void;

int main()
{
    InitWindow(1600, 1200, "Rubix Cube");
    SetTargetFPS(120);

    Camera camera = {
        .position = { 0.0f, 0.0f, 7.0f },
        .target = { 0.0f, 0.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    Cube cube { 2, Vector3{ 0, 0, 0 }, 2.0f };
    cube.Rotate(0.4f, -0.2f, 0.0f);

    CubeSolver solver(cube);

    cube.MakeMoves("z2 R U R' U'");

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            cube.Scramble();
        if (IsKeyPressed(KEY_ENTER))
            solver.Solve();

        CheckMoves(cube);

        BeginDrawing();
        BeginMode3D(camera);

        ClearBackground(Color{ 40, 40, 40, 255 });

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
            DisableCursor();

        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
            cube.Rotate(GetMouseDelta().y * 0.003f, GetMouseDelta().x * 0.003f, 0);
        
        if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
            EnableCursor();


        cube.Draw();

        EndMode3D();

        DrawText(cube.IsSolved() ? "Solved" : "Not solved", 20, 20, 40, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

auto CheckMoves(Cube& cube) -> void
{
    if (IsKeyDown(KEY_LEFT_SHIFT))
    {
        if (IsKeyPressed(KEY_U))
            cube.MakeMove(Move::U_);
        if (IsKeyPressed(KEY_F))
            cube.MakeMove(Move::F_);
        if (IsKeyPressed(KEY_R))
            cube.MakeMove(Move::R_);
        if (IsKeyPressed(KEY_B))
            cube.MakeMove(Move::B_);
        if (IsKeyPressed(KEY_L))
            cube.MakeMove(Move::L_);
        if (IsKeyPressed(KEY_D))
            cube.MakeMove(Move::D_);
        if (IsKeyPressed(KEY_M))
            cube.MakeMove(Move::M_);
    }
    else
    {
        if (IsKeyPressed(KEY_U))
            cube.MakeMove(Move::U);
        if (IsKeyPressed(KEY_F))
            cube.MakeMove(Move::F);
        if (IsKeyPressed(KEY_R))
            cube.MakeMove(Move::R);
        if (IsKeyPressed(KEY_B))
            cube.MakeMove(Move::B);
        if (IsKeyPressed(KEY_L))
            cube.MakeMove(Move::L);
        if (IsKeyPressed(KEY_D))
            cube.MakeMove(Move::D);
        if (IsKeyPressed(KEY_M))
            cube.MakeMove(Move::M);
    }
}