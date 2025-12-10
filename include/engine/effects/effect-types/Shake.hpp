#pragma once
#include "engine/effects/Effect.hpp"

namespace gfx {
    // Shake type macros
    enum class ShakeType : uint8_t {
        RANDOM = 0,
        CIRCULAR = 1,
        FLOATY = 2,
        SIDE = 3
    };

    /** @brief Shakes are a subclass of an Effect. To add a Shake, use @code engine.add_effect(...)@endcode.
     * To specify a shake's type, assign it a @code GENG_Shake@endcode enum in its constructor.
     */
    class Shake : public geng::Effect {

    public:
        /// Constructor for the shaking!
        Shake(geng::Gear* g, ShakeType shakeType, float amplitude, float speed = 1.0, float duration = -1.f, bool decay = false);

        /// The effect override
        bool update() override;

    protected:
        /// Speed of the shake
        float speed;
        /// Type of shake (random pos, circular, "floaty")
        ShakeType shakeType;
        /// Whether you want the amplitude of displacement to decay
        bool decay;
        /// Determines if a shake is complete in all three direction (x,y,z).
        uint8_t complete = false;

        // Various functions for each shake type.
        void shake_random(geng::Transform& tref);
        void shake_circular(geng::Transform& tref) const;
        void shake_floaty(geng::Transform& tref) const;
        void shake_side(geng::Transform& tref) const;

    };
}

