#ifndef EMPLOYEE_HPP
#define EMPLOYEE_HPP
#include <string>

const int kMinTecExp = 0;
const int kMinComSkill = 0;
const int kMaxTecExp = 10;
const int kMaxComSkill = 10;

class Employee {
public:
  Employee(const std::string& name,
            int tec_experience,
            int communication_skills,
            bool senior_staff,
            bool intern);

  std::string GetName() const;
  int GetTecExperiance() const;
  int GetCommunicationSkills() const;
  bool IsSeniorStaff() const;
  bool IsIntern() const;

private:
  std::string name_;
  int TecExperiance_;
  int CommunicationSkills_;
  bool IsSeniorStaff_;
  bool IsIntern_;
};

void EmployeeSwitch(Employee& one, Employee& two);

#endif