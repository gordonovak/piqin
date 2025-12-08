#pragma once

#include <cstdint>

// General editing
#define PIXEL_PERFECT true
#define LOAD_RENDER_STYLE "0"

/* ************************** */
/* SHADOW CONSTANTS           */
#define SHADOW_ALPHA 50
#define SHADOW_OFFSET 5

/* Z-Indexing */
#define Z_MAX 100.0f

namespace geng {
    /** Bitmask that contains several useful flags. The effect of each flag if "true" is given below:
     * - @code hidden@endcode › Does not render this object
     * - @code shadow@endcode › Render the shadow of this object
     * - @code flipX@endcode › Flip this object horizontally
     * - @code flipY@endcode › Flip this object vertically
     * - @code locked@endcode › Do not perform complicated render logic on this object, such as rotation
     * - @code tagged@endcode › Print this object's to_string each frame
     * - @code remove@endcode › Will remove this object on the next frame
     */
    enum class GFlag : uint16_t {
        none = 0,
        hidden = 1 << 0,    /// Not displayed by the renderer
        shadow = 1 << 1,
        locked = 1 << 4,
        tagged = 1 << 5,
        remove = 1 << 6,
        flipX = 1 << 7,
        flipY = 1 << 8,
    };

    /// Returns true if the inner flag contains the outer flag.
    inline bool operator<<(GFlag f1, GFlag f2) {
        return (static_cast<uint16_t>(f1) & static_cast<uint16_t>(f2));
    }

    inline GFlag operator|(GFlag f1, GFlag f2) {
        return static_cast<GFlag>(static_cast<uint16_t>(f1) | static_cast<uint16_t>(f2));
    }

    inline void operator|=(GFlag& f1, GFlag f2) {
        f1 = static_cast<GFlag>(static_cast<uint16_t>(f1) | static_cast<uint16_t>(f2));
    }

    inline GFlag operator&(GFlag f1, GFlag f2) {
        return static_cast<GFlag>(static_cast<uint16_t>(f1) & static_cast<uint16_t>(f2));
    }

    inline void operator&=(GFlag& f1, GFlag f2) {
        f1 = static_cast<GFlag>(static_cast<uint16_t>(f1) & static_cast<uint16_t>(f2));
    }
    constexpr uint16_t GFLAG_ALL =
        static_cast<uint16_t>(GFlag::hidden) |
        static_cast<uint16_t>(GFlag::shadow) |
        static_cast<uint16_t>(GFlag::locked) |
        static_cast<uint16_t>(GFlag::tagged) |
        static_cast<uint16_t>(GFlag::remove) |
        static_cast<uint16_t>(GFlag::flipX) |
        static_cast<uint16_t>(GFlag::flipY);

    inline GFlag operator~(GFlag a) {
        return static_cast<GFlag>(
            (~static_cast<uint16_t>(a)) & GFLAG_ALL
        );
    }

    /// Converts a GFlag into a string.
    inline std::string to_string(GFlag flag) {
        auto f = [](bool op) { return (op) ? "true" : "false"; };
        std::string ret = "Hidden: ";
        ret += f(flag << GFlag::hidden);
        ret += "\nShadow: ";
        ret += f(flag << GFlag::shadow);
        ret += "\nLocked: ";
        ret += f(flag << GFlag::locked);
        ret += "\nTagged: ";
        ret += f(flag << GFlag::tagged);
        ret += "\nRemove: ";
        ret += f(flag << GFlag::remove);
        return ret;
    }

    /* Objects Tags */
    enum class GENG_Tag: uint8_t {
        NONE = 0,
        SELECTOR = 1
    };
    /* Render Frames */
    enum class GENG_Anim : uint8_t {
        IDLE = 0,
        RESET = 1,
        CONTINUE = 2,
        REPEAT = 3
    };
}