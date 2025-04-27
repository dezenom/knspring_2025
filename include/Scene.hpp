// store scene in folders , png scenes, name files in ascending order from 0 on how they are to be render, ie 0.png-farrr back,
// name folder with scene name, ie level one etc
#pragma once
#include <kn/KrakenEngine.hpp>

struct layer{
    layer(kn::math::Vec2 pos,const std::string& f_image);

    kn::Texture image;
    kn::Rect rect;
    void render();
};

class Scene
{
public:
    Scene(kn::math::Vec2 pos,const std::string& folder_path);
    void render(float bound);

private:

    std::vector<std::unique_ptr<layer> > layers;

    void loadLayers(kn::math::Vec2 pos,const std::string& folder_path);

};
