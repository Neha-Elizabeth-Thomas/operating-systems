#! /bin/bash

echo -e  "Enter age: \c"
read age
#int comparison
# when angular bracket used use (( ))
# -eq -ne(only this)
# lt <,gt >,le <=,ge >=

#string(ascii) comparison
# when angular bracket is used use [[ ]]
# == != 
# no <= >=

# always keep space start and end of square bracket []
if [ $age -gt 10  -a  $age -lt 30 ]
then
  echo valid age
else 
  echo "invalid age"
fi

# logical and op 3 ways
# [] && []
# [[ && ]]
# [ -a ]

# logical or 3ways
# [] || []
# [[ || ]]
# [ -o ]
