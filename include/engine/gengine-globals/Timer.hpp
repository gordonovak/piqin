#pragma once
#include <functional>
#include <deque>
#include "scene.hpp"

namespace geng {
    class EventTimer final {
    private:
        std::deque<std::pair<float, std::function<void()>>> callbacks;
    public:
        EventTimer() {
        }

        void add_event(float time, const std::function<void()> callback) {
            callbacks.emplace_back(time, callback);
        }

        void update() {
            if (!callbacks.empty()) {
                callbacks.front().first -= global::scene().dt;
                if (callbacks.front().first <= 0) {
                    const auto f = callbacks.front().second;
                    callbacks.pop_front();
                    f();
                }
            }
        }
    };

    EventTimer& events();
}
