#include "Thing.h"

Thing::Thing
(void)
{
  this->name = "";
  this->model = "";  
}

Thing::Thing
(std::string name, std::string model, Person arg_owner)
{
  this->name = name;
  this->model = model;
  this->owner = arg_owner;
}

void Thing::dump
(void)
{
  std::cout << "[Thing] dump-begin" << std::endl;
  std::cout << "model          = " << this->model << std::endl;
  std::cout << "name          = " << this->name << std::endl;
  std::cout << "[Thing] dump-end" << std::endl;
  return;
}

Json::Value
Thing::dump2JSON
()
{
  Json::Value result;
  if (this->name != "")
    {
      result["name"] = this->name;
    }

  if (this->model != "")
    {
      result["model"] = this->model;
    }

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
    return result;
}

bool Thing::JSON2Object(Json::Value arg_jv)
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
  if (!arg_jv.isMember("model")) {
    throw ecs36b_Exception("Missing model");
  }

  // Condition 2: Unexpected/mismatched value type
  if (!arg_jv["name"].isString()) {
    throw ecs36b_Exception("name must be a string");
  }
  if (!arg_jv["model"].isString()) {
    throw ecs36b_Exception("model must be a string");
  }

  // Condition 4: Critical hidden detected
  if (arg_jv.isMember("hidden") && arg_jv["hidden"].isString()) {
    std::string hiddenValue = arg_jv["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP") {
      throw ecs36b_Exception("A Critical Hidden detected");
    }
  }

  this->name = arg_jv["name"].asString();
  this->model = arg_jv["model"].asString();

  return true;
}


