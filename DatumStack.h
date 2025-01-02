/*
 *  DatumStack.h
 *  Daniel Jarka
 *  10/22/24
 *
 *  CS 15 Project 2: CalcYourLater
 *
 *  DatumStack is a class that represents a list of Datum elements which is
 *  implemented as a stack. The DatumStack can begin empty or can be
 *  initialized with an array of Datum elements. Beccause this class represents
 *  a stack, clients can only add and remove from the front of the list. This
 *  stack implementation uses the std::list library.
 * 
*/

#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__

#include <iostream>
#include <string>
#include <list>
#include "Datum.h"

using namespace std;

class DatumStack {
   public:
    DatumStack();
    DatumStack(Datum arr[], int size);

    Datum top();
    void pop();
    void push(const Datum &element);
    int size();
    void clear();
    bool isEmpty();
   private:
    std::list<Datum> datum_stack;

};

#endif