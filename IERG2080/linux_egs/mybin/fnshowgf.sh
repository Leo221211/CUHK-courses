#!/bin/bash

stthelpline=$LINENO
# no argument: show the short form of the name of girlfriend
# -b: show birthday and the number of days to go
# -B: show name of his boyfriend
# -d: show number of days in love (since 13 Dec 2022)
# -h: show help
# -l: show the long form of the name of the girlfriend
endhelpline=$LINENO

OPTIND=1
while getopts "bBhdl" opt; do
    case $opt in
        b)
            today=$(date +%s)
            year=$(date +%Y)
            may3=$(date -j -f "%Y-%m-%d" "${year}-05-03" +%s)
            if [ $may3 -lt $today ]; then
                year=$(($year + 1))
                may3=$(date -j -f "%Y-%m-%d" "${year}-05-03" +%s)
            fi
            diff=$((($may3 - $today) / 86400))
            echo "Leonie's birthday is May 3.\n$diff days to go!"
            ;;
        B)
            echo "Leonie already has a handsome boyfriend Leo!\nStay away from her!!"
            ;;
        h)
            head -$(($endhelpline-1)) /Users/mac/Documents/CUHK/sem2/IERG2080/linux_egs/mybin/fnshowgf.sh | tail -$(($endhelpline-$stthelpline-1))
            ;;
        d)
            current_date=$(date +%s)
            target_date=$(date -j -f "%Y-%m-%d" "2022-12-13" "+%s")
            date_diff=$((current_date - target_date))
            days_diff=$((date_diff / 86400))
            echo -e "Leo and Leonie are in love for\n❤️ ❤️ ❤️ ❤️ ❤️  $days_diff days ❤️ ❤️ ❤️ ❤️ ❤️"
            ;;
        l)
            echo "HU Dihan Leonie"
            ;;
        ?)
            echo "illegal syntax! Use -h to find help!"
            ;;
    esac
done

if [ $# -eq 0 ]; then
echo "Leonie"
fi