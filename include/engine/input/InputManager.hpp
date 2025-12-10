#pragma once
#include "InputQueue.hpp"
#include "InputTarget.hpp"
#include <SDL.h>
#include <unordered_map>

#include "engine/actors/Actor.hpp"

namespace geng {
    class InputManager final {
        InputQueue iqueue;
        InputTarget* it;
        Actor* hover_target = nullptr;
        std::unordered_map<SDL_Scancode, Input> mapToBindings;
        std::unordered_map<Input, bool> pressedKeys;
        std::unordered_map<Input, bool> nullMap;

        // Gets the keybind for each scancode
        Input keybind(SDL_Scancode key);
    public:
        // Constructor, we need the menu
        explicit InputManager(InputTarget* menu);
        // Update with a given key event
        void update(SDL_Event & e);

        void mouse_hover(std::vector<Gear *> &actors);

        // Initializes the keybinds
        void load_keybinds(std::unordered_map<SDL_Scancode, Input> mappy);
        // Sets the input target
        void setInputTarget(InputTarget* target);
        // Gets if a key is pressed down.
    };
}
