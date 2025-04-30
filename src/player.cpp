#include "Player.hpp"


Player::Player(const std::string spritesheet_filepath,const kn::math::Vec2 pos,const kn::math::Vec2 size)
:rect(pos,size) , spritesheet(spritesheet_filepath), spritesheet_surface(IMG_Load("res/images/animations/player.png")),
anim_index(0), anim_status(2),anim_src_rect({0,0},size*2),anim_speed(60/anim_src_rect.w*8)
{
    setDirection();
    setVector(velocity);
    setGravity();
    setMovement();
    // still doesnt work, i should learn more on this
    // kn::Texture t(spritesheet_filepath);
    // setSpritesheet(t);
    onground = false;

    utils::print(spritesheet.getSize());

}

Player::~Player(){
    SDL_FreeSurface(spritesheet_surface);
}
// combined

void Player::update(){
    movement();
    body = utils::getVertices(rect);
    animation();
}
void Player::render(){
    kn::window::blit(spritesheet,rect,anim_src_rect);
}

void Player::movement(){
    setDirection(kn::input::getDirection("left", "right","up","down"));
    // if(direction.x!=0 || direction.y!=0){
    //     setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,accelaration,max_speed*direction.x),kn::math::increment(velocity.y,accelaration,max_speed*direction.y)));
    // }else {
    //    setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,friction,0),kn::math::increment(velocity.y,friction,0)));
    // }


    if(direction.x!=0){
        anim_status = 1;
        setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,accelaration,max_speed*direction.x),0));
    }else {
        anim_status = 0;
       setVector(velocity,kn::math::Vec2(kn::math::increment(velocity.x,friction,0),0));
    }
    if (!onground)anim_status = 2;

    // // setVector(gravity_vector,kn::math::Vec2(kn::math::increment(gravity_vector.x,std::abs(gravity.x),max_gravity*gravity.x),kn::math::increment(gravity_vector.y,std::abs(gravity.y),max_gravity*gravity.y)));
    rect.x += velocity.x;
    rect.y += velocity.y;
    rect.x += gravity_vector.x;
    rect.y += gravity_vector.y;

    if (gravity_vector.y < max_gravity)gravity_vector.y+=gravity.y;

    if(kn::input::isJustPressed("up")){
        gravity_vector.y = -jump_height;
        onground = false;
    }

    chunks = {};
    int cut[2] = {-3,-3};
    int chunk[2] = {
        static_cast<int>(std::floor(rect.x / chunksize.x)),//shouldnt be like this, just learning dont be dumb tho ahahahahaha
        static_cast<int>(std::floor(rect.y / chunksize.y)),
    };

    for(int y=0;y<7;y++){
        for(int x=0;x<7;x++){
            int c[2] = {
                chunk[0]+cut[0],
                chunk[1]+cut[1]
            };
            chunks.push_back(utils::toStrChunk(c));
            cut[0]++;
        }
        cut[1]++;
    }

}

void Player::animation(){
    anim_index += anim_speed;
    if(anim_index>anim_src_rect.w){
        anim_src_rect.x += anim_src_rect.w;
        anim_index = 0;
    }

    anim_src_rect.y = 0;
    anim_src_rect.y = anim_src_rect.h * anim_status;
    if(anim_src_rect.right()>=spritesheet.getSize().x){anim_index=0;anim_src_rect.x=0;}
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
std::vector<kn::math::Vec2>& Player::getBody(){
    return body;
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



Coolcube::Coolcube(Player* p_entity,kn::Rect p_rect,kn::Color p_color , bool p_moving):rect(p_rect),entity(p_entity),color(p_color),moving(true),timer(0),direction(0,0),speed(5),
range(30){

}
Coolcube::~Coolcube(){
    entity = nullptr;
}
void Coolcube::update(){
    controlPath();
    movement();
    controlCollision();
}
void Coolcube::render(){
    kn::draw::rect(rect,color,100);
}


void Coolcube::controlPath(){
    if(!path.empty()){
        if(std::abs(rect.x-path.front().x)< range && std::abs(rect.y-path.front().y)< range){
            path.pop();
        }
    }
    if(moving){
        if(!path.empty()){
            if(timer>=3 && (std::abs(path.back().x-entity->getRect().x)> range || std::abs(path.back().y-entity->getRect().y)> range)){
                timer = 0;
                path.push({entity->getRect().x-10,entity->getRect().y-10});
            }
        }else {
            if(timer>=3 && (std::abs(rect.x-entity->getRect().x)> range || std::abs(rect.y-entity->getRect().y)> range)){
                timer = 0;
                path.push({entity->getRect().x-10,entity->getRect().y-10});
            }
        }
    }
    if(!moving){
        if(timer%3 == 0)path.push(kn::mouse::getPos());
    }
    if(kn::input::isJustPressed("rightClick")){
        path = std::queue<kn::math::Vec2>();
        path.push((kn::mouse::getPos()));
        moving = false;
        timer = 0;
    }
    if(kn::input::isJustPressed("leftClick")){
        moving=true;
    }

    if(timer >600 && !moving)moving = true;
    if(path.size()>15)path = std::queue<kn::math::Vec2>();

    timer++;
}

void Coolcube::controlCollision(){
    mtv = {0,0};
    if(!moving){
        body = utils::getVertices(rect);
        if(utils::SATCollision(entity->getBody(),body,mtv)){
            entity->getRect().x-=mtv.x;
            entity->getRect().y-=mtv.y;
            entity->getBody() = utils::getVertices(entity->getRect());
        }
    }
    if(mtv.y>0 and entity->getGravityVector().y > 0){
        entity->getGravityVector().y = 0;
        entity->onground = true;
;    }
}

void Coolcube::movement(){
    if(!path.empty()){
        const kn::math::Vec2 point (path.front().x-rect.x,path.front().y-rect.y);
        float inc = (point.getLength())/30;
        direction = kn::math::normalize(point);
        if(rect.x!=(path.front().x) || rect.y!=(path.front().y)){
            rect.x += speed * direction.x *inc;
            rect.y += speed * direction.y *inc;
        }
    }

}
