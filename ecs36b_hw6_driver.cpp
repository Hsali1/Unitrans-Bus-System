#include "Person.h"
#include "Thing.h"
#include "Record.h"
#include "JhTime.h"

int main()
{
  // GPS and Person declarations

  GPS_DD GPS_Everson { 38.5387597000194, -121.7501328966561 , "Everson Hall"};
  GPS_DD GPS_Silo_Station {38.538834158923194, -121.75302024080716, "Silo Station"};
  GPS_DD GPS_8th_J_Street {38.55196067071078, -121.73879676082973, "8th and J Street" };
  GPS_DD GPS_Moore_Pollock {38.56463560592732, -121.71912561850077, "Moore and Pollock"};

  Person Felix{ "Felix", "Professor"};
  Person Tiffany{"Tiffany", "Bus Driver"};
  Person John{ "John", "Student" };

  // Thing declarations

  Thing Bus {"Unitrans", "L Line", Tiffany};
  Thing Phone {"Phone", "Android", Felix};
  Thing Computer {"Computer", "Blackberry", John};

  // JhTime declarations

  JhTime Everson_Time {"Wednesday", "12", "April", "2023", "06:00 PM"};
  JhTime Silo_Time {"Wednesday", "12", "April", "2023", "06:10 PM"};
  JhTime J_Time {"Wednesday", "12", "April", "2023", "06:20 PM"};
  JhTime Moore_Time {"Wednesday", "12", "April", "2023", "06:32 PM"};

  // Record 1

Json::Value x;
try {
  Record Felix_Record {Felix, Phone, GPS_Everson, Everson_Time};
  x = Felix_Record.dump2JSON();
  std::cout << "Running dump2JSON for Record 1" << std::endl;
  //std::cout << x.toStyledString() << std::endl;

  char buff[128];
  snprintf(buff, strlen("./hw4_Felix_Record.json") + 1, "./hw4_Felix_Record.json");
  int rc = myJSON2File(buff, &x);

  std::cout << "Copying JSON to the file hw4_Felix_Record.json" << std::endl;
  Json::Value another_x;
  rc = myFile2JSON(buff, &another_x);
  //std::cout << "Now showing contents of hw4_Felix_Record.json" << std::endl;
  //std::cout << another_x.toStyledString() << std::endl;

  // ---------------- Generating Code Here ---------------------------
  std::cout << "Here we try removing a key attribute to see if the program will catch it" << std::endl;
  another_x.removeMember("what"); // Removing the 'what' attribute
  // -----------------------------------------------------------------


  Record r_another;
  bool b = r_another.JSON2Object(another_x);
  Json::Value jv2 = r_another.dump2JSON();
  std::cout << "JSON value now being copied to object jv2" << std::endl;
  std::cout << "Now showing contents of jv2 after running JSON2Object" << std::endl;
  std::cout << jv2.toStyledString() << std::endl;
} catch (const ecs36b_Exception& e) {
  std::cout << "Exception occurred: " << e.what() << std::endl;
    std::cout << "=========================================\n" << std::endl;

}


  // Record 2

try {
  Record Felix_Tiffany_Record {Felix, Tiffany, Phone, GPS_Silo_Station, Silo_Time};
  x = Felix_Tiffany_Record.dump2JSON();
  std::cout << "Running dump2JSON for Record 2" << std::endl;
 // std::cout << x.toStyledString() << std::endl;

  char buff2[128];
  snprintf(buff2, strlen("./hw4_Felix_Tiffany_Record.json") + 1, "./hw4_Felix_Tiffany_Record.json");
  int rd = myJSON2File(buff2, &x);
  std::cout << "Copying JSON to the file hw4_Felix_Tiffany_Record.json" << std::endl;
  Json::Value another_y;
  rd = myFile2JSON(buff2, &another_y);
  //std::cout << "Now showing contents of hw4_Felix_Tiffany_Record.json" << std::endl;
  //std::cout << another_y.toStyledString() << std::endl;

  // ---------------- Generating Code Here ---------------------------
  std::cout << "Here we manually change the expected datatype of the value to see if the program will catch it" << std::endl;
  another_y["where"]["latitude"] = "38.5387597"; // Assigning a string value instead of expected numeric value
  // -----------------------------------------------------------------

  Record s_another;
  bool c = s_another.JSON2Object(another_y);
  Json::Value jv3 = s_another.dump2JSON();
  std::cout << "JSON value now being copied to object jv3" << std::endl;
  std::cout << "Now showing contents of jv3 after running JSON2Object" << std::endl;
  std::cout << jv3.toStyledString() << std::endl;
} catch (const ecs36b_Exception& e) {
  std::cout << "Exception occurred: " << e.what() << std::endl;
    std::cout << "=========================================\n" << std::endl;

}


// Record 3

try {
  Record Felix_Tiffany_John_Record {Felix, Tiffany, John, Computer, GPS_8th_J_Street, J_Time};
  x = Felix_Tiffany_John_Record.dump2JSON();
  std::cout << "Running dump2JSON for Record 3" << std::endl;
 // std::cout << x.toStyledString() << std::endl;

  char buff3[128];
  snprintf(buff3, strlen("./hw4_Felix_Tiffany_John_Record.json") + 1, "./hw4_Felix_Tiffany_John_Record.json");
  int re = myJSON2File(buff3, &x);
  std::cout << "Copying JSON to the file hw4_Felix_Tiffany_John_Record.json" << std::endl;
  Json::Value another_z;
  re = myFile2JSON(buff3, &another_z);
  //std::cout << "Now showing contents of hw4_Felix_Tiffany_John_Record.json" << std::endl;
 // std::cout << another_z.toStyledString() << std::endl;

  // ---------------- Generating Code Here ---------------------------
  std::cout << "Creating a Json object manually that is not expected in the structure" << std::endl;
  Json::Value invalidJSON;
  invalidJSON.append(1);
  invalidJSON.append(2);
  invalidJSON.append(3);

  Record t_another;
  bool d = t_another.JSON2Object(invalidJSON);
  // -----------------------------------------------------------------

  Json::Value jv4 = t_another.dump2JSON();
  std::cout << "JSON value now being copied to object jv4" << std::endl;
  std::cout << "Now showing contents of jv4 after running JSON2Object" << std::endl;
  std::cout << jv4.toStyledString() << std::endl;
} catch (const ecs36b_Exception& e) {
  std::cout << "Exception occurred: " << e.what() << std::endl;
  std::cout << "=========================================\n" << std::endl;
}

// Record 4

try {
  Record Felix_Record_2 {Felix, Phone, GPS_Moore_Pollock, Moore_Time};
  x = Felix_Record_2.dump2JSON();
  std::cout << "Running dump2JSON for Record 4" << std::endl;
  //std::cout << x.toStyledString() << std::endl;

  char buff4[128];
  snprintf(buff4, strlen("./hw4_Felix_Record4.json") + 1, "./hw4_Felix_Record4.json");
  int rf = myJSON2File(buff4, &x);
  std::cout << "Copying JSON to the file hw4_Felix_Record4.json" << std::endl;
  Json::Value another_a;
  rf = myFile2JSON(buff4, &another_a);
  //std::cout << "Now showing contents of hw4_Felix_Record4.json" << std::endl;
  //std::cout << another_a.toStyledString() << std::endl;

  // ---------------- Generating Code Here ---------------------------
  std::cout << "Manually changing the hidden attribute to SOS" << std::endl;
  another_a["hidden"] = "SOS";
  // -----------------------------------------------------------------

  Record u_another;
  bool e = u_another.JSON2Object(another_a);
  Json::Value jv5 = u_another.dump2JSON();
  std::cout << "JSON value now being copied to object jv5" << std::endl;
  std::cout << "Now showing contents of jv5 after running JSON2Object" << std::endl;
  std::cout << jv5.toStyledString() << std::endl;
} catch (const ecs36b_Exception& e) {
  std::cout << "Exception occurred: " << e.what() << std::endl;
}

return 0;
}
