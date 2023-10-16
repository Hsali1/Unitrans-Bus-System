
#ifndef _RECORD_H_
#define _RECORD_H_

// Record.h

#include "Person.h"
#include "Thing.h"
#include "GPS.h"
#include "JvTime.h"
#include "JhTime.h"
#include "ecs36b_Exception.h"

#include "ecs36b_Common.h"

class Record
{
 private:
  Person* person1{nullptr};
  Person* person2{nullptr};
  Person* person3{nullptr};
  Thing what;
  GPS_DD where;
  JhTime when;
  std::string hidden = "";
  
public:
  //Record(Person, Thing, GPS_DD, JvTime);
  Record(Person, Thing, GPS_DD, JhTime);
  Record(Person, Person, Thing, GPS_DD, JhTime);
  Record(Person, Person, Person, Thing, GPS_DD, JhTime);
  Record();
  ~Record();
  //void setWho(Person);
  void setWhat(Thing);
  void setWhere(GPS_DD);
  void setWhen(JhTime);
  virtual Json::Value dump2JSON();
  virtual bool JSON2Object(const Json::Value&);
};

#endif  /* _RECORD_H_ */
