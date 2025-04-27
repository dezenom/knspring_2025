#include "Game.hpp"


Game::Game(const std::string& env):environment({0,0},env),
walls("res/data/saves/polygons/walls.json"),xbounds("res/data/saves/polygons/xbounds.json"),ybounds("res/data/saves/polygons/ybounds.json"),
player("res/images/animations/player.png",{300,900},{16,16}),c1(&player){
    setBinds();
    walls.clean();


}

void Game::render(){
        kn::window::clear({40,40,40,255});
    environment.render(player.getRect().x);
    player.render();
    c1.render();

        kn::window::flip();
}
void Game::update(){
    walls.update();
    mtv = {0,0};
    player.update();
    c1.update();

    for(const auto& chunk:player.chunks){
        if(walls.chunked.find(chunk) != walls.chunked.end()){
            for(const auto& polygon:walls.chunked[chunk]){
                if(utils::SATCollision(player.getBody(),polygon,mtv)){
                    player.getRect().x -= mtv.x;
                    player.getRect().y -= mtv.y;
                    player.getBody() = utils::getVertices(player.getRect());
                }
            }
        }
    } //doesnt work weirdly
    // for(const auto& polygon:walls.polygons){
    //     if(utils::SATCollision(body,polygon,mtv)){
    //         player.getRect().x -= mtv.x;
    //         player.getRect().y -= mtv.y;
    //     }
    // }

    bool xfreeze = false;
    for(const auto& polygon:xbounds.polygons){
        if(utils::SATCollision(player.getBody(),polygon,mtv)){
            xfreeze = true;
        }
        if(xfreeze)break;
    }
    bool yfreeze = false;
    for(const auto& polygon:ybounds.polygons){
        if(utils::SATCollision(player.getBody(),polygon,mtv)){
            yfreeze = true;
        }
        if(yfreeze)break;
    }

    if (!xfreeze)
        kn::camera.x = player.getRect().center().x - screendimensions.x/2;
    if(!yfreeze)
        kn::camera.y = player.getRect().center().y - screendimensions.y/2;


}
