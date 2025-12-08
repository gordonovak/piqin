#pragma once
#include "../types/Vertex.hpp"
#include <SDL.h>

#include "engine/gengine-globals/EngineEnums.hpp"


namespace geng {
    /** @brief The fundamental target for all effects, paths, shaking, and rendering.
     * @details The Transform contains all the position information necessary for a game object to be rendered. Although @code gengine::Actors@endcode are the primary
     * holders of transforms, other object types, like user-defined subclasses of @code gengine::Mesh@endcode can also hold transforms. We briefly cover
     * how the engine interfaces with @code gengine::Transform@endcode.
    * - @code gengine::Effect@endcode& @code gengine::Path@endcode target transform objects. Thus, if you want the convenience of these classes, use a Transform. Note
     * that they directly alter variables in the Transform object. Thus, if you intend to use these features, do not attempt to change Transform properties while they are in effect.
     * - @code engine.render()@endcode Relies on the width, height, position, and offset within a transform to render @code gengine::Actors@endcode
     * - @code gengine::Vertex pos@endcode and @code gengine::Vertex offset@endcode perform two different functions. @code pos@endcode keeps track of the absolute position
     * of the transform, while @code offset@endcode tells the render how far away from the base @code pos@endcode it should render the Transform.
     * @warning Any negative value in a Transform object is not defined behavior within the engine. There are no safeguards.
     * @note In order for computationally-intensive Transform calculations like rotation to be used, the @code bool locked@endcode flag must be set to @code false@endcode.
     * */
    struct Transform {
    private:
        /// Base width of the object
        uint16_t baseWidth = 10;
        /// Base height of the object
        uint16_t baseHeight = 10;
    public:
        /// ID of the transform. This should persist through any object carrying a transform. It is vital to the engine.
        int id = -1;
        /// Scale at which the object is rendered
        float scale = 1;
        /// Angle of rotation in degrees about the center
        float angle = 0;
        /// Editable width of the object
        float w = 10;
        /// Editable height of the object.
        float h = 10;
        /// Color of the transform.
        SDL_Color color = {255, 255, 255, 255};
        /// Contains rendering and engine
        GFlag flag;

        // Positioning
        /// Position of the Transform
        Vertex pos = Vertex(0,0,0);
        /// Rendering offset of the Transform
        Vertex offset = Vertex(0,0,0);

        /// Default constructor
        Transform() = default;
        /// Explicit constructor for position
        explicit Transform(Vertex pos) : pos(pos) {}
        /// Defines position, height, and width
        Transform(Vertex pos, uint16_t height, uint16_t width)
            : pos(pos), h(height), w(width), baseHeight(height), baseWidth(width) {}
        /// Defines position, height, width, and scale.
        Transform(Vertex pos, uint16_t height, uint16_t width, float scale)
            : pos(pos), h(height), w(width), baseHeight(height), baseWidth(width), scale(scale) {}

        // Member functions below
        // Locking
        /// Prevents Transform from undergoing complex vertex calculations like rotation
        void lock() { flag |= GFlag::locked; }
        /// Allows the renderer to pass the transform through complex vertex calcualtions like rotation
        void unlock() { flag &= ~GFlag::locked; }
        /// Returns if the Transform is locked or not
        [[nodiscard]] bool is_locked() const { return flag << GFlag::locked; }

        // Flipping
        /// Flips the object horizontally if not locked. (flip = !flip)
        void flipX() { flag |= GFlag::flipX; }
        /// Returns the object to the unflipped state
        void unflip() { flag &= ~GFlag::flipX; }

        // Hiding and unhiding
        /// Prevents the object from being rendered
        void hide() { flag |= GFlag::hidden; }
        /// Ensures the object is rendered
        void unhide() { flag &= ~GFlag::hidden; }


        // Resetting
        /// Returns flipping, width, height, and rotation to default values
        void reset() { unflip(); w = baseWidth; h = baseHeight; angle = 0;}

        [[nodiscard]] std::string to_string() const {
            std::string result = "{\n";

            result += "  id: " + std::to_string(id) + ",\n";
            result += "  scale: " + std::to_string(scale) + ",\n";
            result += "  angle: " + std::to_string(angle) + ",\n";
            result += "  width: " + std::to_string(w) + ",\n";
            result += "  height: " + std::to_string(h) + ",\n";
            result += "  baseWidth: " + std::to_string(baseWidth) + ",\n";
            result += "  baseHeight: " + std::to_string(baseHeight) + ",\n";

            result += "  color: {r:" + std::to_string(color.r) +
                      ", g:" + std::to_string(color.g) +
                      ", b:" + std::to_string(color.b) +
                      ", a:" + std::to_string(color.a) + "},\n";

            result += "  flag: " + geng::to_string(flag) + ",\n";
            result += "  pos: " + pos.to_string() + "\n";

            result += "}";
            return result;
        }
    };
}
