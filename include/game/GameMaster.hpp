#pragma once

#include "blackjack/Board.hpp"
#include "blackjack/Round.hpp"

class GameMaster {
private:
    blackjack::Board board;
    blackjack::Round* round;
public:
    GameMaster() = default;
    ~GameMaster();
    void initialize();

    // Updating the actors
    void update();
    // Dealing with the Hand
    void add_card_to_hand(blackjack::Card c);
    // Set input target
    void set_hand_as_target();

    void blackjack();
};