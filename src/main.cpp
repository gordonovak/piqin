#include <SDL.h>
#include <iostream>
#include <emscripten/html5.h>
#include <emscripten.h>

#include "engine/Engine.hpp"
#include "engine/animation/asset-info/FrameTableRegistry.hpp"
#include "engine/animation/asset-info/sheets/Asset-Card-Selector.hpp"
#include "engine/animation/asset-info/sheets/Asset-Card-Stack.hpp"
#include "engine/animation/asset-info/sheets/Asset-Deck.hpp"
#include "Card.hpp"
#include "engine/effects/effect-types/Shake.hpp"
#include "engine/effects/effect-types/Stretch.hpp"
#include "engine/particles/particle-types/ParticleRhombus.hpp"
#include "engine/particles/particle-types/ParticleSparkle.hpp"

Card* c = new Card(55, blackjack::BJ_Suit::SPECIAL);

// gameloop defined below
EM_BOOL gameloop(double time, void* userdata) {
	(void)userdata;
	// <><><><><><><><>
	// Updates our time and grabs user input & runs events
	// <><><><><><><><>

	if (!bob.tick(time))
		return EM_FALSE;


	// <><><><><><><><>
	// Finally we render
	// <><><><><><><><>
	bob.render();

	return EM_TRUE;
}


int main() {
	std::cerr << "into main?\n";
	{
		std::cerr << "tyring to register first frame\n";
		geng::get_TableRegistry().emplace(1, asset_draw_deck);
		std::cerr << "added frame 1.\n";
		geng::get_TableRegistry().emplace(2, asset_card_selector);
		std::cerr << "added frame 2.\n";
		geng::get_TableRegistry().emplace(0, asset_deck);
		std::cerr << "added frameSheets.\n";
	}
	bob.initialize();

	bob.add_actor(c);
	c->t.pos.y += geng::global::scene().height/2.f;
	c->set_hoverable();
	c->set_clickable();
	c->set_draggable();

	bob.apply_effect(new gfx::Stretch(c, 10.f, 2.f));


	std::cerr << "dont initializing\n";
	/******** END OF FUCK AROUND ZONE *******/
	emscripten_request_animation_frame_loop(gameloop, nullptr);
	emscripten_exit_with_live_runtime();

	// He's just a lil guy
	return 0;
}

