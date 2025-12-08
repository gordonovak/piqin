#pragma once
#include <cstdint>
#include <iostream>

namespace geng {
    // Scene information
    struct Scene final {
    private:
        double prevTime = 0.0f;
    public:
        // Game timing
        double time = 0.0f;
        uint64_t frame = 0;
        float dt = 0.0f;
        // Main menu?
        bool mainMenu = false;
        // Scene width, and height
        int width = 330;
        int height = 240;

        void update(const double game_time) {
            time = game_time;
            dt = static_cast<float>(game_time - prevTime);
            prevTime = game_time;
            frame++;
        }
    };

    namespace global {
        inline Scene scene;
    }
    // Fading in/out
    struct fader {
        // Member variables
        bool active = false;
        uint8_t faderAlpha = 80;
        uint8_t fadeStyle = 0;
    };
}
