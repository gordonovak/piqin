#pragma once

#include <vector>
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
        GFlag flag = GFlag::locked | GFlag::shadow;
    public:
        /// The transform of any gear
        Transform t;
        /// Id of the Gear
        int id = -1;
        /// vector index of the gear
        int index = -1;

        /// Default constructor
        Gear() = default;
        /// Establish a pos
        explicit Gear(const Vertex &pos) : t(pos) {}
        /// Constructor with a transform
        explicit Gear(Transform t) : t(std::move(t)) {}

        /// Z_index of the gear
        virtual float z_index() const = 0;
        /// Gets the rendering vertices of the gear
        virtual void to_vertex(std::vector<SDL_Vertex>& buffer) = 0;
        /// Virtual destructor of the gear.
        virtual ~Gear() = default;
        /// Virtual to_string for the gear
        virtual std::string to_string() const {
            return "Id: " + std::to_string(id) + "\nFlag: " + geng::to_string(flag);
        }

        /* ............. */
        /* Bitmask helpers for easy flagging */
        /* ............. */
        // Hiding
        void lock() { flag |= GFlag::locked; }  /// Prevents complex transformation calculations from taking place
        void unlock() { flag &= ~GFlag::locked;}   /// Unflips the lock flag, such that complex render calculations like rotation will be performed on the object
        bool locked() const { return flag << GFlag::locked; } /// Returns if the flag is locked or not
        // hiding
        void hide() { flag |= GFlag::hidden; } /// Hides the object
        void unhide() { flag &= ~GFlag::hidden; } /// Unhides the object
        bool hidden() const { return flag << GFlag::hidden; } /// Returns true if the object is hidden
        // Flipping
        void flipX() { flag |= GFlag::flipX; }  /// Flips the object horizontally
        void flipY() { flag |= GFlag::flipY; }  /// Flip the object vertically
        void unflipX() { flag &= ~GFlag::flipX; }   /// Unflips the object horizontally
        void unflipY() { flag &= ~GFlag::flipY; }   /// Unflips the object vertically
        bool flippedX() const { return flag << GFlag::flipX; }    /// Returns true if flipped horizontally
        bool flippedY() const { return flag << GFlag::flipY; }    /// Returns true if flipped vertically
        // Shadows
        void set_shadow() { flag |= GFlag::shadow; }    /// Displays a shadow for this object
        void unset_shadow() { flag &= ~GFlag::shadow; } /// Prevents the display of a shadow for this object
        bool shadow() const { return flag << GFlag::shadow; } /// Returns true if the object should have a shadow rendered.
        // Removal
        void flag_removal() { flag |= GFlag::remove; }  /// Flags the object to be removed in the next frame
        void unflag_removal() { flag &= ~GFlag::remove; }
        bool remove() const { return flag << GFlag::remove;}  /// Returns true if the object is flagged for removal
        // Tagging
        void tag() { flag |= GFlag::tagged; }       /// The objects tostring will be printed out every frame.
        void untag() { flag &= ~GFlag::tagged; }    /// The object's tostring will not be printed out every frame
        bool tagged() const { return flag << GFlag::tagged; }     /// Returns true if tagged
        // Gives the type of the object
        bool is_actor() const { return flag << GFlag::actor; }    /// Returns true if the object is an actor
        bool is_particle() const { return flag << GFlag::particle; }  /// Returns true if th object is a particle
        bool is_panel() const { return flag << GFlag::panel; }    /// Returns true if the object is a panel
        /* .... Clicking and dragging .... */
        // hovering
        void set_hoverable() { flag |= GFlag::hoverable; }  /// Specifies this gear can be hovered over and it will have specific effects
        void unset_hoverable() { flag &= ~GFlag::hoverable; }   /// Specifies this gear cannot be hovered over
        bool hoverable() const { return flag << GFlag::hoverable; }
        // clicking
        void set_clickable() { flag |= GFlag::clickable; }  /// Specifies this gear can be clicked
        void unset_clickable() { flag &= ~GFlag::clickable; }   /// Specified this gear cannot be clicked
        bool clickable() { return flag << GFlag::clickable; }
        bool clicked() { return flag << GFlag::clicked; } /// Returns true if the object is currently clicked
        // dragging
        void set_draggable() { flag |= GFlag::draggable; }  /// Specifies this gear can be dragged
        void unset_draggable() { flag &= ~GFlag::draggable; }   /// Specifies this Gear can no longer be dragged
        bool draggable() const { return flag << GFlag::draggable; }

        // For engine use exclusively. DO NOT USE
        void engine_flagger(GFlag engine_flag) { flag |= engine_flag; } /// Adds special flags to the Gear
        void engine_deflagger(GFlag engine_deflag) { flag &= ~engine_deflag; }  /// Removes special flag from the gear
    };
}
