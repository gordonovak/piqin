#pragma once

#include "../pathing/Path.hpp"
#include "engine/actors/Transform.hpp"
#include "engine/animation/AnimInfo.hpp"
#include "engine/gengine-globals/Shadow.hpp"
#include "engine/types/Gear.hpp"

namespace geng {
    /**
     * @brief A @code gengine::Actor@endcode is a simple game entity that carries with it a @code gengine::Transform@endcode and a @code gengine::FrameState@endcode.
     * It is the base unit the engine performs ticks on.
     * - To access most features of actors, you access the public member variables, @code Transform t@endcode and @code AnimInfo anim@endcode.
     * - Actors also have a virtual update function. The default implementation does nothing,
     * but the engine will call @code update()@endcode on every actor, so if you want features like velocity, you can place them in
     * a subclass's @code update()@endcode func.
     */
    struct Actor : public Gear {
    public:
        /// An actor's transformation information
        Transform t;
        /// An actor's animation information.
        AnimInfo anim;

    public:
        /// Default Constructor
        Actor() = default;
        /// Default copy constructor
        Actor(Actor& o) = default;
        /// Defines an Actor with a starting position
        explicit Actor(Vertex pos) : t(pos) {}
        /// Defines an actor with a starting position and animation info.
        Actor(Vertex pos, AnimInfo anim) : t(pos), anim(anim) {}

        /// Virtual update function
        virtual void update() {}
        /// Virtual Destructor
        virtual ~Actor() = default;

        /// To String
        [[nodiscard]] std::string to_string() const {
            return	"Actor: \n" + t.to_string() + "\n" +  anim.to_string();
        }

        // Manual overrides for Gears
        /// Converts an actor to vertices
        void to_vertex(std::vector<SDL_Vertex> &buffer) override {
            anim.calc_vertices(buffer, t);
            if (shadow())
                shadows.apply_shadow(buffer, 4);
        }
        /// Returns the z-index of
        [[nodiscard]] float z_index() const override {
            return t.pos.z;
        }
    };
}
