/*
 *  DatumStack.cpp
 *  Daniel Jarka
 *  10/22/24
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  This file contains the implementation of the
 *  RPNCalc class.
*/
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <istream>
#include <iostream>
#include <fstream>


#include "RPNCalc.h"

using namespace std;

/*
 * name:      default constructor
 * purpose:   initializes an instance of RPNCalc
 * arguments: none
 * returns:   none
 * effects:   creates an RPNCalc object
 */
RPNCalc::RPNCalc() {
    run_calculator = true;
}

/*
 * name:      run()
 * purpose:   runs RPNCalc commands with user input
 * arguments: none
 * returns:   none
 * effects:   runs RPNCalc commands by accepting user input
 */
void RPNCalc::run() {
    commands(std::cin);
    std::cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name:      commands
 * purpose:   query loop that processes various commands to perform RPNCalc
 *            functions
 * arguments: an istream object that can accept input from different sources,
 *            which are user input, file input, and string input.
 * returns:   none
 * effects:   proccesses commands and updates the underlying stack based on
 *            input. catches any runtime errors that are thrown from datum
 *            class.
 */
void RPNCalc::commands(istream &input) {
    string s;
    int p;
    while(run_calculator and input >> s) {
        // commands
        try {
            if(got_int(s, &p)) {
                num(p);
            } else if(s[0] == '#') {
                boolean(s);
            } else if(s == "print") {
                print();
            } else if(s == "not") {
                not_bool();
            } else if(s == "drop") {
                drop();
            } else if(s == "dup") {
                dup();
            } else if(s == "swap") {
                swap();
            } else if(s == "clear") {
                clear();
            } else if(isI_operator(s)) {
                int_operator(s);
            } else if(isB_operator(s)) {
                bool_operator(s);
            } else if(s == "{") {
                stack.push(Datum(parseRString(input)));
            } else if(s == "exec") {
                exec();
            } else if(s == "file") {
                file();
            } else if(s == "if") {
                if_func();
            } else if(s == "quit") {
                run_calculator = false;
            } else {
                std::cerr << s << ": unimplemented\n";
            }
        } catch(const std::runtime_error &e) {
            std::cerr << "Error: " << e.what() << endl;
        }
    }
}

/*
 * name:      print()
 * purpose:   helper function that prints the element on top of the
 *            calculator stack
 * arguments: none
 * returns:   none
 * effects:   none
 */
void RPNCalc::print() {
    cout << stack.top().toString() << endl;
}

/*
 * name:      clear()
 * purpose:   helper function that clears all elements from the calculator
 *            stack.
 * arguments: none
 * returns:   none
 * effects:   empties the calculator stack.
 */
void RPNCalc::clear() {
    stack.clear();
}

/*
 * name:      num()
 * purpose:   helper function that pushes a Datum containing an integer on
 *            top of the stack.
 * arguments: an integer to be pushed onto the stack
 * returns:   none
 * effects:   adds an integer to the stack
 */
void RPNCalc::num(int number) {
    Datum new_num = Datum(number);
    stack.push(new_num);
}

/*
 * name:      boolean()
 * purpose:   helper function that pushes a Datum containing a boolean value
 *            on top of the stack.
 * arguments: a string that represents either a true or false boolean
 * returns:   none
 * effects:   adds a boolean to the stack
 */
void RPNCalc::boolean(std::string boolean) {
    if (boolean == "#t") {
        Datum new_bool = Datum(true);
        stack.push(new_bool);
    }
    else if (boolean == "#f") {
        Datum new_bool = Datum(false);
        stack.push(new_bool);
    }
    else {
        std::cerr << "Error: invalid boolean " << boolean << endl;
    }
}

/*
 * name:      not_bool()
 * purpose:   helper function that pops a boolean from the top of the stack
 *            and negates it.
 * arguments: none
 * returns:   none
 * effects:   adds a negated boolean to the stack
 */
void RPNCalc::not_bool() {
    if(return_popped().getBool()) {
        stack.push(Datum(false));
    }
    else {
        stack.push(Datum(true));
    }
}

/*
 * name:      drop()
 * purpose:   helper function that pops the top Datum element from the
 *            calculator stack.
 * arguments: none
 * returns:   none
 * effects:   removes an element from the stack
 */
void RPNCalc::drop() {
    stack.pop();
}

/*
 * name:      dup()
 * purpose:   helper function that duplicates the top element of the stack
 * arguments: none
 * returns:   none
 * effects:   adds the duplicated element to the stack.
 */
void RPNCalc::dup() {
    stack.push(stack.top());
}

/*
 * name:      swap()
 * purpose:   helper function that swaps the top two elements of the stack.
 * arguments: none
 * returns:   none
 * effects:   swaps the top two elements of the stack.
 */
void RPNCalc::swap() {
    Datum temp1 = return_popped();
    Datum temp2 = return_popped();
    stack.push(temp1);
    stack.push(temp2);
}

/*
 * name:      exec()
 * purpose:   helper function that processes the commands inside an rstring.
 * arguments: none
 * returns:   none
 * effects:   sends the rstring as an istringstream input to the commands
 *            function.
 */
void RPNCalc::exec() {
    Datum rs = return_popped();
    if (not rs.isRString()) {
        std::cerr << "Error: cannot execute non rstring\n";
        return;
    }
    std::string rstring = clean_string(rs.getRString());
    std::istringstream iss(rstring);
    commands(iss);
}

/*
 * name:      file()
 * purpose:   helper function that processes the inputs in the file that
 *            corresponds to the filename in an rstring
 * arguments: none
 * returns:   none
 * effects:   sends the file input as an ifstream to the commands function.
 */
void RPNCalc::file() {
    std::string rstring = return_popped().getRString();
    std::string filename = clean_string(rstring);
    std::ifstream infile(filename);
    if (infile.fail()) {
        std::cerr << "Unable to read " << filename << '\n';
        return;
    }
    commands(infile);
    infile.close();
}

/*
 * name:      if_func()
 * purpose:   helper function that executes an rstring depending on a 
 *            processed boolean condition
 * arguments: none
 * returns:   none
 * effects:   executes a false case if the boolean test condition is false
 *            and executes a true case if the boolean test condition is true.
 */
void RPNCalc::if_func() {
    Datum false_case = return_popped();
    Datum true_case = return_popped();
    Datum condition = return_popped();
    if (not condition.isBool()) {
        std::cerr << "Error: expected boolean in if test\n";
        return;
    }
    if (not false_case.isRString() or not true_case.isRString()) {
        std::cerr << "Error: expected rstring in if branch\n";
        return;
    }
    if (condition.getBool()) {
        stack.push(true_case);
        exec();
    }
    else {
        stack.push(false_case);
        exec();
    }
}

/*
 * Name: got_int 
 * Purpose: determines if a string contains an integer and loads said
 *           integer into an integer variable whose address has been
 *           passed to this function
 * Parameters: a string to check if it contains an integer as well as 
 *              a pointer to an integer to load in the event an 
 *              integer can be parsed from said string
 * Returns: a boolean where true indicates an integer was successfully
 *           parsed from the provided string (and therefore the
 *           addressed integer has been loaded) and false indicates 
 *           an integer could not be read 
 * Effects: the integer pointed to by the passed pointer will be updated
 *           with the integer parsed from the string in the event true
 *           is returned (otherwise nothing happens)
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
bool RPNCalc::got_int(string s, int *resultp) {
    /* Holds the first non-whitespace character after the integer */
    char extra;
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name:      isI_operator()
 * purpose:   helper function that checks if input is an integer operator
 * arguments: a string that represents an input to be checked
 * returns:   true if the input is an integer operator, false otherwise
 * effects:   none
 */
bool RPNCalc::isI_operator(std::string s) {
    return s == "+" 
           or s == "-"
           or s == "*"
           or s == "/"
           or s == "mod";
}

/*
 * name:      int_operator()
 * purpose:   helper function that performs an integer operation
 * arguments: a string that represents the operation to be performed
 * returns:   none
 * effects:   pops the top two elements from the stack and performs an integer
 *            operation on them. the result is pushed onto the stack. 
 *            throws an error if there is a division by 0.
 */
void RPNCalc::int_operator(std::string s) {
    Datum num2 = return_popped();
    Datum num1 = return_popped();
    int int2 = num2.getInt();
    int int1 = num1.getInt();
    if (s == "+") {
        stack.push(Datum(int1 + int2));
    }
    else if (s == "-") {
        stack.push(Datum(int1 - int2));
    }
    else if (s == "*") {
        stack.push(Datum(int1 * int2));
    }
    else if (s == "/") {
        if(int2 == 0) {
            throw runtime_error("division by 0.");
        }            
        stack.push(Datum(int1 / int2));
    }
    else if (s == "mod") {
        if(int2 == 0) {
            throw runtime_error("division by 0.");
        }   
        stack.push(Datum(int1 % int2));
    }
}

/*
 * name:      isB_operator()
 * purpose:   helper function that checks if input is a boolean operator
 * arguments: a string that represents an input to be checked
 * returns:   true if the input is a boolean operator, false otherwise
 * effects:   none
 */
bool RPNCalc::isB_operator(std::string s) {
    return s == ">" 
           or s == "<"
           or s == ">="
           or s == "<="
           or s == "==";
}

/*
 * name:      bool_operator()
 * purpose:   helper function that performs a boolean operation
 * arguments: a string that represents a boolean operation
 * returns:   none
 * effects:   pops the top two elements from the stack and performs a boolean
 *            comparison. pushes the result of this comparison to the stack.
 */
void RPNCalc::bool_operator(std::string s) {
    Datum bool2 = return_popped();
    Datum bool1 = return_popped();
    if (s == "==") {
        stack.push(Datum(bool1 == bool2));
        return;
    }
    int int2 = bool2.getInt();
    int int1 = bool1.getInt();

    if (s == ">") {
        stack.push(Datum(int1 > int2));
    }
    else if (s == "<") {
        stack.push(Datum(int1 < int2));
    }
    else if (s == ">=") {
        stack.push(Datum(int1 >= int2));
    }
    else if (s == "<=") {
        stack.push(Datum(int1 <= int2));
    }
}

/*
 * name:      return_popped()
 * purpose:   helper function that returns top Datum element from the stack
 *            and pops it from the stack.
 * arguments: none
 * returns:   A Datum element at the top of the stack.
 * effects:   none
 */
Datum RPNCalc::return_popped() {
    Datum popped = stack.top();
    stack.pop();
    return popped;
}

/*
 * name:      clean_string()
 * purpose:   helper function that formats an rstring into a readable
 *            commands string input
 * arguments: a string that represents an rstring to be cleaned
 * returns:   a formatted string where input can properly be read from
 * effects:   none
 */
std::string RPNCalc::clean_string(std::string s) {
    s.erase(s.size() - 2, s.size());
    s.erase(0 , 2);
    return s;
}