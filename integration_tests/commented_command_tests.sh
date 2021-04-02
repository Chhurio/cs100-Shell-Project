#!/bin/sh

#ls and other stuff
input="ls; exit #adfaaasdfasffafasfasfasdfafasfaf" 
echo "ls test: "

output=$(echo "$input" | ./../rshell)
#input2="exit"
#output+=$(echo "$input2" | ./../rshell) #does this work?
var="$ "
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo 

#single &&  test
input="ls && echo hello; exit #this is a comment"  
echo "Single && test: "

output=$(echo "$input" | ./../rshell)

var="$ "
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 
echo



#single || test
input="ls && echo hello; exit #this is a comment"  
echo "Single || test: "

output=$(echo "$input" | ./../rshell)

var="$ "
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo 

 
#different connectors  test
input="ls -a; echo hello && pwd  || echo world; git status; exit #comment ls"  
echo "Different connectors  test: "

output=$(echo "$input" | ./../rshell)

var="$ "
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else
	echo "Test failed" 
fi 
