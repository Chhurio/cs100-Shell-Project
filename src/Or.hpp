#ifndef __OR_HPP__
#define __OR_HPP__

#include "Executable.hpp"
class Or: public Executable{
	private:
		Executable* left;
		Executable* right;
	public:
		//Constructor
		Or(Executable* l, Executable* r);

		virtual bool execute();
};

#endif
