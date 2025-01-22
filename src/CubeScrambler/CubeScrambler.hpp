
#ifndef CUBESCRAMBLER_H
#define CUBESCRAMBLER_H

#include "Cube/Cube.hpp"
#include "Algorithm/Algorithm.hpp"

#include <string>

class CubeScrambler
{
public:
    explicit CubeScrambler(Cube& cube);

    auto Scramble(uint32_t moveCount = 0) -> std::string;

private:
    Cube& m_Cube;
};

#endif