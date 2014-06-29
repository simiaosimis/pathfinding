#include "DynamicEntity.h"
#include "Logger.h"
#include "Collision.h"
#include "Math.h"

DynamicEntity::DynamicEntity(const double x_, const double y_, const std::string& path_) :
	Entity(x_, y_, path_),
	vx(0.0),
	vy(0.0),
	speed(20.0),
	maxSpeed(550.0),
	isGrounded(false),
	nextX(x_),
	nextY(y_),
	reachedLevelEnd(false),
    activated(false),
    strength(0),
    distance(0),
    flightTime(0.0),
    levelW(0),
	levelH(0)
{

}

DynamicEntity::~DynamicEntity(){
	
}

void DynamicEntity::setLevelWH(const unsigned int width_, const unsigned int height_){
	this->levelW = width_;
	this->levelH = height_;
}

void DynamicEntity::updatePosition(const double dt_){
	((void)dt_); // Unused?

	this->x = this->nextX;
	this->y = this->nextY;

	this->isRight = (this->vx >= 0.0);
}

void DynamicEntity::scoutPosition(const double dt_){
	this->nextX += this->vx * dt_;
	this->nextY += this->vy * dt_;
}

std::array<bool, CollisionSide::SOLID_TOTAL> DynamicEntity::detectCollision(){
	std::array<bool, CollisionSide::SOLID_TOTAL> detections;
	detections.fill(false);

	for(auto tileBox : this->collisionRects){
		const Collision::RectangleSide side = Collision::rectsCollidedSide(this->boundingBox, tileBox.rect);
		if(side != Collision::RectangleSide::NONE){

			switch(side) {
				case Collision::RectangleSide::TOP: // Hitting under the tile.
					detections.at(SOLID_TOP) = (tileBox.type == COLLISION) ? true : false;
					break;

				case Collision::RectangleSide::BOTTOM: // Hitting top of the tile.
					detections.at(SOLID_BOTTOM) = (tileBox.type == COLLISION) ? true : false;
					break;

				case Collision::RectangleSide::RIGHT: // Hitting right side of the tile.
					detections.at(SOLID_RIGHT) = (tileBox.type == COLLISION) ? true : false;
					break;

				case Collision::RectangleSide::LEFT: // Hitting left side of the tile.
					detections.at(SOLID_LEFT) = (tileBox.type == COLLISION) ? true : false;
					break;

				default:
					Log(ERROR) << "Unknown rectangle side collided with a dynamic entity.";
					break;
			}
		}
		else{
			// No collision.
		}
		
	}

	return detections;
}

void DynamicEntity::moveHorizontal(const bool movingLeft_, const bool movingRight_){
	const double turnHandle = 5.5;
	if(movingLeft_ || movingRight_){
		if(movingLeft_){
			if(this->vx > 0.0){
				this->vx -= this->speed * turnHandle;
			}
			else{
				this->vx -= this->speed;
			}
			
			this->vx = (this->vx < -this->maxSpeed) ? -this->maxSpeed : this->vx;
		}
		if(movingRight_){
			if(this->vx < 0.0){
				this->vx += this->speed * turnHandle;
			}
			else{
				this->vx += this->speed;
			}
			this->vx = (this->vx > this->maxSpeed) ? this->maxSpeed : this->vx;
		}
	}
	else{
		slowVx();
	}
}

void DynamicEntity::moveVertical(const bool movingUp_, const bool movingDown_){
	const double turnHandle = 5.5;
	if(movingUp_ || movingDown_){
		if(movingUp_){
			if(this->vy > 0.0){
				this->vy -= this->speed * turnHandle;
			}
			else{
				this->vy -= this->speed;
			}
			
			this->vy = (this->vy < -this->maxSpeed) ? -this->maxSpeed : this->vy;
		}
		if(movingDown_){
			if(this->vy < 0.0){
				this->vy += this->speed * turnHandle;
			}
			else{
				this->vy += this->speed;
			}
			this->vy = (this->vy > this->maxSpeed) ? this->maxSpeed : this->vy;
		}
	}
	else{
		slowVy();
	}
}


void DynamicEntity::slowVx(){
	const int vsign = Math::sign(this->vx);
	this->vx -= 100 * vsign;
	if (Math::sign(this->vx) != vsign) {
        this->vx = 0.0001 * vsign;
	}
}

void DynamicEntity::slowVy(){
	const int vsign = Math::sign(this->vy);
	this->vy -= 100 * vsign;
	if (Math::sign(this->vy) != vsign) {
        this->vy = 0.0001 * vsign;
	}
}

SDL_RendererFlip DynamicEntity::getFlip(){
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if(!this->isRight){
		flip = SDL_FLIP_HORIZONTAL;
	}

	return flip;
}
