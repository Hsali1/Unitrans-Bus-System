
#include "Person.h"

Person::Person(std::string arg_name, std::string occupation)
{
  this->name = arg_name;
  this->occupation = occupation;
}

Person::Person()
{
  this->name = "";
  this->occupation = "";
}

std::string
Person::getName()
{
  return this->name;
}

void Person::setName(std::string name1)
{
  this->name = name1;
}

std::string
Person::getOccupation()
{
  return this->occupation;
}

void Person::setOccupation(std::string occupation1)
{
  this->occupation = occupation1;
}

// function prototype
bool
Person::operator==
(Person& aPerson)
{

  return (this->name == aPerson.getName());
  
}

void Person::dump
(void)
{
  std::cout << "[Person] dump-begin" << std::endl;
  std::cout << "name                  = " << this->name << std::endl;
  std::cout << "occupation            = " << this->occupation << std::endl;
  std::cout << "[Person] dump-end" << std::endl;
  return;
}

Json::Value
Person::dump2JSON
()
{
  Json::Value result;
  if (this->name != "")
    {
      result["name"] = this->name;
    }

  if (this->occupation != "")
    {
      result["occupation"] = this->occupation;
    }

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
    return result;
}


bool Person::JSON2Object(Json::Value arg_jv)
{
  if ((arg_jv.isNull() == true))
  {
    return false;
  }

  // Condition 3: Incorrect JSON structure
  if (arg_jv.isObject() != true)
  {
    throw ecs36b_Exception("Input JSON is not an object");
    return false;
  }

  // Condition 1: Missing essential key-value pairs
  if (!arg_jv.isMember("name")) {
    throw ecs36b_Exception("Missing name");
  }
  if (!arg_jv.isMember("occupation")) {
    throw ecs36b_Exception("Missing occupation");
  }

  // Condition 2: Unexpected/mismatched value type
  if (!arg_jv["name"].isString()) {
    throw ecs36b_Exception("name must be a string");
  }
  if (!arg_jv["occupation"].isString()) {
    throw ecs36b_Exception("occupation must be a string");
  }

  // Condition 4: Critical hidden detected
  if (arg_jv.isMember("hidden") && arg_jv["hidden"].isString()) {
    std::string hiddenValue = arg_jv["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP") {
      throw ecs36b_Exception("A Critical Hidden detected");
    }
  }

  // we allow GPS_DD to be modified (for mobility)
  this->name = arg_jv["name"].asString();
  this->occupation = arg_jv["occupation"].asString();

  return true;
}
