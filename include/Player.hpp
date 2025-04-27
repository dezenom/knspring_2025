#pragma once
#include <queue>
#include <kn/KrakenEngine.hpp>
#include <SDL_image.h>
#include "utils.hpp"
#include "globals.hpp"

class Player
{
public:
    Player(const std::string spritesheet_filepath,const kn::math::Vec2 pos = kn::math::Vec2(0,0),const kn::math::Vec2 size = kn::math::Vec2(32,32));
    ~Player();

    void update();
    void render();

    void setDirection(kn::math::Vec2 vector = kn::math::Vec2(0,0));
    void setVector(kn::math::Vec2& reference,kn::math::Vec2 vector = kn::math::Vec2(0,0));
    void setGravity(kn::math::Vec2 vector = kn::math::Vec2 (0,1));
    void setMovement(float p_accelaration = 1,
                     float p_friction = 1,
                     float p_max_speed = 10.0,
                     float p_jump_height =15.0,
                     float p_max_gravity = 5.0);
    void setSpritesheet(const kn::Texture& texture);

    kn::Rect& getRect();
    std::vector<kn::math::Vec2>& getBody();
    kn::math::Vec2& getVelocity();
    kn::math::Vec2 getDirection();
    kn::math::Vec2& getGravity();
    kn::math::Vec2& getGravityVector();
    std::array<float, 4> getMovement();
    kn::Texture getSpritesheet();

    std::vector<std::string> chunks;

private:

    float accelaration;
    float friction;
    float max_speed;
    float jump_height;
    float max_gravity;

    kn::Rect rect;
    std::vector<kn::math::Vec2> body;

    kn::math::Vec2 gravity;
    kn::math::Vec2 gravity_vector;
    kn::math::Vec2 velocity;
    kn::math::Vec2 direction;

    kn::Texture spritesheet;
    SDL_Surface* spritesheet_surface;

    void movement();

    int anim_index;
    int anim_status;
    int anim_speed;
    kn::Rect anim_src_rect;
    std::vector<bool> anim_mask;
    void animation();
};

class Coolcube
{
public:
    Coolcube(Player* p_entity,kn::Rect p_rect = kn::Rect(100,100,32,32),kn::Color p_color = {200,255,255,255}, bool p_moving = false);
    ~Coolcube();

    void update();
    void render();

    void controlPath();
    void controlCollision();
    void movement();

private:

    kn::Rect rect;
    Player* entity;
    kn::Color color;
    bool moving;

    int timer;
    kn::math::Vec2 direction;
    kn::math::Vec2 mtv;
    int speed;
    int range;

    std::vector<kn::math::Vec2> body;

    std::queue<kn::math::Vec2> path;


};
