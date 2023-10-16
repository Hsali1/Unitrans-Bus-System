#include "JhTime.h"

JhTime::JhTime
(void)
{
  this->day = "";
  this->date = "";
  this->month = "";
  this->year = "";
  this->time = "";
}

JhTime::JhTime(std::string day, std::string date, std::string month, std::string year, std::string time)
{
  this->day = day;
  this->date = date;
  this->month = month;
  this->year = year;
  this->time = time;
}

void JhTime::dump
(void)
{
  std::cout << "[Thing] dump-begin" << std::endl;
  std::cout << "Day               = " << this->day << std::endl;
  std::cout << "Date              = " << this->day << std::endl;
  std::cout << "Month             = " << this->month << std::endl;
  std::cout << "Year              = " << this->year << std::endl;
  std::cout << "Time              = " << this->time << std::endl;
  std::cout << "[Thing] dump-end" << std::endl;
  return;
}

Json::Value
JhTime::dump2JSON
()
{
  Json::Value result;
  if (this->day != "")
    {
      result["day"] = this->day;
    }

  if (this->date != "")
    {
      result["date"] = this->date;
    }

  if (this->month != "")
    {
      result["month"] = this->month;
    }

  if (this->year != "")
    {
      result["year"] = this->year;
    }

  if (this->time != "")
    {
      result["time"] = this->time;
    }

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
    return result;
}

bool
JhTime::JSON2Object
(Json::Value arg_jv)
{

  if ((arg_jv.isNull() == true))
    {
      return false;
    }

  // Condition 3: Incorrect JSON structure
  if (!arg_jv.isObject())
  {
    throw ecs36b_Exception("Input JSON is not an object");
    return false;
  }

  // Condition 1: Missing essential key-value pairs
  if (!arg_jv.isMember("day"))
  {
    throw ecs36b_Exception("Missing day");
  }
  if (!arg_jv.isMember("date"))
  {
    throw ecs36b_Exception("Missing date");
  }
  if (!arg_jv.isMember("month"))
  {
    throw ecs36b_Exception("Missing month");
  }
  if (!arg_jv.isMember("year"))
  {
    throw ecs36b_Exception("Missing year");
  }
  if (!arg_jv.isMember("time"))
  {
    throw ecs36b_Exception("Missing time");
  }

  // Condition 2: Unexpected/mismatched value type
  if (!arg_jv["day"].isString())
  {
    throw ecs36b_Exception("day must be a string");
  }
  if (!arg_jv["date"].isString())
  {
    throw ecs36b_Exception("date must be a string");
  }
  if (!arg_jv["month"].isString())
  {
    throw ecs36b_Exception("month must be a string");
  }
  if (!arg_jv["year"].isString())
  {
    throw ecs36b_Exception("year must be a string");
  }
  if (!arg_jv["time"].isString())
  {
    throw ecs36b_Exception("time must be a string");
  }

  // Condition 4: Critical hidden detected
  if (arg_jv.isMember("hidden") && arg_jv["hidden"].isString())
  {
    std::string hiddenValue = arg_jv["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP")
    {
      throw ecs36b_Exception("A Critical Hidden detected");
    }
  }

  if (((arg_jv["day"]).isNull() == true) ||
      ((arg_jv["day"]).isString() != true) ||
      ((arg_jv["date"]).isNull() == true) ||
      ((arg_jv["date"]).isString() != true) ||
      ((arg_jv["month"]).isNull() == true) ||
      ((arg_jv["month"]).isString() != true) ||
      ((arg_jv["year"]).isNull() == true) ||
      ((arg_jv["year"]).isString() != true) ||
      ((arg_jv["time"]).isNull() == true) ||
      ((arg_jv["time"]).isString() != true))
    {
      return false;
    }

  this->day = (arg_jv["day"]).asString();
  this->date = (arg_jv["date"]).asString();
  this->month = (arg_jv["month"]).asString();
  this->year = (arg_jv["year"]).asString();
  this->time = (arg_jv["time"]).asString();
  
  return true;
}
