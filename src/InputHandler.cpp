#include "InputHandler.h"
#include "Logger.h"

InputHandler::InputHandler() :
	quitFlag(false)
{
	this->keyStates.fill(false);
	this->mouseX = 0;
	this->mouseY = 0;
}

InputHandler::~InputHandler(){

}

void InputHandler::handleInput(){

	int pendingEvent = 0;

	do{

		pendingEvent = SDL_PollEvent(&this->sdlEvent); 

		if(this->sdlEvent.type == SDL_CONTROLLERBUTTONDOWN 
			|| this->sdlEvent.type == SDL_CONTROLLERBUTTONUP 
			|| this->sdlEvent.type == SDL_CONTROLLERAXISMOTION){
			
		}

		if(this->sdlEvent.type == SDL_MOUSEBUTTONDOWN){ 
		 	//If the left mouse button was pressed 
		 	if(this->sdlEvent.button.button == SDL_BUTTON_LEFT){ 
			 	//Get the mouse offsets 
			 	mouseX = this->sdlEvent.button.x; 
			 	mouseY = this->sdlEvent.button.y; 
			 	Log(DEBUG) << mouseX << "  " << mouseY;
		 	}
		}

		// On keydown.
		if(this->sdlEvent.type == SDL_KEYDOWN){

			switch(this->sdlEvent.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					if(this->sdlEvent.key.repeat == 0){
						this->keyStates[GameKeys::SPACE] = true;
					}	
					break;
				case SDLK_UP: // UP.
					this->keyStates[GameKeys::UP] = true;
					break;
				case SDLK_DOWN: // DOWN.
					this->keyStates[GameKeys::DOWN] = true;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = true;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = true;
					break;
				case SDLK_ESCAPE: // Esc.
					this->keyStates[GameKeys::ESCAPE] = true;
					break;
				default:
					break;
			}
		}

		// On keyup.
		else if(this->sdlEvent.type == SDL_KEYUP){
			
			switch(this->sdlEvent.key.keysym.sym){
				case SDLK_SPACE: // Jump.
					this->keyStates[GameKeys::SPACE] = false;
					break;
				case SDLK_UP: // UP.
					this->keyStates[GameKeys::UP] = false;
					break;
				case SDLK_DOWN: // DOWN.
					this->keyStates[GameKeys::DOWN] = false;
					break;
				case SDLK_LEFT: // Move left.
					this->keyStates[GameKeys::LEFT] = false;
					break;
				case SDLK_RIGHT: // Move right.
					this->keyStates[GameKeys::RIGHT] = false;
					break;
				case SDLK_ESCAPE: // Esc.
					this->keyStates[GameKeys::ESCAPE] = false;
					break;
				default:
					break;
			}
		}
		
		//On window exit (X).
		else if(this->sdlEvent.type == SDL_QUIT){
	    	signalExit();
	    }

	} while(pendingEvent != 0);
}

std::array<bool, GameKeys::MAX> InputHandler::getKeyStates(){
	return this->keyStates;
}

bool InputHandler::isQuitFlag(){
	return this->quitFlag;
}

void InputHandler::signalExit(){
	this->quitFlag = true;
}

void InputHandler::clearKey(const GameKeys key_){
	this->keyStates.at(key_) = false;
}
