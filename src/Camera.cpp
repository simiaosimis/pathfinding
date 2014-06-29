#include "Camera.h"
#include "Configuration.h"
#include "Game.h"
#include "Logger.h"

Camera::Camera(Entity* const entity_):
    entity(entity_),
    levelW(0),
    levelH(0),
    clip{0, 0, (int)Configuration::getCameraDistanceWidth(), (int)Configuration::getCameraDistanceHeight()}
{
    this->clip.x = (this->entity->x + this->entity->getWidth() / 2) - (this->clip.w / 2);
    this->clip.y = (this->entity->y + this->entity->getHeight() / 2) - (this->clip.h / 2);
    this->canMove = true;
}

Camera::~Camera(){

}

void Camera::update(){
    updatePosition();

    int x = Game::instance().getMouseX();
    int y = Game::instance().getMouseY(); 

    if(this->canMove && x != 0 && y != 0){
        Game::instance().dijkstra->printPath(x/64 + (y/64 * ((int)Configuration::getCameraDistanceWidth()/64)),
            this->entity->x/64 + (this->entity->y/64 * ((int)Configuration::getCameraDistanceWidth()/64)));
        this->canMove = false;
        this->entity->canMove = true;
    }
}

SDL_Rect& Camera::getClip(){
    return this->clip;
}

void Camera::updatePosition(){

    std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

    if(keyStates[GameKeys::LEFT]){
        this->clip.x -= 10;
    }
    else if(keyStates[GameKeys::RIGHT]){ 
        Log(DEBUG) << "direita";
        this->clip.x += 10;
    }
    else{}

    if(keyStates[GameKeys::UP]){
        this->clip.y -= 10;
    }
    else if(keyStates[GameKeys::DOWN]){ 
        this->clip.y += 10;
    }
    else{}

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
