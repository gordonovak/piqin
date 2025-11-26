#pragma once
#include <vector>
#include "game/cards/Card.hpp"


class Deal {
private:
    // Holds all the cards in our hand
    std::vector<Card*> deal;
    // Position of the deal
    Vertex pos;
    // Score of the deal
    int score = 0;
public:
    Deal();
    Deal(Vertex pos);

    // Adds a card to the deal
    void add_card(Card* card, bool flipped = false);
    // Pops all the cards off the vector
    std::vector<Card*> pop_cards();
    // Gets the score of the curent deal
    int get_score();

};
