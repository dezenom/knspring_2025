#include "kn/Font.hpp"
#include "kn/Color.hpp"
#include "kn/ErrorLogger.hpp"
#include "kn/Texture.hpp"
#include "kn/Window.hpp"

#include "kn/fonts/minecraftia.h"
#include "kn/fonts/titillium.h"

namespace kn
{
Font::Font(const std::string& fileDir, const int ptSize)
{
    if (!openFromFile(fileDir, ptSize))
        throw Exception("Failed to open font: " + fileDir);
}

Font::~Font()
{
    if (font)
        TTF_CloseFont(font);
}

bool Font::openFromFile(const std::string& fileDir, const int ptSize)
{
    if (ptSize < 0)
        return false;

    if (font)
    {
        TTF_CloseFont(font);
        font = nullptr;
    }

    if (fileDir == "kraken-clean")
    {
        SDL_RWops* rw = SDL_RWFromMem(TitilliumWeb_Regular_ttf, TitilliumWeb_Regular_ttf_len);
        font = TTF_OpenFontRW(rw, 1, ptSize);
    }
    else if (fileDir == "kraken-retro")
    {
        SDL_RWops* rw = SDL_RWFromMem(Minecraftia_Regular_ttf, Minecraftia_Regular_ttf_len);
        const int ptSizeFixed = ((ptSize + 4) / 8) * 8;
        font = TTF_OpenFontRW(rw, 1, ptSizeFixed);
    }
    else
    {
        font = TTF_OpenFont(fileDir.c_str(), ptSize);
    }

    return font != nullptr;
}

void Font::render(const std::string& text, const kn::math::Vec2& pos,const bool antialias, const Color& color,
                     const int wrapLength) const
{
    if (!font)
        return;

    SDL_Surface* surface;

    if (antialias)
    {
        surface = wrapLength > 0
                      ? TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, wrapLength)
                      : TTF_RenderUTF8_Blended(font, text.c_str(), color);
    }
    else
    {
        surface = wrapLength > 0
                      ? TTF_RenderText_Solid_Wrapped(font, text.c_str(), color, wrapLength)
                      : TTF_RenderText_Solid(font, text.c_str(), color);
    }

    if (!surface)
        FATAL("Failed to render text: " + std::string(TTF_GetError()));

    // if (!sdlTexture)
    //     FATAL("Failed to create texture: " + std::string(SDL_GetError()));
    SDL_FreeSurface(surface);

    kn::window::blit(
        kn::Texture(SDL_CreateTextureFromSurface(window::getRenderer(), surface))
        ,pos);

}
} // namespace kn
