#! /bin/bash

echo -e "Enter a vehile: \c"
read vehicle

case $vehicle in
  "car" )
    echo "car" ;;
  "van" )
    echo "van" ;;
  "truck" )
    echo "truck" ;;
  * ) # default
    echo "invalid vehicle" ;;
esac


#pattern identifcation
echo -e "Enter a char: \c"
read char

case $char in
  [a-z] )
    echo "$char in a to z" ;;
  [A-Z] )
    echo "$char in A to Z" ;;
  [0-9] )
    echo "$char in 0 to 9" ;;
  ? )
    echo "$char is a special char" ;;
  * )
    echo  "invalid" ;;
esac
