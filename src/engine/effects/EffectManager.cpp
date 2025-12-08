#include "engine/effects/EffectManager.hpp"

using namespace geng;

void EffectManager::add_effect(Actor &a, Effect *e) {
    e->set_transform(a.t);
    effects.add(e);
}

void EffectManager::add_effect(Transform &t, Effect *e) {
    e->set_transform(t);
    effects.add(e);
}

void EffectManager::remove_effect(Actor &a) {
    remove_effect(a.t);
}

void EffectManager::remove_effect(Transform &t) {
    for (auto it = effects.begin(); it != effects.end(); ++it)
        if ((*it) != nullptr && (*it)->get_target_id() == t.id)
            effects.erase(*it);
}

void EffectManager::remove_effect(Effect *e) {
    effects.erase(e);
}

void EffectManager::update() {
    for (auto & e : effects)
        if (e->update())
            remove_effect(e);
}

