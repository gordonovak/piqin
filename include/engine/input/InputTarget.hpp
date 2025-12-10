#pragma once
#include <unordered_map>

#include "InputConstants.hpp"

namespace geng {
    class InputTarget {
    public:
        // All the keys that are currently held down
        std::unordered_map<Input, bool>* heldKeys;
        // Default constructor
        InputTarget() = default;
        // Gets a held key
        void getHeld(Input keybind) {(*heldKeys)[keybind] = true;};

        // Gets if a key is held
        bool is_held(Input keybind) const {
            if (heldKeys->find(keybind) != heldKeys->end())
                return true;
            return false;
        }
        // Gets a pressed key. Must be virtual cause every interface will have valid/invalid inputs
        // Also must return a boolean.
        virtual bool get_press(Input keybind) = 0;
        // Gets the release of a held key
        virtual void get_release(Input keybind) = 0;

        virtual ~InputTarget() = default;
    };
}
