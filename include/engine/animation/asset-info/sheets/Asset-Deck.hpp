#pragma once

#include <iostream>

#include "../RegistryConstants.hpp"
#include "../FrameTableRegistry.hpp"

// Path to item
#define ASSET_DECK_PATH
// Render type
#define ASSET_DECK_RENDER_TYPE RENDER_VERTICAL



// Sprite info
const geng::FrameTable asset_deck = {
    "assets/full-texture.png",
    TEX_WIDTH,
    TEX_HEIGHT,
    0,0,
    32,48,
    13,65
};