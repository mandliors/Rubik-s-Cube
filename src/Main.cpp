#include "Cube/Cube.hpp"
#include "CubeScrambler/CubeScrambler.hpp"
#include "CubeSolver/CubeSolver.hpp"
#include "GUI/GUI.hpp"

#include <raylib.h>

#include <array>
#include <format>

enum class GameState
{
    MENU = 0,
    PLAYGROUND,
    DUEL,
    EXIT
};

enum class DuelState
{
    START = 0,
    SCRAMBLING,
    SCRAMBLED,
    BOTH_SOLVING,
    PLAYER_SOLVING,
    COMPUTER_SOLVING,
    SOLVED
};

constexpr float WINDOW_SCALE = 1.0f;

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
            state = Menu();
            break;
        case GameState::PLAYGROUND:
            state = Playground(camera);
            break;
        case GameState::DUEL:
            state = Duel(camera);
            break;
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
    static constexpr uint32_t btnHeight = static_cast<uint32_t>(50 * WINDOW_SCALE);
    static constexpr uint32_t btnSpacing = static_cast<uint32_t>(20 * WINDOW_SCALE);
    static constexpr uint32_t btnOffset = btnHeight + btnSpacing;
    
    uint32_t btnY = WINDOW_HEIGHT / 2 - static_cast<uint32_t>(btnCount * 0.5f * btnOffset);
    if (
        static auto btnStatePlayground = gui::State::NONE;
        gui::Button("Playground", WINDOW_WIDTH / 2, btnY, static_cast<uint32_t>(200 * WINDOW_SCALE), btnHeight, TEXT_SIZE, btnStatePlayground)
    )
        nextState = GameState::PLAYGROUND;

    btnY += btnOffset;
    if (
        static auto btnStateDuel = gui::State::NONE;
        gui::Button("Duel", WINDOW_WIDTH / 2, btnY, static_cast<uint32_t>(150 * WINDOW_SCALE), btnHeight, TEXT_SIZE, btnStateDuel)
    )
        nextState = GameState::DUEL;

    btnY += btnOffset;
    if (
        static auto btnStateExit = gui::State::NONE;
        gui::Button("Exit", WINDOW_WIDTH / 2, btnY, static_cast<uint32_t>(125 * WINDOW_SCALE), btnHeight, TEXT_SIZE, btnStateExit)
    )
        nextState = GameState::EXIT;

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
    static CubeScrambler scrambler { cube };
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
        scrambler.Scramble();
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
    hidden = gui::Panel(
        "i",
        static_cast<uint32_t>(25 * WINDOW_SCALE),
        static_cast<uint32_t>(25 * WINDOW_SCALE),
        static_cast<uint32_t>(30 * WINDOW_SCALE),
        static_cast<uint32_t>(30 * WINDOW_SCALE),
        TEXT_SIZE,
        hidden
    );

    if (hidden)
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
    static std::array<std::string, 5> texts = {
        "UP/DOWN: adjust difficulty (speed)",
        "TAB: toggle scramble animation",
        "LEFT/RIGHT: change cube size",
        "SPACE: scramble, start/stop",
        "ESCAPE: back to menu"
    };

    static Cube cube { 3, { 0, 0, 0 }, 2.0f };
    static CubeScrambler scrambler { cube };
    static CubeSolver solver { cube };

    static std::string scramble = "";
    static DuelState state = DuelState::START;
    GameState nextState = GameState::DUEL;

    // back to menu
    if (IsKeyPressed(KEY_ESCAPE))
    {
        SetWindowTitle("Rubix Cube");
        cube.Reset();
        state = DuelState::START;
        nextState = GameState::MENU;
    }

    // animations
    static bool animations = true;
    if (IsKeyPressed(KEY_TAB))
    {
        animations = !animations;
        if (state == DuelState::SCRAMBLING)
            cube.FinishAllQueuedMoves();
    }
    if (IsKeyPressed(KEY_UP))
        cube.SetAnimationSpeed(cube.GetAnimationSpeed() / 0.9f);
    if (IsKeyPressed(KEY_DOWN))
        cube.SetAnimationSpeed(cube.GetAnimationSpeed() * 0.9f);

    // algorithms
    if (IsKeyPressed(KEY_BACKSPACE))
        cube.Reset();
    if (IsKeyPressed(KEY_LEFT))
    {
        uint32_t cubeSize = cube.GetSize();
        uint32_t newCubeSize = cubeSize > 2 ? cubeSize - 1 : 2;
        if (newCubeSize != cubeSize)
        {
            cube.SetSize(newCubeSize);
            state = DuelState::START;
        }
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        uint32_t cubeSize = cube.GetSize();
        uint32_t newCubeSize = cubeSize < 3 ? cubeSize + 1 : 3;
        if (newCubeSize != cubeSize)
        {
            cube.SetSize(newCubeSize);
            state = DuelState::START;
        }
    }

    // cube rotation
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        DisableCursor();

    if (IsMouseButtonDown(MOUSE_LEFT_BUTTON))
        cube.Rotate(GetMouseDelta().y * 0.003f, GetMouseDelta().x * 0.003f, 0);
    
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON))
        EnableCursor();

    // check if solved
    bool solved = cube.IsSolved();
    if (solved)
        SetWindowTitle("Rubix Cube [SOLVED]");
    else
        SetWindowTitle("Rubix Cube");   

    // state machine
    static double startTime = 0.0f;
    static double computerFinishTime = 0.0f;
    static double playerFinishTime = 0.0f;
    switch (state)
    {
    case DuelState::SCRAMBLING:
        if (!cube.IsTurning())
            state = DuelState::SCRAMBLED;
        else if (IsKeyPressed(KEY_SPACE))
        {
            cube.FinishAllQueuedMoves();
            state = DuelState::SCRAMBLED;
        }
        break;
    case DuelState::SCRAMBLED:
        if (IsKeyPressed(KEY_SPACE))
        {
            startTime = GetTime();
            solver.Solve();
            state = DuelState::BOTH_SOLVING;
        }
        break;
    case DuelState::BOTH_SOLVING:
        // computer finished solving
        if (solved)
        {
            state = DuelState::PLAYER_SOLVING;
            computerFinishTime = GetTime();
            cube.MakeMove(Move::z2);
        }
        // player finished solving
        if (IsKeyPressed(KEY_SPACE))
        {
            state = DuelState::COMPUTER_SOLVING;
            playerFinishTime = GetTime();
        }
        break;
    case DuelState::COMPUTER_SOLVING:
        if (solved)
        {
            state = DuelState::SOLVED;
            computerFinishTime = GetTime();
            cube.MakeMove(Move::z2);
        }
        break;
    case DuelState::PLAYER_SOLVING:
        if (IsKeyPressed(KEY_SPACE))
        {
            state = DuelState::SOLVED;
            playerFinishTime = GetTime();
        }
        break;
    case DuelState::START:
    case DuelState::SOLVED:
        if (IsKeyPressed(KEY_SPACE))
        {
            scramble = scrambler.Scramble();
            if (!animations)
                cube.FinishAllQueuedMoves();
            state = DuelState::SCRAMBLING;
        }
        break;
    }

    BeginDrawing();
    BeginMode3D(camera);

    ClearBackground(Color{ 40, 40, 40, 255 });

    cube.Update(GetFrameTime());
    cube.Draw();

    EndMode3D();

    static bool hidden = false;
    hidden = gui::Panel(
        "i",
        static_cast<uint32_t>(25 * WINDOW_SCALE),
        static_cast<uint32_t>(25 * WINDOW_SCALE),
        static_cast<uint32_t>(30 * WINDOW_SCALE),
        static_cast<uint32_t>(30 * WINDOW_SCALE),
        TEXT_SIZE,
        hidden
    );

    // info texts or scramble
    if (hidden)
    {
        for (uint32_t i = 0; i < texts.size(); i++)
            DrawText(texts[i].c_str(), WINDOW_PADDING, WINDOW_PADDING + TEXT_SIZE * i, TEXT_SIZE, GRAY);
    }
    else if (state == DuelState::SCRAMBLING || state == DuelState::SCRAMBLED || state == DuelState::SOLVED)
    {
        const auto fontSize = static_cast<uint32_t>(26 * WINDOW_SCALE);        
        DrawText(
            scramble.c_str(),
            WINDOW_WIDTH / 2 - MeasureText(scramble.c_str(), fontSize) / 2,
            static_cast<int32_t>(50 * WINDOW_SCALE),
            fontSize,
            WHITE
        );
    }

    // big timer
    if (state == DuelState::BOTH_SOLVING || state == DuelState::PLAYER_SOLVING || state == DuelState::COMPUTER_SOLVING)
    {
        const auto fontSize = static_cast<uint32_t>(50 * WINDOW_SCALE);
        const double solveTime = GetTime() - startTime;
        std::string solveTimeString = std::format("{:.2f}", solveTime);
        DrawText(
            solveTimeString.c_str(),
            WINDOW_WIDTH / 2 - MeasureText(solveTimeString.c_str(), fontSize) / 2,
            static_cast<int32_t>(50 * WINDOW_SCALE),
            fontSize,
            WHITE
        );
    }

    // finish times
    if (state == DuelState::PLAYER_SOLVING || state == DuelState::SOLVED)
    {
        const auto fontSize = static_cast<uint32_t>(26 * WINDOW_SCALE);
        const double solveTime = computerFinishTime - startTime;
        std::string solveTimeString = std::format("Computer's time: {:.2f}", solveTime);
        Color color;
        if (state == DuelState::SOLVED)
            color = computerFinishTime < playerFinishTime ? GREEN : RED;
        else
            color = GREEN;

        DrawText(
            solveTimeString.c_str(),
            WINDOW_WIDTH / 4 - MeasureText(solveTimeString.c_str(), fontSize) / 2,
            static_cast<int32_t>(WINDOW_HEIGHT - fontSize - 50 * WINDOW_SCALE),
            fontSize,
            color
        );
    }
    if (state == DuelState::COMPUTER_SOLVING || state == DuelState::SOLVED)
    {
        const auto fontSize = static_cast<uint32_t>(26 * WINDOW_SCALE);
        const double solveTime = playerFinishTime - startTime;
        std::string solveTimeString = std::format("Player's time: {:.2f}", solveTime);
        Color color;
        if (state == DuelState::SOLVED)
            color = playerFinishTime < computerFinishTime ? GREEN : RED;
        else
            color = GREEN;

        DrawText(
            solveTimeString.c_str(),
            WINDOW_WIDTH * 3 / 4 - MeasureText(solveTimeString.c_str(), fontSize) / 2,
            static_cast<int32_t>(WINDOW_HEIGHT - fontSize - 50 * WINDOW_SCALE),
            fontSize,
            color
        );
    }

    EndDrawing();

    return nextState;
}