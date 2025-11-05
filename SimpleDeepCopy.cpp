#include<iostream>
using namespace std;
class Deep
{
    public:
    int i, *ip;
    Deep()
    {
        cout<<"Default constructor"<<endl;
    }
    Deep(int a)
    {
        i = a;
        ip = new int(a);
    }
    
    Deep(Deep &obj)
    {
        i = obj.i;
        ip = new int;
        *ip = *(obj.ip);
    }
    void operator=(Deep &obj)
    {
        i = obj.i;
        ip = new int;
        *ip = *(obj.ip);
    }
    void Display()
    {
        cout<<"value of i  = "<<i<<" "
        <<"address of ip = "<<ip<<" "
        <<"value at ip = "<<*ip<<endl;
    }
    ~Deep()
    {
        if(ip != nullptr)
        {
            delete ip;
            ip = nullptr;
        }
    }
};

int main()
{
    Deep obj(10);
    // Deep obj1(10);
    cout<<"Before copy"<<endl;
    obj.Display();
    
    cout<<"After copy Constructor"<<endl;
    Deep obj1(obj);
    obj.Display();
    obj1.Display();
    
    cout<<"Modify using obh"<<endl;
    *(obj.ip) = 200;
    obj.Display();
    obj1.Display();
}

