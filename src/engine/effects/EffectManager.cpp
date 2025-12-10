#include "engine/effects/EffectManager.hpp"

using namespace geng;

void EffectManager::add_effect(Effect *e) {
    effects.add(e);
}

void EffectManager::remove_effect(Gear* g) {
    for (auto& e: effects) {
        if (e != nullptr && e->get_gear_ptr() == g) {
            remove_effect(e);
        }
    }
}

void EffectManager::remove_effect(Effect *e) {
    effects.erase(e);
}

void EffectManager::update() {
    for (auto & e : effects)
        if (e->update())
            remove_effect(e);
}

bool EffectManager::has_effect(Gear *g) {
    return std::any_of(effects.begin(),
        effects.end(),
        [g](Effect *e)
        { return e->get_gear_ptr() == g; });
}
