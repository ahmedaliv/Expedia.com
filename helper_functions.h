#ifndef HELPER_FUNCTIONS_H_INCLUDED
#define HELPER_FUNCTIONS_H_INCLUDED
#include <iostream>
#include <vector>
using std::vector;
using std::string;

// Added parameter. Respect backward compatibility

int ReadInt(int low, int high, bool cancel_choice_allowed = false);


int ShowReadMenu(const vector<string> &choices, string header = "Menu");

string GetCurrentTimeDate();
#endif // HELPER_FUNCTIONS_H_INCLUDED
