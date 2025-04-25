#include <kn/KrakenEngine.hpp>
#include "PolygonManager.hpp"
#include "utils.hpp"

PolygonManager::PolygonManager(const std::string& file):save_file(file)
{
    edit = true;
    current_polygon =-1;
    current_vertex = -1;
    load(save_file);

    utils::print("PMREADY");
}
PolygonManager::~PolygonManager(){
    save(save_file);
}


void PolygonManager::update(){
    if(edit){
        if (kn::input::isJustPressed("addPolygon"))addPolygon();
        else if (kn::input::isJustPressed("delPolygon"))delPolygon();
        if(polygons.size()){
            if (kn::input::isJustPressed("leftClick"))addVertex();
            else if (kn::input::isJustPressed("rightClick"))delVertex();
        }
    }
}

void PolygonManager::render(const kn::Color& col){
    for(const auto& polygon:polygons){
        kn::draw::polygon(polygon,col,2);
    }
}


// std::string PolygonManager::getName(){
//     SDL_StartTextInput();
//     std::string text = "";
//     kn::Event event;

//     bool get = true;

//     while(get){
//         while (kn::window::pollEvent(event)) {
//             while (kn::window::pollEvent(event)) {
//                 if (event.type == SDL_TEXTINPUT) {
//                     text += event.text.text;
//                     std::cout << "Typed: " << text << std::endl;
//                 }
//             }

//             if(kn::input::isJustPressed("return")){get =false;SDL_StopTextInput();}

//         }
//     }
//     return text;
// }

// void PolygonManager::addGroup(const std::string& group){
//     groups[group] = std::vector<std::vector<kn::math::Vec2>>();
//     current_polygon.key = group;current_polygon.index = -1;
// }
// void PolygonManager::delGroup(){
//     groups.erase(current_polygon.key);
// }

void PolygonManager::addPolygon(){
    std::vector<kn::math::Vec2> v = { {kn::mouse::getPos().x,kn::mouse::getPos().y} };
    polygons.push_back(v);
    current_polygon++;
    current_vertex = 0;
    utils::print("added polygon");
    // groups[current_polygon.key].push_back(v);

}
void PolygonManager::delPolygon(){
    // groups[current_polygon.key].erase(groups[current_polygon.key].begin() + current_polygon.index);
    if(current_polygon>-1){
        polygons.erase(polygons.begin() + current_polygon);
        current_polygon--;
        if(current_polygon>-1) current_vertex = (int)(polygons[current_polygon].size()-1); else current_vertex = -1;
        utils::print("removed polygon");
    }else
        utils::print("no polygons available");

}
void PolygonManager::addVertex(){
    // kn::math::Vec2 v = {kn::mouse::getPos().x,kn::mouse::getPos().y}
    // groups[current_polygon.key][current_polygon.index].push_back(v);

    polygons[current_polygon].push_back({kn::mouse::getPos().x,kn::mouse::getPos().y});
    utils::print("added vertex in polygon: ",current_polygon);
    current_vertex ++;
}
void PolygonManager::delVertex(){
    //get nearest vertex in the current polygon and delete it, work on later
    if(current_vertex>-1){
        if (current_vertex>0){
            polygons[current_polygon].erase(polygons[current_polygon].begin() + current_vertex);
            current_vertex--;
            utils::print("removed vertex");
        }else {delPolygon();}
    }else utils::print("no vertex available");
}

void PolygonManager::save(const std::string& file_path){
    json j = polygons;

    std::ofstream file(file_path);
    file << j.dump(4);
    file.close();
}
void PolygonManager::load(const std::string& file_path){
    std::ifstream in(file_path);
    if (in.is_open()){
        json j;
        in >> j;
        polygons = j.get<std::vector<std::vector<kn::math::Vec2>>>();
        current_polygon = (int)polygons.size()-1;
        current_vertex = (int)polygons[current_polygon].size()-1;
    }
}

// void PolygonManager::collision(const std::string& group){

// }
