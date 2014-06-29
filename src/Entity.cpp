#include "Entity.h"
#include "Game.h"
#include "SDLWrapper.h"
#include "Logger.h"

Entity::Entity(const double x_, const double y_, const std::string& path_) :
    x(x_),
    y(y_),
    isRight(true),
    sprite(Game::instance().getResources().get(path_)),
    width(0),
    height(0),
    animationClip{0,0,0,0},
    boundingBox{(int)x_, (int)y_, 0, 0}
{
    // Only serves as the initializer for the derived classes.

    if(this->sprite != nullptr){
        this->width = this->sprite->getWidth();
        this->height = this->sprite->getHeight();
        
        this->boundingBox.w = this->width;
        this->boundingBox.h = this->height;
    }
    else{
        Log(WARN) << "Entity sprite is null, width and height will be undefined.";
    }
}

Entity::~Entity(){

}

unsigned int Entity::getWidth(){
	return this->width;
}

unsigned int Entity::getHeight(){
	return this->height;
}

SDL_Rect& Entity::getAnimationClip(){
	return this->animationClip;
}

SDL_Rect& Entity::getBoundingBox(){
    return this->boundingBox;
}

void Entity::setCollisionRects(const std::vector<CollisionRect>& collisionRects_){
    this->collisionRects = collisionRects_;   
}
