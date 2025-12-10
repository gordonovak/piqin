#include <iostream>
#include "engine/animation/FrameManager.hpp"

#include "engine/animation/asset-info/FrameTableRegistry.hpp"


using namespace geng;

FrameManager::FrameManager() = default;

void FrameManager::initialize() {
    // Links each Frame Table to a Table ID.
    std::cout << "going through the table registry\n";
    int count = 0;

    auto& registry = get_TableRegistry();
    sheets.reserve(registry.size());
    for (auto it : registry) {
        sheets.emplace_back(it.second);
        count++;
    }
    std::cout << "clearing registry\n";
    get_TableRegistry().clear();
    std::cout << "sheets printout:\n";
    count = 0;
    for (int i = 0; i < sheets.size(); i++) {
        std::cerr << "index: " << i << " sheet: " << sheets[i].get_texture_id() << "\n";
    }
}

void FrameManager::apply_framestate(Actor &a) {
    std::cerr << "applying framestate\n";
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

