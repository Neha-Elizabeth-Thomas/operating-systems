#! /bin/bash

echo -e "Enter the value of n: \c"
read n

num1=0
num2=1
i=2
echo $num1
echo $num2

while [ $i -lt $n ]
do
  fib=$((num1+num2))
  num1=$num2
  num2=$fib
  echo $fib
  ((i++))
done

