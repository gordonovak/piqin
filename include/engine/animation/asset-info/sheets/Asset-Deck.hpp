#pragma once

#include "../RegistryConstants.hpp"
#include "../FrameTableRegistry.hpp"

// Path to item
#define ASSET_DECK_PATH
// Render type
#define ASSET_DECK_RENDER_TYPE RENDER_VERTICAL

// Sprite info
static const geng::FrameTable asset_deck = {
    "assets/game-cards.ktx2",
    TEX_WIDTH,
    TEX_HEIGHT,
    0,0,
    32,48,
    13,65
};

static geng::textures::TableRegister asset_deck_obj(ASSET_DECK_ID, asset_deck);