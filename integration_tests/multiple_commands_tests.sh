#!/bin/sh 

#single ; test
input="ls; echo hello; exit"  
echo "Single ; test: "

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


#single &&  test
input="ls && echo hello; exit"  
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
input="ls && echo hello; exit"  
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
input="ls -a; echo hello && pwd  || echo world; git status; exit"  
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

echo 


#quotation mark test 
input="echo \" hello && goodbye\"; exit" 
echo "Quotation mark test: "

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






#no right op for && test
#input="ls && ; exit"  
#echo ";, no right Op test: "

#output=$(echo "$input" | ./../rshell)

#var="$ "
#var+=$(echo "$input" | sh) 

#if [ "$output" = "$var" ] 
#then 
#	echo "Test passed"
#else 
#	echo "Test failed" 
#fi 

#echo 
