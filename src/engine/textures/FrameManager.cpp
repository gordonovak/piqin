#include "engine/animation/FrameManager.hpp"

#include <iostream>

#include "../../../include/engine/animation/asset-info/TextureRegister.hpp"
#include "engine/gengine-globals/scene.hpp"
#include "engine/animation/asset-info/FrameTableRegistry.hpp"

using namespace geng;

FrameManager::FrameManager() = default;

void FrameManager::initialize() {
    // Links each Frame Table to a Table ID.
    for (auto& [id, sheet] : textures::get_TableRegistry()) {
        sheets[id] = sheet;
    }
    // Removes entries from the TableRegistry because we don't need them anymore.
    textures::get_TableRegistry().clear();
}

void FrameManager::apply_framestate(Actor &a) {
    a.anim.set_frame(sheets[a.anim.get_frame_table_id()].get_frame(a.anim.get_anim_id()));
}

void FrameManager::apply_framestates(const std::vector<Actor *> &actors) {
    for (auto &a : actors) {
        apply_framestate(*a);
    }
}


int FrameManager::get_texture_id(Mesh& m) {
    return m.texture_id;
}

FrameTable& FrameManager::get_table(Actor &a) {
    return sheets[a.anim.get_frame_table_id()];
}

void FrameManager::update(const std::vector<AnimInfo*>& anims) {
    for (auto& anim : anims)
        sheets[anim->get_frame_table_id()].update_frame(*anim);
}
