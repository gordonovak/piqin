#pragma once

#include "engine/pathing/Path.hpp"

namespace geng {
    /**
     * @brief LinearPath moves a Transform towards a destination
     * in a straight line at constant speed.
     */
    class LinearPath final : public Path {
    private:
        geng::Vertex direction;
    public:
        /// Regular constructor
        LinearPath(Gear* gear, const Vertex &target, float speed);
        /// Update override (true if done)
        bool update() override;
    };
}