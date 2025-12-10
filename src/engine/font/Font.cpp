#include "engine/font/Font.hpp"

#include <iostream>

#include "engine/animation/asset-info/TextureRegister.hpp"


using namespace geng;


Font::Font(std::string path, std::unordered_map<char, geng::Quad> quads,int tex_width, int tex_height, short spacing, short offset_x, short offset_y) : spacing(spacing){
    texture_id = get_tex_register().register_texture(path);

    for (auto& [c, q] : quads) {
        q.x += offset_x;
        q.y += offset_y;
        chars.emplace(c, FontChar(q, tex_width, tex_height));
    }

}

short Font::get_height() const {
    if (chars.size() == 0 ) {
        std::cerr << "ERR: No Font Characters added.\n";
        return -1;
    }
    for (auto& [c, q] : chars)
        return q.h;
    return -1;
}

void Font::add_FontChar(char c, std::vector<FontChar> &buffer, Vertex pos) {
    if (chars.find(c) != chars.end()) {
        FontChar f = chars.at(c);
        for (auto& i: f.points) {
            i.x += pos.x;
            i.y += pos.y;
        }
        buffer.push_back(chars.at(c));
    }
}
