#pragma once

#include "engine/pathing/Path.hpp"

namespace geng {
    /**
     * @brief Balloon path starts moving a Transform very fast, and then slows down as it approaches the target.
     */
    class BalloonPath final : public Path {
    private:
        Vertex direction;
    public:
        /// Regular constructor
        BalloonPath(Transform* t, const Vertex &target, float speed);
        /// Update override (true if done)
        bool update() override;
    };
}