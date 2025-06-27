#! /bin/bash

echo -e "Enter filename: \c"
#to enable \c(which is an escape char)(keep cusor on same line) use -e with echo
read filename

if [ -f $filename ]
then 
  if [ -w $filename ]
  then
    echo "type required text ctrl+d to stop"
    cat >> $filename
  else
    echo "file not writeable"
  fi
else
  echo "$filename is not a file"
fi

# -e file exist
# -f file or not
# -d directory or not
# -c char special file or not
# -b block special(binary) file or not
# -s file empty or not
# -r read permission
# -w write "
# -x execute "
