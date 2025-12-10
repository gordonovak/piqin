#include "engine/pathing/path-types/BalloonPath.hpp"
#include "engine/gengine-globals/scene.hpp"

using namespace geng;

BalloonPath::BalloonPath(Gear *g, const Vertex &target, float speed)
    : Path(g, target, speed), direction((target-g->t.pos).unit()) {}

bool BalloonPath::update() {
    // dereference for speed
    Transform& t = gear->t;

    float DIST = target.dist(t.pos);
    Vertex dist = direction * global::scene().dt * speed * ((DIST < 1.0f) ? 1.0f : DIST) / 70.0f;
    //minimum step of movement
    float minny = (target.dist(t.pos) * 0.02f);
    const float minStep = std::max(minny, 0.02f);
    // This way we can preserve minimum stepping
    for (int i = 0; i < 3; ++i) {
        if (abs(dist[i]) < minStep) {
            dist[i] = (direction[i] >= 0.0f ? minStep : -minStep);
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
