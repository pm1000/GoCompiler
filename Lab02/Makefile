####################################################################
# This Makefile started out as a copy of the one in the flex manual.
# Cf. http://flex.sourceforge.net/manual/Makefiles-and-Flex.html#Makefiles-and-Flex
#
# It replaces the amazingly complex Makefile that comes with the C++calc example
# found in the Bison manual.
#
# This is Verison 0.3 of the Makefile (as of 28 April 2020).
#
####################################################################
#      Make "Variables" used here
#      Cf. http://www.makelinux.net/make3/make3-CHP-2-SECT-2.html
# $@ = The filename representing the target.
# $< = The filename of the first prerequisite.
# $* = The stem of the filename of the target (i.e. without .o, .cpp...)
# $^ = The names of all the prerequisites, with spaces between them.
####################################################################

# Uncomment only one of the next two lines (choose your c++ compiler)
CC=g++
# CC=clang++

LEX=flex
YACC=bison
YFLAGS=-v -d
# Where   -d is important to force creation of header files (*.hh)
# but -v  is not so important. It forces creation of the file
#         parser.output which is nice to have (but not 
#         strictly necessary).

project : scanner.o parser.o driver.o TreeNode.o main.o
	$(CC) -o $@ $^

main.o: parser.hh parser.cc scanner.cc

%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

%.o: %.cc
	$(CC) $(CFLAGS) -o $@ -c $<

scanner.cc: scanner.ll
	$(LEX) $(LFLAGS) -o scanner.cc scanner.ll

parser.cc parser.hh: parser.yy
	$(YACC) $(YFLAGS) -o parser.cc parser.yy

clean:
	$(RM) *~ *.o  calc++  scanner.cc parser.cc  scanner.hh parser.hh parser.output location.hh stack.hh position.hh

tests: test.sh project
	./test.sh

# Alternative (directly on the command line):
#   ./test.sh 2>&1 | less
# (to see the output before it scrolls off your screen).
