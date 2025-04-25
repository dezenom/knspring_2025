#include <kn/KrakenEngine.hpp>
#include "utils.hpp"
#include "Game.hpp"

int main() {
    kn::math::Vec2 screendimensions(1280,800);
    kn::window::init(screendimensions,"kraken-jam",true);
    kn::Event event;
    kn::time::Clock clock;

    Game game("res/scenes/background","res/scenes/foreground");


    while (kn::window::isOpen()) {
        while (kn::window::pollEvent(event)) {
        }

        game.update();
        game.render();
        clock.tick(60);
        // utils::outFPS();

    }
    kn::window::quit();

    return 0;
}


