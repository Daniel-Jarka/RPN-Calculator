/*
 *  DatumStack.cpp
 *  Daniel Jarka
 *  10/22/24
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  This file contains the implementation of the
 *  DatumStack class.
*/

#include "DatumStack.h"
#include <iostream>
#include <string>

/*
 * name:      Default Constructor
 * purpose:   Default constructor of DatumStack instance.
 * arguments: none
 * returns:   none
 * effects:   initializes an empty stack.
 */
DatumStack::DatumStack() {
}

/*
 * name:      Parametized Constructor
 * purpose:   Accepts an array of Datum elements and initializes 
 *            a stack based on these elements.
 * arguments: An array of Datum elements and an integer that represents
 *            its size.
 * returns:   none
 * effects:   initializes a stack.
 */
DatumStack::DatumStack(Datum arr[], int size) {
    for (int i = 0; i < size; ++i) {
        datum_stack.push_front(arr[i]);
    }
}

/*
 * name:      top
 * purpose:   returns the first element in the stack.
 * arguments: none
 * returns:   the first element in the stack.
 * effects:   none
 */
Datum DatumStack::top() {
    if(datum_stack.empty()) {
        throw runtime_error("empty_stack");
    }
    return datum_stack.front();
}

/*
 * name:      pop
 * purpose:   removes the first element from the stack.
 * arguments: none
 * returns:   removes first element from the stack.
 * effects:   decreases the stack by one.
 */
void DatumStack::pop() {
    if(datum_stack.empty()) {
        throw runtime_error("empty_stack");
    }
    datum_stack.pop_front();
}

/*
 * name:      push
 * purpose:   pushes the given element onto the front of the stack.
 * arguments: a Datum element to push onto the stack.
 * returns:   none
 * effects:   increases the stack by one
 */
void DatumStack::push(const Datum &element) {
    datum_stack.push_front(element);
}

/*
 * name:      size
 * purpose:   returns the size of the stack
 * arguments: none
 * returns:   the size of the stack
 * effects:   none
 */
int DatumStack::size(){
    return datum_stack.size();
}

/*
 * name:      clear
 * purpose:   turns the current instance into an empty stack
 * arguments: none
 * returns:   none
 * effects:   makes the stack empty
 */    
void DatumStack::clear(){
    datum_stack.clear();
}

/*
 * name:      empty
 * purpose:   checks if stack is empty
 * arguments: none
 * returns:   true if stack is empty, false otherwise
 * effects:   none
 */    
bool DatumStack::isEmpty() {
    return datum_stack.empty();
}