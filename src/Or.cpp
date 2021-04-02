#include "Or.hpp"

Or::Or(Executable* l, Executable* r){
	left = l;
	right = r;
}

bool Or::execute(){
	if(left->execute()){
		return true;
	}
	else if(right->execute()){
		return true;
	}
	return false;
}
