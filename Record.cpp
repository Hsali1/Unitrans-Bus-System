
#include "Record.h"

Record::Record(Person _p, Thing _t, GPS_DD _g, JhTime _jt)
{
  this->person1 = new Person(_p);
  this->person2 = nullptr;
  this->person3 = nullptr;
  this->what = _t;
  this->where = _g;
  this->when = _jt;
}

Record::Record(Person _p, Person _p2, Thing _t, GPS_DD _g, JhTime _jt)
{
  this->person1 = new Person(_p);
  this->person2 = new Person(_p2);
  this->person3 = nullptr;
  this->what = _t;
  this->where = _g;
  this->when = _jt;
}

Record::Record(Person _p, Person _p2, Person _p3, Thing _t, GPS_DD _g, JhTime _jt)
{
  this->person1 = new Person(_p);
  this->person2 = new Person(_p2);
  this->person3 = new Person(_p3);
  this->what = _t;
  this->where = _g;
  this->when = _jt;
}

Record::Record()
{
}

Record::~Record()
{
  delete this->person1;
  delete this->person2;
  delete this->person3;
}

void
Record::setWhat(Thing _t)
{
  this->what = _t;
}

void
Record::setWhere(GPS_DD _g)
{
  this->where = _g;
}

void
Record::setWhen(JhTime _jt)
{
  this->when = _jt;
}

Json::Value
Record::dump2JSON()
{
  Json::Value result;
  Json::Value persons(Json::arrayValue);
  persons.append((*(this->person1)).dump2JSON());
  if(this->person2 != nullptr){
    persons.append((*(this->person2)).dump2JSON());
  }
  if(this->person3 != nullptr){
    persons.append((*(this->person3)).dump2JSON());
  }
  result["who"] = persons;
  result["where"] = (this->where).dump2JSON();
  result["when"] = (this->when).dump2JSON();
  result["what"] = (this->what).dump2JSON();
  if (!hidden.empty()) {
    result["hidden"] = hidden;
  }
  return result;
}


// Implementing hw6
bool Record::JSON2Object(const Json::Value& json)
{
  if (!json.isObject())
    throw ecs36b_Exception("Input JSON is not an Object");

  const Json::Value& personsJson = json["who"];
  if (!personsJson.isArray())
    throw ecs36b_Exception("Missing 'who' Array");

  if (personsJson.size() > 0) {
    if (!personsJson[0].isObject())
      throw ecs36b_Exception("Expected 'who' Array element to be an Object");
    Person* person = new Person();
    if (!person->JSON2Object(personsJson[0])) {
      delete person;
      throw ecs36b_Exception("Error parsing 'who' Array element");
    }
    person1 = person;
  }

  if (personsJson.size() > 1) {
    if (!personsJson[1].isObject())
      throw ecs36b_Exception("Expected 'who' Array element to be an Object");
    Person* person = new Person();
    if (!person->JSON2Object(personsJson[1])) {
      delete person;
      throw ecs36b_Exception("Error parsing 'who' Array element");
    }
    person2 = person;
  }

  if (personsJson.size() > 2) {
    if (!personsJson[2].isObject())
      throw ecs36b_Exception("Expected 'who' Array element to be an Object");
    Person* person = new Person();
    if (!person->JSON2Object(personsJson[2])) {
      delete person;
      throw ecs36b_Exception("Error parsing 'who' Array element");
    }
    person3 = person;
  }

  if (!json.isMember("where"))
    throw ecs36b_Exception("Missing 'where' attribute");
  if (!json["where"].isObject())
    throw ecs36b_Exception("'where' attribute must be an Object");
  where.JSON2Object(json["where"]);

  if (!json.isMember("what"))
    throw ecs36b_Exception("Missing 'what' attribute");
  if (!json["what"].isObject())
    throw ecs36b_Exception("'what' attribute must be an Object");
  what.JSON2Object(json["what"]);

  if (!json.isMember("when"))
    throw ecs36b_Exception("Missing 'when' attribute");
  if (!json["when"].isObject())
    throw ecs36b_Exception("'when' attribute must be an Object");
  when.JSON2Object(json["when"]);

  if (json.isMember("hidden")) {
    if (!json["hidden"].isString()) {
      throw ecs36b_Exception("'hidden' attribute must be a String");
    }
    std::string hiddenValue = json["hidden"].asString();
    if (hiddenValue == "SOS" || hiddenValue == "HELP") {
      throw ecs36b_Exception("A Critical Hidden detected");
    }
    hidden = hiddenValue; // Store the value in the hidden member variable
  }

  if (json.isMember("what") && json["what"].isObject()) {
    if (!json["what"].isMember("model") || !json["what"]["model"].isString()) {
        throw ecs36b_Exception("Invalid data type for key 'model'\n");
    }
}


  return true;
}
