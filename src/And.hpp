#ifndef __AND_HPP__
#define __AND_HPP__

#include "Executable.hpp"
class And: public Executable{
	private:
		Executable* left;
		Executable* right;
	public:
		//Constructor
		And(Executable* l, Executable* r);

		virtual bool execute();
};

#endif
