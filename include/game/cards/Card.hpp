#pragma once
#include "generics/Object.hpp"
#include "textures/asset-info/RegistryConstants.hpp"


#define CARD_FLIPPED 53

class Card : public Object {
    uint8_t value;
    char suite;
    bool flipped = false;

    [[nodiscard]] uint8_t to_state(uint8_t val, char suit) const;

public:
    Card(uint8_t value, char suite);

    // Copy constructor
    Card(Card& c);

    bool operator==(const Card c) const;

    void flip();
    [[nodiscard]] bool is_flipped() const;
};
inline const Transform defaultCardTransform = {
    {scene::width / 2.0f, 0, 0},
    {0,0,0},
    48,
    32,
    1,
    0.0f
};

inline const FrameState defaultCardFrameState = {
    ASSET_DECK_ID
};