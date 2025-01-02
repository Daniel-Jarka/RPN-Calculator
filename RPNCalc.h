#ifndef __RPNCALC_H 
#define __RPNCALC_H

/*
 *  RPNCalc.h
 *  Daniel Jarka
 *  10/22/24
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  RPNCalc is a class that represents the calculator that stores inputs on a
 *  stack and performs operations in Reverse Polish order. The calculator
 *  accepts three main types of inputs, which are integers, booleans, and
 *  rstrings. This is accomplished because every input type is stored inside
 *  a Datum element. This is to avoid type mismatch between elements when
 *  pushing them on the stack. In this way, RPNCalc uses a Datum Stack to
 *  store input information. RPNCalc primarily reads inputs through the
 *  user, but it can also read file and string inputs through the exec()
 *  and file() commands respectively. 
 * 
 */
#include <string>
#include <sstream>
#include <istream>
#include "DatumStack.h"
#include "parser.h"

using namespace std;

class RPNCalc {
    public:
    RPNCalc();
    void run();

    private:
    bool run_calculator;
    DatumStack stack;

    void commands(istream &input);
    void num(int number);
    void boolean(std::string boolean);
    void not_bool();
    void drop();
    void dup();
    void swap();
    void print();
    void clear();
    void if_func();
    void exec();
    void file();
    bool got_int(string s, int *resultp);
    bool isI_operator(std::string s);
    void int_operator(std::string s);
    bool isB_operator(std::string s);
    void bool_operator(std::string s);
    Datum return_popped();
    std::string clean_string(std::string s);
};

#endif 
