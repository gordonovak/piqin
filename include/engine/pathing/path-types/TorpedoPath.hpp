#pragma once

#include "engine/pathing/Path.hpp"

namespace geng {
    /**
     * @brief TorpedoPath starts an object moving slowly, and then speeds it up as it moves along.
     */
    class TorpedoPath final : public Path {
    private:
        /// Direction of travel for the path.
        Vertex direction;
    public:
        /// Regular constructor
        TorpedoPath(Gear* gear, const Vertex &target, float speed);
        /// Update override (true if done)
        bool update() override;
    };
}