#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h> 
#include <string> 
#include <cstdlib> 

using namespace std; 


int main() {
	struct stat buf; 
	//char mtime[100];

	stat("yo.txt", &buf); 

	return 0;
}
