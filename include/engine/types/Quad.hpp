#pragma once
#include "engine/animation/Frame.hpp"
#include "engine/gengine-globals/EngineEnums.hpp"

namespace geng {
    /**
    * @brief Largely a temporary type used for converting rectangular coordinates into Frame objects or vertices for vertex rendering.
    * @details You primary use the @code to_frame@endcode function to convert to a frame object. Frame objects can then take Vertex data and create render output from it.
    */
    struct Quad {
        int x, y, w, h;
        float duration;
        GENG_Anim anim;
        Quad(int x, int y, int w, int h,
            float duration = 0.f, GENG_Anim anim = GENG_Anim::IDLE);
        Frame to_frame(int &texWidth, int &texHeight) const;
    };
}
