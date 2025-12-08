#pragma once

/* Z-INDEXING */
// Z-indexing for blackjack
#define SELECTOR_Z_BASE 13.0f
#define HAND_Z_BASE 10.0f
#define BOARD_Z_BASE 9.0f
#define DRAW_Z_BASE 8.0f
#define DECK_Z_BASE 7.0f

// Default positions
// CardDraws
#define BJ_DEFAULT_PLAYER_POS geng::Vertex(3.3*geng::global::scene.width/8, 5*geng::global::scene.height/8.0, DRAW_Z_BASE)
#define BJ_DEFAULT_OPPONENT_POS geng::Vertex(3.3*geng::global::scene.width/8, 2*geng::global::scene.height/8.0, DRAW_Z_BASE)
// Floater card
#define BJ_DEFAULT_FLOATER_POS geng::Vertex(geng::global::scene.width/8.0f, 1.5*geng::global::scene.height/3.0f, DECK_Z_BASE)
#define BJ_DEFAULT_DISCARD_POS geng::Vertex(7*geng::global::scene.width/8.0f, 4*geng::global::scene.height/6.0f, HAND_Z_BASE)
// Deck & discard
#define BJ_DEFAULT_DECK_POS geng::Vertex(7*geng::global::scene.width/8.0f, 2.3*geng::global::scene.height/8, DECK_Z_BASE)
#define BJ_DEFAULT_SELECTOR_POS geng::Vertex(geng::global::scene.width/2.0f, 1.8f*geng::global::scene.height/2.0f, SELECTOR_Z_BASE)

// Selection offset
#define BJ_SELECT_OFFSET geng::Vertex(0, 5, 0)
#define BJ_SELECTOR_OFFSET geng::Vertex(0, -33, 0)
// Selection pathing
#define BJ_SELECT_PATH geng::GENG_Path::BALLOON

// Increment Card
#define CARD_INCREMENT_VALUE 3
// For shaking
#define BJ_SHAKE_DENY new geng::EffectShake(geng::GENG_Shake::SIDE, 5.0, 450, 10.f, true)
#define BJ_SHAKE_FLOATER geng::GENG_Shake::FLOATY, 5.0, -1, 2.0, false
#define BJ_SHAKE_FLOATER_TO_DISCARD geng::GENG_Shake::RANDOM, 3.0, 450, 2.0, true
#define BJ_SHAKE_END_ROUND new geng::EffectShake(geng::GENG_Shake::RANDOM, 2.0, 1000, 1.0, true)
// For particles
#define BJ_PARTICLE_FLOATER