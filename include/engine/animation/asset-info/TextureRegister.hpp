#pragma once
#include <SDL_render.h>
#include <string>
#include <unordered_map>

namespace geng {
    /** @brief The TextureRegister links asset paths to GPU textures via two unordered maps. Each unique file path is assigned an ID, and each ID links to one texture.
     * @details The TextureRegister should know of all textures before main starts. There exists no "post-load asset" feature yet.
     * - To use the TextureRegister, call @code register_texture(string path)@endcode, and it
     * will return an integer with the ID of that texture.
     * - Then the engine should automatically call the @code initialize_textures@endcode method during main, loading all textures into memory.
     * @warning You should not access the texture register yourself. Instead, use the FrameTableRegistry to register FrameTables, which will
     * automatically be assigned a texture ID.
     */
    class TextureRegister {
    private:
        std::unordered_map<std::string, int> path_to_textureID;
        std::unordered_map<int, SDL_Texture*> ID_to_texture;
    public:
        // Constructs
        TextureRegister();
        ~TextureRegister();

        // Registers a sprite. Returns sheet_id
        int register_texture(std::string path);
        // Initializes all the textures with the renderer. This is essential
        void initialize_textures(SDL_Renderer* renderer);
        // Destroys the texture with the given ID if not needed
        void destroy_texture(int index);

        // Accesses the texture with a specific sheet_id (both do the same thing)
        SDL_Texture* operator[](const int& index);
        SDL_Texture* get_texture(int index);
    };

    inline TextureRegister tex_register;
}