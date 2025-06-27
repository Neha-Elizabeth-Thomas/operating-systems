#! /bin/bash

echo -e "Enter filename:\c"
read filename

if [ -f $filename ]
then
    if [ -w $filename ]
    then
        echo "Write some data: enter ctrl+d"
        cat >> $filename
        echo "data appende to $filename"
    else
        echo "file not writable"
    fi
else
    echo "$filename not exist"
fi
