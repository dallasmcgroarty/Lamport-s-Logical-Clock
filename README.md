# Lamport-s-Logical-Clock
program that simulates lamport's logical clock

Group-members:

Dallas McGroarty, email -> dallasmcgroarty@csu.fullerton.edu 
    -- wrote all code except for verify.h
Brandon Hawkinson, email -> b.hawkinson245@csu.fullerton.edu, github-> github.com/Hawkinsonb 
    --wrote verify.h code

Program Info:
Program was made using visual studio code on windows
Language used: C++
A .exe file is included but may not run if you are using a linux machine.
The program will prompt user for the number of processes
The program will then ask for the file containing the matrix to be used
Choose to run either calculate or verify
    
Calculate:
Calculate will take a matrix of events each event specified by characters; s = send, r = receive, and any other single letter is an internal event. Calculate will output the logical clock values for each event.
    
Verify:    
Verify works the same way except in reverse, it will output the events given the logical clock values
    
Examples:
Three test examples and their output are included in the project folder
Verify will accept test examples two and three
Calculate will accept test example one
