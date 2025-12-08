#pragma once
#include "engine/font/Font.hpp"

namespace geng {
    /**
     * Creates a registry linking texture_ids to Fonts.
     */
    using FontRegistry = std::unordered_map<int, geng::Font>;

    /**
     * @return Returns the global FrameTableRegistry. Register a FrameTable with the syntax, @code static FrameTableRegister my_asset_name(ASSET_ID, FrameTable Object)@endcode
     */
    inline FontRegistry& get_FontRegistry() {
        static FontRegistry registry;
        return registry;
    }

    // This allows us to call function constructions even though we haven't entered main yet
    // super cool
    struct FontRegister {
        // marked as explicit just cause
        explicit FontRegister(int table_id, const Font& font) {
            get_FontRegistry().emplace(table_id, font);
        }
    };
}
