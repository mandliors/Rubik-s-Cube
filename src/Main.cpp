#include "Cube/Cube.hpp"
#include "CubeSolver/CubeSolver.hpp"

#include <raylib.h>

#include <array>

auto CheckMoves(Cube& cube) -> void;
auto RecreteCubeAndSolver(Cube* cube, uint32_t cubeSize, CubeSolver* solver) -> void;

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

    uint32_t cubeSize = 3;
    Cube cube { cubeSize, { 0, 0, 0 }, 2.0f };
    CubeSolver solver { cube };

    RecreteCubeAndSolver(&cube, cubeSize, &solver);

    std::array<std::string, 7> texts = {
        "U/F/R/B/L/D/M/E/S: CW turns",
        "SHIFT+U/F/R/B/L/D/M/E/S: CCW turns",
        "SPACE: scramble cube",
        "ENTER: solve cube",
        "TAB: toggle rotation anim.",
        "UP/DOWN: change anim. speed",
        "LEFT/RIGHT: change cube size",
    };

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            cube.Reset();
            cube.Rotate(0.4f, -0.2f, 0.0f);
        }
        if (IsKeyPressed(KEY_SPACE))
            cube.Scramble();
        if (IsKeyPressed(KEY_ENTER))
            solver.Solve();
        if (IsKeyPressed(KEY_TAB))
            cube.SetAnimationsEnabled(!cube.GetAnimationsEnabled());
        if (IsKeyPressed(KEY_UP))
            cube.SetAnimationSpeed(cube.GetAnimationSpeed() / 0.9f);
        if (IsKeyPressed(KEY_DOWN))
            cube.SetAnimationSpeed(cube.GetAnimationSpeed() * 0.9f);
        if (IsKeyPressed(KEY_LEFT))
        {
            cubeSize = cubeSize > 2 ? cubeSize - 1 : 2;
            RecreteCubeAndSolver(&cube, cubeSize, &solver);
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            cubeSize = cubeSize < 69 ? cubeSize + 1 : 69;
            RecreteCubeAndSolver(&cube, cubeSize, &solver);
        }

        if (cube.IsSolved())
            SetWindowTitle("Rubix Cube [SOLVED]");
        else
            SetWindowTitle("Rubix Cube");

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

        cube.Update(GetFrameTime());
        cube.Draw();

        EndMode3D();

        for (uint32_t i = 0; i < texts.size(); i++)
            DrawText(texts[i].c_str(), 20, 20 + 28 * i, 28, GRAY);

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
        if (IsKeyPressed(KEY_E))
            cube.MakeMove(Move::E_);
        if (IsKeyPressed(KEY_S))
            cube.MakeMove(Move::S_);
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
        if (IsKeyPressed(KEY_E))
            cube.MakeMove(Move::E);
        if (IsKeyPressed(KEY_S))
            cube.MakeMove(Move::S);
    }
}
auto RecreteCubeAndSolver(Cube* cube, uint32_t cubeSize, CubeSolver* solver) -> void
{
    *cube = Cube { cubeSize, Vector3{ 0, 0, 0 }, 2.0f };
    cube->Rotate(0.4f, -0.2f, 0.0f);

    *solver = CubeSolver { *cube };
}