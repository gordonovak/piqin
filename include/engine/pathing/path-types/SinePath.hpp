#pragma once

#include "engine/pathing/Path.hpp"

namespace geng {
    /**
     * @brief SinePath moves an object's x linearly, and has it y follow a sin wave.
     */
    class SinePath final : public Path {
    private:
        /// Direction of travel for the path.
        Vertex direction;
    public:
        /// Regular constructor
        SinePath(Gear* gear, const Vertex &target, float speed);
        /// Update override (true if done)
        bool update() override;
    };
}