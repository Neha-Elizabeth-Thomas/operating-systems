#! /bin/bash
while :
do
echo "Enter 2 numbers: "
read num1 num2

echo -e "Enter your choice:\n1)Addition\n2)Subtraction\n3)Multiplication\n4)Division\n5)Remainder\n6)close"
read choice

case $choice in
    1 )
    result=$(( num1+num2 ));;
    2)
    result=$(( num1-num2 ));;
    3)
    result=$(( num1*num2 ));;
    4)
    result=$(( num1/num2 ));;
    5)
    result=$(( num1%num2 ));;
    6 )
    exit;;
    *)
    echo "Invalid choice"
esac

echo result="$result"
done
