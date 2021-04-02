//SOME TESTS ARE COMMENTED OUT BECAUSE WHENEVER WE TRY TO TEST GIBBERISH OR EMPTY COMMANDS IT SEEMS TO DOUBLE THE AMOUNT OF TESTS BEING DONE
#ifndef __TESTS__HPP__
#define __TESTS_HPP__

#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <stdlib.h>

#include "../src/And.hpp"
#include "../src/And.cpp"	

#include "../src/Semicolon.hpp"
#include "../src/Semicolon.cpp"

#include "../src/Or.hpp"
#include "../src/Or.cpp"


#include "../src/Command.hpp"
#include "../src/Command.cpp"


//Tommy changed it so that, it starts with vector<string> instead of vector<char*>
//not needed to to convert here  
using namespace std; 

//Command tests
TEST(CommandTest, initalComTest) {
	vector<string> c;  
	string ls = "ls"; 
	c.push_back(ls); 

	Executable* x = new Command(c);
	EXPECT_EQ(x->execute(), 1); //returns 1 	
}

TEST(CommandTest, invalidComTest) {
	vector<string> c;  
	string ls = "bacon"; 

	c.push_back(ls);

	Executable* x = new Command(c);
	EXPECT_EQ(x->execute(), 0); //should returns 0? returns 1 instead 	
}


//And tests
TEST(AndTest, initalTest) {
	vector<string> c; 
	vector<string> d; 
	string ls = "ls";
	string ls2 = "ls"; 
	
	c.push_back(ls); 
	d.push_back(ls2);
	
	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 1); //Expect true	

}


//Is 1 for some reason?
TEST(AndTest, invalidLeftCommand) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "yeet";
	string ls2 = "ls"; 

	c.push_back(st1);
	d.push_back(ls2);
	
	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 0); 

}

//this is 1?
TEST(AndTest, emptyLeft) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back(st1);
	d.push_back(st2);

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 0); 	
}

TEST(AndTest, emptyRight) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back(st1);
	d.push_back(st2);
		

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 0); 	
}



//Returns opposite of whatever is expected?
TEST(AndTest, invalidRighttCommand) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "ls";
	string st2 = "demon"; 

	c.push_back(st1);
	d.push_back(st2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new And(x,y);

	EXPECT_EQ(test->execute(), 0); //Expect tru (had this as false before?	
}



//Semicolon tests
TEST(SCTest, initalSCTest) {
	vector<string> c; 
	vector<string> d; 
	string ls = "ls";
	string ls2 = "ls"; 

	c.push_back(ls);
	d.push_back(ls2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}


TEST(SCTest, jibberishCmds) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "cs";
	string st2 = "time"; 

	c.push_back(st1);
	d.push_back(st2);
	


	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 0); 	
}

TEST(SCTest, emptyLeft) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back(st1);
	d.push_back(st2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(SCTest, emptyRight) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back(st1);
	d.push_back(st2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Semicolon(x,y);

	EXPECT_EQ(test->execute(), 0); 	
}





//Or Tests
//ALl supposed to return 1? 
TEST(OrTest, initalOrTest) {
	vector<string> c; 
	vector<string> d; 
	string ls = "ls";
	string ls2 = "ls"; 

	c.push_back(ls);
	d.push_back(ls2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); //returns 1 	
}


TEST(OrTest, jibberishCmds) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "cs";
	string st2 = "time"; 

	c.push_back(st1);
	d.push_back(st2);
	

	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 0); // 1 again 	
}

TEST(OrTest, emptyLeft) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "";
	string st2 = "pwd"; 

	c.push_back(st1);
	d.push_back(st2);
	


	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); 	
}

TEST(OrTest, emptyRight) {
	vector<string> c; 
	vector<string> d; 
	string st1 = "pwd";
	string st2 = ""; 

	c.push_back(st1);
	d.push_back(st2);
	


	Executable* x = new Command(c);
	Executable* y = new Command(d); 
 
	Executable* test = new Or(x,y);

	EXPECT_EQ(test->execute(), 1); //1 onc again  	
}

//Test tests	unsure if this works 
TEST(TesCmdTest, initalTest) {
	vector<string> c; 
	string test = "test testFile.txt";

	c.push_back(test); 	

	Executable* x = new Command(c);	
	EXPECT_EQ(x->execute(), 0); 	
}

#endif 
