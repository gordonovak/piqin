#pragma once

#include "engine/effects/Effect.hpp"

namespace gfx {

    /** Stretch is a permanent (by default) effect that stretches an object when it moves.  **/
    class Stretch final : public geng::Effect{
    private:
        geng::Vertex oldPos;
        float stretchX = 1.f;
        float stretchY = 1.f;
        float snappiness = 1.f;
    public:
        /// Snappiness specifies how fast the object stretches.
        Stretch(geng::Gear* gear, float amplitude, float snappiness = 1.f);

        /// Override function.
        bool update() override;
    };
}
