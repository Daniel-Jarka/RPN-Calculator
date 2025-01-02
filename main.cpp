/*
 *  main.cpp
 *  Daniel Jarka
 *  10/22/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  This file contains the driver that allows the user to create an instance
 *  of a RPN calculator and run it. Running the calculator allows the user
 *  to enter commands to perform integer operations and boolean operations.
 *  This implementation also allows the user to enter rstrings, which are
 *  specially formatted strings that contain instructions for the calculator
 *  to perform. The user can additionally make the calculator read inputs from
 *  a file!
 */

#include <iostream>
#include <fstream>
#include <string>

#include "RPNCalc.h"
#include "parser.h"

using namespace std;

int main(int argc, char *argv[])
{
    RPNCalc calc;
    calc.run();
    
    return 0;
}
