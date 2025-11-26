#pragma once
#include "Deal.hpp"
#include "game/cards/Card.hpp"
#include "input/InputTarget.hpp"
#include <vector>

#define BOARD_Z_BASE 9.0f
class Board : public InputTarget {
private:
    // The deck with all the cards
    std::vector<Card*> deck;
    // Player character's deal
    Deal* player;
    // Opponent's deal
    Deal* opponent;
    // Pointer back to player's hand
    InputTarget* hand;
    // Number it takes to get blackjack
    int targetScore;

public:
    // Default constructor -> creates deck of cards
    Board();
};