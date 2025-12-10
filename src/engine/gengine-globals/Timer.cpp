#include "engine/gengine-globals/Timer.hpp"

geng::EventTimer& geng::events() {
    static EventTimer timer;
    return timer;
}