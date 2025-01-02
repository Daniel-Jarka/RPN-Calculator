###
### Makefile for CalcYouLater Project
###
### Author:  Daniel Jarka

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

## This rule lets the program execute with ./CalcYouLater
CalcYouLater: main.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(LDFLAGS) -o $@ $^
	
## Rules for building an executable from Datum+vector_example.cpp
## This is useful in seeing the behavior of Datum::toString()
Datum+vector_example.o: Datum+vector_example.cpp Datum.h

Datum+vector_example: Datum+vector_example.o Datum.o
	${CXX} ${LDFLAGS} -o $@ $^
## This rule builds DatumStack.o
DatumStack.o: DatumStack.cpp DatumStack.h Datum.h
	${CXX} ${LDFLAGS} -c DatumStack.cpp
## This rule builds parser.o
parser.o: parser.cpp parser.h
	${CXX} ${LDFLAGS} -c parser.cpp
## This rule builds main.o
main.o: main.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	${CXX} ${LDFLAGS} -c main.cpp
## This rule builds RPNCalc.o
RPNCalc.o: RPNCalc.cpp RPNCalc.h DatumStack.h Datum.h parser.h
	${CXX} ${LDFLAGS} -c RPNCalc.cpp

# The below rule will be used by unit_test.
unit_test: unit_test_driver.o RPNCalc.o DatumStack.o Datum.o parser.o
	$(CXX) $(CXXFLAGS) $^

##
## Here is a special rule that removes all .o files besides the provided one
## (Datum.o), all temporary files (ending with ~), and 
## a.out produced by running unit_test. First, we find all .o files 
## that are not provided files, then we run rm -f on each found file 
## using the -exec find flag. Second, we delete the temporary files
## and a.out. @ is used to suppress stdout.
## 
## You do not need to modify or further comment this rule!
##
clean:
	@find . -type f \( \
	-name '*.o' ! -name 'Datum.o' \
	\) -exec rm -f {} \;
	@rm -f *~ a.out

##
## Here is a rule for compiling .cyl files for use in your testing
##
%.cylc:  %.cyl
	./cylc $^
