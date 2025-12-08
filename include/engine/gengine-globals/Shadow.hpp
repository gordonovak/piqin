#pragma once
#include <SDL_render.h>
#include <utility>
#include <vector>

#include "EngineEnums.hpp"
#include "scene.hpp"


namespace geng {

    /// Renders shadows directly onto the background
    static void shadow_background(std::vector<SDL_Vertex>& buffer, int& numVertices);
    /// Renders shadows onto a given floor.
    static void shadow_floor(std::vector<SDL_Vertex>& buffer, int& numVertices);

    using shadowFunc = std::function<void(std::vector<SDL_Vertex>& buffer, int& numVertices)>;

    /** @brief The shadow calculator takes in a buffer of vertices, and renders a shadow behind the number of provided vertices.
     * @details The shadow calculator can dynamically change it's shadow render method on the fly with the set_function(...) method. Two shadow casting methods are pre-provided
     * which can be selected with @code set_function("background")@endcode and @code set_function("floor")@endcode. However, you are free to program shadow calculation functions yourself with
     * the @code add_function(std::string, std::function<void(SDL_Vertex>&buffer, int& numVertices)>)@endcode method. ShadowCalc is intended to be accessed exclusively through the @code shadow_calc@endcode inline global variable.
     * ShadowCalc has the following member variables and member functions
     * - @code shadowFunc currentFunc@endcode › current shadow rendering function
     * - @code int floor@endcode › determines the floor by which the floor calculation method calculates shadows
     * - @code unordered_map<string, shadowFunc>@endcode › Links shadow names to their respective functions
     * - @code set_function(std::string)@endcode › Sets the current shadow in accordance with the string
     * - @code add_function(std::string, shadowFunc)@endcode › Adds a shadow rendering method to the map of shadow functions
     * - @code apply_shadow(...)@endcode › Used exclusively by Actors, ParticleGroups, and Panels to render themselves
     * - @code set_floor(...)@endcode › Sets the floor for the floor rendering method
     */
    class ShadowCalc final {
    private:
        shadowFunc currentFunc = shadow_background;
        int floor = 50;
    public:
        std::unordered_map<std::string, shadowFunc> shadowfuncs {
            {"background", shadow_background},
            {"floor", shadow_floor}
        };

        void set_function(const std::string &shadow) {
            if (shadowfuncs.find(shadow) != shadowfuncs.end()) {
                currentFunc = shadowfuncs[shadow];
            }
            else {
                std::cerr << "FATAL: Shadow function does not exist.\n";
                abort();
            }
        }
        void add_function(const std::string& shadow, shadowFunc func) {
            if (shadowfuncs.find(shadow) != shadowfuncs.end()) {
                std::cerr << "Err adding shadow: function already exists.\n";
            }
            else {
                shadowfuncs[shadow] = std::move(func);
            }
        }
        void apply_shadow(std::vector<SDL_Vertex>& buffer, int numVertices) {
            if (buffer.size() < numVertices) {
                std::cerr << "ERR: Requesting more shadows than Vertices rendered.\n";
                numVertices = buffer.size();
            }
            currentFunc(buffer, numVertices);
        }
        void set_floor(int shadowFloor) {
            floor = shadowFloor;
        }
    };

    inline ShadowCalc shadows;

    static void shadow_background(std::vector<SDL_Vertex>& buffer, int& numVertices) {
        // First gets our size before we update with new buffer
        int oldsize = static_cast<int>(buffer.size());
        // Resize our vector accordingly.
        buffer.resize(oldsize + numVertices);
        // Now we copy the old memory to the new positions
        // First we get the location of the new data
        SDL_Vertex* loc = buffer.data() + oldsize;
        // And the size of each SDL_Vertex is 24, so we have 24*numVertices bytes to copy
        // Then we memcpy them cause it's fast
        std::memcpy(loc, loc - numVertices, numVertices*sizeof(SDL_Vertex));
        // Finally we update each vertex location
        for (int i = oldsize - numVertices; i < oldsize; i++) {
            // Store vertex in reference for easy access
            SDL_Vertex& vert = buffer[i];
            // Update its position
            vert.position = {
                vert.position.x + 0.02f*(vert.position.x - (global::scene.width*0.5f)),
                vert.position.y + (0.02f*(vert.position.y - global::scene.height*0.25f))
            };
            // Update it's color
            vert.color = {0, 0, 0, 50};
        }
    }

    static void shadow_floor(std::vector<SDL_Vertex>& buffer, int& numVertices) {

    }
}
