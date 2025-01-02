#ifndef __PARSER_H 
#define __PARSER_H

/*
 *  parser.h
 *  Daniel Jarka
 *  10/12/24
 *
 *  CS 15 Project 2: CalcYouLater
 *
 *  parser is a helper class that is helpful for
 *  correctly formatting inputs in a way that the 
 *  RPNCalc can read.
 */
#include <string>
#include <istream>

std::string parseRString(std::istream &input);

#endif 
