CXXFLAGS=-std=c++20 -Iincludes -Wall -Wextra -Werror -pedantic -O0 -gdwarf-4
CXX=clang++

clean:
	rm -f bin/*

exec: ./driver.cc ./team.cc ./employeee.cc ./team.hpp ./employeee.hpp 
	$(CXX) $(CXXFLAGS) ./driver.cc ./team.cc ./employeee.cc -o bin/exec


