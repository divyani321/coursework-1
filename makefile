CXX = g++
CXXFLAGS = -g -Wall -Wextra -Wpedantic
.PHONY : all
all : program

program : my_code.cpp 
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY : clean
clean :
	$(RM) *.o
	$(RM) program
