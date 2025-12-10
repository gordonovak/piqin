#include "engine/animation/asset-info/TextureRegister.hpp"
#include <iostream>
#include "engine/utilities/PNGDecoder.hpp"

using namespace geng;

TextureRegister::TextureRegister() {
    std::cerr << "making a texture register.\n";
}

int TextureRegister::register_texture(std::string path) {
    std::cerr << "trying to register a texture.\n";
    if (path_to_textureID.find(path) == path_to_textureID.end()) {
        int i = ID_to_texture.size();
        path_to_textureID[path] = i;
        return i;
    }
    return path_to_textureID[path];
}

void TextureRegister::initialize_textures(SDL_Renderer *renderer) {
    // Goes through all the uninitialized assets and renders them.
    for (auto& [path, i] : path_to_textureID)
        if (ID_to_texture.find(i) == ID_to_texture.end())
            ID_to_texture[i] = PNGDecoder::load_image_as_texture(renderer, path);
}

void TextureRegister::destroy_texture(int index) {
    if (ID_to_texture.find(index) != ID_to_texture.end()) {
        SDL_DestroyTexture(ID_to_texture[index]);
        ID_to_texture.erase(index);
    }
}


SDL_Texture* TextureRegister::get_texture(int index) {
    if (ID_to_texture.find(index) == ID_to_texture.end()) {
        std::cerr << "TextureRegister::Texture ID does not exist. [FATAL]\n";
        return nullptr;
    }
    return ID_to_texture[index];
}


SDL_Texture* TextureRegister::operator[](const int& index) {
    if (ID_to_texture.find(index) == ID_to_texture.end()) {
        std::cerr << "TextureRegister::Texture ID does not exist. [FATAL]\n";
        return nullptr;
    }
    return ID_to_texture[index];
}


TextureRegister::~TextureRegister() {
    for (auto& [i, tex] : ID_to_texture) {
        SDL_DestroyTexture(tex);
    }
}

TextureRegister& geng::get_tex_register() {
    static TextureRegister tex_register;
    return tex_register;
}
