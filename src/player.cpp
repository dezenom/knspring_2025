#include "Player.hpp"


Player::Player(const std::string spritesheet_filepath,const kn::math::Vec2 pos,const kn::math::Vec2 size)
:rect(pos,size) , spritesheet(spritesheet_filepath), spritesheet_surface(IMG_Load("res/images/animations/player.png")),
anim_index(0), anim_status(0), anim_speed(60/anim_src_rect.w*8),anim_src_rect({0,64},size*2),anim_mask(utils::generateAlphaMask(spritesheet_surface))
{
    setDirection();
    setVector(velocity);
    setGravity();
    setMovement();
    // still doesnt work, i should learn more on this
    // kn::Texture t(spritesheet_filepath);
    // setSpritesheet(t);

    utils::print(spritesheet.getSize());

}

Player::~Player(){
    SDL_FreeSurface(spritesheet_surface);
}
// combined

void Player::update(){
    movement();
    animation();
}
void Player::render(){
    kn::window::blit(spritesheet,rect,anim_src_rect);
}

void Player::movement(){
    setDirection(kn::input::getDirection("left", "right","up","down"));
    if(direction.x!=0 || direction.y!=0){
        setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,accelaration,max_speed*direction.x),kn::math::increment(velocity.y,accelaration,max_speed*direction.y)));
    }else {
       setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,friction,0),kn::math::increment(velocity.y,friction,0)));
    }
    // setVector(gravity_vector,kn::math::Vec2(kn::math::increment(gravity_vector.x,std::abs(gravity.x),max_gravity*gravity.x),kn::math::increment(gravity_vector.y,std::abs(gravity.y),max_gravity*gravity.y)));
    rect.x += velocity.x;
    rect.y += velocity.y;

}

void Player::animation(){
    anim_index += anim_speed;
    if(anim_index>anim_src_rect.w){
        anim_src_rect.x += anim_src_rect.w;
        anim_index = 0;
    }if(anim_src_rect.x>spritesheet.getSize().x){anim_index=0;anim_src_rect.x=0;}

    if(utils::isRegionTransparent(anim_mask,spritesheet.getSize().x,anim_src_rect)){
        anim_src_rect.x=0;
        anim_index = 0;
    }

}

// setters

void Player::setDirection(kn::math::Vec2 vector){
    direction = vector;
}
void Player::setVector(kn::math::Vec2& reference,kn::math::Vec2 vector){
    reference = vector;

}
void Player::setGravity(kn::math::Vec2 vector){
    gravity = vector;

}
void Player::setMovement(float p_accelaration,float p_friction,float p_max_speed,float p_jump_height,float p_max_gravity){
    accelaration = p_accelaration;
    friction = p_friction;
    max_speed = p_max_speed;
    jump_height = p_jump_height;
    max_gravity = p_max_gravity;
}


void Player::setSpritesheet(const kn::Texture& texture){
    spritesheet = std::move(texture);
}

// getters

kn::Rect& Player::getRect(){
    return rect;
}
kn::math::Vec2 Player::getDirection(){
    return direction;
}
kn::math::Vec2& Player::getVelocity(){
    return velocity;
}
kn::math::Vec2& Player::getGravity(){
    return gravity;
}
kn::math::Vec2& Player::getGravityVector(){
    return gravity_vector;
}
std::array<float, 4> Player::getMovement(){
    return std::array<float, 4>{accelaration,friction,max_speed,jump_height};
}

kn::Texture Player::getSpritesheet(){
    return spritesheet;
}
