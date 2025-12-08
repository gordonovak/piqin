#pragma once

#include <vector>
#include <SDL_rect.h>

#include "FontTransform.hpp"
#include "engine/types/Quad.hpp"

namespace geng {
    /** Stores the information for one character of a font. Has member varibles:
     * - @code std::vector<SDL_FPoint> points@endcode › contains the base points of the font
     * - @code short w, h@endcode › The width and height of the character.
     * **/
    struct FontChar {
        /// Contains all the points on the texture atlas
        std::vector<SDL_FPoint> points;
        /// Contains width and height
        short w, h;
        /// Appends vertices to a buffer for editing.
        void to_vertex(const FontTransform& t, std::vector<SDL_Vertex>& buffer) {
            SDL_Vertex topleft = { {t.pos.x, t.pos.y}, t.color, points[0]};
            SDL_Vertex topright = {{t.pos.x + w * t.scale, t.pos.y}, t.color, points[1]};
            SDL_Vertex bottomleft = { {t.pos.x, t.pos.y + h * t.scale}, t.color, points[2]};
            SDL_Vertex bottomright = {{t.pos.x + w * t.scale, t.pos.y + h * t.scale}, t.color, points[3]};

            buffer.push_back(topleft);
            buffer.push_back(bottomleft);
            buffer.push_back(bottomright);
            buffer.push_back(topleft);
            buffer.push_back(topright);
            buffer.push_back(bottomright);
        }

        /// Converts quad into points
        FontChar(geng::Quad quad, int tex_width, int tex_height) {
            SDL_FPoint topleft = {1.f*(quad.x)/tex_width, 1.f*(quad.y)/tex_height};
            SDL_FPoint topright = {1.f*(quad.x+quad.w)/tex_width, topleft.y};
            SDL_FPoint bottomleft = {topleft.x, 1.f*(quad.y+quad.h)/tex_height};
            SDL_FPoint bottomright = {topright.x, bottomleft.y};

            points = {topleft, topright, bottomleft, bottomright};

            w = quad.w;
            h = quad.h;
        }
    };
}
