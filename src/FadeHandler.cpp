#include "FadeHandler.h"
#include "Logger.h"

FadeHandler::FadeHandler(Sprite* const sprite_) :
	shouldFadeIn(false),
	shouldFadeOut(false),
	percentageOfStop(0.0),
	sprite(sprite_),
	time(0.0),
	currentPercentage(0.0),
	rate(0.0)
{
	this->currentPercentage = (this->sprite->getAlpha()/255.0);
}

FadeHandler::~FadeHandler() {
	this->sprite = nullptr;
}

void FadeHandler::fadeIn(const double percentage_, const double time_){
	this->shouldFadeIn = true;
	this->shouldFadeOut = false;
	this->percentageOfStop = percentage_;
	this->currentPercentage = (this->sprite->getAlpha()/255.0);
	this->rate = (this->percentageOfStop - this->currentPercentage)/time_;
}

void FadeHandler::fadeOut(const double percentage_, const double time_){
	this->shouldFadeOut = true;
	this->shouldFadeIn = false;
	this->percentageOfStop = percentage_;
	this->currentPercentage = (this->sprite->getAlpha()/255.0);
	this->rate = (this->currentPercentage - this->percentageOfStop)/time_;
}

void FadeHandler::update(const double dt_){
	if(this->sprite == nullptr){
		Log(WARN) << "No sprite set to Fade Handler.";
		return;
	}

	if(shouldFadeIn){
		if(this->currentPercentage < this->percentageOfStop){
			this->currentPercentage += this->rate * dt_/1000.0;
			this->sprite->setAlpha(255.0 * this->currentPercentage);
		}
		else{
			shouldFadeIn = false;
			this->currentPercentage = this->percentageOfStop;
			this->sprite->setAlpha(255.0 * this->currentPercentage);
		}
	}
	else if(shouldFadeOut){
		if(this->currentPercentage > this->percentageOfStop){
			this->currentPercentage -= this->rate * dt_/1000.0;
			this->sprite->setAlpha(255.0 * this->currentPercentage);
		}
		else{
			shouldFadeOut = false;
			this->currentPercentage = this->percentageOfStop;
			this->sprite->setAlpha(255.0 * this->currentPercentage);
		}
	}

}

double FadeHandler::getCurrentPercentage(){
	return this->currentPercentage;
}
