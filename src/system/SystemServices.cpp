#include "SystemServices.h"

#include <chrono>
#include <cstdint>
#include <random>

#include "runtime/AppRuntime.h"

namespace {
class SystemServices {
public:
    SystemServices()
        : random_(0),
          startedAt_(std::chrono::steady_clock::now()) {}

    void randomize(int seed) {
        random_.seed(static_cast<std::uint32_t>(seed));
    }

    int rnd(int max) {
        if (max <= 0) {
            return 0;
        }

        std::uniform_int_distribution<int> distribution(0, max);
        return distribution(random_);
    }

    int timerMilliseconds() const {
        const auto elapsed =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                std::chrono::steady_clock::now() - startedAt_);
        return static_cast<int>(elapsed.count());
    }

private:
    std::mt19937 random_;
    std::chrono::steady_clock::time_point startedAt_;
};

SystemServices& systemServices() {
    static SystemServices services;
    return services;
}
}  // namespace

namespace litegdk {
void randomize(int seed) {
    systemServices().randomize(seed);
}

int rnd(int max) {
    return systemServices().rnd(max);
}

int timerMilliseconds() {
    return systemServices().timerMilliseconds();
}

int screenWidth() {
    return runtime().displayWidth();
}

int screenHeight() {
    return runtime().displayHeight();
}
}  // namespace litegdk
