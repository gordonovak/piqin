#include "engine/animation/FrameTable.hpp"

#include <iostream>

#include "engine/animation/AnimInfo.hpp"
#include "engine/animation/asset-info/TextureRegister.hpp"


using namespace geng;

FrameTable::FrameTable(std::string path, int texWidth, int texHeight, std::vector<std::vector<Quad>> quads) {
    texture_id = get_tex_register().register_texture(path);
    frames.resize(quads.size());
    for (int i = 0; i < quads.size(); i++) {
        for (auto q : quads[i]) {
            frames[i].push_back(q.to_frame(texWidth, texHeight));
        }
    }
}

FrameTable::FrameTable(std::string path, int texWidth, int texHeight, int startx, int starty, int w, int h,
            short numColumns, short numAnimations) {
    std::cerr << "entering frame table construction\n";
    texture_id = get_tex_register().register_texture(path);
    frames.resize(numAnimations);
    int count = 0;
    for (int k = 0; count < numAnimations; k++) {
        for (int i = 0; i < numColumns && count < numAnimations; i++) {
            Quad q(startx + (w*i), starty + (k*h), w, h);
            frames[count].push_back(q.to_frame(texWidth, texHeight));
            count++;
        }
    }
    std::cerr << "exiting frame table construction\n";
}

FrameTable::FrameTable(std::string path, int texWidth, int texHeight,
        int startx, int starty,
        int w, int h, short numColumns, short numAnimations,
        const std::vector<std::pair<int, std::vector<Quad>>> overrides)
{
    texture_id = get_tex_register().register_texture(path);
    frames.resize(numAnimations);

    size_t ovr = 0;
    for (int anim = 0; anim < numAnimations; ++anim) {

        if (ovr < overrides.size() && overrides[ovr].first == anim) {
            // Explicit override frames
            for (const Quad& q : overrides[ovr].second)
                frames[anim].push_back(q.to_frame(texWidth, texHeight));
            ++ovr;
        }
        else {
            int col = anim % numColumns;
            int row = anim / numColumns;
            Quad q(startx + col * w, starty + row * h, w, h);
            frames[anim].push_back(q.to_frame(texWidth, texHeight));
        }
    }
}

int FrameTable::get_texture_id() const {
    return texture_id;
}

Frame& FrameTable::get_frame(int animationNum, int frameNum) {
    if (animationNum < frames.size() && frameNum < frames[animationNum].size()) {
        return frames[animationNum][frameNum];
    }
    std::cerr << "FrameTable::frame [" << animationNum << "][" << frameNum << "] does not exist. aborting.\n";
    std::cerr << "Actual dimensions: numanimations: " << frames.size() << "\n";
    std::cerr << "frame layout:\n";
    for (auto& q : frames) {
        std::cerr << "<" << q.size() << "> ";
    }
    std::cerr << std::endl;
    abort();
}

void FrameTable::update_frame(AnimInfo& s) {
    if (s.frameType== GENG_Anim::IDLE)
        s.set_frame(frames[s.get_anim_id()][0]);
    if (s.frameType == GENG_Anim::CONTINUE)
        s.set_frame(frames[s.get_anim_id()][s.pre_increment_frame()]);
    else if (s.frameType == GENG_Anim::RESET)
        s.set_frame(frames[s.default_animation][0]);
    else if (s.frameType == GENG_Anim::REPEAT)
        s.set_frame(frames[s.get_anim_id()][s.pre_increment_frame()]);
    s.dirty = false;
}

