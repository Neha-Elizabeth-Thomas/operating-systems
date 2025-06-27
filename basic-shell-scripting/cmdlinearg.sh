#! /bin/bash

#as variables
echo $0,$1,$2,$3 '<echo $0 $1 $2 $3'
#use single quotes to not consider variables

#as array in @ which is adefault variable
#assign array @ to variable args
#starts from 0
args=("$@")
echo ${args[0]},${args[1]},${args[2]}

echo $@

#no of args
echo $#
