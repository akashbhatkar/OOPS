#include <iostream>
using namespace std;

class Manufacture
{
  public : 
  static int Units;
  string Device;
  
  Manufacture(string name)
  {
    Device = name;
    Units++;
    cout<<Device<<" is ready"<<" and no of devices = "<<Units<<endl;
  }
  
  static void GetUnitCount()
  {
    cout<<"The total unit manufactured = "<<Units<<endl;
  }
};

 int Manufacture::Units = 0;
 int main()
 {
   Manufacture::GetUnitCount();
   
   Manufacture m("Mobile");
   Manufacture m1("Laptop");
   Manufacture m2("Watch");
   
   Manufacture::GetUnitCount();   
 }
