#pragma once

#include "../FrameTableRegistry.hpp"
#include "../RegistryConstants.hpp"

#define ASSET_DRAW_DECK_PATH
#define ASSET_DRAW_DECK_DRAW_TYPE RENDER_VERTICAL


const geng::FrameTable asset_draw_deck = {
    "assets/full-texture.png",
    TEX_WIDTH, TEX_HEIGHT,
    416, 0,
    37, 53,
    2, 6,
};