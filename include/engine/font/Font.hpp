#pragma once

#include "FontChar.hpp"
#include <unordered_map>

namespace geng {
    /** Stores all the information for one font be rendered. **/
    struct Font {

        /// Texture that stores the font
        short texture_id = 0;
        /// Spacing between each font item
        float spacing = 0.f;
        /// Map between char and
        std::unordered_map<char, FontChar> chars;

        /** Mandatory constructor for a font:
         * - @code std::string path@endcode › path to the source texture
         * - @code std::unordered_map<char, Quad>@endcode › mapping each character to a position from the source texture
         * - @code short tex_width@endcode › width of the source texture
         * - @code short tex_height@endcode › height of the source texture
         * - @code short spacing = 0.f@endcode › pt spacing between each letter
         * - @code short offset_x = 0@endcode › how much off from x = 0 your original quad positons are (if you're using a texture atlas)
         * - @code short offset_y = 0@endcode › same thing
         */
        Font(std::string path, std::unordered_map<char, Quad> quads, int tex_width, int tex_height, short spacing = 0.f, short offset_x = 0, short offset_y = 0);

        /// Adds the correct character to a buffer of characters
        void add_FontChar(char c, std::vector<FontChar> &buffer, Vertex pos);

        /// Gets the height of the text
        [[nodiscard]] short get_height() const;

    };
}

