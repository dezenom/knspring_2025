#include <kn/KrakenEngine.hpp>
#include "utils.hpp"
#include "globals.hpp"
#include "Game.hpp"

int main() {
    kn::window::init(screendimensions,"kraken-jam",true);
    kn::Event event;
    kn::time::Clock clock;

    Game game("res/scenes/environment");

    // const float starttime = SDL_GetTicks();

    while (kn::window::isOpen()) {
        while (kn::window::pollEvent(event)) {
        }

        game.update();
        game.render();
        clock.tick(60);
        // utils::outFPS(starttime);

    }
    kn::window::quit();

    return 0;
}


