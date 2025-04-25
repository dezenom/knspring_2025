#include "TileManager.hpp"
#include <SDL_image.h>

namespace  utils
{

    Tile::Tile(int p_tile_id,SDL_Surface* p_sprite,const kn::Rect& p_dst_rect):
        tile_id(p_tile_id),sprite(p_sprite),dst_rect(p_dst_rect),texture(SDL_CreateTextureFromSurface(kn::window::getRenderer(),sprite))
        {}

    Tile::~Tile(){
        SDL_FreeSurface(sprite);
    }

    void Tile::render(){
        kn::window::blit(texture,dst_rect,{0,0,32,32});
    }


    void loadTileset(const std::string& image_filepath, std::unordered_map<int, Tile>& result,kn::Rect tilesize){
        SDL_Surface*  surface = IMG_Load(image_filepath.c_str());

        int mag[2] = {(int)(surface->w/tilesize.w),(int)(surface->h/tilesize.h)};
        int tile_id = 0;

        for (int row = 0; row < mag[1]; row++) {
            for(int col = 0;col<mag[0];col++){
                SDL_Surface* sprite  = SDL_CreateRGBSurfaceWithFormat(0, tilesize.w, tilesize.h, 32, SDL_PIXELFORMAT_RGBA32);
                SDL_Rect rect = tilesize;
                SDL_BlitSurface(surface, &rect, sprite, nullptr);
                Tile tile(tile_id,sprite,{0,0,32,32});
                result[tile_id] = tile;

                tilesize.x+=tilesize.w;
                tile_id++;
                sprite = nullptr;
            }
            tilesize.y+=tilesize.w;
        }

        SDL_FreeSurface(surface);
        surface = nullptr;
    }
}//namespace utils
