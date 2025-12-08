#pragma once
#include <SDL_render.h>
#include <vector>
#include "engine/gengine-globals/EngineEnums.hpp"
#include "engine/actors/Transform.hpp"

namespace geng {
    /**
     * @brief Holds the points from a texture necessary to render a single sprite at render time. Usually, you do not make Frames manually,
     * and form them from a @code gengine::Quad@endcode with the @code Quad.to_frame()@endcode function. Quads can be found in utilities/types
     * */
    struct Frame {
    private:
        /// Holds the points on a vertex necessary for rendering.
        std::vector<SDL_FPoint> vertexPoints;
        /// Base duration of the frame.
        float duration;
        /// What we do after this animation ends (CONTINUE, STOP, IDLE, REPEAT)
        GENG_Anim anim;
    public:
        /// Constructs a frame from a vector of points, a duration, and an animation.
        Frame(std::vector<SDL_FPoint> points, float duration, GENG_Anim anim);
        /// Sends the vertices to the renderer for rendering. Performs all the calculations for rotation, scaling, ect.
        void append_vertices(std::vector<SDL_Vertex>& buffer, Transform& t);

        // Getters
        /// Returns the duration of the frame
        [[nodiscard]] float get_duration() const;
        /// Returns the animation type of the frame.
        [[nodiscard]] GENG_Anim get_anim() const;
    };
}
