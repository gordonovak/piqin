#include "game/board/Board.hpp"

#include "input/InputConstants.hpp"

Board::Board() {
    deckPos = Vertex(3*scene::width/4, scene::height/2, 0);
    for (int i = 1; i <= 13; i++) {
        add_card(new Card(i, 'h'));
        add_card(new Card(i, 'c'));
        add_card(new Card(i, 'd'));
        add_card(new Card(i, 's'));
    }
}


std::vector<Card *> &Board::get_deck() {
    return deck;
}

Path Board::get_card_path(Card*& c) const {
    Vertex target(deckPos.x + deck.size()/4,
        deckPos.y + deck.size()/4,
        deckPos.z);
    Path p = {
        target,
        c->pos(),
        PATH_TORPEDO,
        1.0
    };
    return p;
}

bool Board::remove_card(Card *c) {
    for (int i = 0; i < deck.size(); i++) {
        if (deck[i] == c) {
            deck.erase(deck.begin() + i);
            return true;
        }
    }
    return false;
}

Card* Board::pop_card(const int i) {
    if (i < deck.size()) {
        Card* c = deck[i];
        deck.erase(deck.begin() + i);
        return c;
    }
    return nullptr;
}

void Board::add_card(Card *c) {
    deck.push_back(c);
    c->set_z_index(BOARD_Z_BASE + deck.size()/MAX_DECK_SIZE);
    c->set_path(get_card_path(c));
}

bool Board::hit_player() {
    if (deck.size() <= 0) return false;
    int cardnum = random() % deck.size();
    player.add_card(pop_card(cardnum));
}

bool Board::hit_opponent() {
    if (deck.size() <= 0) return false;
    int cardnum = random() % deck.size();
    opponent.add_card(pop_card(cardnum), opponent.get_num_cards() == 0);
}

bool Board::getPress(short keybind) {
    switch_to_hand = (keybind == INPUT_MODIFY);
    if (keybind == INPUT_SELECT)
        return hit_player();
    if (keybind == INPUT_BACK)
        return hit_opponent();
    return false;
}
