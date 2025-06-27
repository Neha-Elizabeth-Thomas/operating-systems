echo -e "Enter two numbers: \c"
read num1 num2

echo $(( num1 + num2 ))
echo $(( num1 - num2 )) 
echo $(( num1 * num2 ))
echo $(( num1 / num2 ))
echo $(( num1 % num2 ))

echo
#use expr command
# only one bracket needed
# use seperste $ with each variable
echo $(expr $num1 + $num2 )
echo $(expr $num1 - $num2 ) 
echo $(expr $num1 \* $num2 ) #use escape char
echo $(expr $num1 / $num2 )
echo $(expr $num1 % $num2 )

