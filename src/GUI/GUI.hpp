#include <memory>
#include <string>
#include <functional>

namespace gui {
    enum class State {
        NONE = 0,
        PRESSED
    };

    auto Button(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, State& state) -> bool;
    auto Panel(const std::string& text, uint32_t x, uint32_t y, uint32_t width, uint32_t height, bool hidden) -> bool;
}