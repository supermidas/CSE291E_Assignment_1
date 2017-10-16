# CSE291E_Assignment_1
Assignment 1

The .cpp file can be compiled via Microsoft Visual Studio 2010.

You can try any other benchmarks by changing the name of the .cnf file in line #68 of the .cpp file.
( fstream fin("unif-k5-r21.117-v390-c8236-S7412914535193118493.cnf");     //can handle different CNFs )

About the outputs:
Case 1: Output "sat" and the corresponding assignment if the program finds a solution within 10 seconds. 
Assume there are n variables, then the program will output n 0/1's for each variable as the assignment.
Case 2: Output "unsat" if the program has exhausted all possible assgnments within 10 seconds and finds no solution.
Case 3: Output "unkonwn" if none of the two cases occurs. 
The ratio between "the # of assignment have been explored" and "total # of assignments" will also be in the outputs. 
