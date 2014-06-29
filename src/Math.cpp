#include "Math.h"

int Math::sign(const int number_){
	if (number_ > 0) { 
    	return 1;
    }
    else if (number_ < 0) {
    	return -1;
    }
    else {
    	return 0;
    }
}

int Math::sign(const double number_){
	if (number_ > 0.0) { 
    	return 1;
    }
    else if (number_ < 0.0) {
    	return -1;
    }
    else {
    	return 0;
    }
}
