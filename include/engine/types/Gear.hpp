#pragma once
#include "engine/gengine-globals/EngineEnums.hpp"


namespace geng {
    /** @brief A gear is the fundamental abstract base class the engine handles. Actors, ParticleGroups, and Panels are all subclasses of the Gear class.
     * @details Member variables and classes are listed below:
     * - @code int id@endcode The id of the Gear
     * - @code GFlag flag@endcode Contains rendering information, like hidden, shadow, ect.
     * - @code virtual float z_index() = 0@endcode Returns the z-index of the object
     * - @code virtual void to_vertex() = 0@endcode Gets the rendering vertices of the object
     * - @code virtual ~Gear() = default@endcode Virtual destructor.
     */
    struct Gear {
    private:
        /// Rendering flag for the gear
        GFlag flag = GFlag::locked;
    public:
        /// Id of the Gear
        int id = -1;
        // vector index of the gear
        int index = -1;

        /// Z_index of the gear
        [[nodiscard]] virtual float z_index() const = 0;
        /// Gets the rendering vertices of the gear
        virtual void to_vertex(std::vector<SDL_Vertex>& buffer) = 0;
        /// Virtual destructor of the gear.
        virtual ~Gear() = default;
        /// Virtual to_string for the gear
        virtual std::string to_string() {
            return "Id: " + std::to_string(id) + "\nFlag: " + geng::to_string(flag);
        }

        // Bitmask helpers
        // Lock
        /// Prevents complex transformation calculations from taking place
        void lock() { flag |= GFlag::locked; }
        /// Unflips the lock flag
        void unlock() { flag &= ~GFlag::locked;}
        /// Returns if the flag is locked or not
        [[nodiscard]] bool locked() const { return flag << GFlag::locked; }
        // hide
        /// Hides the object
        void hide() { flag |= GFlag::hidden; }
        /// Unhides the object
        void unhide() { flag &= ~GFlag::hidden; }
        /// Returns true if the object is hidden
        [[nodiscard]] bool hidden() const { return flag << GFlag::hidden; }
        // Flipping
        void flipX() { flag |= GFlag::flipX; }
        void flipY() { flag |= GFlag::flipY; }
        void unflipX() { flag &= ~GFlag::flipX; }
        void unflipY() { flag &= ~GFlag::flipY; }
        [[nodiscard]] bool flippedX() const { return flag << GFlag::flipX; }
        [[nodiscard]] bool flippedY() const { return flag << GFlag::flipY; }
        // Shadows
        void set_shadow() { flag |= GFlag::shadow; }
        void unset_shadow() { flag &= ~GFlag::shadow; }
        [[nodiscard]] bool shadow() const { return flag << GFlag::shadow; }
        // Removal
        void flag_removal() { flag |= GFlag::remove; }
        void unflag_removal() { flag &= ~GFlag::remove; }
        [[nodiscard]] bool remove() const { return flag << GFlag::remove;}
        // Tagging
        void tag() { flag |= GFlag::tagged; }
        void untag() { flag &= ~GFlag::tagged; }
        [[nodiscard]] bool tagged() const { return flag << GFlag::tagged; }


    };
}
