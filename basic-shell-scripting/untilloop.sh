#! /bin/bash

#until loop opposite of while loop

#in while loop 
#get out of loop when condition is false
#loop when condition is true

#untl loop
#get out of loop when condition is true
#loop when condition is false

echo -e "Enter the value of n: \c"
read n

i=1

until [ $i -ge 11 ]
do
  echo $i
#  i=$((i+1))
#   (( i++ ))
   (( ++i ))
done

