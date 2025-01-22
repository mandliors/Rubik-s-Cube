#include <memory>
#include <string>
#include <functional>

struct Color;

namespace gui {

    enum class State {
        NONE = 0,
        PRESSED
    };

    auto Button(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t fontSize, State& state) -> bool;
    auto Panel(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, uint32_t fontSize, bool hidden) -> bool;
    auto Text(const std::string& text, uint32_t x, uint32_t y, uint32_t fontSize, const Color& color) -> void;
}