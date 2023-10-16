
#ifndef _THING_H_
#define _THING_H_

// Thing.h
#include "Person.h"
#include "ecs36b_Exception.h"

class Thing
{
 private:
 protected:
 public:
  
  std::string name;
  std::string model;
  Person      owner;
  Thing(void);
  Thing(std::string name, std::string model, Person arg_owner);
  virtual void dump();
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value); // Hassan hw4 change
};

#endif /* _THING_H_ */
