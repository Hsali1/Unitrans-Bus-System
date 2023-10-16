
#ifndef _PERSON_H_
#define _PERSON_H_

// Person.h
#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

class Person
{
 private:
  std::string name;
  std::string occupation;
  
public:
  Person(std::string, std::string);
  Person();
  bool operator==(Person& aPerson);
  std::string getName();
  void setName(std::string);
  std::string getOccupation();
  void setOccupation(std::string);
  void dump();
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value);
};

#endif  /* _PERSON_H_ */
