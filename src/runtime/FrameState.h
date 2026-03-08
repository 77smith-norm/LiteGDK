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
    bool clearRequested() const;
    bool frameActive() const;
    bool syncEnabled() const;
    int syncRate() const;
    Color clearColor() const;
    Color textColor() const;
    Color textBackgroundColor() const;

    void setClearRequested(bool requested);
    void setFrameActive(bool active);
    void setSyncEnabled(bool enabled);
    void setSyncRate(int rate);
    void setClearColor(Color color);
    void setTextColor(Color color);
    void setTextBackgroundColor(Color color);

private:
    std::uint64_t frameCount_{0};
    bool clearRequested_{false};
    bool frameActive_{false};
    bool syncEnabled_{true};
    int syncRate_{60};
    Color clearColor_{};
    Color textColor_{};
    Color textBackgroundColor_{};
};
}  // namespace litegdk
