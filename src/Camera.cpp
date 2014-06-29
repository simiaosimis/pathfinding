#include "Camera.h"
#include "Configuration.h"

Camera::Camera(Entity* const entity_):
    entity(entity_),
    levelW(0),
    levelH(0),
    clip{0, 0, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()}
{
    /// @todo If the player changes the resolution, so should the clip. (?)
}

Camera::~Camera(){

}

void Camera::update(){
    updatePosition();
}

SDL_Rect& Camera::getClip(){
    return this->clip;
}

void Camera::updatePosition(){
    this->clip.x = (this->entity->x + this->entity->getWidth() / 2) - (this->clip.w / 2);
    this->clip.y = (this->entity->y + this->entity->getHeight() / 2) - (this->clip.h / 2);

    // Left wall.
    if(this->clip.x < 0){
        this->clip.x = 0;
    }
    // Right wall.
    else if(this->clip.x > (int)this->levelW - this->clip.w){
        this->clip.x = (int)this->levelW - this->clip.w;
    }
    // Top wall.
    if(this->clip.y < 0){
        this->clip.y = 0;
    }
    // Bottom wall.
    else if(this->clip.y > (int)this->levelH - this->clip.h){
        this->clip.y = (int)this->levelH - this->clip.h;
    }
}

void Camera::centralizeOn(Entity* const entity_){
    this->entity = entity_;
}

void Camera::setLevelWH(const unsigned int width_, const unsigned int height_){
    this->levelW = width_;
    this->levelH = height_;
}
