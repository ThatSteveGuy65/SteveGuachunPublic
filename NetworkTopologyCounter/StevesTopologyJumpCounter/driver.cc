#include <iostream>
#include "Comp_net.hpp"

int main() {

Network Example("devices.csv", "communication_link.csv");



std::cout << "helloworld" << std::endl;

 
                           
std::cout <<  Example.CountTopology() << std::endl;


std::cout << Example.ShortestPathLenght("ComputerA", "ComputerB") << std::endl;


return 0;
}




