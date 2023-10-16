
#ifndef _GPS_H_
#define _GPS_H_

// GPS.h

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <cstdlib>
#include "ecs36b_Exception.h"

#include "ecs36b_Common.h"

using namespace std;

class GPS_DD
{
 private:
  double latitude;
  double longitude;
  std::string name;
 public:
  explicit GPS_DD();
  explicit GPS_DD(double, double);
  explicit GPS_DD(std::string);
  explicit GPS_DD(double, double, std::string);
  double getLatitude();
  double getLongitude();
  void setLatitude(double);
  void setLongitude(double);
  void setName(std::string);
  std::string getName();
  double distance(GPS_DD);
  Json::Value dump2JSON();
  virtual bool JSON2Object(Json::Value); // Hassan hw4 change
};

#endif /* _GPS_H_ */
