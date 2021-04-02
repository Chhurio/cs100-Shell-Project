#!/bin/sh 

#Needs  ;exit after or crashes?

input="ls; exit" #without exit

#ls 
echo "ls test: "
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

#pwd
input="pwd; exit" 
echo "pwd test: "

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

#clear
input="clear; exit" 
echo "clear test: "

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

#invalid command
input="asdfasfsafsf; exit" 
echo "invalid command test: "

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

#empty command
input="; exit" 
echo "empty command test: "

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


