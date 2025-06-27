#! /bin/bash

echo -e "Enter filename: \c"
read filename

echo -e "Enter search word: \c"
read search_word

if [ -f $filename ]
then
    if [ -r $filename ]
    then
        if grep -q "$search_word" "$filename" 
        then
             echo "$search_word found in file $filename" 
        else
            echo "$search_word does not found in file $filename"
        fi
    else
        echo "$filename has no read permission"
    fi
else
    echo "$filename does not exist"
fi

