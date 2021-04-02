#include "Semicolon.hpp"

Semicolon::Semicolon(Executable* l, Executable* r){
	left = l;
	right = r;
}

bool Semicolon::execute(){
	left->execute();
	if(right->execute()){
		return true;
	}
	return false;
}
