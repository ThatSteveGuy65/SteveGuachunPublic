#ifndef GROUP_HPP
#define GROUP_HPP

#include <ostream>
#include <vector>
#include "employeee.hpp"

class Team {
public:
  Team();

  void Update();

  void AddEmployee(const Employee& vol);

  double GetAvgTecExperiance() const;

  double GetAvgCommunicationSkills() const;

  int GetSeniorStaff() const;

  int GetInternAmount() const;

  friend std::ostream& operator<<(std::ostream& os, const Team& team);

  Employee& GetRandomEmployee();

private:
  double AvgTecExp_ = 0;
  int SeniorStaffAmount_ = 0;
  double AvgCommunicationExp_ = 0;
  int internAmount_ = 0;

  std::vector<Employee> list_;
};

std::ostream& operator<<(std::ostream& os, const Team& team);

bool AllTeamsFollowRules(std::vector<Team>& team);

bool FollowsRules(Team& team);

void Switcher(std::vector<Team>& team);

std::vector<Team> PeopleSeperater(std::vector<Employee> employee);
#endif
