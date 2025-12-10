#pragma once

#include "engine/input/InputConstants.hpp"
#include <vector>

#include "engine/gengine-globals/scene.hpp"

namespace geng {
    class InputQueue {
    private:
        std::vector<std::pair<Input, short>> queue;
        int front = 0, back = 0;
    public:
        InputQueue() {queue.resize(30); }

        void push(Input input) {
            if ((back + 1) % queue.size() != front)
                queue[back++] = std::pair(input, get_buffer());
            back %= queue.size();
        }
        Input pop() {
            Input returnVal = Input::NONE;
            if (front != back)
                returnVal = queue[front++].first;
            front %= queue.size();
            return returnVal;
        }

        bool empty() {
            return front == back;
        }
        void update() {
            for (int f = front; f != back; f = (f + 1) % queue.size()) {
                queue[f].second -= (geng::global::scene().dt); // NOLINT(*-narrowing-conversions)
                if (queue[f].second <= 0) pop();
            }
        }
        void clear() {
            front = 0; back = 0;
        }
    };
}
