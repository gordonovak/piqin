#pragma once
#include <SDL.h>
#include <string>

class PNGDecoder {
public:
    // New function signature for loading any image format supported by SDL_image
    static SDL_Texture* load_image_as_texture(SDL_Renderer* renderer, std::string path);
};
