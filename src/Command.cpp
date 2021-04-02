#include "Command.hpp"
Command::Command(vector<string> c){
	this->c = c;	
}

bool Command::hasPipes(){
	for(int i = 0; i < c.size(); ++i){
		if(c.at(i) == "|"){
			return true;
		}
	}
	return false;
}

vector<vector<string> > Command::makePipeVector(){
	int begin = 0;
	int numCommand = -1;
	vector<vector<string> > p;
	vector<string> temp;

	for(int i = 0; i < c.size(); i++){
		if(c.at(i) == "|" || i == c.size() - 1){
			if(i == c.size() - 1){
				temp.push_back(c.at(i));
			}
			p.push_back(temp);
			temp.clear();
				
		}
		else{
			temp.push_back(c.at(i));
		}
	}
	return p;
}

bool Command::execute(){
	if(hasPipes()){
		vector<vector<string> > p = makePipeVector();
		int numCommands = 0;
		for(int i = 0; i < c.size(); i++){
			if(c.at(i) == "|"){
				numCommands++;
			}
		}
		numCommands++;
		return createPipe(numCommands, p);
	}
	else{
		return execute(this->c);
	}
}


bool Command::pipeExecute(vector<string> p){
	bool has_in = false;
	bool has_out = false;
	bool has_outAppend = false;
	
	vector<char*> charVector;
	for(int i = 0; i < p.size(); ++i){
		if(p.at(i) == "<"){
			has_in = true;
			i++;
		}
		else if(p.at(i) == ">"){
			has_out = true;
			i++;
		}
		else if(p.at(i) == ">>"){
			has_outAppend = true;
			i++;
		}
		else{
			charVector.push_back((char*)p.at(i).c_str());
		}
	}
	
	//converting the vector in to a char* array
	char* args[charVector.size() + 1];
	for(int i = 0; i < charVector.size(); ++i){
		args[i] = charVector.at(i);
	}

	//setting the end of the argumants array to NULL
	args[charVector.size()] = 0;
	
	
	if(has_in){
		int i;
		char* filename;
		for(i = 0; i < p.size(); i++){
			if(p.at(i) == "<"){
				i++;
				break;
			}
		}
		filename = (char*) p.at(i).c_str();
		int fd = open(filename, O_RDWR);
		
		close(0);
		dup(fd);		
	}
	if(has_out){
		int i;
		char* filename;
		for(i = 0; i < p.size(); i++){
			if(p.at(i) == ">"){
				i++;
				break;
			}
		}
		filename = (char*) p.at(i).c_str();
		int fd = open(filename, O_RDWR | O_TRUNC | O_CREAT);
		
		close(1);
		dup(fd);	
		close(fd);	
	}
	else if(has_outAppend){
		int i;
		char* filename;
		for(i = 0; i < p.size(); i++){
			if(p.at(i) == ">>"){
				i++;
				break;
			}
		}
		filename = (char*) p.at(i).c_str();
		int fd = open(filename, O_RDWR | O_APPEND | O_CREAT);
		
		close(1);
		dup(fd);		
		close(fd);
	}
	
	
	return !(execvp(args[0], args) == -1);
}

bool Command::forkPipe(int in, int out, vector<string> p){
	pid_t pid;

	if((pid = fork()) == 0){
		if(in != 0){
			dup2(in, 0);
			close(in);
		}
		if(out != 1){
			dup2(out, 1);
			close(out);
		}
		return pipeExecute(p);
	}
	return true;
}

bool Command::createPipe(int numCommands, vector<vector<string> > pp){
	int i;
	pid_t pid;
	int in;
	int fd[2];
	int status = 1;	
	//stores standard in and out
	int stdout = dup(1);
	int stdin = dup(0);	

	in = 0;
	
	for(i = 0; i < numCommands - 1; i++){
		pipe(fd);

		if(!forkPipe(in, fd[1], pp.at(i))){
			
		
			perror("exec");
			exit(0);
		}
		
		
		close(fd [1]);
		
		in = fd[0];
	}

	if(in != 0){
		dup2(in, 0);
		close(in);
	}
		
		
	pid = fork();
	if(pid == 0){
		if(!pipeExecute(pp.at(i))){
				
			perror("exec");
			
			exit(-1);
			
		}
	}
	if(pid > 0){
		if(waitpid(pid, &status, 0) == -1){
			perror("wait");
		}
	}

	//restores standard in and out
		
	dup2(stdin, 0);
	dup2(stdout, 1);
		
	if(status == 0){
		return true;
	}
	return false;
}

bool Command::execute(vector<string> com){
	//for some reason we have to have a vector<string> member variable and then convert it into a char* for it to work
	//we cannot just have a char* vector apparently or we get some very wierd pointer error
	if(com.size() == 0){
		return false;
	}
	bool has_in = false;
	bool has_out = false;
	bool has_outAppend = false;
	//stores standard in and out
	int stdout = dup(1);
	int stdin = dup(0);
	int status = 1;
	vector<char*> charVector;
	for(int i = 0; i < com.size(); ++i){
		if(com.at(i) == "<"){
			has_in = true;
			i++;
		}
		else if(com.at(i) == ">"){
			has_out = true;
			i++;
		}
		else if(com.at(i) == ">>"){
			has_outAppend = true;
			i++;
		}
		else{
			charVector.push_back((char*)com.at(i).c_str());
		}
	}
	//create a boolean to check if the command executes without failure

	string firstCommand(charVector.at(0));
	string lastInput(com.at(charVector.size() -1)); 
	//converting the vector in to a char* array
	char* args[charVector.size() + 1];
	for(int i = 0; i < charVector.size(); ++i){
		args[i] = charVector.at(i);
	}

	//setting the end of the argumants array to NULL
	args[charVector.size()] = 0;
	

	//checking to see if exit was called
	string Exit = "exit";

	
	
	if(Exit  == firstCommand){
		exit(0);
	}
	
	if(has_in){
		int i;
		char* filename;
		for(i = 0; i < com.size(); i++){
			if(com.at(i) == "<"){
				i++;
				break;
			}
		}
		filename = (char*) com.at(i).c_str();
		int fd = open(filename, O_RDWR);
		
		close(0);
		dup(fd);		
	}
	if(has_out){
		int i;
		char* filename;
		for(i = 0; i < com.size(); i++){
			if(com.at(i) == ">"){
				i++;
				break;
			}
		}
		filename = (char*) com.at(i).c_str();
		int fd = open(filename, O_RDWR | O_TRUNC | O_CREAT, 00007);
		
		close(1);
		dup(fd);		
	}
	else if(has_outAppend){
		int i;
		char* filename;
		for(i = 0; i < com.size(); i++){
			if(com.at(i) == ">>"){
				i++;
				break;
			}
		}
		filename = (char*) com.at(i).c_str();
		int fd = open(filename, O_RDWR | O_APPEND | O_CREAT);
		
		close(1);
		dup(fd);		
	}

	//checking if the command is a test	
	
	if("test" == firstCommand || "[" == firstCommand && "]" == lastInput ){
		string firstTestInput(args[1]);
		struct stat buf;
		
		if(firstTestInput == "-e"){
			
			if(stat(args[2], &buf) == 0){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}			
		}
		else if(firstTestInput == "-d"){
			
			stat(args[2], &buf);
			if(S_ISDIR(buf.st_mode)){
				cout << "(True)" << endl;
				return true;
			}
				else{
				cout << "(False)" << endl;
				return false;
			}
		}
		else if(firstTestInput == "-f"){
			
			stat(args[2], &buf);
			if(S_ISREG(buf.st_mode)){
				cout << "(True)" << endl;
				return true;
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		}
		else{
			if(stat(args[1], &buf) == 0){
				cout << "(True)" << endl;
				return true;	
			}
			else{
				cout << "(False)" << endl;
				return false;
			}
		}
	}
	
	
	//executes functions using execvp
	pid_t pid = fork();
	if(pid == -1){
		perror("fork");
		exit(1);
	}
	if(pid == 0){
			
		if(execvp(args[0], args) == -1){
			perror("exec");
			exit(-1);
		}
	}
	if(pid > 0){
		waitpid(pid, &status, 0);
		/*
		if(wait(0) == -1){
			perror("wait");
		}*/
	}
	
	if(has_in){
		close(0);
		dup(stdin);
	}
	if(has_out || has_outAppend){
		close(1);
		dup(stdout);
	}
	
        if(status == 0){
		return true;
	}	      
	return false;
			
}

