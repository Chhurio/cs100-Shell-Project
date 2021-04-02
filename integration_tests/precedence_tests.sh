#!/bin/sh 


#One set of () 
input="(echo A && echo B) || ls; exit"  
echo "One set of () and || test: "

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


#Two sets of () (not nested) specss
input="(echo A && echo B) || (echo C && echo D); exit"  
echo "Two sets of () [not nested] and || test: "

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

#echo "$ouput"	#outputs Rshell output
#echo 
#echo "$var"	#outputs what shell outputs


#Nested parentheses  
input="((echo a && echo b) || echo c) && echo a; exit"

echo "Nested parantheses test: "

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



#Nested parentheses 2  
input="(echo a && (echo b && echo c)) && echo a; exit"

echo "Nested parantheses test 2: "

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

#echo "$ouput"	#outputs Rshell output
#echo 
#echo "$var"	#outputs what shell outputs

#three sets of parentheses 
input="(((echo a && echo b) && (echo c && echo d)) && echo f); exit"

echo "Three sets of parentheses test: "

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


