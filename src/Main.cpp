#include "Cube/Cube.hpp"
#include "CubeSolver/CubeSolver.hpp"
#include "GUI/GUI.hpp"

#include <raylib.h>

#include <array>

enum class GameState
{
    MENU = 0,
    PLAYGROUND,
    DUEL,
    EXIT
};

constexpr float WINDOW_SCALE = 2.0f;

constexpr uint32_t WINDOW_WIDTH = static_cast<uint32_t>(800 * WINDOW_SCALE);
constexpr uint32_t WINDOW_HEIGHT = static_cast<uint32_t>(600 * WINDOW_SCALE);
constexpr uint32_t WINDOW_PADDING = static_cast<uint32_t>(10 * WINDOW_SCALE);
constexpr uint32_t TEXT_SIZE = static_cast<uint32_t>(14 * WINDOW_SCALE);

auto Menu() -> GameState;
auto Playground(const Camera& camera) -> GameState;
auto Duel(const Camera& camera) -> GameState;

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

    while (!WindowShouldClose() && state != GameState::EXIT)
    {
        switch(state)
        {
            case GameState::MENU:
            {
                state = Menu();
                break;
            }
            case GameState::PLAYGROUND:
            {
                state = Playground(camera);
                break;
            }
            case GameState::DUEL:
            {
                state = Duel(camera);
                break;
            }
            default:
                break;
        } 
    }

    CloseWindow();

    return 0;
}

auto Menu() -> GameState
{
    GameState nextState = GameState::MENU;

    if (IsKeyPressed(KEY_ESCAPE))
        nextState = GameState::EXIT;

    BeginDrawing();
    
    ClearBackground(Color{ 40, 40, 40, 255 });

    static constexpr uint32_t btnCount = 3;
    static constexpr uint32_t btnHeight = 100;
    static constexpr uint32_t btnSpacing = 20;
    static constexpr uint32_t btnOffset = btnHeight + btnSpacing;
    
    uint32_t btnY = WINDOW_HEIGHT / 2 - btnCount * 0.5f * btnOffset;    
    static gui::State btnStatePlayground = gui::State::NONE;
    if (gui::Button("Playground", WINDOW_WIDTH / 2, btnY, 400, 100, btnStatePlayground))
        return GameState::PLAYGROUND;

    btnY += btnOffset;
    static gui::State btnStateDuel = gui::State::NONE;
    if (gui::Button("Duel", WINDOW_WIDTH / 2, btnY, 300, 100, btnStateDuel))
        return GameState::DUEL;

    btnY += btnOffset;
    static gui::State btnStateExit = gui::State::NONE;
    if (gui::Button("Exit", WINDOW_WIDTH / 2, btnY, 250, 100, btnStateExit))
        return GameState::EXIT;

    EndDrawing();

    return nextState;
}

auto Playground(const Camera& camera) -> GameState
{
    static std::array<std::string, 9> texts = {
        "U/F/R/B/L/D/M/E/S: CW turns",
        "SHIFT+U/F/R/B/L/D/M/E/S: CCW turns",
        "UP/DOWN: change animation speed",
        "TAB: toggle rotation animation",
        "LEFT/RIGHT: change cube size",
        "SPACE: scramble cube",
        "ENTER: solve cube",
        "BACKSPACE: reset sube",
        "ESCAPE: back to menu"
    };

    static Cube cube { 3, { 0, 0, 0 }, 2.0f };
    static CubeSolver solver { cube };

    GameState nextState = GameState::PLAYGROUND;

    // back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        SetWindowTitle("Rubix Cube");
        cube.Reset();
        nextState = GameState::MENU;
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
        cube.Reset();
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
        uint32_t cubeSize = cube.GetSize();
        cubeSize = cubeSize > 2 ? cubeSize - 1 : 2;
        cube.SetSize(cubeSize);
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        uint32_t cubeSize = cube.GetSize();
        cubeSize = cubeSize < 69 ? cubeSize + 1 : 69;
        cube.SetSize(cubeSize);
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

    static bool hidden = false;
    if (gui::Panel("i", 60, 60, 80, 80, hidden))
    {
        for (uint32_t i = 0; i < texts.size(); i++)
            DrawText(texts[i].c_str(), WINDOW_PADDING, WINDOW_PADDING + TEXT_SIZE * i, TEXT_SIZE, GRAY);
     
        hidden = true;
    }
    else
        hidden = false;

    EndDrawing();

    return nextState;
}
auto Duel(const Camera& camera) -> GameState
{
    static std::array<std::string, 1> texts = {
        "U/F/R/B/L/D/M/E/S: CW turns"
    };

    static Cube cube { 3, { 0, 0, 0 }, 2.0f };
    static CubeSolver solver { cube };

    GameState nextState = GameState::DUEL;

    // back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        SetWindowTitle("Rubix Cube");
        cube.Reset();
        nextState = GameState::MENU;
    }

    // algorithms
    if (IsKeyPressed(KEY_BACKSPACE))
        cube.Reset();
    if (IsKeyPressed(KEY_LEFT))
    {
        uint32_t cubeSize = cube.GetSize();
        cubeSize = cubeSize > 2 ? cubeSize - 1 : 2;
        cube.SetSize(cubeSize);
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        uint32_t cubeSize = cube.GetSize();
        cubeSize = cubeSize < 69 ? cubeSize + 1 : 69;
        cube.SetSize(cubeSize);
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

    static bool hidden = false;
    std::string scramble = "R U R' B2 F D2 L' U' F R2 U2 D2 L F' B R' F L2";
    hidden = gui::Panel("i", 60, 60, 80, 80, hidden);
    if (hidden)
    {
        for (uint32_t i = 0; i < texts.size(); i++)
            DrawText(texts[i].c_str(), WINDOW_PADDING, WINDOW_PADDING + TEXT_SIZE * i, TEXT_SIZE, GRAY);
    }
    else
    {
        DrawText(
            scramble.c_str(),
            WINDOW_WIDTH / 2 - MeasureText(scramble.c_str(), 60) / 2,
            20,
            60,
            WHITE
        );
    }

    EndDrawing();

    return nextState;
}