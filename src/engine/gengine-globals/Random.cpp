#include "engine/gengine-globals/Random.hpp"

geng::Random& geng::global::rand() {
    static Random r;
    return r;
}