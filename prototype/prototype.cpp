#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stdio.h>
#include <string.h>
#include <wait.h>

#include <vector> 

#include <string> 
#include <cstring> 

using namespace std; 

//Works for just ls 
//Could extend
void forkExecWaitTest() {
	char* args[3];

	//string ls = "ls"; 
	//args[0] = (char*)ls.c_str();	//( ) casting it to char pointer  
	
	//Testing with "pwd" 
	//=> IT WORKS!!!
	//string pwd = "pwd"; 
	//args[0] = (char*)pwd.c_str();
	
	cout << "$ "; 
	string userInput;
	getline(cin, userInput); 

	args[0] = (char*)userInput.c_str();
	args[1] = NULL;
		
	pid_t pid = fork();
	int status;		//need this for waitpid, but unsure of what it does  

	if (pid == 0) {
		//child 
		cout << "child " << pid << endl; 
		if ( execvp (args[0], args) == -1) { //Returns -1 if error happens 
			perror ("exec"); 
		}
	}

	if (pid > 0) {
		//parent 
		while (waitpid(pid, &status, WNOHANG) == 0) {	 
			sleep(1); 
		} 
		cout << "parent: " << pid << endl;
	}	
	return;
}

//TESTING WITHOUT OTHER FUNCTIONS INTO ACCOUNT
//Uses strtok, 
//Parses string give user input  
//Only token right now is spaces, but could add additional funcitonality for dif tokens
//Need to make vector of commands and connectors?
void testParser() { 
	vector <string> cmd;	//vector of the commands	
	vector <string> conn;	//vector of connectors

	//
	string str; 
	cout << "$ "; 
	
	//Gets input from user 
	getline(cin, str); 
	char* cstr = new char [str.length() + 1]; //stores cmds
	char* cstr2 = new char [str.length() + 1]; //stores connectors 

	strcpy (cstr, str.c_str()); //cstr copies a c-string copy of str
	strcpy (cstr2, str.c_str()); //Strcpy for connectors  	
	

	//FOR COMMANDS 
	char* token = strtok(cstr, "  &&  || ; ");//accounts for all cases  	
 	//While hasn't reached a null value 	
	while (token != NULL) { 
		cmd.push_back(token); 
	 	token = strtok(NULL, "  &&  || ; ");	//changed to "   &&  " 	
	}
							//(Two spaces in front) 
	delete[] cstr;
	//prints array  
	cout << "list of commands: ";
	for (int i = 0; i < cmd.size(); i++) {
		cout << cmd.at(i) << endl;
	}

	cout << endl;


	//FOR CONNECTORS
	//Ugly to be honest, but it works  	
	char* conToken = strtok(cstr2, "qwertyuiop[]{}asdfghjkkl'zxcvbnm,./1234567890-=!@$%^*_+:?><\\ ()");//accounts for all cases  	
 	//While hasn't reached a null value 	
	while (conToken != NULL) { 
		conn.push_back(conToken); 
	 	conToken = strtok(NULL, "qwertyuiop[]{}asdfghjkkl'zxcvbnm,./1234567890-=!@$%^*_+:?><\\ ()"); 
	}
					 
	delete[] cstr2;
	//prints array: Just for testing  
	cout << "list of connectors: ";
	for (int i = 0; i < conn.size(); i++) {
		cout << conn.at(i) << endl;
	}
	
	return;
} 

int main () {
	int select = 0;

	cout << "Select 1 to test Parser, 2 to see test fork excevp, and waitpid: ";
	cin >> select;

	cin.ignore();	//do this for the getline in fork2 

	if (select == 1) { 	
		testParser();
	}
	if (select == 2) {
		forkExecWaitTest();
	}

	return 0; 
}
