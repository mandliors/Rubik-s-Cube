#include "CubeScrambler.hpp"

#include <format>

CubeScrambler::CubeScrambler(Cube& cube)
    : m_Cube(cube) { }

auto CubeScrambler::Scramble(uint32_t moveCount) -> std::string
{
    static std::array<std::string_view, 6> sides { "U", "D", "F", "B", "L", "R" };
    static std::array<std::string_view, 3> modifiers = { "", "\'", "2" };

    if (moveCount == 0)
    {
        switch (m_Cube.GetSize())
        {
        case 2:
            moveCount = 10;
            break;
        case 3:
            moveCount = 20;
            break;
        case 4:
            moveCount = 40;
            break;
        case 5:
            moveCount = 60;
            break;
        case 6:
            moveCount = 80;
            break;
        case 7:
            moveCount = 100;
            break;
        
        default:
            moveCount = m_Cube.GetSize() * 20;
            break;
        }
    }

    std::string moves{ };
    uint32_t prevSideIndex = -1;
    for (uint32_t i = 0; i < moveCount; i++)
    {
        uint32_t turnWidth = m_Cube.GetSize() <= 3 ? 1 : GetRandomValue(1, m_Cube.GetSize() - 1);
        uint32_t modifierIndex = GetRandomValue(0, 2);

        uint32_t sideIndex;
        do
        {
            sideIndex = GetRandomValue(0, 5);
        } 
        while (sideIndex / 2 == prevSideIndex / 2);
        prevSideIndex = sideIndex;

        std::string move = std::format(
            "{}{}{}",
            turnWidth == 1 ? "" : std::to_string(turnWidth),
            sides[sideIndex],
            modifiers[modifierIndex]
        );

        m_Cube.MakeMove(move);
        moves += move + " ";
    }

    moves.resize(moves.size() - 1);
    
    return moves;
}