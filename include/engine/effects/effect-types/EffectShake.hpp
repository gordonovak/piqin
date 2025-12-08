#pragma once
#include "../../utilities/types/Vertex.hpp"
#include "engine/effects/Effect.hpp"

namespace geng {
    // Shake type macros
    enum class Shake : uint8_t {
        RANDOM = 0,
        CIRCULAR = 1,
        FLOATY = 2,
        SIDE = 3
    };

    /** @brief Shakes are a subclass of an Effect. To add a Shake, use @code engine.add_effect(...)@endcode.
     * To specify a shake's type, assign it a @code GENG_Shake@endcode enum in its constructor.
     */
    class EffectShake : public Effect {

    public:
        /// Constructor for the shaking!
        EffectShake(Shake shakeType, float amplitude, float duration, float speed = 1.0, bool decay = false);

        /// The effect override
        bool update() override;

    protected:
        /// Speed of the shake
        float speed;
        /// Type of shake (random pos, circular, "floaty")
        Shake shakeType;
        /// Whether you want the amplitude of displacement to decay
        bool decay;
        /// Determines if a shake is complete in all three direction (x,y,z).
        uint8_t complete = false;

        // Various functions for each shake type.
        static void shake_random(Transform& tref);
        void shake_circular(Transform& tref) const;
        void shake_floaty(Transform& tref) const;
        void shake_side(Transform& tref) const;

    };
}

