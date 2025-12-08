#pragma once

#include "engine/animation/FrameTable.hpp"

namespace geng::textures {
    /**
     * Creates a registry linking texture_ids to FrameTables.
     */
    using FrameTableRegistry = std::unordered_map<int, FrameTable>;

    /**
     * @return Returns the global FrameTableRegistry. Register a FrameTable with the syntax, @code static FrameTableRegister my_asset_name(ASSET_ID, FrameTable Object)@endcode
     */
    inline FrameTableRegistry& get_TableRegistry() {
        static FrameTableRegistry registry;
        return registry;
    }

    // This allows us to call function constructions even though we haven't entered main yet
    // super cool
    struct TableRegister {
        // marked as explicit just cause
        explicit TableRegister(int table_id, const FrameTable& sheet) {
            get_TableRegistry().emplace(table_id, sheet);
        }
    };
}
