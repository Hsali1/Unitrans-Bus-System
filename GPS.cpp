
#include "GPS.h"

GPS_DD::GPS_DD()
{
  this->latitude = 0.0;
  this->longitude = 0.0;
  this->name = "";
}

GPS_DD::GPS_DD(std::string name)
{
  this->name = name;
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longitude)
{
  float latitude = 0.3;
  // latitude = arg_latitude;       // option 1
  this->latitude = arg_latitude;    // option 2
  this->longitude = arg_longitude;
}

GPS_DD::GPS_DD(double arg_latitude, double arg_longitude, std::string name)
{
  float latitude = 0.3;
  // latitude = arg_latitude;       // option 1
  this->latitude = arg_latitude;    // option 2
  this->longitude = arg_longitude;
  this->name = name;
}

double 
GPS_DD::getLatitude()
{
  return this->latitude;
}
 
void 
GPS_DD::setLatitude(double x)
{
  this->latitude = x;
}

void 
GPS_DD::setName(std::string x)
{
  this->name = x;
}

double
GPS_DD::getLongitude()
{
  return this->longitude;
}

void 
GPS_DD::setLongitude(double x)
{
  this->longitude = x;
}

std::string
GPS_DD::getName()
{
  return this->name;
}

// DD distance calculation

/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::                                                                         :*/
/*::  This routine calculates the distance between two points (given the     :*/
/*::  latitude/longitude of those points). It is being used to calculate     :*/
/*::  the distance between two locations using GeoDataSource(TM) products.   :*/
/*::                                                                         :*/
/*::  Definitions:                                                           :*/
/*::    South latitudes are negative, east longitudes are positive           :*/
/*::                                                                         :*/
/*::  Passed to function:                                                    :*/
/*::    lat1, lon1 = Latitude and Longitude of point 1 (in decimal degrees)  :*/
/*::    lat2, lon2 = Latitude and Longitude of point 2 (in decimal degrees)  :*/
/*::    unit = the unit you desire for results                               :*/
/*::           where: 'M' is statute miles (default)                         :*/
/*::                  'K' is kilometers                                      :*/
/*::                  'N' is nautical miles                                  :*/
/*::  Worldwide cities and other features databases with latitude longitude  :*/
/*::  are available at https://www.geodatasource.com                         :*/
/*::                                                                         :*/
/*::  For enquiries, please contact sales@geodatasource.com                  :*/
/*::                                                                         :*/
/*::  Official Web site: https://www.geodatasource.com                       :*/
/*::                                                                         :*/
/*::           GeoDataSource.com (C) All Rights Reserved 2018                :*/
/*::                                                                         :*/
/*::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/

#include <math.h>
#define pi 3.14159265358979323846

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  Function prototypes                                           :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double);
double rad2deg(double);

double GeoDataSource_distance(double lat1, double lon1, double lat2, double lon2, char unit) 
{
  double theta, dist;
  if ((lat1 == lat2) && (lon1 == lon2))
    {
      return 0;
    }
  else
    {
      theta = lon1 - lon2;
      dist = sin(deg2rad(lat1)) * sin(deg2rad(lat2)) + cos(deg2rad(lat1)) * cos(deg2rad(lat2)) * cos(deg2rad(theta));
      dist = acos(dist);
      dist = rad2deg(dist);
      dist = dist * 60 * 1.1515;
      switch(unit)
	{
	case 'M':
	  break;
	case 'K':
	  dist = dist * 1.609344;
	  break;
	case 'N':
	  dist = dist * 0.8684;
	  break;
	}
      return (dist);
    }
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts decimal degrees to radians             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double deg2rad(double deg)
{
  return (deg * pi / 180);
}

/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
/*::  This function converts radians to decimal degrees             :*/
/*:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::*/
double rad2deg(double rad)
{
  return (rad * 180 / pi);
}

double
GPS_DD::distance
(GPS_DD another)
{
  return GeoDataSource_distance(this->latitude, this->longitude,
				another.getLatitude(), another.getLongitude(), 'M');
}

Json::Value
GPS_DD::dump2JSON
()
{
  Json::Value result;
  if (this->latitude != 0.0)
    {
      result["latitude"] = this->latitude;
    }

  if (this->longitude != 0.0)
    {
      result["longitude"] = this->longitude;
    }

  if (this->name != "")
    {
      result["name"] = this->name;
    }

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result;
}

bool GPS_DD::JSON2Object(Json::Value arg_jv)
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
  if (!arg_jv.isMember("latitude")) {
    throw ecs36b_Exception("Missing latitude");
  }
  if (!arg_jv.isMember("longitude")) {
    throw ecs36b_Exception("Missing longitude");
  }
  if (!arg_jv.isMember("name")) {
    throw ecs36b_Exception("Missing name");
  }

  // Condition 2: Unexpected/mismatched value type
  if (!arg_jv["latitude"].isDouble()) {
    throw ecs36b_Exception("latitude must be a double");
  }
  if (!arg_jv["longitude"].isDouble()) {
    throw ecs36b_Exception("longitude must be a double");
  }
  if (!arg_jv["name"].isString()) {
    throw ecs36b_Exception("name must be a string");
  }


  // Condition 4: Critical hidden detected
  if (arg_jv.isMember("hidden") && arg_jv["hidden"].isString()) {
    std::string hiddenValue = arg_jv["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP") {
      throw ecs36b_Exception("A Critical Hidden detected");
    }
  }

  this->latitude = arg_jv["latitude"].asDouble();
  this->longitude = arg_jv["longitude"].asDouble();
  this->name = arg_jv["name"].asString();

  return true;
}
