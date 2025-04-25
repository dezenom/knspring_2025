#pragma once

#include <kn/KrakenEngine.hpp>

namespace  utils
{
    struct Tile
    {
        int tile_id;
        SDL_Surface* sprite;
        kn::Rect dst_rect;
        kn::Texture texture;

        Tile() = default;
        Tile(int p_tile_id,SDL_Surface* p_sprite,const kn::Rect& p_dst_rect = {0,0,32,32});
        ~Tile();
        void render();
    };

    void loadTileset(const std::string& image_filepath, std::unordered_map<int, Tile>& result,kn::Rect tilesize = {0,0,32,32});
    //typeset - ie what the tyle correlates to, eg tile 0 is solid static etc,
    //typset is csv file, image is png file for now atleast

}//namespace utils
