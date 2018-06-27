#!/bin/bash

#file="hello.txt"
#if [ -e $file ]
#then
#	rm $file
#fi
#touch $file
##declare -i i=1
#i=1
#while (($(wc -c < $file)/1000 < $1))
#do
#	echo "${i}: hello, world" >> $file
#	((i++))
#done
base64 /dev/urandom | head -c 100000000 > hello.txt
