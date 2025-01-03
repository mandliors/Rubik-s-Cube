#ifndef FACECOLOR_H
#define FACECOLOR_H

#include <raylib.h>

#include <array>

enum class FaceColor
{
    White = 0,
    Yellow,
    Green,
    Blue,
    Red,
    Orange,
    None
};

static std::array<Color, 7> FaceColors = {
    WHITE,
    YELLOW,
    GREEN,
    BLUE,
    RED,
    ORANGE,
    BLACK
};

#endif