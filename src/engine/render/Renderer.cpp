#include "engine/rendering/Renderer.hpp"
#include <string>

#include "engine/actors/Actor.hpp"
#include "engine/animation/asset-info/TextureRegister.hpp"

using namespace geng;

Renderer::Renderer(Camera* cam) :
		cam(cam), atlas(nullptr) {
	// Create the texture we will end up rendering to.
	canvasTex = nullptr;
	// Initializes good stuff
	vertices.resize(10000);
	vertices.clear();
}

void Renderer::initialize() {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Norton",
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			global::scene().width, global::scene().height, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
	bg = new Background(renderer);
	canvasTex = SDL_CreateTexture(
		renderer,
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_TARGET,
		global::scene().width, global::scene().height);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
	get_tex_register().initialize_textures(renderer);
}

Renderer::~Renderer() {
	delete cam;
}

void Renderer::set_render_texture() {
	SDL_SetRenderTarget(renderer, canvasTex);
	SDL_SetRenderDrawColor(renderer, 242, 32, 21, 255);
	SDL_RenderClear(renderer);
}

void Renderer::render(std::vector<Gear*>& gears) {

	/* RENDER SETUP */
	// First we set our draw color in case nothing renders
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	// We set up the camera center.
	camCenter = cam->center();
	// Then we update our canvas in case the user changed the window size
	update_canvas_size();
	// We flush the page
	SDL_RenderClear(renderer);
	/* RENDERING SHIT */

	vertices.clear();
	// Now we set our renderTexutre (global::scene.width x global::scene.height)
	// This will be global::scene().scaled up after we draw the background & actors
	set_render_texture();
	// Draw the background
	draw_background();

	// ><><><><><>< BIG PHASE ><><><><><><
	render_elements(gears);
	// ><><><><><>< BIG PHASE ><><><><><><

	/* Now we global::scene().scale up our texture in accordance with the gamera */
}



void Renderer::present() {
	// Sert our render to the backbuffer
	SDL_SetRenderTarget(renderer, nullptr);
	// Then we establish the thing we're writing to.

	// Otherwise we global::scene().scale without pixel perfect scaling
	// This is the rectangle we draw to if we don't use pixel perfect.
	SDL_Rect fr = {0, 0, 0,0};
	// These next lines
	fr.x = global::scene().borderX;
	fr.y = global::scene().borderY;
	fr.w = (global::scene().width * global::scene().scale);
	fr.h = (global::scene().height * global::scene().scale);

	// Now we global::scene().scale up our whole canvas
	SDL_RenderCopy(
		renderer,
		canvasTex,
		nullptr,
		&fr);
	// Finally we present our hard work
	SDL_RenderPresent(renderer);
}

void Renderer::set_texture_atlas(SDL_Texture *t) {
	atlas = t;
}

void Renderer::draw_background() {
	bg->update(global::scene().dt);
	SDL_RenderCopy(
		renderer,
		bg->get_texture(),
		nullptr,
		nullptr);
}


/*******************/
/* RENDER FUNCTIONS */
/*******************/

// <><><><><><><><><><><>><>
// Elements come presorted from the Engine
// <><><><><><><><><><><>><>
// Then, we separate each element into it's proper type and render it.
void Renderer::render_elements(const std::vector<Gear*>& gears) {
	for (auto& e: gears) {
		// If our item is not hidden
		if (!e->hidden()) {
			e->to_vertex(vertices);
		}

	}
	// Finally we make the render call.
	SDL_RenderGeometry(
		renderer,
		atlas,
		vertices.data(),
		vertices.size(),
		nullptr,
		0);
}

/* ............... */
/* UPDATE CANVAS   */
/* ............... */
// Updates our canvas size if the user resizes the window
void Renderer::update_canvas_size(){
	double wid, hei;
	// Gets the size of the window
	emscripten_get_element_css_size("canvas", &wid, &hei);

	int w = static_cast<int>(round(wid));
	int h = static_cast<int>(round(hei));
	// If our window changes we update shit
	if (w != canvasWidth || h != canvasHeight) {
		// Convert our w and h to ints to they go into width and height
		canvasWidth = w;
		canvasHeight = h;
		// Updates the window size
		SDL_SetWindowSize(window, canvasWidth, canvasHeight);
		// Tells our renderer to update its logic size.
		SDL_RenderSetScale(renderer, 1.0f, 1.0f);
		SDL_RenderSetLogicalSize(renderer, 0, 0);

		// Set our new camera width and height
		cam->set_width(canvasWidth);
		cam->set_height(canvasHeight);

		// Updates our global::scene().scale accordingly
		global::scene().scale = ((1.0 * canvasHeight) / canvasWidth < 0.75) ? 1.0*canvasHeight/global::scene().height : 1.0*canvasWidth/global::scene().width;
		if (global::scene().scale < 1.0) global::scene().scale = 1.0;

		if (PIXEL_PERFECT) {
			global::scene().scale = static_cast<int>(global::scene().scale); // NOLINT(*-narrowing-conversions)
			global::scene().borderX = static_cast<int>((canvasWidth-(global::scene().width*global::scene().scale))/2.f); // NOLINT(*-narrowing-conversions)
			global::scene().borderY = static_cast<int>((canvasHeight-(global::scene().height*global::scene().scale))/2.f); // NOLINT(*-narrowing-conversions)
		}
		else {
			global::scene().borderX = 0;
			global::scene().borderY = 0;
		}
	}
}
