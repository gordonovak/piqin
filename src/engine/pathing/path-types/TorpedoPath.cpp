#pragma once

#include "engine/pathing/path-types/TorpedoPath.hpp"

#include "engine/gengine-globals/scene.hpp"

using namespace geng;

TorpedoPath::TorpedoPath(Transform *t, const Vertex &target, float speed)
    : Path(t, target, speed), direction((target-t->pos).unit()) {}

bool TorpedoPath::update() {
    // Deref for speed
    Transform& t = *payload;
    //calculate our unit vector
    Vertex unit = (target - t.pos).unit();
    Vertex dist = unit * global::scene.dt * speed * (1.0f/target.dist(t.pos)) * 0.10f;
    if (dist.mag() < 0.00001f) { return true; }
    //minimum step of movement
    const float minStep = 0.0025f * target.dist(t.pos);
    // This way we can preserve minimum stepping
    for (int i = 0; i < 3; ++i) {
        if (fabs(dist[i]) < minStep) {
            dist[i] = (unit.x >= 0.0f ? minStep : -minStep);
        }
    }
    // Then we check if we overshoot or whether we're done or not!
    if (!(completeX & 1) && overshoot(t.pos.x, target.x, dist[0]))
        completeX = true;
    if (!(completeX & 2) && overshoot(t.pos.y, target.y, dist[1]))
        completeY = true;
    if (!(completeX & 4) && overshoot(t.pos.z, target.z, dist[2]))
        completeZ = true;

    return (completeX && completeY && completeZ);
}
