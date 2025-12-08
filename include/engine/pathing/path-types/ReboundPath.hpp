#pragma once

#include "engine/pathing/Path.hpp"

namespace geng {
    /**
     * @brief ReboundPath moves a Transform away from the target, then slingshots to the target.
     */
    class ReboundPath final : public Path {
    public:
        /// Regular constructor
        ReboundPath(Transform* t, const Vertex &target, float speed);
        /// Update override (true if done)
        bool update() override;
    };
}