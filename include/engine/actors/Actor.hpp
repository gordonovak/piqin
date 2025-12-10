#pragma once

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
        /// An actor's animation information.
        AnimInfo anim;

    public:
        /// Default Constructor
        Actor() { set_shadow(); };
        /// Default copy constructor
        Actor(Actor& o) = default;
        /// Defines an Actor with a starting position
        explicit Actor(Vertex pos) : Gear(pos) { set_shadow(); }
        /// Defines an actor with a starting position and animation info.
        Actor(Vertex pos, AnimInfo anim) : Gear(pos), anim(anim) { set_shadow(); }

        /// Virtual update function
        virtual void update() {}
        /// Virtual Destructor
        ~Actor() override = default;

        /// To String
        [[nodiscard]] std::string to_string() const override {
            return	"Actor:" + Gear::to_string() + " " + t.to_string() + "\n" +  anim.to_string();
        }

        // Manual overrides for Gears
        /// Converts an actor to vertices
        void to_vertex(std::vector<SDL_Vertex> &buffer) override {
            anim.calc_vertices(buffer, this);
            if (shadow())
                get_shadow_calc().apply_shadow(buffer, 6);
        }
        /// Returns the z-index of
        [[nodiscard]] float z_index() const override {
            return t.pos.z;
        }

        /// This function is called when hovering over the actor with a cursor
        virtual void on_hover() { std::cerr << "Actor::on_hover()" << std::endl; }
        /// This function is caleld when the hoverable is pulled away from the actor
        virtual void hover_release() {}
        /// This function is called when the object is clicked on
        virtual void on_click() {}
        /// This function is called when the click for this object is released
        virtual void click_release() {}
        /// This function is called by the input manager when moving an object.
        virtual void move(Vertex dist) {}
    };
}
