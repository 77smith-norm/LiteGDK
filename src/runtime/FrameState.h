#pragma once

#include <cstdint>

namespace litegdk {
struct Color {
    std::uint8_t red{0};
    std::uint8_t green{0};
    std::uint8_t blue{0};
    std::uint8_t alpha{255};
};

class FrameState {
public:
    FrameState();

    void reset();
    void advanceFrame();

    std::uint64_t frameCount() const;
    bool syncEnabled() const;
    int syncRate() const;
    Color clearColor() const;
    Color textColor() const;

    void setSyncEnabled(bool enabled);
    void setSyncRate(int rate);
    void setClearColor(Color color);
    void setTextColor(Color color);

private:
    std::uint64_t frameCount_{0};
    bool syncEnabled_{true};
    int syncRate_{60};
    Color clearColor_{};
    Color textColor_{};
};
}  // namespace litegdk
