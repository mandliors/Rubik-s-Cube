#include "Cube/Cube.hpp"
#include "CubeSolver/CubeSolver.hpp"

#include <raylib.h>

#include <array>

enum class GameState
{
    MENU = 0,
    PLAYGROUND,
    DUEL
};

constexpr float WINDOW_SCALE = 2.0f;

constexpr uint32_t WINDOW_WIDTH = static_cast<uint32_t>(800 * WINDOW_SCALE);
constexpr uint32_t WINDOW_HEIGHT = static_cast<uint32_t>(600 * WINDOW_SCALE);
constexpr uint32_t WINDOW_PADDING = static_cast<uint32_t>(10 * WINDOW_SCALE);
constexpr uint32_t TEXT_SIZE = static_cast<uint32_t>(14 * WINDOW_SCALE);

auto Playground(const Camera& camera) -> GameState;
auto RecreateCubeAndSolver(Cube* cube, uint32_t cubeSize, CubeSolver* solver) -> void;

int main()
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetTargetFPS(120);

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rubix Cube");
    SetExitKey(KEY_NULL);

    Camera camera = {
        .position = { 2.0f, 2.5f, 6.0f },
        .target = { 0.0f, 0.0f, 0.0f },
        .up = { 0.0f, 1.0f, 0.0f },
        .fovy = 45.0f,
        .projection = CAMERA_PERSPECTIVE
    };

    GameState state = GameState::MENU;

    while (!WindowShouldClose())
    {
        switch(state)
        {
            case GameState::MENU:
            {
                if (IsKeyPressed(KEY_ENTER))
                    state = GameState::PLAYGROUND;
                else if (IsKeyPressed(KEY_ESCAPE))
                    CloseWindow();

                BeginDrawing();
                ClearBackground(Color{ 40, 40, 40, 255 });
                EndDrawing();

                break;
            }
            case GameState::PLAYGROUND:
            {
                state = Playground(camera);
                break;
            }
            case GameState::DUEL:
            {
                break;
            }
        } 
    }

    CloseWindow();

    return 0;
}

auto Playground(const Camera& camera) -> GameState
{
    static std::array<std::string, 8> texts = {
        "U/F/R/B/L/D/M/E/S: CW turns",
        "SHIFT+U/F/R/B/L/D/M/E/S: CCW turns",
        "UP/DOWN: change animation speed",
        "TAB: toggle rotation animation",
        "LEFT/RIGHT: change cube size",
        "SPACE: scramble cube",
        "ENTER: solve cube",
        "ESCAPE: back to menu"
    };

    static uint32_t cubeSize = 3;
    static Cube cube { cubeSize, { 0, 0, 0 }, 2.0f };
    static CubeSolver solver { cube };

    // back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        SetWindowTitle("Rubix Cube");
        return GameState::MENU;
    }

    // moves
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

    // algorithms
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
        RecreateCubeAndSolver(&cube, cubeSize, &solver);
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        cubeSize = cubeSize < 69 ? cubeSize + 1 : 69;
        RecreateCubeAndSolver(&cube, cubeSize, &solver);
    }

    // cube rotation
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        DisableCursor();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        cube.Rotate(GetMouseDelta().y * 0.003f, GetMouseDelta().x * 0.003f, 0);
    
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        EnableCursor();

    // check if solved
    if (cube.IsSolved())
        SetWindowTitle("Rubix Cube [SOLVED]");
    else
        SetWindowTitle("Rubix Cube");   

    BeginDrawing();
    BeginMode3D(camera);

    ClearBackground(Color{ 40, 40, 40, 255 });

    cube.Update(GetFrameTime());
    cube.Draw();

    EndMode3D();

    for (uint32_t i = 0; i < texts.size(); i++)
        DrawText(texts[i].c_str(), WINDOW_PADDING, WINDOW_PADDING + TEXT_SIZE * i, TEXT_SIZE, GRAY);

    EndDrawing();

    return GameState::PLAYGROUND;
}
auto RecreateCubeAndSolver(Cube* cube, uint32_t cubeSize, CubeSolver* solver) -> void
{
    *cube = Cube { cubeSize, Vector3{ 0, 0, 0 }, 2.0f };
    *solver = CubeSolver { *cube };
}