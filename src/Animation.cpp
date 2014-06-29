#include "Animation.h"

int animationCount = 0;

Animation::Animation(const int x_, const int y_, const int spriteWidth_,
	const int spriteHeight_, const int numberOfImages_, const bool loop_) :

	x(x_),
	y(y_),
	spriteWidth(spriteWidth_),
	spriteHeight(spriteHeight_),
	numberOfImages(numberOfImages_),
	loop(loop_),
	totalElapsedTime(0.0)
{

}

Animation::~Animation(){

}

void Animation::update(SDL_Rect& clip, const double dt_){

	const unsigned int ANIMATION_LIMIT = 10;

	// Compare the position on the sprite with the number of positions to know if is the
	// end of the animation.
	bool endOfAnimation = animationCount + 1 >= this->numberOfImages;

	const double deltaT = (this->totalTime / this->numberOfImages);

	// Check if the frame has changed.
    this->totalElapsedTime += dt_;

    if(this->totalElapsedTime >= deltaT) {
        
        this->totalElapsedTime = 0;
        animationCount += 1;

        if(Animation::animationCount <= this->numberOfImages){
	        if(this->x < (int)ANIMATION_LIMIT){
	        	this->x += 1;
	        }
	        else{
	        	this->y += 1;
	        	this->x = 0;
	        }
    	}

    	if(endOfAnimation){
    		this->x= this->initialX;
    		this->y= this->initialY;
    		Animation::animationCount = 0;
    	}
    }

   	const int positionX_ = this->x * this->spriteWidth;
	const int positionY_ = this->y * this->spriteHeight;
	updateClip(clip, positionX_, positionY_);
}

void Animation::changeAnimation(const int x_, const int y_, const int numberOfImages_,
	const bool loop_, const double totalTime_){

	this->x = x_;
	this->y = y_;
	this->initialX = x_;
	this->initialY = y_;
	this->numberOfImages = numberOfImages_;
	this->loop = loop_;
	this->totalTime = totalTime_;
	animationCount = 0;
}

void Animation::updateClip(SDL_Rect& clip, const int x_, const int y_){
	clip.x = x_;
	clip.y = y_;
	clip.w = this->spriteWidth;
	clip.h = this->spriteHeight;
}

int Animation::getCurrentFrame(){
	return animationCount + 1;
}
