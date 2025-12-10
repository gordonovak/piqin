#include "engine/input/InputConstants.hpp"

short& geng::get_buffer() {
    static short GENG_buffer = 400;
    return GENG_buffer;
}