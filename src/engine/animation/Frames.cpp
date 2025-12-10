#include <iostream>
#include <ostream>

#include "engine/animation/Frame.hpp"
#include "engine/gengine-globals/EngineEnums.hpp"
#include "engine/utilities/Utilities.hpp"

using namespace geng;

// ................
// Frame Code
// ................

Frame::Frame(std::vector<SDL_FPoint> points, float duration, geng::GENG_Anim anim)
    : vertexPoints(points),duration(duration), anim(anim) { }

void Frame::append_vertices(std::vector<SDL_Vertex>& buffer, Gear* gear) {
    Gear& g = *gear;

    const float hw = (g.t.w * g.t.scale) * 0.5f;
    const float hh = (g.t.h * g.t.scale) * 0.5f;

    const float cx = g.t.pos.x + g.t.offset.x;
    const float cy = g.t.pos.y + g.t.offset.y;

    // --- Texture coordinates (already correct, just flipped if needed)
    SDL_FPoint uvTL = vertexPoints[0];
    SDL_FPoint uvTR = vertexPoints[1];
    SDL_FPoint uvBL = vertexPoints[2];
    SDL_FPoint uvBR = vertexPoints[3];

    if (g.flippedX()) {
        std::swap(uvTL, uvTR);
        std::swap(uvBL, uvBR);
    }
    if (g.flippedY()) {
        std::swap(uvTL, uvBL);
        std::swap(uvTR, uvBR);
    }

    // --- Local corners relative to center
    SDL_FPoint ltl{-hw, -hh};
    SDL_FPoint ltr{ hw, -hh};
    SDL_FPoint lbl{-hw,  hh};
    SDL_FPoint lbr{ hw,  hh};

    auto rotate = [&](SDL_FPoint p) {
        if (g.t.angle < 0.001f)
            return SDL_FPoint{cx + p.x, cy + p.y};

        float a = g.t.angle * gutils::degreesToRadians;
        float cs = cosf(a);
        float sn = sinf(a);

        return SDL_FPoint{
            cx + (p.x * cs - p.y * sn),
            cy + (p.x * sn + p.y * cs)
        };
    };

    SDL_Vertex tl{rotate(ltl), g.t.color, uvTL};
    SDL_Vertex tr{rotate(ltr), g.t.color, uvTR};
    SDL_Vertex bl{rotate(lbl), g.t.color, uvBL};
    SDL_Vertex br{rotate(lbr), g.t.color, uvBR};

    // --- Two triangles (correct winding)
    buffer.push_back(tl);
    buffer.push_back(bl);
    buffer.push_back(br);

    buffer.push_back(tl);
    buffer.push_back(tr);
    buffer.push_back(br);
}

float Frame::get_duration() const {
    return duration;
}

geng::GENG_Anim Frame::get_anim() const {
    return anim;
}



