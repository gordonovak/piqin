#pragma once
#include <iostream>

#include "engine/animation/FrameTable.hpp"

namespace geng {
    /**
     * Creates a registry linking texture_ids to FrameTables.
     */
    using FrameTableRegistry = std::unordered_map<int, FrameTable>;

    FrameTableRegistry& get_TableRegistry();
    // This allows us to call function constructions  though we haven't entered main yet
    // super cool
    struct TableRegister {
        // marked as explicit just cause
        explicit TableRegister(int table_id, const FrameTable& sheet);
    };
}
