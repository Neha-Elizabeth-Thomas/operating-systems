#! /bin/bash

#echo $BASH_VERSION

for i in 0 1 2 3 4 5
do
  echo $i
done

echo
#for version 4 and above

for i in {1..10}
do
  echo $i
done

echo
for i in {1..10..2} #{start..end..increment}
do
  echo $i
done

echo
# similar to C pgm
for((i=1 ; i<=10 ; i++))
do
  echo $i
done

for command in ls -al pwd date
do
  echo "--------------$command----------"
  $command
done

echo
for item in *
do
  if [ -f $item ]
  then  
    echo $item
  fi
done
