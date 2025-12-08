#pragma once

#include "engine/pathing/path-types/ReboundPath.hpp"

using namespace geng;

ReboundPath::ReboundPath(Transform *t, const Vertex &target, float speed)
    : Path(t, target, speed) {}

bool ReboundPath::update() {
    //deref
    Transform& t = *payload;

    speed += 0.025f * ((fabsf(speed) > 1.0f) ? sqrtf(fabsf(speed)) : 1.0f);
    Vertex dist = start * (speed * -20.f);

    if (speed > 0.0f) {
        if (overshoot(t.pos.x, target.x, speed*global::scene.dt*direction[0]))
            completeX = true;
        if (overshoot(t.pos.y, target.y, speed*global::scene.dt*direction[1]))
            completeY = true;
        if (overshoot(t.pos.z, target.z, speed*global::scene.dt*direction[2]))
            completeZ = true;

        return (completeX && completeY && completeZ);
    }
    t.pos += dist;
    return false;
}
