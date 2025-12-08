#pragma once

#include "engine/actors/Transform.hpp"

namespace geng {
    /**
  * @brief Effects attach themselves to Transform objects, so any type with a Transform can have an effect applied to it.
  * @details To create a new effect, make a subclass of the effect object and add it via the Engine.
  * Effects have six member variables:
  * 1. Transform* t -> pointer to the object's Transform [protected]
  * 2. float initDuration -> initial duration of the effect (-1 implies permanent) [protected]
  * 3. float duration -> current duration of the effect [protected]
  * 4. bool permanent -> if duration is set to -1, permanent is set to true in the effect class. [protected]
  * 5. int id -> for engine identification and speed purposes [private]
  * 6. int target_id -> lets us remove effect by object ID, since Objects don't have an effect pointer [private]
  *
  * @note Notes for making effects:
  * - Effect is a pure virtual class
  * - Effect's constructors will initialize the initDuration and permanent fields for you
  * - Add effects to the EffectManager with @code engine.add_effect(Object* o, Effect* e) @endcode
  * - Remove permanent effects with @code engine.remove_effect(Effect *e) @endcode or @code engine.remove_effect(Object* o) @endcode
  * - Unless you explicitly program it, Effects will not return an object to its original transform upon completion
  *
  * @warning To make an effect you must override the update() function. Update() returns true if the effect is done, false otherwise.
  */
    class Effect {
    protected:
        /// Transform object the effect is applied to
        Transform* t = nullptr;
        /// Initial duration of the effect.
        float initDuration;
        /// Current duration of the effect.
        float duration;
        /// Amplitude of the effect
        float amplitude = 1;
        /// If the effect is permanent
        bool permanent;
    private:
        /// For engine identification purposes.
        int id = -1;
    public:
        /// Constructor without transform (permanent)
        Effect()
            : initDuration(0), duration(0), permanent(true) {}
        /// Constructor without transform (duration-limited)
        explicit Effect(float duration)
            : initDuration(duration), duration(duration), permanent(duration == -1) {}
        /// Constructor without transform (duration-limited and amplitude)
        explicit Effect(float duration, float amplitude)
            : initDuration(duration), duration(duration), amplitude(amplitude), permanent(duration == -1) {}
        /// Constructor for Permanent Effect
        explicit Effect(Transform& t)
            : t(&t), initDuration(0), duration(0), permanent(true) {}
        /// Constructor for duration-bound effect
        Effect(Transform& t, float duration)
            : t(&t), initDuration(duration), duration(initDuration), permanent(duration == -1) {}
        /// Constructor for a duration and an amplitude
        Effect(Transform& t, float duration, float amplitude)
            : t(&t), initDuration(duration), duration(duration),
                    amplitude(amplitude), permanent(duration == -1) {}

        /// Virtual destructor cause i'm considerate like that
        virtual ~Effect() = default;
        /// Pure virtual update function. Return true if effect is done. False otherwise.
        virtual bool update() = 0;
        /// Immmediately ends an effect
        virtual void end() { duration = 0; permanent = false;};


        // ............... //
        // For use by the engine //
        // ............... //
        /// Sets the transform the effect targets.
        void set_transform(Transform& transform) { t = &transform; }
        /// Sets the ID of the effect
        void set_id(int i) { id = i; }
        /// Gets the ID of the effect
        [[nodiscard]] int get_id () const { return id; }
        /// Gets the target_id of the transform the effect is applied to
        [[nodiscard]] int get_target_id () const { return (t == nullptr) ? 0 : t->id; }
        /// Returns if the effect is permanent or not
        [[nodiscard]] bool is_permanent () const { return permanent; }

    };
}