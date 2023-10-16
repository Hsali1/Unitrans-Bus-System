#ifndef _JHTIME_H_
#define _JHTIME_H_

// Time.h
#include "ecs36b_Common.h"
#include "ecs36b_Exception.h"

class JhTime
{
 private:
 protected:
 public:
  
  std::string day;
  std::string date;
  std::string month;
  std::string year;
  std::string time;
  JhTime(void);
  JhTime(std::string, std::string, std::string, std::string, std::string);
  virtual void dump();
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value);
};

#endif /* _JHTIME_H_ */
