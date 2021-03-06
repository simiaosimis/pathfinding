#include "Player.h"
#include "Game.h"
#include "Logger.h"
#include "Configuration.h"
#include <cmath>
#include <cfloat>

#include "Window.h"

#define ADD_STATE(stateEnum, stateClass) this->statesMap.emplace(stateEnum, new stateClass(this))

Player::Player(const double x_, const double y_, const std::string& path_) :
    DynamicEntity(x_, y_, path_),
    animation(nullptr)
{
    this->width = 64;
    this->height = 64;

    // Shouldn't be here?
    this->animation = new Animation(0, 0, this->width, this->height, 3, false);
    this->getAnimation()->changeAnimation(0, 0, 3, false, 2);

}

Player::~Player(){

}

void Player::update(const double dt_){
    std::array<bool, GameKeys::MAX> keyStates = Game::instance().getInput();

    Game::instance().clearKeyFromInput(GameKeys::ACTION);

    scoutPosition(dt_);

    updateBoundingBox();

    const std::array<bool, CollisionSide::SOLID_TOTAL> detections = detectCollision();
    handleCollision(detections);

    updatePosition(dt_);

    this->animation->update(this->animationClip, dt_);

    if(this->canMove){
        if(!Game::instance().path.empty()){
            if(goToLocation(Game::instance().path[0])){
                Game::instance().path.erase(Game::instance().path.begin() + 1);
            }
        }
        else{
            this->canMove = false;
        }
    }

}

void Player::handleCollision(std::array<bool, CollisionSide::SOLID_TOTAL> detections_){

    if(detections_.at(CollisionSide::SOLID_TOP)){ 
        this->nextY = this->y;
        this->vy = 0.001;
    }
    if(detections_.at(CollisionSide::SOLID_BOTTOM)){
        this->nextY = this->y;
        this->vy = -0.001;
    }
    else{
    }
    if(detections_.at(CollisionSide::SOLID_LEFT)){
        this->nextX = this->x;
        this->vx = 0.001;
    }
    if(detections_.at(CollisionSide::SOLID_RIGHT)){
        this->nextX = this->x;
        this->vx = -0.001;
    }

}

void Player::render(const double cameraX_, const double cameraY_){

    const double dx = this->x - cameraX_;
    const double dy = this->y - cameraY_;

    ///////////////////////////////////////////////////////////////////////////////////////////
    // // Actual.
    // SDL_Rect actualRect = {(int)dx, (int)dy, (int)this->width, (int)this->height};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0x00, 0x00, 0x00, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &actualRect);

    // Bounding box.
    // SDL_Rect boundingBox2 = {(int)(this->boundingBox.x - cameraX_), (int)(this->boundingBox.y - cameraY_), (int)this->boundingBox.w, (int)this->boundingBox.h};
    // SDL_SetRenderDrawColor( Window::getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
    // SDL_RenderFillRect(Window::getRenderer(), &boundingBox2);
    /////////////////////////////////////////////////////////////////////////////////////

    if(this->sprite != nullptr){
        SDL_RendererFlip flip = getFlip();

        if(flip == SDL_FLIP_HORIZONTAL)
            this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
        else
            this->sprite->render(dx, dy, &this->animationClip, false, 0.0, nullptr, flip);
    }

}

Animation* Player::getAnimation(){
    return (this->animation);
}

bool Player::goToLocation(int location_){
    int goingX = (location_ % 50) * 64;
    int goingY = (location_ / 50) * 64;
    bool gotX;
    bool gotY;

    if(this->x < goingX){
        moveHorizontal(false, true);
    }
    else if(this->x > goingX){
        moveHorizontal(true, false);
    }
    else{
        gotX = true;
    }

    if(this->y < goingY){
        moveVertical(false, true);
    }
    else if(this->y > goingY){
        moveVertical(true, false);
    }
    else{
        gotY = true;
    }
    if(gotX && gotY){
        return true;
    }

}

void Player::updateBoundingBox(){
    this->boundingBox.x = (int) this->nextX; //+ this->currentState->box.x;
    this->boundingBox.y = (int) this->nextY; //+ this->currentState->box.y;
    this->boundingBox.w = this->width; //currentState->box.w;
    this->boundingBox.h = this->height; //currentState->box.h;
}
