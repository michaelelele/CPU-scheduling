# CPU-scheduling
CPU scheduling algorithms in C++ using First Come First Serve, Shortest Job First, and Priority Scheduling

Scheduler.cc:
This file is the only file used for this project. There are four different functions
called by main to complete the task. read, FCFS, SJFP, and Priority.
The read function reads in data from a csv file into a 2D array.
The FCFS function sorts the 2D array by arrival time and computes the desired times
The SJFP and Priority functions are similar except that SJFP sorts by burst time and 
Priority sorts by Priority. 

The program can be run by running make all and then typing ./Scheduler ".csv" file.
