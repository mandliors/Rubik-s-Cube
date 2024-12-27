#include "Cube/Cube.hpp"

#include <raylib.h>

int main()
{
    InitWindow(1600, 1200, "Rubix Cube");
    SetTargetFPS(120);
    SetExitKey(0);

    Camera camera = {
        .position = { 2.0f, 4.0f, 6.0f },
        .target = { 0.0f, 0.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    Cube cube { 3, Vector3{ 0, 0, 0 }, 2.0f };

    while (!WindowShouldClose())
    {
        if (IsCursorHidden())
            UpdateCamera(&camera, CAMERA_FIRST_PERSON);

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
            DisableCursor();
        if (IsKeyPressed(KEY_ESCAPE))
        {
            if (IsCursorHidden())
                EnableCursor();
            else
                break;
        }

        if (IsKeyPressed(KEY_U))
            cube.TurnU(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_F))
            cube.TurnF(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_R))
            cube.TurnR(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_B))
            cube.TurnB(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_L))
            cube.TurnL(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_D))
            cube.TurnD(IsKeyDown(KEY_LEFT_SHIFT));
        if (IsKeyPressed(KEY_M))
            cube.TurnM(IsKeyDown(KEY_LEFT_SHIFT));


        BeginDrawing();
        BeginMode3D(camera);

        ClearBackground(Color{ 40, 40, 40, 255 });
        cube.Draw();

        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}