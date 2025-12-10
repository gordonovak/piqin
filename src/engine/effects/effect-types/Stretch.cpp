#include "engine/effects/effect-types/Stretch.hpp"

using namespace gfx;

Stretch::Stretch(geng::Gear *gear, float amplitude, float snappiness)
    : Effect(gear, amplitude, snappiness), snappiness(snappiness), oldPos(gear->t.pos){}

bool Stretch::update() {
    geng::Gear& g = *gear;
    // Target-stretch x, target stretch y.
    float tsx, tsy;
    geng::Vertex diff = (g.t.pos - oldPos).unit();
    if (oldPos == g.t.pos) {
        tsx = 1.f;
        tsy = 1.f;
    }
    else {
        geng::Vertex diff = (g.t.pos - oldPos).unit().abs();
        tsx = (1 + diff[0]*amplitude*0.1f);
        tsy = (1 + diff[1]*amplitude*0.1f);
        float norm = 1/(tsx*tsy);
        tsx *= norm;
        tsy *= norm;
    }
    float targetW = g.t.get_base_width()*tsx;
    float targetH = g.t.get_base_height()*tsy;
    if (std::abs(g.t.w - targetW) < 0.5f) g.t.w = targetW;
    else g.t.w += (targetW - g.t.w) * snappiness * 0.1f;
    if (std::abs(g.t.h - targetH) < 0.5f) g.t.h = targetH;
    else g.t.h += (targetH - g.t.h) * snappiness * 0.1f;
    oldPos = g.t.pos;
    return false;
}
