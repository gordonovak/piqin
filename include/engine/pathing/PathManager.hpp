#pragma once

#include <vector>

#include "Path.hpp"
#include "engine/actors/Transform.hpp"
#include "../utilities/SparseVector.hpp"

namespace geng {
    /** @brief Updates all paths such that they affect their assigned @code gengine::Transform@endcode object correctly.
     * @details Constains a @code std::unordered_map<Path*>@endcode and defines how it can be interacted with.
     * The following member functions apply:
     * 1. @code PathManager()@endcode › default constructor
     * 2. @code void add_path(Transform& t, Path* p)@endcode › adds a path to the given transform
     * 3. @code void remove_path(Transform& t, Path* p)@endcode › removes a path from the given transform
     * 4. @code void update()@endcode › updates all paths in the PathManager, and deletes finished paths.
     * 5. @code ~PathManager()@endcode › deletes all paths in the PathManager
     */
    class PathManager {
        /// A SparseVector containing all the paths. Destroyed paths are nullptrs.
        std::unordered_map<uint32_t, Path*> paths;
    public:
        /// Default constructor for PathManager
        PathManager() = default;

        /// Adds a path to the path manager
        void add_path(Path *p);
        /// Adds a path, targeted at the provided transform with a given offset.
        void add_path(Path *p, Transform &t, const Vertex &offset = {0.f,0.f,0.f});

        /// Removes a path from the given transform
        void remove_path(const Transform &t);
        /// Removes a path with the given path pointer (not recommended to use because not O(1))
        void remove_path(const Path *path);

        /// Updates all paths in the PathManager
        void update();

        /// Destructor that destroys all paths in the PathManager
        ~PathManager();

    };
}
