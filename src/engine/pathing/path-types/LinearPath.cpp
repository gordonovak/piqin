#include "engine/pathing/path-types/LinearPath.hpp"
#include "engine/gengine-globals/scene.hpp"

using namespace geng;

LinearPath::LinearPath(Gear *g, const Vertex &target, float speed)
    : Path(g, target, speed), direction((target-g->t.pos).unit()) {}

bool LinearPath::update() {
    // dereference for speed
    Transform& t = gear->t;

    if (overshoot(t.pos.x, target.x, speed*global::scene().dt*direction[0]))
        completeX = true;
    if (overshoot(t.pos.y, target.y, speed*global::scene().dt*direction[1]))
        completeY = true;
    if (overshoot(t.pos.z, target.z, speed*global::scene().dt*direction[2]))
        completeZ = true;

    return (completeX && completeY && completeZ);
}
