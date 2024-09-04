#!/bin/bash

#take path name
read -p "enter the path: " path

#loop and rename
#echo $path
#`cd "$path"`

date=$(echo $(date "+%Y%m%d"))

for i in ${path}/* ; do
    mv $i "${i}$date"
done
