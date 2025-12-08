#pragma once
#include "effects/EffectManager.hpp"
#include "particles/ParticleManager.hpp"
#include "actors/ActorManager.hpp"
#include "input/InputManager.hpp"
#include "gengine-globals/Random.hpp"
#include "pathing/PathManager.hpp"
#include "rendering/Renderer.hpp"
#include "animation/FrameManager.hpp"


namespace geng {
    /**
     * @brief The engine handles input, effect, particles, ECS, rendering, sound, and text. You do not have direct control over how the engine does its job. You only feed it inputs, and it gives you an output, and sends you keyboard input.
     * @details In order to use the engine, you have to speak in its language: @code gengine::Actor@endcode, @code gengine::Effect@endcode, @code gengine::ParticleGroup@endcode, @code gengine::inputTarget@endcode, @code gengine::Font@endcode, and @code gengine::Sound@endcode. It is recommended to review these files before continuing with the engine.
     * Using the engine's features can be a bit of a hurdle to get used to, but it is designed to be somewhat intuitive.
     * - For @code Actors@endcode: @code engine.add_actor(...)@endcode and @code engine.remove_actor(...)@endcode
     * - For @code Particles@endcode: @code engine.attach_particle(...)@endcode and @code engine.detach_particle(...)@endcode
     * - For @code Effects@endcode: @code engine.apply_effect(...)@endcode and @code engine.strip_effect(...)@endcode
     */
    class Engine {
    private:
        /// Holds all the gears to be rendered in the engine.
        std::vector<Gear*> gears;

        /// Engine's Renderer. Very very off-limits no touching.
        Renderer _rend;
        Camera _cam;

        /// Engine's InputManager. Try not to touch.
        geng::InputManager _input;

        /// Engine's ParticleManager
        ParticleManager partm;
        /// Engine's ActorManager
        ActorManager am;
        /// Engine's FrameManager
        FrameManager fm;
        /// Engine's EffectManager
        geng::EffectManager em;
        /// Engine's PathManager
        PathManager pathm;

        // ID Management
        /// Keeps track of IDs of removed actors
        gutils::IDStack id_stack;
        /// Keeps track of the top-most ID
        int top_id = 0;
        /// If we've removed an object, we use that dissolved object's ID before making a new one.
        int pop_id();
        /// This is how we add any gear to the system
        void add_gear(Gear* g);

        void remove_gear(Gear *g);

    public:
        // Constructor/destructor
        Engine();
        ~Engine() = default;

        // .......................... //
        /* Engine vitals  */
        // .......................... //
        /// Initializes the engine. Must be called in @code int main(...)@endcode
        void initialize();

        /// Runs the entire engine. Must call every frame, and put in the current time.
        bool tick(double time);

        /// Sends things to the renderer and presents it. Should call every frame.
        void render();

        /// Sets an input target.
        void set_input_target(InputTarget* t);

        // .......................... //
        /* Additions to the engine!!! */
        // .......................... //
        // <><><> Actors <><><>
        /// Adds an actor to the engine
        void add_actor(Actor* a);
        /// Adds several actors to the engine.
        void add_actors(const std::vector<Actor*>& actors);
        // <><><> Particle groups <><><>
        /// Adds a detatched particle to the rendering pipeline
        void instantiate_particle(ParticleGroup *pg);
        /// Attatches a particle to an actor and then adds it to the rendering pipline.
        void attach_particle(Actor* o, ParticleGroup* pg);
        /// Adds multiple particles to the rendering pipeline.
        void attach_particles(std::vector<ParticleGroup*>& pgs);
        // <><><> Effects <><><>
        /// Adds an effect to an actor
        void apply_effect(Actor& a, geng::Effect* e);
        /// Adds an effect to a transform object.
        void apply_effect(Transform& t, geng::Effect* e);
        // <><><> Paths <><><>
        void set_path(Path* p);
        void set_path(Path* p, Transform& t, const Vertex &offset = {0.f, 0.f, 0.f});

        // .......................... //
        /* Removals from the engine!!! */
        // .......................... //
        // <><><> Actors <><><>
        /// Removes an actor from the engine (does not delete).
        void remove_actor(const Actor *a);
        /// Removes a vector of actors from the engine (does not delete).
        void remove_actor(const std::vector<Actor*>& objs);
        // <><><> Particle groups <><><>
        /// Removes a particle
        void detach_particle(ParticleGroup* pg);
        /// Removes all particles attaches to an actor.
        void detach_particle(Actor *a);
        /// Removes a bunch of particles.
        void detach_particle(const std::vector<ParticleGroup*>& pgs);
        // <><><> Effects <><><>
        /// Removes all effects from an actor
        void strip_effect(Actor* a);
        /// Removes all effects from a transform
        void strip_effect(Transform& t);
        /// Removes a specific effect
        void strip_effect(geng::Effect* e);
        /// Removes an effect from a transform

        // .......................... //
        /* Weird utility functions */
        // .......................... //
        /// Removes all engineElements matching the IDs specified.
        void remove(const std::vector<int>& ids);
        /// Returns true if an object has an effect applied to it
        bool has_effect(Actor& a);
    };
}