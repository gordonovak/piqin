#pragma once

#include <unordered_map>

#include "FontRegister.hpp"
#include "engine/animation/asset-info/RegistryConstants.hpp"
#include "engine/font/Font.hpp"
#include "engine/types/Quad.hpp"

const geng::Font default_pixel_font = {
    "assets/full-texture.ktx2",
    {
    {'a', {0, 0, 4, 9}}, // 'a'
    {'b', {5, 0, 4, 9}},
    {'c', {10, 0, 3, 9}},
    {'d', {14, 0, 4, 9}},
    {'e', {19, 0, 4, 9}}, // 'e'
    {'f', {24, 0, 3, 9}},
    {'g', {27, 0, 4, 9}},
    {'h', {32,0, 4, 9}},
    {'i',{37,0,1,9}},
    {'j',{38,0,2,9}},
    {'k',{41,0,4,9}},
    {'l', {46,0,1,9}},
    {'m',{48,0,7,9}},
    {'n',{56,0,4,9}},
    {'o', {61,0,4,9}},
    {'p',{66,0,4,9}},
    {'q',{71,0,4,9}},
    {'r',{76, 0, 3, 9}},
    {'s', {80, 0, 3, 9}},
    {'t',{84,0,4,9}},
    {'u',{88,0,4,9}},
    {'v',{93,0,5,9}},
    {'w',{99,0,7,9}},
    {'x',{107,0,5,9}},
    {'y',{113,0,4,9}},
    {'z', {118, 0, 4,9}},
    {'.', {50, 18, 1, 9}},
    },
    TEX_WIDTH, TEX_HEIGHT,
    1,
    0, 240
};

//inline geng::FontRegister pixel_font_register(0, default_pixel_font);