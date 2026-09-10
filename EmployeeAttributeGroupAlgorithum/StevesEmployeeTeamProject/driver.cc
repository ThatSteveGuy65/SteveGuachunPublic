#include <fstream>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "groupRequirments.hpp"
#include "team.hpp"


int main(int argc, char* argv[]) {
  
  if (argc != 3) {
    std::cout << argv[0] << std::endl;
    return 1;
  }
  std::ifstream ifs{argv[1]};

  srand(time(nullptr));
  std::vector<Employee> everyone;  
  std::vector<Team> everyone_split; 
  std::string name;                  
  int tec_exp = 0;
  int com_exp = 0;
  bool seniorStaff = false;
  bool intern = false;
  
  int iterations = 0;
  
  while (ifs >> name >> tec_exp >> com_exp >> seniorStaff >> intern) {
    everyone.push_back({Employee(name, tec_exp, com_exp, seniorStaff, intern)});
  }
  everyone_split = PeopleSeperater(everyone);
  bool all_corect = AllTeamsFollowRules(everyone_split);
  while (!all_corect) {
    Switcher(everyone_split);
    iterations += 1;
    all_corect = AllTeamsFollowRules(everyone_split);

    if (iterations == kMaxIterations) {
      std::cout << "Group making not possible" << std::endl;
      return 1;
    }
  }
  std::ofstream output(argv[2]);
  for (const auto& group : everyone_split) {
    output << group << std::endl;
  }
  return 0;
}

