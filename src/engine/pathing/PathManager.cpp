#include "engine/pathing/PathManager.hpp"

using namespace geng;

void PathManager::add_path(Path *p) {
    int id = p->get_payload()->id;
    // If it exists already we replace it with the new path.
    if (paths.find(id) == paths.end())
        delete paths[id];
    paths[id] = p;

}

void PathManager::add_path(Path* p, Transform& t, const Vertex &offset) {
    p->set_target(t.pos + offset);
    if (paths.find(t.id) != paths.end()) {
        p->set_target(paths[t.id]->get_target() + offset);
    }
    add_path(p);
}

void PathManager::remove_path(const Transform &t) {
    if (paths.find(t.id) != paths.end()) {
        delete paths[t.id];
        paths.erase(t.id);
    }
}

void PathManager::remove_path(const Path* path) {
    for (auto& [id, p]: paths) {
        if (p == path) {
            delete p;
            paths.erase(id);
            return;
        }
    }
}

void PathManager::update() {
    for (auto& [id, p] : paths) {
        // If it's not null and the update says it's done.
        if (p->update()) {
            // Guarentees we hit the target at the end
            p->get_payload()->pos = p->get_target();
            // Then we destroy the path.
            delete p;
            paths.erase(id);
        }
    }
}

PathManager::~PathManager() {
    for (auto& [id, p]: paths)
        delete p;
}

