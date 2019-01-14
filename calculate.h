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
#include "message.h"
#include "process.h"

using namespace std;

//print calculated matrix
void print_calc_matrix(process procArray[], int numProcs, int numEvents)
{
    for(int i = 0; i < numProcs; i++)
    {
        for(int j = 0; j < numEvents; j++)
        {
            cout << procArray[i].LC[j] << " ";
        }
        cout << "\n";
    }
}
message msg_array[10];
int msg_index = 0;
void calculate(process procArray[], int numProcs, int numEvents)
{

    //int matrix[numProcs][numEvents];
    
    for(int k = 0; k < numProcs; k++)
    {
        for (int i = 0; i < numEvents; i++)
        {
        string event;
        char ch;
        ch = procArray[k].events[i][0];
        //send event
        if(ch == 's')
        {
            ch = procArray[k].events[i][1];
            //send is first event
            if(i == 0)
            {
                procArray[k].LC[i] = 1;
                bool sent = false;
                //dont send msg if its in the message array
                for(int p = 0; p < msg_index; p++)
                {
                    if(ch == msg_array[p].send_msg)
                    {
                        sent = true;
                    }
                }
                //send msg i.e. put into message array
                if(!sent)
                {
                    message msg;
                    msg.send_msg = ch;
                    msg.LC = 1;
                    msg_array[msg_index] = msg;
                    msg_index ++;
                    calculate(procArray, numProcs, numEvents);  //call calculate to update LC values
                }
            }
            //send is not first event
            else
            {
                procArray[k].LC[i] = procArray[k].LC[i-1] + 1;
                bool sent = false;
                //dont send msg if its in the message array but update value instead
                for(int p = 0; p < msg_index; p++)
                {
                    if(ch == msg_array[p].send_msg)
                    {
                        if(msg_array[p].LC != procArray[k].LC[i])
                        {
                            msg_array[p].LC = procArray[k].LC[i-1] + 1;
                            calculate(procArray, numProcs, numEvents); //call calculate to update LC values
                        }
                        sent = true;
                    }
                }
                //send msg i.e. put into message array
                if(!sent)
                {
                    message msg;
                    msg.send_msg = ch;
                    msg.LC = procArray[k].LC[i-1] + 1;
                    msg_array[msg_index] = msg;
                    msg_index ++;
                    calculate(procArray, numProcs, numEvents);  //call calculate to update LC values
                }
                
            }
        }
        //receive event
        else if(ch == 'r')
        {
            ch = procArray[k].events[i][1];
            //receive is first event
            if(i == 0)
            {
                //check the message array for messages
                for(int j = 0; j < msg_index; j++)
                {
                    if(ch == msg_array[j].send_msg)
                    {
                        procArray[k].LC[i] = msg_array[j].LC + 1;
                        msg_array[j].received = true;
                    }
                }

            }
            //receive is not first event
            else
            {
                //check the message array for messages
                for(int j = 0; j < msg_index; j++)
                {
                    if(ch == msg_array[j].send_msg)
                    {
                        procArray[k].LC[i] = max(procArray[k].LC[i-1], msg_array[j].LC) + 1;
                        msg_array[j].received = true;
                    }
                }
            }
        }
        //internal event
        else if(isalpha(ch))
        {
            //N = NULL, set event and events after it to 0
            if(ch == 'N')
            {
                for(int j = i; j < numEvents; j++)
                {
                    procArray[k].LC[j] = 0;
                }
            }
            //internal event is first event
            else if(i == 0)
            {
                procArray[k].LC[i] = 1;
            }
            //internal event is not first event;
            else
            {
                procArray[k].LC[i] = procArray[k].LC[i-1] + 1;
            }
        }
        }
    }

}