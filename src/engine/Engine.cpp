#include "../../include/engine/Engine.hpp"
#include "engine/gengine-globals/Timer.hpp"
#include "engine/animation/asset-info/TextureRegister.hpp"

using namespace geng;

// ReSharper disable once CppMemberInitializersOrder
Engine::Engine () :
        _cam(0,0,Z_MAX, global::scene.width, global::scene.height),
        _rend(&_cam), fm(), am(), partm(), _input(nullptr) {
}

void Engine::initialize() {
    _rend.initialize();
    fm.initialize();
    textures::tex_register.initialize_textures(_rend.get_renderer());
    _rend.set_texture_atlas(textures::tex_register[0]);
}

int Engine::pop_id() {
    if (!id_stack.is_empty())
        return id_stack.pop();
    return top_id++;
}

void Engine::add_gear(Gear *g) {
    int id = pop_id();
    g->id = id;
    g->index = gears.size();
    gears.push_back(g);
}

void Engine::remove_gear(Gear* g) {
    gears.erase(gears.begin() + g->index);
}

bool Engine::tick(const double time) {
    // First we update our global scene
    global::scene.update(time);

    // Now we check for user input
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            return false;
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
            _input.update(e);
    }

    GENG_Events.update();

    return true;
}

void Engine::render() {
    // Update all of our actors and their attatchments
    std::vector<AnimInfo*> frameStates = am.update_objects();
    fm.update(frameStates);
    // Render
    partm.update();
    if (partm.particles_to_remove())
        remove(partm.pop_removed_particles());

    std::sort(gears.begin(), gears.end(), [](const Gear* e1, const Gear* e2) {
        return e1->z_index() < e2->z_index();
    });

    _rend.render(gears);
    // Present our hard work
    _rend.present();
}

void Engine::set_input_target(geng::InputTarget *t) {
    _input.setInputTarget(t);
}

void Engine::detach_particle(Actor *a) {
    partm.dissolve(a);
}

void Engine::remove_actor(const Actor* a) {
    if (a == nullptr) return;
    am.dissolve(a);
    gears.erase(
    std::remove_if(
            gears.begin(),
            gears.end(),
            [&](const Gear* e){
                if (e == a) {
                    id_stack.push(e->id); // optional
                    return true;
                }
                return false;
            }
        ),
        gears.end()
    );
}

void Engine::remove_actor(const std::vector<Actor*>& objs) {
    for (const auto& i: objs) {
        remove_actor(i);
    }
}

void Engine::detach_particle(ParticleGroup* pg) {
    if (pg == nullptr) return;
    partm.remove(pg);
    remove_gear(pg);
}

void Engine::detach_particle(const std::vector<ParticleGroup*>& pg) {
    for (const auto& i: pg)
        detach_particle(i);
}

void Engine::strip_effect(Actor *a) {
    em.remove_effect(*a);
}

void Engine::strip_effect(Transform &t) {
    em.remove_effect(t);
}

void Engine::strip_effect(geng::Effect *e) {
    em.remove_effect(e);
}

void Engine::remove(const std::vector<int>& ids) {
    for (auto& id: ids) {
        gears.erase(
        std::remove_if(
                gears.begin(),
                gears.end(),
                [&](const Gear* e){
                    if (e->id == id) {
                        id_stack.push(e->id);
                        return true;
                    }
                    return false;
                }
            ),
            gears.end()
        );
    }
}

bool Engine::has_effect(Actor &a) {
    em.has_effect(a.t);
}

void Engine::add_actor(Actor *a) {
    // First, we assign an ID
    add_gear(a);
    // Add object to manager
    am.add_actor(a);
    fm.apply_framestate(*a);
    // Now it's z-sorted!
    gears.insert(gears.end(), a);
}

void Engine::add_actors(const std::vector<Actor*>& actors) {
    for (auto& a: actors)
        add_gear(a);
    fm.apply_framestates(actors);
    am.add_actors(actors);
}

void Engine::instantiate_particle(ParticleGroup *pg) {
    // Add to our particle manager
    partm.add(pg);
    // Add it as a gear.
    add_gear(pg);
}

void Engine::attach_particle(Actor *o, ParticleGroup *pg) {
    partm.add(pg);
    add_gear(pg);
    pg->horse = &o->t;
}

void Engine::attach_particles(std::vector<ParticleGroup*>& pgs) {
    // Add all our particles
    partm.add(pgs);
    for (auto&i : pgs)
        add_gear(i);
}

void Engine::apply_effect(Actor& a, geng::Effect *e) {
    em.add_effect(a, e);
}

void Engine::apply_effect(Transform &t, geng::Effect *e) {
    em.add_effect(t, e);
}

void Engine::set_path(Path *p) {
    pathm.add_path(p);
}

void Engine::set_path(Path *p, Transform &t, const Vertex &offset) {
    pathm.add_path(p, t, offset);
}
