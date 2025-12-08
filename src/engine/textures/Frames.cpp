#include "engine/animation/Frame.hpp"
#include "engine/gengine-globals/EngineEnums.hpp"
#include "engine/utilities/Utilities.hpp"

using namespace geng;

// ................
// Frame Code
// ................

Frame::Frame(std::vector<SDL_FPoint> points, float duration, geng::GENG_Anim anim)
    : vertexPoints(points),duration(duration), anim(anim) { }

void Frame::append_vertices(std::vector<SDL_Vertex>& buffer, Transform& t) {
    SDL_Vertex tl, tr, bl, br;
    if (t.is_locked()) {
        float ttw = roundf(t.pos.x +t.offset.x - t.w/2);
        float ttwt = roundf(t.pos.x+t.offset.x + t.w/2);
        float tth = roundf(t.pos.y+t.offset.y - t.h/2);
        float ttht = roundf(t.pos.y+t.offset.y + t.h/2);
        // If our Transform isn't unlocked, we don't do anything fancy with it.
        tl = {{ttw, tth}, t.color, vertexPoints[0]};
        tr = {{ttwt, tth}, t.color, vertexPoints[1]};
        bl = {{ttw, ttht}, t.color, vertexPoints[2]};
        br = {{ttwt, ttht}, t.color, vertexPoints[3]};
    }
    else {
        // Flipping if we choose to do so
        signed char flipX = (t.flag << GFlag::flipX) ? -1 : 1;
        signed char flipY = (t.flag << GFlag::flipX) ? -1 : 1;
        float ttw = flipX * t.w * t.scale;
        float tth = flipY * t.h * t.scale;

        // New texture coordinate if flipped?
        SDL_FPoint vpTL = vertexPoints[0];
        SDL_FPoint vpTR = vertexPoints[1];
        SDL_FPoint vpBL = vertexPoints[2];
        SDL_FPoint vpBR = vertexPoints[3];
        // If we flipped x
        if (t.flag << GFlag::flipX) {
            std::swap(vpTL, vpTR);
            std::swap(vpBL, vpBR);
        }
        // if we flipped y
        if (t.flag << GFlag::flipY) {
            std::swap(vpTL, vpBL);
            std::swap(vpTR, vpBR);
        }
        // If we aren't rotating
        if (t.angle < 0.1f) {
            tl = {{t.pos.x, t.pos.y}, t.color, vpTL};
            tr = {{t.pos.x + ttw, t.pos.y}, t.color, vpTR};
            bl = {{t.pos.x, t.pos.y + tth}, t.color, vpBL};
            br = {{t.pos.x + ttw, t.pos.y + tth}, t.color, vpBR};
        }
        else {
            float angle = t.angle * gutils::degreesToRadians;
            // Get our adjusted center
            float rw = ttw * 0.5f;
            float rh = tth * 0.5f;
            // Our pivot point (the center)
            float px = t.pos.x + rw;
            float py = t.pos.y + rh;
            // Do a pre-calculation for cosine and sine
            float cs = cosf(angle);
            float sn = sinf(angle);
            // Create a lambda to rotate for us
            auto rotate = [&](float vx, float vy) {
                // First we get our x rotation (prabal)
                float rx = vx * cs - vy * sn;
                //Now our y
                float ry = vx * sn + vy * cs;
                // Return our point
                return SDL_FPoint{px + rx, py + ry};
            };
            // Now we just store it in our vertexes
            SDL_FPoint ftl = rotate(-rw, -rh);
            SDL_FPoint ftr = rotate(rw, -rh);
            SDL_FPoint fbl = rotate(-rw, rh);
            SDL_FPoint fbr = rotate(rw, rh);
            // Storing
            tl = {ftl, t.color, vpTL};
            tr = {ftr, t.color, vpTR};
            bl = {fbl, t.color, vpBL};
            br = {fbr, t.color, vpBR};
        }
    }
    // Finally we push everything back on the buffer.
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



