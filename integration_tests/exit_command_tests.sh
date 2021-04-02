#!/bin/sh 

#one exit 
input="exit" 
echo "One exit test: "

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



#&& exit 
input="ls && exit" 
echo "exit && test: "

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

# ||  exit 
input="ls || exit; exit" 
echo "exit || test: "

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
