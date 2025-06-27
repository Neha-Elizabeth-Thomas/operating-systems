#! /bin/bash

os=('ubuntu' 'windows' 'linux')
os[2]='neha'
unset os[0]
os[6]='mac'
echo ${os[@]}
echo ${!os[@]}
echo ${#os[@]}
echo ${os[0]}
