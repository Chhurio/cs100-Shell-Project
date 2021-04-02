//things to fix for next time: quotes, exit function behaving bizarrely sometimes, and google unit test behaving wierdly
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include "Command.hpp"
#include "Command.cpp"
#include "Or.hpp"
#include "Or.cpp"
#include "And.hpp"
#include "And.cpp"
#include "Semicolon.hpp"
#include "Semicolon.cpp"
#include <cstring>
#include <string.h>
using namespace std;


Executable* breakupCommand(string str){
	vector<string> c;
	string strProcessed = str;
	bool firstQuoteSet = false;
	string theFirstStringInQuotes = "";
	unsigned indexOfFirstQuote = 0;
	unsigned indexOfSecondQuote = 0;
	
	//checks if there are any comments in the input and removes them

	
	
	//checks if there are quotes in the input and if there are, the index of the first and second occurance of the character '"' is taken
	for(unsigned i = 0; i < strProcessed.size(); i++){
		if(strProcessed[i] == '"' && !firstQuoteSet){
			firstQuoteSet = true;
			indexOfFirstQuote = i;
		}
		else if(strProcessed[i] == '"' && firstQuoteSet){
			indexOfSecondQuote = i;
		}			
	}
	if(indexOfFirstQuote != 0 && indexOfSecondQuote != 0){
		//im just assuming that theres only one set of quotes in a given command and that it is always the last argument for a command	
		theFirstStringInQuotes = strProcessed.substr(indexOfFirstQuote + 1, indexOfSecondQuote - indexOfFirstQuote-1);
		strProcessed = strProcessed.substr(0, indexOfFirstQuote);
	}
	
	//creates an array of characters that has the same values as strProcessed because strtok only takes in an array of chars terminated by a null char	
	int stringlength = strProcessed.length();
	char array[strProcessed.length()+1];
	strcpy(array, strProcessed.c_str());
	array[stringlength] = 0;	

	//after the array is made, breaks up the string every time there is a spacce and puts it into vector c, for example if str is "echo hello", c.at(0) = "echo" and c.at(1) = "hello"
	char* ptr = strtok(array, " ");
	
	while(ptr != NULL){
		//converts the char pointer to a string before adding it to the vector
		string x(ptr);
		c.push_back(x);
		ptr = strtok(NULL, " ");
	}
	
	//if theFirstStringInQuotes is not empty, then there was a quote in this output, so we add it back
	if(theFirstStringInQuotes != ""){
		c.push_back(theFirstStringInQuotes);
	}
	
	return new Command(c);
	
}

//helper function for Get_List_Commands to figure out if the current index is in a set of quotes
bool inQuotes(string str, int index){
	int quotes = 0;
	for(int i = 0; i < index; i++){
		if(str[i] == '"'){
			quotes++;
		}
	}

	//if there is an odd number of quotes behind the index, it will be in quotes if there is a quote after index
	if(quotes % 2 == 0){
		return false;
	}
	
	for(int i = index + 1; i < str.size(); ++i){
		if(str[i] == '"'){
			return true;
		}
	}
	return false;
	
	
}
//if there is a '#' in the input string, returns the string up until that point, else return the input string
string removeComments(string str){
	for(unsigned i = 0; i < str.size(); i++){
		if(str.at(i) == '#'){
			return str.substr(0, i);
		}
	}
	return str;
}

//checks if there are any connectors in the string input, if there are connectors in a set of quotes, ignores them
bool no_connectors(string str){
	for(int i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str.at(i) == ';' && str.at(i+1)== ' '){
				return false;
			}
			if(str.at(i) == '|' && str.at(i+1) == '|'){
				return false;
			}
			if(str.at(i) == '&' && str.at(i+1) == '&'){
				return false;
			}

		}
	}
	return true;
}

//returns the index of the next connector from the given index in the string,
//also ignores any connectors inside quotes
//if there are none, then return str.size()
int getIndexOfNextConnector(string str, int index) {
	//If index never found, return str.size()
	int indexOfNC; 

	//Give this index, find the next connector
	for (indexOfNC = index; indexOfNC < str.size(); indexOfNC++) {
		if (!inQuotes(str, indexOfNC)) { 

			if (str.at(indexOfNC) == ';') {
				return indexOfNC; 	
			}
			else if (str.at(indexOfNC) == '|' && str.at(indexOfNC + 1) == '|') {
				return indexOfNC;	 
			}
			else if (str.at(indexOfNC) == '&' && str.at(indexOfNC + 1) == '&') {
				return indexOfNC; 
			}
		 }
	}

	return indexOfNC; 
}


//given the index of a '(' character, finds its corresponidng ')' character
//takes nested parentheses into account Ex: if the string is "((input))" and index is 0
//it will return str.size() - 1 instead of str.size() - 2
//also ignores any parentheses in quotes
int getIndexOfMatchingParenthesis(string str, int index) {
	int numLeftP = 0;
	int numRightP = 0; 

	int i;
	for (i = index; i < str.size(); i++) { 
		//returns if same number of  left and right parentheses
		if(!inQuotes(str, i)){
			if (str.at(i) == '(') {
				numLeftP++;
			}

			if (str.at(i) == ')') {
				numRightP++;
			
				if (numLeftP == numRightP) {
					return i;
				}		
			}
		}	
	}
	//if no closing thing
	return i; 
}

//checks for the exitence of parentheses in the string
//it will return true if there are a set of parentheses in the string
//it will return false if there are no parentheses or there is a single parentheses without its corresponding parentheses
//this function also ignores any parentheses in quotes
bool hasParentheses(string str){
	int numLeftP = 0;
	int numRightP = 0;
	for(int i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str.at(i) == '('){
				numLeftP++;
			}
			else if(str.at(i) == ')'){
				numRightP++;
			}
		}
	}

	return (numLeftP != 0 && numRightP != 0) && numLeftP == numRightP;
}
//makes sure that the input give to the createtree function always has an even number of parentheses
//this function also ignores parentheses in quotes
bool evenNumberOfParentheses(string str){
	int numLeftP = 0;
	int numRightP = 0;
	for(int i = 0; i < str.size(); i++){
		if(!inQuotes(str, i)){
			if(str.at(i) == '('){
				numLeftP++;
			}
			else if(str.at(i) == ')'){
				numRightP++;
			}
		}
	}	
	return (numLeftP == numRightP) && ((numLeftP + numRightP) % 2  == 0);
}

//recursive function to create an expression tree given input str
Executable* createtree(string str){
	//checks if the input is just a basic command
	//i.e there are no connectors or parentheses
	if(no_connectors(str) && !hasParentheses(str)){
		return breakupCommand(str);
	}
	//connector keeps track of the next connector to add to root
	string connector = "";
	//root keeps track of what we currently have built with our tree
	Executable* root = 0;
	//temp helps create the tree by holding the next node to be added to the tree
	Executable* temp = 0;
	//begin holds the starting index of the command we are trying to parse
	int begin = 0;
	// i holds the ending index of the command we are trying to parse
	int i = 0;
	
	//if there are parentheses, creates an exectuable of whatever is inside of the parentheses and
	//sets the variable index i to whatever the next connector is or if there is no next connector
	//sets i to str.size() and returns root
	if(str.at(i) == '('){
		i = getIndexOfMatchingParenthesis(str, i);
		root = createtree(str.substr(begin+1, i - (begin +1)));
		while(i != str.size() && (str.at(i) == ')' || str.at(i) == ' ')){
			i++;
		}
		if(i == str.size()){
			return root;
		}
	}
	//if there are no parentheses takes the input until the index right before the next connector
	//and makes an executable out of it
	else{
		i = getIndexOfNextConnector(str, i);
		root = createtree(str.substr(begin, i));
	}

	
	//this while loop constructs the rest of the tree if the tree is not a single node
	while(i != str.size()){
		//checks sets connector to whatever the connector at index i is
		if(str.at(i) == '&' && str.at(i+1) == '&'){
			connector = "&&";
		}
		else if(str.at(i) == '|' && str.at(i+1) == '|'){
			connector = "||";
		}
		else if(str.at(i) == ';' && str.at(i+1) == ' '){
			connector = "; ";
		}
		//increments i to the starting index of the command to the right of the connector
		while(str.at(i) == '|' || str.at(i) == '&' || str.at(i) == ';' || str.at(i) == ' '){
			i++;
		}
		//sets begin to i
		begin = i;
		
		//if the right command is inside parentheses,
		//constructs a tree for that right command and sets it to temp
		//depending on the value of the connector string, root will become a new connector class and 
		//with its former value as the left command and temp's value as the right command
		if(str.at(i) == '('){
			//i gets set to the matching right facing parentheses ')' for
			//the index of whatever left facing parentheses '(' it is cuurently at
			i = getIndexOfMatchingParenthesis(str, i);
			temp = createtree(str.substr(begin+1, i - (begin+1)));
			if(connector == "&&"){
				root = new And(root, temp);
			}
			else if(connector == "||"){
				root = new Or(root, temp);
			}
			else if(connector == "; "){
				root = new Semicolon(root, temp);
			}
			//i gets set to the index of the next connector or the end of the string
			while(i != str.size() && (str.at(i) == ')' || str.at(i) == ' ')){
				i++;
			}
			//returns root if there is no more to parse
			if(i == str.size()){
				return root;
			}
		}
		//if the right command is not within parentheses
		//constructs a tree with a single command(i.e just the root node)
		//and adds it to the root using the same method as above
		else{
			//i gets set to the index of the next connector or the end of the string
			i = getIndexOfNextConnector(str,i);
			temp = createtree(str.substr(begin, i));
			if(connector == "&&"){
				root = new And(root, temp);
			}
			else if(connector == "||"){
				root = new Or(root, temp);
			}
			else if(connector == "; "){
				root = new Semicolon(root, temp);
			}
			//returns root if there is no more to parse
			if(i == str.size()){
				return root;
			}
		}
		
	}
	return root;
}

//processes the string to remove comments and makes sure there are an even
//number of parentheses before calling the recursive createtree fuction
//returns null if the string is empty
//prints out an error message and returns null if the string has an uneven number of parentheses
Executable* createTree(string str){
	string str1 = removeComments(str);
	if(evenNumberOfParentheses(str1) && str1 != ""){
		return createtree(str1);
	}	
	else if(str1 ==  ""){
		return 0;
	}
	else{
		cout << "Error: Check the number of Parentheses" << endl;
		return 0;
	}

}

int main(){
	while(1){
		
		cout << "$ ";	

		string input;
	
		getline(cin, input);


		Executable* x = createTree(input);
		if(x != 0){
			x->execute();
		}
		

	}
	
	return 0; 
}  

