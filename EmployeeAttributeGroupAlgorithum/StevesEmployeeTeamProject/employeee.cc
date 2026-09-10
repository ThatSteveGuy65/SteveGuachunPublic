#include "employeee.hpp"
#include <string>

std::string Employee::GetName() const { return name_; }

int Employee::GetTecExperiance() const { return TecExperiance_; }

int Employee::GetCommunicationSkills() const { return CommunicationSkills_; }

bool Employee::IsSeniorStaff() const { return IsSeniorStaff_; }

bool Employee::IsIntern() const { return IsIntern_; }

Employee::Employee(const std::string& name,
                     int TecExperiance,
                     int CommunicationSkills,
                     bool IsSeniorStaff,
                     bool intern):
    name_(name),
    TecExperiance_(TecExperiance),
    CommunicationSkills_(CommunicationSkills),
    IsSeniorStaff_(IsSeniorStaff), IsIntern_(intern) {
  if (CommunicationSkills > kMaxComSkill) {
    CommunicationSkills_ = kMaxComSkill;
  }
  if (CommunicationSkills < kMinComSkill) {
    CommunicationSkills_ = kMinComSkill;
  }
  if (TecExperiance < kMinTecExp) {
    TecExperiance_ = kMinTecExp;
  }
  if (TecExperiance > kMaxTecExp) {
    TecExperiance_ = kMaxTecExp;
  }
}

void EmployeeSwitch(Employee& one, Employee& two) {
  Employee temp = one;
  one = two;
  two = temp;
}