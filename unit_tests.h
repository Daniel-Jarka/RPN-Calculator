/*
 *  unit_tests.h
 *  Daniel Jarka
 *  10/12/24
 *
 *  CS 15 Project 2 CalcYouLater
 *
 *  Uses Matt Russell's unit_test framework to 
 *  test the Passenger and PassengerQueue classes.
 */

#include "DatumStack.h"
#include <cassert>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "parser.h"
#include "RPNCalc.h"

using namespace std;

void dummy_test() {}

void empty_constructor() {
    DatumStack new_stack;
    assert(new_stack.isEmpty());
}

void array_constructor() {
    Datum data[6] = {Datum(3), Datum(5), Datum(21), Datum(false), 
    Datum("heck naw"), Datum(true)};
    DatumStack new_stack(data, 6);
    assert(new_stack.size() == 6);
    assert(new_stack.top().getBool());
}

void pop_test() {
    Datum data[6] = {Datum(3), Datum(5), Datum(21), Datum(false), 
    Datum("heck naw"), Datum(true)};
    DatumStack new_stack(data, 6);
    for (int i = 0; i < 6; ++i) {
        new_stack.pop();
    }
    assert(new_stack.isEmpty());
}

void pop_empty_test() {
    bool runtime_error_thrown = false;
    std::string error_message = "";
    DatumStack new_stack;
    try {
        new_stack.pop();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void top_empty_test() {
    bool runtime_error_thrown = false;
    std::string error_message = "";
    DatumStack new_stack;
    try {
        new_stack.top();
    }
    catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

void push_test() {
    Datum data[6] = {Datum(3), Datum(5), Datum(21), Datum(false), 
    Datum("heck naw"), Datum(true)};
    DatumStack new_stack(data, 6);
    for (int i = 0; i < 6; ++i) {
        new_stack.push(Datum(i));
    }
    assert(new_stack.top().getInt() == 5);
    assert(new_stack.size() == 12);
}

void push_empty_test() {
    DatumStack new_stack;
    for (int i = 0; i < 6; ++i) {
        new_stack.push(Datum(i));
    }
    assert(new_stack.top().getInt() == 5);
    assert(new_stack.size() == 6);
}

void clear_test() {
    Datum data[6] = {Datum(3), Datum(5), Datum(21), Datum(false), 
    Datum("heck naw"), Datum(true)};
    DatumStack new_stack(data, 6);
    for (int i = 0; i < 6; ++i) {
        new_stack.push(Datum(i));
    }
    new_stack.clear();
    assert(new_stack.isEmpty());
}

void clear_empty_test() {
    DatumStack new_stack;
    new_stack.clear();
    assert(new_stack.isEmpty());
}

void parser() {
    ifstream infile("parse_test.txt");
    string s = parseRString(infile);
    cout << s;
}

void rstring() {
    ifstream infile("parse_test.txt");
    string s = parseRString(infile);
    Datum new_datum = Datum(s);
    cout << new_datum.getRString();

}

void parse_empty() {
    string input = "}";
    std:istringstream iss(input);
    string s = parseRString(iss);
    cout << s;

}
/*
void num_test() {
    std::stringstream ss;
    string input = "10 20 -100 1000000 -21321 0";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(test_calc.stack.top().getInt() == 0);
    test_calc.drop();
    assert(test_calc.stack.top().getInt() == -21321);
    test_calc.drop();
    assert(test_calc.stack.top().getInt() == 1000000);
    test_calc.drop();
    assert(test_calc.stack.top().getInt() == -100);
    test_calc.drop();
    assert(test_calc.stack.top().getInt() == 20);
    test_calc.drop();
    assert(test_calc.stack.top().getInt() == 10);
}

void bool_test() {
    std::stringstream ss;
    string input = "#t #f #f";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(not test_calc.stack.top().getBool());
    test_calc.drop();
    assert(not test_calc.stack.top().getBool());
    test_calc.drop();
    assert(test_calc.stack.top().getBool());
}

void not_bool_test() {
    std::stringstream ss;
    string input = "#t #f #f not";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(test_calc.stack.top().getBool());
    test_calc.drop();
    test_calc.not_bool();
    assert(test_calc.stack.top().getBool());
    test_calc.drop();
    test_calc.not_bool();
    assert(not test_calc.stack.top().getBool());
}

void print_test() {
    std::stringstream ss;
    string input = "#t #f #f print drop print drop print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void print_clear_test() {
    std::stringstream ss;
    string input = "#t #f #f clear print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void print_clear_empty_test() {
    std::stringstream ss;
    string input = "clear print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void print_clear_and_input_test() {
    std::stringstream ss;
    string input = " 1 2 3 clear 123 print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void dup_test() {
    std::stringstream ss;
    string input = " 1 2 3 dup print drop print drop print drop dup print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void swap_int_test() {
    std::stringstream ss;
    string input = " 1 2 3 swap print drop print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void swap_bool_test() {
    std::stringstream ss;
    string input = " #t #f swap print drop print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void swap_rstring_test() {
    std::stringstream ss;
    string input = " { bottom }  { top } swap print drop print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void swap_different_type_test() {
    std::stringstream ss;
    string input = " { bottom } #f { top } 1 swap print drop print drop swap";
    input += " print drop print ";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void int_operations_test() {
    std::stringstream ss;
    string input = " 5 5 * -10 + 10 - 25 5 / mod 5 4 / +";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(test_calc.stack.top().getInt() == 1);
}

void bool_operations_test() {
    std::stringstream ss;
    string input = " 5 5 >= 4 3 > == 9 10 <= -1 0 < ==";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(test_calc.stack.top().getBool());
}

void rstring_comparison_test() {
    std::stringstream ss;
    string input = " { yes } { yes } == { YES } { yes } == print drop print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
    assert(test_calc.stack.top().getBool());
}

void not_int_operations_test() {
    std::stringstream ss;
    string input = " #t 5 * { } #f + { a } { s } / 2 #f - 2 2 mod { w } mod"
    input += " print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void not_bool_operations_test() {
    std::stringstream ss;
    string input = " #t 5 > { } #f < { a } { a } >= 2 #f <= print";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

void exec_test() {
    std::stringstream ss;
    string input = " { 12 12 * { 4 3 + } exec - print }";
    ss.str(input);
    RPNCalc test_calc;
    test_calc.commands(ss);
}

*/