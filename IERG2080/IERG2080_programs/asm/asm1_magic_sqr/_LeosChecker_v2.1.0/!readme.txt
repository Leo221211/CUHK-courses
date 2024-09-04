Hello there!
This is a script that helps you to test all of the 4998 cases of assignment 1 of IERG 2080.

BASIC DESCRIPTION:
    if there are wrong answers, it will be printed in the file [wrong_ans.txt],
    the standard output is only for you to check the current process.
    It can be run on macOS terminal, and virtual linux machines of IE lab

GUIDE OF USING THIS TOOL:
    0. on your terminal, cd to this directory first

    1. paste your code file (.c file) into this folder

    2. run command (remember to change file name!):
        gcc [your_program_name.c] -o exe -O3 -w -std=gnu11

    3. run command:
        gcc checker.c -o checker -O3 -w -std=gnu11

    4. run command:
        ./all_checker.sh

    5. wait for the program to check your code!
    (it would take a long time (up to hours) to check all the possibilities so you can start the checking and leave it aside and do other jobs!)

    6. check the result!

HOW TO CHECK THE RESULT:
    If your standard output shows the line "end of checking! check your result in wrong_ans.txt",
    that means the checking is finished. Open wrong_ans.txt in the same folder.
    The first line of this file should be the starting time of the checking.
    The last line of this file should be "end of wrong answer file".
    In the middle, there should be the the input that generates incorrect answers under your code.
    If there aren't any incorrect answers (i.e. only 2 lines in wrong_ans.txt), 
    then congrats! your code is correct

COPYRITE:
    Leo 1155191596@link.cuhk.edu.hk 
    all rights reserved