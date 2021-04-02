#ifndef __SEMICOLON_HPP__
#define __SEMICOLON_HPP__

#include "Executable.hpp"
class Semicolon: public Executable{
	private:
		Executable* left;
		Executable* right;
	public:
		//Constructor
		Semicolon(Executable* l, Executable* r);

		virtual bool execute();
};

#endif
