# CS 100 Programming Project
- Fall Quarter 2019 
- Alfredo Gonzalez 862114871 
- Tommy Chhur 862071238

# Introduction 
This program is a command shell written in C++ for CS100. It prints out a command prompt and  parses user input in order to feed it into a composite class structure that will execute the
commands given to it. This composite structure will use left to right ordering as well as taking connectors such as &&, ||, and ; into account when deciding which order to execute the 
commands. The commands will be executed using fork, execvp, and waitpid. The parser will take in user input and contruct the corresponding tree for the set of commands and connectors
inputted.

# Diagram 
![alt text](https://github.com/cs100/assignment-demon_slayers/blob/master/images/newOMT.PNG "OMT Diagram")

# Classes 
Executable Class - Acts at the base class in the composite pattern, it has a virtual function called execute(), which will be inherited and implemented by its children

Command Class - This class inherits from the base Executable class and is considered a leaf in the composite pattern. It represents a single command in the system(i.e without connectors) and takes in a vector a strings the represents a single command or multiple commands connected through pipes. Calling the execute() function on this object should convert the vector of type <string> into a vector of type <char*> and execute the command contained within the vector or if there are pipes, it creates a vector of string vectors that is then used to create the vectors of <char*> needed for execvp. The execute() function will return true if the command executed without any errors. 

Or Class - This class inherits from the Executable class and is considered a composite element in the composite pattern. It has two pointers to executable objects denoted left and right.
Calling the execute() function on this object will call the execute() function on the left executable object first. If the command on the left executable object fails, then the execute()
function will be called on the right executable object. The execute() function will return true if either the left or right command execute successfully.

And Class- This class inherits from the Executable class and is cosidered a composite element in the composite pattern. It has two pointers to executable objects denoted left and right.
Calling the execute() function on this object will call the execute() function on the left executable object first. If the command on the left executable object succeeds, the the execute()
funtion will be called on the right executable obejct. The execute() function will return true if both commands execute sucessfully.

Semicolon Class - This class inherits from the the Executable class and is considered a composite element in the composite pattern. It has two pointers to executable object denoted left
and right. Calling the execute() function on this object will call the execute() function on the left executable object first followed by an execute() call to the right object regardless
of whether the command in the left executable fails or succeeds. The execute() function will return true if the right command executes sucessfully.

# Prototypes/Research 
In our prototype function, it tests out waitpid(), execvp() and fork(), as well as a test for parsing user input. 

For the Parser - We used the strtok() function from the C standard library to parse in input. It works as intended, however the only token that it currently parses are spaces. However, it can be updated to include different types of tokens, eg. "&&". For the rest of our assignment, after the user’s input is parsed, we will call our classes in order to actually execute the commands.   

waitpid(), execvp() and fork() - The function we wrote calls all three functions at once, working with just the “ls” command as of now. Testing with the ls command of the terminal, we get teh exact same result, listing the correct contents of the current directory. We plan to use it in the assignment to handle the execution of different commands, in addition to ls. 


# Development and Testing Roadmap 
- [Add Executable Class](https://github.com/cs100/assignment-demon_slayers/issues/3)			FINISHED
- [Add Executable Class Unit Tests](https://github.com/cs100/assignment-demon_slayers/issues/4) 	FINISHED	
- [Develop Parser](https://github.com/cs100/assignment-demon_slayers/issues/14)				FINISHED
- [Add Command Class](https://github.com/cs100/assignment-demon_slayers/issues/5) 			FINISHED
- [Add Command Class Unit Tests](https://github.com/cs100/assignment-demon_slayers/issues/6) 		FINISHED
- [Add Or Class](https://github.com/cs100/assignment-demon_slayers/issues/7) 				FINISHED
- [Add Or Class Unit Tests](https://github.com/cs100/assignment-demon_slayers/issues/8) 		FINISHED
- [Add And Class](https://github.com/cs100/assignment-demon_slayers/issues/9) 				FINISHED
- [Add And Class Unit Tests](https://github.com/cs100/assignment-demon_slayers/issues/10) 		FINISHED
- [Add Semicolon Class](https://github.com/cs100/assignment-demon_slayers/issues/11) 			FINISHED
- [Add Semicolon Class Unit Tests](https://github.com/cs100/assignment-demon_slayers/issues/12) 	FINISHED
- [Add Integration Tests between Classes](https://github.com/cs100/assignment-demon_slayers/issues/13) 	FINISHED
- [Add Test of entire system with user input](https://github.com/cs100/assignment-demon_slayers/issues/15) FINISHED
