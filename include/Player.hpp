#pragma once
#include <kn/KrakenEngine.hpp>
#include <SDL_image.h>
#include "utils.hpp"

class Player
{
public:
    Player(const std::string spritesheet_filepath,const kn::math::Vec2 pos = kn::math::Vec2(0,0),const kn::math::Vec2 size = kn::math::Vec2(32,32));
    ~Player();

    void update();
    void render();

    void setDirection(kn::math::Vec2 vector = kn::math::Vec2(0,0));
    void setVector(kn::math::Vec2& reference,kn::math::Vec2 vector = kn::math::Vec2(0,0));
    void setGravity(kn::math::Vec2 vector = kn::math::Vec2 (0,-1));
    void setMovement(float p_accelaration = 1,
                     float p_friction = 1,
                     float p_max_speed = 5.0,
                     float p_jump_height = 12.0,
                     float p_max_gravity = 12.0);
    void setSpritesheet(const kn::Texture& texture);

    kn::Rect& getRect();
    kn::math::Vec2& getVelocity();
    kn::math::Vec2 getDirection();
    kn::math::Vec2& getGravity();
    kn::math::Vec2& getGravityVector();
    std::array<float, 4> getMovement();
    kn::Texture getSpritesheet();

private:

    float accelaration;
    float friction;
    float max_speed;
    float jump_height;
    float max_gravity;

    kn::Rect rect;

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
