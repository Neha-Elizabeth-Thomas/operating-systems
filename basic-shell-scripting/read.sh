#! /bin/bash

read -p "Enter 3 names: " name1 name2 name3
echo "entered name: $name1,$name2,$name3"

read -p "Enter username: " username
read -sp "Enter password: " pass
echo
echo "username = $username password=$pass"
#for new line write echo with no string

#array
echo "enter names: "
read -a names
echo ${names[0]}, ${names[1]}

#read with no args
echo "ENter a name; "
read
echo "entered name: $REPLY"
