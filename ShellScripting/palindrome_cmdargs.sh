#! /bin/bash

num1=$1
num2=$2
echo "palindrome numbers between $num1 and $num2: "
for i in {$num1..$num2} 
do
  rev=0
  num=$i
  echo $num
  while [ $i -ne 0 ]
  do
    dig = $((i%10))
    rev = $((rev*10 + dig))
    i = $((i/10))
  done

  if [ $rev -eq $num ]
  then
    echo "$num"
  fi

done
