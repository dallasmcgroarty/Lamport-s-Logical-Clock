/*
Dallas McGroarty
Brandon Hawkinson
Project 1
CPSC 474-01
Visual Studio Code
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "calculate.h"

using namespace std;

void print_ver_matrix(process procArray[], int numProcs, int numEvents)
{
    cout << "The verified matrix: \n";
    for (int i = 0; i < numProcs; i++)
    {
        for (int j = 0; j < numEvents; j++)
        {
            cout << procArray[i].events[j] << " ";
        }
        cout << "\n";
    }
}

bool ver_last_calc = false;

bool is_correct(process procArray[], int numProcs, int numEvents, vector<int> seen)
{
    sort(seen.begin(), seen.end());
    for (int i = 1; i <= seen.size(); i++)
    {
        if (i == 1)
        {
            if (seen.at(i - 1) != 1)
            {
                cout << endl
                     << "Incorrect: missing a logical clock value \n";
                return false;
            }
        }
        else
        {
            if ((seen.at(i - 1) != i || seen.at(i - 2) != (i - 1)))
            {
                cout << endl
                     << "Incorrect: missing a logical clock value \n";
                return false;
            }
        }
    }

    for (int k = 0; k < numProcs; k++)
    {
        vector<int> in_row;
        for (int i = 0; i < numEvents; i++)
        {
            int num = procArray[k].LC[i];
            if (num != 0)
            {
                in_row.push_back(num);
                for (int j = 0; j < in_row.size(); j++)
                {
                    if (in_row.at(j) > num)
                    {
                        cout << endl
                             << "Incorrect: cannot have a logical clock value that's lower than one previously in the row.\n";
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void verify(process procArray[], int numProcs, int numEvents)
{
    vector<int> seen;
    vector<int> isCharacter;
    vector<int> isSender;
    vector<int> isReciever;

    for (int k = 0; k < numEvents; k++)
    {
        vector<int> in_col;
        for (int i = 0; i < numProcs; i++)
        {
            vector<int> in_row;
            int num = procArray[i].LC[k];
            in_col.push_back(num);
            if (num != 0)
            {
                if ((num == 1) && !(find(seen.begin(), seen.end(), num) != seen.end())) //if it's the first clock time, and It's not already added. add to vector
                {
                    seen.push_back(num);
                }

                if ((num != 1 && !(find(seen.begin(), seen.end(), (num - 1)) != seen.end())) || (find(in_col.begin(), in_col.end(), (num - 1)) != in_col.end())) //if I can't find the previous in seen.
                {
                    for (int j = 0; j < numEvents; j++)
                    {
                        int num = procArray[i].LC[j];
                        in_row.push_back(num);
                    }

                    if (k != 0)
                    {
                        if (!(in_row.at(k - 1) == (num - 1)))
                        {
                            isReciever.push_back(num);
                            isSender.push_back(num - 1);
                            if (!(find(seen.begin(), seen.end(), (num)) != seen.end()))
                            {
                                seen.push_back(num);
                            }
                        }
                        else
                        {
                            isCharacter.push_back(num);
                            if (!(find(seen.begin(), seen.end(), (num)) != seen.end()))
                            {
                                seen.push_back(num);
                            }
                        }
                    }
                    else
                    {
                        isReciever.push_back(num);
                        isSender.push_back(num - 1);
                        if (!(find(seen.begin(), seen.end(), (num)) != seen.end()))
                        {
                            seen.push_back(num);
                        }
                    }

                    if (num == 1 && find(isCharacter.begin(), isCharacter.end(), (num)) != isCharacter.end())
                    {
                        isCharacter.erase(find(isCharacter.begin(), isCharacter.end(), (num)));
                    }
                }
                else
                {
                    isCharacter.push_back(num);
                    if (!(find(seen.begin(), seen.end(), num) != seen.end())) //if it's the first clock time, and It's not already added. add to vector
                    {
                        if (!(find(seen.begin(), seen.end(), (num)) != seen.end()))
                        {
                            seen.push_back(num);
                        }
                    }
                }
            }
        }
    }

    int charIter = 96;
    vector<int> recCopy = isReciever;
    vector<int> sendCopy = isSender;
    sort(recCopy.begin(), recCopy.end());
    sort(sendCopy.begin(), sendCopy.end());

    bool isCorrect = is_correct(procArray, numProcs, numEvents, seen);
    if (isCorrect)
    {
        for (int k = 0; k < numEvents; k++)
        {
            for (int i = 0; i < numProcs; i++)
            {
                int num = procArray[i].LC[k];
                if (num != 0)
                {
                    bool isChar = find(isCharacter.begin(), isCharacter.end(), (num)) != isCharacter.end();
                    bool isRec = find(isReciever.begin(), isReciever.end(), (num)) != isReciever.end();
                    bool isSend = find(isSender.begin(), isSender.end(), (num)) != isSender.end();
                    if (isChar)
                    {
                        if (isChar && isRec)
                        {
                            procArray[i].events[k] = "r" + to_string(distance(recCopy.begin(), find(recCopy.begin(), recCopy.end(), num)) + 1);
                            isReciever.erase(find(isReciever.begin(), isReciever.end(), (num)));
                        }
                        else if (isChar && isSend)
                        {
                            procArray[i].events[k] = "s" + to_string(distance(sendCopy.begin(), find(sendCopy.begin(), sendCopy.end(), num)) + 1);
                            isSender.erase(find(isSender.begin(), isSender.end(), (num)));
                        }
                        else
                        {
                            charIter++;
                            procArray[i].events[k] = static_cast<char>(charIter);
                        }
                    }
                    else if (isRec)
                    {
                        procArray[i].events[k] = "r" + to_string(distance(recCopy.begin(), find(recCopy.begin(), recCopy.end(), num)) + 1);
                        isReciever.erase(find(isReciever.begin(), isReciever.end(), (num)));
                    }
                    else if (isSend)
                    {
                        procArray[i].events[k] = "s" + to_string(distance(sendCopy.begin(), find(sendCopy.begin(), sendCopy.end(), num)) + 1);
                        isSender.erase(find(isSender.begin(), isSender.end(), (num)));
                    } //in isSender
                }
                else
                {
                    procArray[i].events[k] = "NULL";
                }
            }
        }
        print_ver_matrix(procArray, numProcs, numEvents);
    }
    else
    {
        cout << endl
             << "Error in verifying the matrix\n";
    }
}
