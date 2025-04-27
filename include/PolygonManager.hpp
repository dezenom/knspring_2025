#pragma once

// struct polygon{
//     std::string key;
//     int index;
// };

class PolygonManager
{
public:
    PolygonManager(const std::string& file);
    ~PolygonManager();

    // std::unordered_map< std::string,
    //                     std::vector<std::vector<kn::math::Vec2>> > groups;

    bool not_save;

    std::vector<std::vector<kn::math::Vec2>> polygons;std::unordered_map<std::string,std::vector<std::vector<kn::math::Vec2>>> chunked;
    int current_polygon;
    int current_vertex;
    std::string save_file;

    void update();
    void render(const kn::Color& col = {255,255,255,255});

    // std::string getName();

    // void addGroup(const std::string& group);
    // void delGroup();

    void addPolygon();
    void delPolygon();

    void addVertex();
    void delVertex();

    // void getCurrentPolygon(polygon fork);

    void save(const std::string& file_path);
    void load(const std::string& file_path);

    // void collision(const std::string& group);

    void clean();

};
