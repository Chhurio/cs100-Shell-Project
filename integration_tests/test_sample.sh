#!/bin/bash 

#Valid file Test with no flags (existing)
if test -e testFile.txt; then 
	echo "test passed" 
	echo 
else 
	echo "not working"
fi

#input="test testFile.txt; exit"  
#echo "Test command (valid file)  w/ no flags test: "

#output=$(echo "$input" | ./../rshell)

#var="$ "			 #originally double quotes with no $ 
#var+=$(echo "$input" | sh) 
#var+="(True)"


#if [ "$output" = "$var" ] 
#then 
#	echo "Test passed"
#else 
#	echo "Test failed" 
#fi 

#echo




#========================================
#Invalid file Test with no flags (existing)


#input="test names.txt; exit"  
#echo "Test command (invalid file)  w/ no flags test: "

#output=$(echo "$input" | ./../rshell)

#var="$ "			  
#var+=$(echo "$input" | sh) 
#var+="(False)"


#if [ "$output" = "$var" ] 
#then 
#	echo "Test passed"
#else 
#	echo "Test failed" 
#fi 

#echo


