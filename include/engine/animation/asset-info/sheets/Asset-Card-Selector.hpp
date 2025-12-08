#pragma once

#include "../RegistryConstants.hpp"
#include "../FrameTableRegistry.hpp"


// Sprite info
static const geng::FrameTable asset_card_selector = {
    "assets/full-texture.ktx2",
    TEX_WIDTH, TEX_HEIGHT,
    416, 160,
    8,8,
    6,6,
};

// Register our sprite
static geng::textures::TableRegister asset_card_selector_obj(ASSET_CARD_SELECTOR_ID, asset_card_selector);