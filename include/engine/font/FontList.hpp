#pragma once

#include <iostream>
#include <ostream>

#include "Font.hpp"
#include "font-types/FontRegister.hpp"

namespace geng {

    /** Manages all fonts so you can easily print fonts to either the canvas or the UI */
    class FontList {
        std::unordered_map<int, Font> fonts;

    public:
        FontList();
        /// Must call initialize before game loop.
        void initialize() {
            for (auto& [id, font] : get_FontRegistry()) {
                fonts.emplace(id, font);
            }
        }
        /// grabs a font
        Font at(int id) {
            if (fonts.find(id) == fonts.end()) {
                std::cerr << "ERR: Font " << id << " not found" << std::endl;
                abort();
            }
            return fonts.at(id);
        }
        /// grabs a font with the [] operator
        Font operator[](int id) {
            return at(id);
        }
    };

}
