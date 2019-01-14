/*
Dallas McGroarty
Brandon Hawkinson
Project 1
CPSC 474-01
Visual Studio Code
*/
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <typeinfo>
#include "verify.h"

using namespace std;

int N_procs;
int M_events;
bool input = false;
string fname;
string events;

int main(int argc, char * argv[])
{
    
    while(!input)
    {
        cout << "Enter number of processes: ";
        cin >> N_procs;
        if (N_procs <= 5 && N_procs > 0)
        {
            input = true;
        }
        else
        {
            cout << "ERROR: Number of processes must be no more than 5!\n";
        }
    }
    
    process process_array[N_procs];

    cin.ignore();
    cout << "Enter the name of the file to be used: ";
    getline(cin, fname);
    ifstream fin(fname.c_str());

    //open file
    if(fin.is_open())
    {
        string str_input;
        string temp;
    
        int counter = 0;
        //get lines of file and split by spaces to get events for each row
        while(getline(fin, str_input) && counter < N_procs)
        {
            int event_count = 0;
            stringstream str(str_input);
            process proc;
            proc.procNum = counter;
            while(str >> temp)
            {
                int a = atoi(temp.c_str()); //convert the event to an int for verify
                proc.events[event_count] = temp; //put the string event into array of events for calculate
                proc.LC[event_count] = a;   //put the int into LC array for verify
                event_count++;
            }

            M_events = event_count;

            process_array[counter] = proc; //add the process to the process array

            counter ++;
        }
        fin.close();
    }

    int enter;
    cout << "Which algorithm would you like to run?\n";
    cout << "1. Calculate \n";
    cout << "2. Verify \n";
    cin >> enter;

    switch(enter)
    {
        case 1:
            calculate(process_array, N_procs, M_events);

            print_calc_matrix(process_array, N_procs, M_events);

            break;
        case 2:
            verify(process_array, N_procs, M_events);
            break;
        default:
            cout << "Input Error: Choose either 1 or 2. Exiting Program\n";

    }

    system("pause");
    return 0;
}
