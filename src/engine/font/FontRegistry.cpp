#include "engine/font/font-types/FontRegister.hpp"

geng::FontRegistry& geng::get_FontRegistry() {
    static FontRegistry registry;
    return registry;
}