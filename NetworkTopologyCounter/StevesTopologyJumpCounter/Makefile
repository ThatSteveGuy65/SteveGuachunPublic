CXXFLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -pedantic -O0 -gdwarf-4
CXX=clang++

clean:
	rm -f bin/*

exec: ./driver.cc  ./Comp_net.hpp ./Comp_net.cc 
	$(CXX) $(CXXFLAGS) ./driver.cc ./Comp_net.cc  -o bin/exec