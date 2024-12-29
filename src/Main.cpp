#include "Cube/Cube.hpp"
#include "CubeSolver/CubeSolver.hpp"

#include <raylib.h>

#include <iostream>

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

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
            cube.Scramble();
        if (IsKeyPressed(KEY_ENTER))
            solver.Solve();

        if (IsKeyPressed(KEY_U))
            cube.TurnU(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_F))
            cube.TurnF(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_R))
            cube.TurnR(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_B))
            cube.TurnB(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_L))
            cube.TurnL(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_D))
            cube.TurnD(!IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_M))
            cube.TurnM(IsKeyDown(KEY_LEFT_SHIFT));


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

        DrawText(cube.IsSolved() ? "Solved" : "Not solved", 10, 10, 40, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}