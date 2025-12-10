#include "engine/gengine-globals/scene.hpp"

geng::Scene & geng::global::scene() {
    static geng::Scene scn;
    return scn;
}
