#ifndef __EXECUTABLE_HPP__
#define __EXECUTABLE_HPP__

#include<iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <vector>
#include <cstdlib>
class Executable{
	public:
		//Constructor
		Executable(){}

		virtual bool execute() = 0;
};

#endif
