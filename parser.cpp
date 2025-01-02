/*
 *  parser.cpp
 *  Daniel Jarka
 *  10/12/24
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  Implementation of the parser class.
*/

#include <string>
#include <iostream>
#include <sstream>

#include "parser.h"

using namespace std;

/*
 * name:      parseRString
 * purpose:   This function returns the correctly formatted rstring
 *            after reading input.
 * arguments: an istream object that represents input.
 * returns:   A correctly formatted rstring.
 * effects:   none
 */
string parseRString(istream &input) {
    string s;
    string parsed;
    int isBalanced = 1;
    while (isBalanced > 0) {
        input >> s;
        parsed += " " + s;
        if (s == "{") {
            ++isBalanced;
        }
        else if(s == "}") {
            --isBalanced;
        }
    }
    return "{" + parsed;
}


