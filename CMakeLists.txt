cmake_minimum_required(VERSION 3.13)
project(norton)

set(CMAKE_CXX_STANDARD 17)

# These flags get passed when using emcmake
set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_executable(norton
        src/main.cpp
        src/Card.cpp
        src/engine/Engine.cpp
        #[[
        # Main and engine


        # Game Logic Below
        src/game/GameMaster.cpp
        # Blackjack
        # Player and hand
        src/game/blackjack/Board.cpp
        src/game/blackjack/Round.cpp
        src/game/blackjack/bj-objects/Hand.cpp
        # Cards
        src/game/blackjack/cards/Card.cpp
        src/game/blackjack/bj-objects/CardSelector.cpp
        src/game/blackjack/bj-objects/Draw.cpp
        src/game/blackjack/bj-objects/Deck.cpp
        src/game/blackjack/bj-objects/Discard.cpp
        # Logic
        src/game/blackjack/bj-objects/Pather.cpp
        src/game/blackjack/cards/CardLogic.cpp
        src/game/blackjack/bj-logic/BJ-Actions.cpp
        src/game/blackjack/bj-logic/BJ-Input.cpp
        src/game/blackjack/bj-logic/BJ-CardLogic.cpp
        ]]

        # Game Engine Below
        # Input
        src/engine/input/InputManager.cpp
        src/engine/input/InputConstants.cpp

        # Actors
        src/engine/actors/ActorManager.cpp

        # Effects
        src/engine/effects/EffectManager.cpp
        src/engine/effects/effect-types/Shake.cpp
        src/engine/effects/effect-types/Stretch.cpp

        # Particles
        src/engine/particles/ParticleGroup.cpp
        src/engine/particles/ParticleManager.cpp
        src/engine/particles/ParticleRhombus.cpp
        src/engine/particles/ParticleSparkle.cpp

        # Pathing
        src/engine/pathing/PathManager.cpp
        src/engine/pathing/path-types/BalloonPath.cpp
        src/engine/pathing/path-types/TorpedoPath.cpp
        src/engine/pathing/path-types/ReboundPath.cpp
        src/engine/pathing/path-types/LinearPath.cpp
        src/engine/pathing/path-types/SinePath.cpp

        # Rendering
        src/engine/render/Renderer.cpp
        src/engine/render/Background.cpp

        # Frame Management
        src/engine/animation/FrameManager.cpp
        src/engine/animation/FrameTable.cpp
        src/engine/animation/Frames.cpp
        src/engine/animation/AnimInfo.cpp
        src/engine/animation/TextureRegister.cpp
        src/engine/animation/asset-info/FrameTableRegistry.cpp

        # Utilities
        src/engine/utilities/PNGDecoder.cpp
        src/engine/utilities/Utilities.cpp

        # Types
        src/engine/types/Vertex.cpp
        src/engine/types/Quad.cpp

        # Globals
        src/engine/gengine-globals/scene.cpp
        src/engine/gengine-globals/Timer.cpp
        src/engine/gengine-globals/Shadow.cpp
        src/engine/gengine-globals/Random.cpp
)

target_include_directories(norton PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include/scene
    ${CMAKE_SOURCE_DIR}/src/scene
)

# Emscripten-specific compile + link flags
target_compile_options(norton PRIVATE 
    "-sUSE_SDL=2"
    )
# regular run

target_link_options(norton PRIVATE 
    "-sUSE_SDL=2"
    "--shell-file=${CMAKE_SOURCE_DIR}/assets/game_shell.html"
    "--preload-file=assets"
    "--emrun"
    "-sMAXIMUM_MEMORY=32MB"
    "-sALLOW_MEMORY_GROWTH"
    "-sUSE_SDL_IMAGE=2"
    "-sSDL2_IMAGE_FORMATS=[\"png\"]"
)


# release build

#debug
#[[
target_link_options(norton PRIVATE
        "-sUSE_SDL=2"
        "--shell-file=${CMAKE_SOURCE_DIR}/assets/game_shell.html"
        "--preload-file=assets"
        "--emrun"
        "-sMAXIMUM_MEMORY=32MB"
        "-sALLOW_MEMORY_GROWTH"
        "-sASSERTIONS=1"
        "-sSTACK_OVERFLOW_CHECK=2"
        "-sSAFE_HEAP=1"
        "-g4"
        "-O0"
        "-gsource-map"
)
]]

set(CMAKE_TOOLCHAIN_FILE "/Users/gordie/emsdk/upstream/emscripten/.../Emscripten.cmake")