#include "Scene.hpp"
#include "utils.hpp"

layer::layer(kn::math::Vec2 pos,const std::string& f_image):image(f_image),rect(pos,image.getSize()/2){

}
void layer::render(){
    kn::window::blit(image,rect);
}


Scene::Scene(kn::math::Vec2 pos,const std::string& folder_path){
    loadLayers(pos,folder_path);
}

void Scene::render(){
    for(const auto& i:layers){
        i->render();
    }
}

void Scene::loadLayers(kn::math::Vec2 pos,const std::string& folder_path){
    auto files = utils::iterateFolder(folder_path);
    for(auto file:files){
        layers.push_back(std::make_unique<layer>(pos, file));
        pos.x+=1600;
    }
}
