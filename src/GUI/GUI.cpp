#include "GUI.hpp"

#include <raylib.h>
#include <utility>

namespace gui {
    
    static constexpr Color NORMAL_COLOR { 140, 140, 140, 255 };
    static constexpr Color HOVERED_COLOR { 160, 160, 160, 255 };
    static constexpr Color PRESSED_COLOR { 200, 200, 200, 255 };

    auto Button(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, State& state) -> bool
    {
        Rectangle bounds { 
            static_cast<float>(x) - 0.5f * width,
            static_cast<float>(y) - 0.5f * height,
            static_cast<float>(width),
            static_cast<float>(height)
        };
        Color color = NORMAL_COLOR;
        bool clicked = false;

        switch (state)
        {
        case State::NONE:
            if (CheckCollisionPointRec(GetMousePosition(), bounds))
            {
                if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
                {
                    color = PRESSED_COLOR;
                    state = State::PRESSED;
                }
                else
                    color = HOVERED_COLOR;
            }
            break;
        case State::PRESSED:
            if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
            {
                if (CheckCollisionPointRec(GetMousePosition(), bounds))
                    clicked = true;
                
                state = State::NONE;
            }
            else
                color = PRESSED_COLOR;

            break;
        
        default:
            std::unreachable();
            break;
        }

        DrawRectangleLinesEx(bounds, 3.0f, color);
        DrawText(
            text.c_str(),
            x - MeasureText(text.c_str(), 40) / 2,
            y - 20,
            40,
            color
        );

        return clicked;
    }

    auto Panel(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool hidden) -> bool
    {
        Rectangle bounds { 
                static_cast<float>(x) - 0.5f * width,
                static_cast<float>(y) - 0.5f * height,
                static_cast<float>(width),
                static_cast<float>(height)
            };
        Color color = NORMAL_COLOR;
        bool hovered = false;

        if (CheckCollisionPointRec(GetMousePosition(), bounds))
        {
            color = HOVERED_COLOR;
            hovered = true;
        }

        if (!hidden)
        {
            DrawRectangleRoundedLinesEx(bounds, 0.2f, -1, 3.0f, color);
            DrawText(
                text.c_str(),
                x - MeasureText(text.c_str(), 40) / 2,
                y - 20,
                40,
                color
            );
        }

        return hovered;
    }
}