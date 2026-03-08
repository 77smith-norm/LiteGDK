#pragma once

#include <cstddef>
#include <optional>
#include <utility>
#include <vector>

#include "HandlePolicies.h"

namespace litegdk {
template <typename T>
class Registry {
public:
    bool insertOrAssign(int handle, T value) {
        if (!isValidHandle(handle)) {
            return false;
        }

        const auto index = handleToIndex(handle);
        if (slots_.size() <= index) {
            slots_.resize(index + 1);
        }

        if (!slots_[index].has_value()) {
            ++activeCount_;
        }

        slots_[index] = std::move(value);
        return true;
    }

    T* find(int handle) {
        if (!contains(handle)) {
            return nullptr;
        }

        return &slots_[handleToIndex(handle)].value();
    }

    const T* find(int handle) const {
        if (!contains(handle)) {
            return nullptr;
        }

        return &slots_[handleToIndex(handle)].value();
    }

    bool remove(int handle) {
        if (!contains(handle)) {
            return false;
        }

        slots_[handleToIndex(handle)].reset();
        --activeCount_;
        return true;
    }

    bool contains(int handle) const {
        if (!isValidHandle(handle)) {
            return false;
        }

        const auto index = handleToIndex(handle);
        return index < slots_.size() && slots_[index].has_value();
    }

    std::size_t activeCount() const {
        return activeCount_;
    }

    template <typename Fn>
    void forEach(Fn&& fn) const {
        for (std::size_t index = 0; index < slots_.size(); ++index) {
            if (!slots_[index].has_value()) {
                continue;
            }

            fn(indexToHandle(index), slots_[index].value());
        }
    }

private:
    std::vector<std::optional<T>> slots_{};
    std::size_t activeCount_{0};
};
}  // namespace litegdk
