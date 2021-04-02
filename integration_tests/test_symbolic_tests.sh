#!/bin/sh 


#No flags
echo ==============================================  
echo No Flags 
echo ==============================================  
echo

#Valid file Test with no flags (existing)
input="[ testFile.txt ]; exit"			#Changd this from testFile.txt to names.txt? weird error?
echo "Test command (valid file)  w/ no flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			 #originally double quotes with no $ 
var+=$(echo "$input" | sh) 
var+="(True)"

#added && ...]
if [ "$output" = "$var" ]
# && [ test -e testFile.txt; == 1 ]; 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#echo "$output"  #echos out output
#echo 
#echo "$var"  #echos out var


#Invalid file Test with no flags (existing)
input="[ names.txt ]; exit"  
echo "Test command (invalid file)  w/ no flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			  
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else
	echo "Test failed" 
fi

echo 

#Valid directory  Test with no flags (existing)
input="[ testDirectory ]; exit"  
echo "Test command (valid directory)  w/ no flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			  
var+=$(echo "$input" | sh) 
var+="(True)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#Invalid directory  Test with no flags (existing)
input="[ unitTests ]; exit"  
echo "Test command (invalid directory)  w/ no flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			 
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo




#-e flags
echo ==============================================  
echo "-e Flags" 
echo ==============================================  
echo
#Valid file Test with -e  flags (existing)
input="[ -e testFile.txt ]; exit"  
echo "Test command (valid file)  w/ -e flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			 #originally double quotes with no $ 
var+=$(echo "$input" | sh) 
var+="(True)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


#Invalid file Test with -e flags (existing)
input="[ -e names.txt ]; exit"  
echo "Test command (invalid file)  w/ -e flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "		 
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


 
#Valid directory Test with -e flags (existing)
input="[ -e testDirectory ]; exit"  
echo "Test command (valid directory)  w/ -e flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			  
var+=$(echo "$input" | sh) 
var+="(True)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#Invalid directory  Test with -e flags (existing)
input="[ -e unitTests ]; exit"  
echo "Test command (invalid directory)  w/ -e flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			  
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo



#-f flags
echo ==============================================  
echo "-f Flags" 
echo ==============================================  
echo
#Valid file Test with -f  flags (existing)
input="[ -f testFile.txt ]; exit"  
echo "Test command (valid file)  w/ -f flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			 #originally double quotes with no $ 
var+=$(echo "$input" | sh) 
var+="(True)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#Invalid file Test with -f flags (existing)
input="[ -f yuh ]; exit"  
echo "Test command (invalid input)  w/ -f flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "
#var+="(False}"		 
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


#-d flags
echo ==============================================  
echo "-d Flags" 
echo ==============================================  
echo
#Valid file Test with -d  flags (existing)
input="[ -d testDirectory ]; exit"  
echo "Test command (valid file)  w/ -d flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "			 #originally double quotes with no $ 
var+=$(echo "$input" | sh) 
var+="(True)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


#Invalid file Test with -d flags (existing)
input="[ -d yuh ]; exit"  
echo "Test command (invalid input)  w/ -d flags test: "

output=$(echo "$input" | ./../rshell)

var="$ "		 
var+=$(echo "$input" | sh) 
var+="(False)"


if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#mutliple ocnnectors tests
echo ==============================================  
echo "Multiple connectors and Flags" 
echo ==============================================  
echo

#Test with -f  flags (existing), other connectors
input="[ -f testFile.txt ] && echo \"File exists\"; exit"  
echo "Other connectors -f  test: "

output=$(echo "$input" | ./../rshell)

#changed from " " to $' ' in order to get newline  
var=$'$ '
var+=$'(True)\n'			 #originally double quotes with no $ 
var+=$(echo "$input" | sh) 
#var+="(True)"

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo

#echo "$output"  #echos out output
#echo 
#echo "$var"  #echos out var
#echo


#Test with -d  flags (existing), other connectors
input="[ -d testDirectory ] && echo \"File exists\"; exit"  
echo "Other connectors with -d test: "

output=$(echo "$input" | ./../rshell)

  
var=$'$ '
var+=$'(True)\n'
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo 



#Test with -e  flags (existing), other connectors
input="[ -e testDirectory ] && echo \"Exists\"; exit"  
echo "Other connectors with -e test: "

output=$(echo "$input" | ./../rshell)

  
var=$'$ '
var+=$'(True)\n'
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


#Test with ls, other connectors
input="ls; [ testFile.txt ]; exit"  
echo "Other connectors with ls test: "

output=$(echo "$input" | ./../rshell)

  
var=$'$ '
#var+=$'(True)\n'
var+=$(echo "$input" | sh) 
var+=$'\n(True)'

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo


#test lots of commands 
input="[ testFile.txt ]; ls -a; echo hello && pwd  || echo world; git status; exit"   
echo "Lots of commands test: "

output=$(echo "$input" | ./../rshell)

  
var=$'$ '
var+=$'(True)\n'
var+=$(echo "$input" | sh) 

if [ "$output" = "$var" ] 
then 
	echo "Test passed"
else 
	echo "Test failed" 
fi 

echo




