#pragma once

#include "Effect.hpp"
#include "../utilities/SparseVector.hpp"
#include "engine/actors/Actor.hpp"

namespace geng {
    /// EffectManager class. For explicit and exclusive use by the engine.
    /// Handles updating each effect pointer, and removing effects when completed.
    /// EffectManager uses a SparseVector class for removal/insertion efficiency.
    class EffectManager final {
    private:
        /// Vector containing each effect pointer
        gutils::SparseVector<Effect> effects;
    public:
        /// Default constructor
        EffectManager() = default;
        /// Default destructor
        ~EffectManager() = default;

        // Add effects
        /// Adds an effect to a given actor
        void add_effect(Effect *e);
        /// Adds an effect to a given transform
        void add_effect(Gear &g, Effect *e);

        // Remove effects
        /// Removes all effects on an gear (by searching through target_id)
        void remove_effect(Gear *g);
        /// Removes a singular effect by Effect*
        void remove_effect(Effect* e);

        // Updater
        /// Updates all effects in the effect manager. Removes finished effects.
        void update();

        /// Check if a gear has an effect
        bool has_effect(Gear* g);

    };
}