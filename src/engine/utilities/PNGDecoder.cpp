#include "engine/utilities/PNGDecoder.hpp"
#include <iostream>
#include <SDL2/SDL_image.h>
#include <fstream>
#include <vector>

// Note: We rename load_ktx2_as_texture to the new function name load_image_as_texture
SDL_Texture* PNGDecoder::load_image_as_texture(
    SDL_Renderer *renderer, std::string path) {

    // SDL_image provides a much simpler function to load an image file
    // and turn it directly into an SDL_Texture in one go.

    SDL_Texture* texture = IMG_LoadTexture(renderer, path.c_str());

    if (texture == nullptr) {
        // Use IMG_GetError() to report why the load failed
        std::cerr << "Failed to load image file " << path << " using SDL_image.\n";
        std::cerr << "SDL_image Error: " << IMG_GetError() << "\n";
        return nullptr;
    }

    // This blend mode setting is often still required for transparency
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

    return texture;
}

// Remove the following functions entirely as they are no longer needed:
// SDL_Texture* PNGDecoder::load_ktx2_image_as_texture(...)
// ... the Basisu/ZSTD implementation code is gone ...
