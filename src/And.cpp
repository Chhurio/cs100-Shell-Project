#include "And.hpp"

And::And(Executable* l, Executable* r){
	left = l;
	right = r;
}

bool And::execute(){
	if(left->execute()){
		if(right->execute()){
			return true;
		}
	}
	return false;
}
