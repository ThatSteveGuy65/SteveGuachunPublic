#include "team.hpp"

#include <iostream>
#include <utility>
#include <vector>

#include "groupRequirments.hpp"
#include "employeee.hpp"

const int team_number = 10;

Team::Team() = default;

void Team::Update() {
  double totalxp = 0;
  double totalpeople = 0;

  for (unsigned int i = 0; i < list_.size(); ++i) {
    totalxp += list_.at(i).GetTecExperiance();
    totalpeople += 1;
  }
  double output = totalxp / totalpeople;
  AvgTecExp_ = output;

  /////////////split////////

  totalxp = 0;
  totalpeople = 0;

  for (unsigned int i = 0; i < list_.size(); ++i) {
    totalxp += list_.at(i).GetCommunicationSkills();
    totalpeople += 1;
  }
  output = totalxp / totalpeople;
  AvgCommunicationExp_ = output;

int SeniorStaffAmount = 0;
  for (unsigned int i = 0; i < list_.size(); ++i) {
    if (list_.at(i).IsSeniorStaff()) {
      SeniorStaffAmount += 1;
    }
  }
  SeniorStaffAmount_ = SeniorStaffAmount;

int InternNum = 0;
  for (unsigned int i = 0; i < list_.size(); ++i) {
    if (list_.at(i).IsIntern()) {
      InternNum += 1;
    }
  }
  internAmount_ = InternNum;

  





}

void Team::AddEmployee(const Employee& vol) {
  list_.push_back(vol);
  Update();
}

double Team::GetAvgTecExperiance() const { return AvgTecExp_; }
double Team::GetAvgCommunicationSkills() const { return AvgCommunicationExp_; }
int Team::GetSeniorStaff() const { return SeniorStaffAmount_; }
int Team::GetInternAmount() const { return internAmount_; }

Employee& Team::GetRandomEmployee() {
  unsigned long v1 = rand() % list_.size();
  return list_.at(v1);
}

std::ostream& operator<<(std::ostream& os, const Team& team) {
  os << "Get Avg Tech Experiance  :  " << team.GetAvgTecExperiance()
     << ", Get Avg Comminication Experiance  :  " << team.GetAvgCommunicationSkills()
     << ", get senior staff amount :  " << team.GetSeniorStaff() 
     << ", get intern staff amount : " << team.GetInternAmount() << '\n';
  for (unsigned int i = 0; i < team.list_.size(); ++i) {
    os << team.list_.at(i).GetName();
    os << '\n';
  }
  os << '\n';
  return os;
}

bool FollowsRules(Team& a) {
  return a.GetAvgTecExperiance() >= kMinTecExp &&
         a.GetAvgCommunicationSkills() >= kMinAvgCommunicatinExp &&
         a.GetSeniorStaff() >= kSeniorStaff &&
         a.GetInternAmount() >= kInternAmount;
}

bool AllTeamsFollowRules(std::vector<Team>& a) {
  for (unsigned int i = 0; i < a.size(); ++i) {
    if (!FollowsRules(a.at(i))) {
      return false;
    }
  }
  return true;
}

void Switcher(std::vector<Team>& z) {
  unsigned long i = rand() % z.size();
  unsigned long v1 = rand() % z.size();
  while (v1 == i) {
    v1 = rand() % z.size();
  }
  EmployeeSwitch(z.at(i).GetRandomEmployee(), z.at(v1).GetRandomEmployee());
  z.at(i).Update();
  z.at(v1).Update();
}

std::vector<Team> PeopleSeperater(std::vector<Employee> k) {
  std::vector<Team> output;
  for (unsigned int i = 0; i + 9 < k.size(); i += team_number) {
    Team a;
    for (int t = 0; t < team_number; ++t) {
      a.AddEmployee(k.at(i + t));
    }
    output.push_back(a);
  }
  return output;
}
