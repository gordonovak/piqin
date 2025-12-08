#pragma once
// My files
#include "Camera.hpp"
#include "background-utilities/Background.hpp"
#include "engine/particles/ParticleGroup.hpp"
#include "engine/gengine-globals/scene.hpp"

// Libraries
#include  <emscripten/html5.h>
#include <SDL.h>

#include "engine/types/Gear.hpp"


namespace geng {
	/** @brief The RenderManager takes in EngineElements from the Engine, and renders them.
	 * @details To specify a background for the scene, make a subclass of the
	 * @code gengine::Background@endcode class and call the @code engine.set_background(Background* b)@endcode function.
	 * @warning You should not interact with the RenderManager directly. The engine will handle it for you.
	*/
	class Renderer {
	public:
		explicit Renderer(Camera* cam);
		~Renderer();

		// Must call during main
		void initialize();

		// Renders each engine element according to its type.
		void render(std::vector<Gear*>& gears);
		// Present the render
		void present();

		// Gets our renderer for setup purposes. Should not be called once game loop starts.
		SDL_Renderer* get_renderer() { return renderer; }

		// Sets our texture_atlas to the texture specified.
		void set_texture_atlas(SDL_Texture* t);

	private:
		// RENDER PIPELINE
		// 1. Draws the background for our scene
		void draw_background();
		// 2. Divides gears between particles, actors, and UI
		void render_elements(const std::vector<Gear*>& gears);
		// 3. Render the actors and particles in order of z-xais.
		void render_object(Actor& o);

		// This sets our render texture to the small 300 x 200 window so we get pixel-perfect scaling.
		void set_render_texture();
		// Updates the canvas in case the user decides to resize the window
		void update_canvas_size();
		// Adds shadows to the buffer based on the number of vertices specified.
		void add_shadow(int numVertices);
	private:
		// Holds all the vertices we will ever need
		std::vector<SDL_Vertex> vertices;
		// Specifies what we need to access SDL window resources
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		Background* bg = nullptr;
		Camera* cam;
		Vertex camCenter;

		// Scene width and height! */
		int canvasWidth = global::scene.width;
		int canvasHeight = global::scene.height;
		float scale = 1.0; 		// How much the user has scaled things

		// This is the texture we draw to before scaling up.
		SDL_Texture* canvasTex;
		// The mass-game texture that holds everything
		SDL_Texture* atlas;
	};
}
