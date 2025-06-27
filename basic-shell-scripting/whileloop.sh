#! /bin/bash

echo -e "Enter the value of n: \c"
read n

i=1

while [ $i -le $n ]
do
  echo $i
  ((i++))
  sleep 1
 # gnome-terminal & to open multiple terminals
done
