#include "game/board/Deal.hpp"

Deal::Deal() : pos(scene::width/2, scene::height/2, 0);
Deal::Deal(Vertex pos) : pos(pos) {}

void Deal::add_card(Card *card, bool flipped) {
    if (flipped & !card->is_flipped())
        card->flip();
    deal.push_back(card);
}

std::vector<Card*> Deal::pop_cards() {
    std::vector<Card*> cards = deal;
    deal.clear();
    return cards;
}

int Deal::get_score() {
    int sum = 0;
    for (auto& card : deal) {
        sum+=card.;
    }
}