#pragma once

#include "engine/pathing/path-types/SinePath.hpp"
#include "engine/utilities/Utilities.hpp"

using namespace geng;

SinePath::SinePath(Transform *t, const Vertex &target, float speed)
    : Path(t, target, speed), direction((target-t->pos).unit()) {}

bool SinePath::update() {
    //deref
    Transform& t = *payload;

    // real distance-based time instead of x-based time
    float distTraveled = (t.pos - start).mag();
    float totalDist = (target - start).mag();

    float time = distTraveled / speed;
    float totalTime = totalDist / speed;

    // Linear base motion
    t.pos += direction * speed * global::scene.dt * 0.5;

    // Apply sine only to y
    float sineOffset = 10 * sinf(2.0f * utils::pi * time / totalTime);
    if (distTraveled < 0.001f)
        t.pos.y += direction[1] * distTraveled + sineOffset;
    else
        t.pos.y = start.y + direction[1] * distTraveled + sineOffset;

    // Overshoot on x/z only
    if (overshoot(t.pos.x, target.x, direction[0] * global::scene.dt * speed))
        completeX = true;;
    // We dont need to check for y because otherwise itll bmess with movement.
    completeY = true;
    if (overshoot(t.pos.z, target.z, direction[2] * global::scene.dt * speed))
        completeZ = true;

    return (completeX && completeZ);
}
