#! /bin/bash
#use command `which zsh` to find out (?)

declare -r MAX_LEN=5

date=`date`
`echo "test on $date:" > wrong_ans.txt`

correct=1

for i in {3..5000}
do
    `./exe < <(echo $i) | ./checker $i`
    
    if [ $? -ne 0 ]
    then
        #echo "wrong: $i"
        let correct=0
        `echo "wrong answer with size of magic square $i" >> wrong_ans.txt`
    fi

    status=$(($i%100))
    if [ $status -eq 0 ]
    then
        if [ $correct -eq 1 ]
        then
            echo "process: $i / 5000; up to now all correct!"
        else
            echo "! process: $i / 5000 problem occurs!"
        fi
    fi

done

echo "end of checking! check your result in wrong_ans.txt"
if [ $correct -eq 1 ]
then
    echo "all correct! Well done!"
else
    echo "some problem occurs! Please check wrong_ans.txt for detail!"
fi

`echo "end of wrong answer file" >> wrong_ans.txt`

# why can't which zsh
# why can't declare used in for loop?
# how to run a file in script
# $i%50
# subshell in a subshell?