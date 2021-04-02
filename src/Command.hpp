
#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__
#pragma once 


#include "Executable.hpp"
#include <string.h>
#include <cstdlib>
using namespace std;

class Command : public Executable{
	private:
		//helper function to determine whether the command has pipes
		bool hasPipes();
			
		//Creates a vector of vector<string> if there pipes are present in the command
		vector<vector<string> > makePipeVector();
			
		//Similar to execute(vector<string> c), but does not fork on its own and does not check for exit or test
		bool pipeExecute(vector<string> com);
		
		//helper function for createPipe()
		//sets up the fork and pipe and then call the helper function pipeExecute() to execute the command
		bool forkPipe(int in, int out, vector<string> p);

		//helper function for execute(), is called if there is piping in the command
		bool createPipe(int numCommands, vector<vector<string> > pp);

		//helper function for execute(), is called if there is no piping in the command
		bool execute(vector<string> c);

		//stores the command(s) and their arguments
		vector<string> c;
	
	public:
		Command(vector<string> c);

		bool execute();
			
};

#endif
