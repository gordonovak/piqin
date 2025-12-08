#pragma once
#include <unordered_map>

#include "FrameTable.hpp"
#include "Mesh.hpp"
#include "AnimInfo.hpp"
#include "engine/actors/Actor.hpp"


namespace geng {
    /** @brief Manages all the @code Animator@endcode objects, and ensure they update themselves correctly, and can retrieve new frame info when necessary. Also handles loading new textures into memory via the TextureRegistry.
      * @details Holds a vector of @code FrameTable@endcode s indexed by ID.
      * @warning Must be initialized with the engine's renderer before runtime. This should be handled by the engine with @code engine.initialize()@endcode.
    */
    class FrameManager {
    private:
        /// Links frame_table_ids in AnimInfo objects to FrameTables.
        std::vector<FrameTable> sheets;

    public:
        /// Constructs the animatino manager.
        FrameManager();
        /// Loads the FrameSheets found in the FrameRegister
        void initialize();
        /// Initializes an AnimInfo to a new Actor
        void apply_framestate(Actor& a);
        /// Initalizes the appropriate AnimInfo for several actors.
        void apply_framestates(const std::vector<Actor*> &actors);
        /// Gets the texture ID of a mesh.
        int get_texture_id(Mesh& m);
        /// Gets the FrameTable associated with a specific actor.
        FrameTable& get_table(Actor& a);

        /// Updates all Animators in the given vector.
        void update(const std::vector<AnimInfo*>& anims);
    };
}
