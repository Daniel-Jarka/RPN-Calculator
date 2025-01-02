/******************************************************************************
* Project 2: CalcYouLater
* CS 15
* README
* Author: Daniel Jarka djarka01
******************************************************************************/

B. Program Purpose:

     This program is designed to function as a reverse polish notation
     calculator. It works by accepting integer, boolean, or rstring inputs
     that are stored in a stack and are then operated on in order of whichever
     element is on top of the stack. As a calculator, it can perform all
     basic integer operations, but it can also perform boolean comparisons.
     Additionally, inputs can be stored inside rstrings, which are specially
     formatted strings that contain commands for the calculator to execute.
     The client has essentially no access to the underlying logic that runs
     the calculator. In this way, the client can only interact with the program
     through the terminal by entering commands. The calculator has been
     implemented in such a way that it should not crash from malformed
     inputs. It is also possible to redirect file input such that the program
     reads that input as if it were through std::cin.

C. Acknowledgements: 

    I consulted this page https://cplusplus.com/reference/string/string/erase/
    to learn about how the .erase() function works.

D. Files: 

     parser.cpp:
          Implementation of parser class. Used to correctly read and format
          rstrings for the RPNCalc.

     parser.h:
          Interface of parser class.

     DatumStack.cpp:
          Implementation of DatumStack class. Used to represent the stack
          that will store all of the important information used for the RPNCalc

     DatumStack.h:
          Interface of DatumStack.

     RPNCalc.cpp: 
          Implementation of RPNCalc class. Used to represent the calculator
          that will accept commands from the client.

     RPNCalc.h:
          Interface of RPNCalc.

     main.cpp:
          Driver file which can be interacted with by the user to create an
          instance of a RPNCalc.

     unit_test.h:
          A unit testing file for the DatumStack class and the parser class.
          Functions belonging to the RPNCalc class were also tested, but
          these tests are commented out since the members are private.

     Makefile:
          File used to run the "make" command which compiles and builds
          the program.

     operations.cylc:
          Input file used to test basic integer and boolean operations.

     complex.cylc:
          Input file used to test some complex nested commands and a few 
          edge cases like divison by 0 and non rstring exec.
     
     bad_inputs.cylc:
          Input file used to test edge cases when incorrectly running exec
          and if, as well as when incorrectly pushing booleans on the stack.

     empty.cylc:
          Empty file used to test program behavior when reading an empty file.

     file_test.cylc:
          Input file used to test reading a different file while ifstream is 
          active.

     try_quit.cylc:
          Input file primarily used to test quitting in the middle of a file.

     parse_test.txt:
          Input file used to test messy input and nested rstrings for parser.

     README: 
          This file.

E. Compile/run:
     - Compile using
            make CalcYouLater
     - run executable with
            ./CalcYouLater

F. Architechtural Overview:

     The backbone of this implementation relies on the Datum and DatumStack
     classes. Each datum element is initialized with either an integer,
     boolean, or an rstring. The underlying features of this class were not
     programmed by myself, but the DatumStack I created is a stack that stores
     Datum elements in a std::list. This class functions exactly like a stack,
     so the program can only pop elements from the top of the stack and add 
     elements to the top of the stack. It can also return the element at the
     top of the stack without popping it.
     
     The RPNCalc class then uses a single private instance of a DatumStack to 
     keep track of all the elements passed to the calculator. In this way,
     whenever the calculator needs to push or remove elements from the stack,
     it can use the features of DatumStack to simplifiy this process. 
     Reverse Polish Notation lends itself to have high compatibility with
     a stack, so the process of storing elements on a DatumStack is very useful
     for performing the computations and other functions that are a part of
     RPNCalc's implementation.

G. Data Structure:

     The ADT here is a list, which is an ordered sequence of elements.
     There is one primary implementation of the list to run this program.

     The main data structure is a stack, but there is an underlying linked
     list implementation for this program's internal logic. The only role 
     for linked lists is in the DatumStack class, where std::list is used
     to simplify the process of programming the functionality of a stack.
     A vector would have worked just as well, but I decided to use std::list
     because only the top of the stack is manipulated when performing
     functions, and a linked list limits access to only its two ends.  
     
     Creating a properly functioning stack is important for the RPNCalc because
     a stack is an ordered sequence of elements where items can only be added
     to or removed from one end, which is usually called the "top."
     The features of a stack make it a useful data structure for RPN,
     since RPN performs an operation on the two closest integers to the
     left of the operator. In stack terms, an operation will be performed
     on the two closest integers "below" the operator. Since this 
     implementation works with booleans and rstrings as well, the stack
     is a useful tool for keeping track of the current operation, as well
     as what operation(s) should be performed next. Some other examples
     where a stack is used are less computational than an outright calculator,
     but are still pretty common. The problem discussed in lecture is one such
     example where keeping track of "balanced braces" can be accomplished
     by using a stack to keep track of open and closed braces. A stack
     can also be used to keep track of the back and forward buttons on
     websites. If you hit the back button, the page you move to is removed
     from the "back" stack and added to the "forward" stack and vice versa!

     Because stacks are more "restricted" lists, they are very handy for
     specific problems. Additionally, since there are very few operations
     you can perform to a stack, namely adding to the front and removing from
     the front, these operations are very fast. Memory is of relatively little
     concern as well since in this implementation the stack runs on an 
     underlying std::list. Since the stack is being used for a calculator,
     those operations are performed quickly and in the right order!

     While being a restricted list is an advantage, it can also be
     a disadvantage for a program that requires direct access to any
     element in the list. Stacks are useful for very specific applications,
     like this calculator. Other programs that benefit from LIFO representation
     will be very successful in using a stack implementation. In any other
     case, though, they are difficult to work with. As soon as a program
     needs to perform an operation that does more to its list than add
     and remove from the front, a stack will fall short.

     Algorithmically, there aren't any particularly complicated functions
     for stacks. There really is just push(element) and pop(), both of 
     which are O(1), since the program will always know where the top
     of the stack is. In RPNCalc, however, exec() and file() can vary.
     This is largely dependent on the number and type of inputs in the 
     rstring/file, but execution time can be quite long if there is a very 
     large number of inputs. Of course this is unlikely, but I encounered some
     interesting features of n_fibs. After about 22 or so iterations, each 
     execution takes significantly longer than the last, which is largely due
     to the number of recursive calls that reference other recursive calls in 
     this file. In this way, the time complexity can really blow up based on 
     the number of embedded and recursive calls in exec() or file(). The worst 
     case scenario is quite bad, but I think the average user will encounter 
     nothing worse than O(n). In any case, the O complexity of this program is
     quite fast when ignoring some of the shortcomings of the exec() and file()
     calls!


H. Testing:

     1. DatumStack and Parser unit_test
     
     I used the unit_test framework to test the DatumStack and parser
     classes. I ran unit_tests to account for edge cases on empty stacks in
     DatumStack and tested for nested and empty strings in parser. I used a 
     file to test the nested parser strings.

     2. RPNCalc unit_test
     
     I also unit_tested all of the smaller level commands in RPNCalc to test
     the base functionality of user commands. I tested adding integers,
     booleans, and rstrings, as well as integer operations, boolean operations,
     print, drop, swap, not, and dup. I tested for edge cases as well on
     empty stacks and type mismatches where these cases were relevant. I made
     sure the program's behavior was correct when a command required popping
     one or more elements from the stack on an empty or not large enough stack.
     I accounted for popping elements from the stack when performing operations
     on the wrong data type. I also accounted for division by 0.

     3. RPNCalc diff test

     I used several testing files I created to compare my program's edge and
     general case behavior with the reference implementation. I wrote the
     specific details of what each testing file specfically tests for above,
     but in general I checked cases for an empty file, incorrect inputs,
     quitting in the middle of a file, and some complex operations. 
     I additionally compared outputs with the reference from the provided
     .cyl files for this assignment. I compared the outputs by running diff
     tests and found that my program passed all the edge cases I could possibly
     think of.


I. Time Spent: 

     15 hours
