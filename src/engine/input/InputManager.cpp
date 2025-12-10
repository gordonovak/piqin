#include "engine/input/InputManager.hpp"

#include <SDL.h>
#include <utility>

#include "engine/utilities/Utilities.hpp"

#define keyb key.keysym.scancode

namespace geng {
    struct Actor;
}

using namespace geng;

InputManager::InputManager(InputTarget* menu) : it(nullptr) {
    load_keybinds({{SDL_SCANCODE_0, Input::NONE}});
}

void InputManager::load_keybinds(std::unordered_map<SDL_Scancode, Input> mappy) {
    mapToBindings = std::move(mappy);
    mapToBindings[SDL_SCANCODE_LSHIFT] = Input::MODIFY;
    mapToBindings[SDL_SCANCODE_W] = Input::UP;
    mapToBindings[SDL_SCANCODE_S] = Input::DOWN;
    mapToBindings[SDL_SCANCODE_D] = Input::RIGHT;
    mapToBindings[SDL_SCANCODE_A] = Input::LEFT;
    mapToBindings[SDL_SCANCODE_J] = Input::SELECT;
    mapToBindings[SDL_SCANCODE_K] = Input::BACK;
    mapToBindings[SDL_SCANCODE_SPACE] = Input::SELECT_ALT;
    mapToBindings[SDL_SCANCODE_P] = Input::PAUSE;
}

void InputManager::setInputTarget(InputTarget *target) {
    if (it != nullptr)
        it->heldKeys = &nullMap;
    it = target;
    it->heldKeys = &pressedKeys;
}

Input InputManager::keybind(SDL_Scancode key) {
    if (mapToBindings.find(key) != mapToBindings.end())
        return mapToBindings[key];
    return Input::NONE;
}

void InputManager::update(SDL_Event& e) {
    if (it != nullptr) {
        const Uint8* keyHeld = SDL_GetKeyboardState(0);
        // Update our queue and discard
        iqueue.update();
        if (e.type == SDL_KEYDOWN && e.key.repeat == false) {
            // Adds to the update queue
            iqueue.push(keybind(e.keyb)); // NOLINT(*-narrowing-conversions)
            // Sends the press to the input taret
            it->get_press(keybind(e.keyb));
            // Updates the pressed key
            pressedKeys[keybind(e.keyb)] = true;
        }
        // Letting a key up, update shit
        else if (e.type == SDL_KEYUP) {
            pressedKeys[keybind(e.keyb)] = false;
            it->get_release(keybind(e.keyb));
        }
    }
    else if (hover_target != nullptr) {
        // Update our hoverable target
        Actor& a = *hover_target;
        if (e.type == SDL_MOUSEBUTTONDOWN && a.clickable()) {
            a.on_click();
            a.engine_flagger(GFlag::clicked);
        }
        else if (e.type == SDL_MOUSEBUTTONUP && a.clicked()) {
            a.click_release();
            std::cerr << "releasing click\n";
            a.engine_deflagger(GFlag::clicked);
        }
        else if (e.type == SDL_MOUSEMOTION && a.clicked() && a.draggable()) {
            float dx = e.motion.xrel/global::scene().scale;
            float dy = e.motion.yrel/global::scene().scale;
            if (hover_target->is_actor()) {
                a.t.pos += {dx, dy, 0};
                a.move({dx, dy, 0});
                a.t.snap_to_scene();
            }
        }
    }
}

void InputManager::mouse_hover(std::vector<Gear*>& actors) {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    gutils::adjust_to_relative_coords(mouse);
    if (hover_target != nullptr) {
        if (!gutils::contained_within({mouse.x, mouse.y}, hover_target->t)){
            hover_target->hover_release();
            hover_target = nullptr;
        }
    }
    for (long i = static_cast<long>(actors.size()) - 1; i >= 0; i--) {
        if (!actors[i]->is_actor()) continue;
        Actor& a = *static_cast<Actor*>(actors[i]); // NOLINT(*-pro-type-static-cast-downcast)
        if (gutils::contained_within({mouse.x,mouse.y}, a.t)) {
            if (&a == hover_target)
                return;
            if (hover_target != nullptr)
                hover_target->hover_release();
            hover_target = &a;
            a.on_hover();
            return;
        }
    }
    if (hover_target != nullptr)
        hover_target->hover_release();
    hover_target = nullptr;
}