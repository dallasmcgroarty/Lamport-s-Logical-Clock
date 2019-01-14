/*
Dallas McGroarty
Brandon Hawkinson
Project 1
CPSC 474-01
Visual Studio Code
*/
#include <string>

using namespace std;

struct process
{
    int procNum; //process number
    string events[25]; //holds string events
    int LC[25]; //holds logical clock values for each event
    int eventNum; //number of events per process
};