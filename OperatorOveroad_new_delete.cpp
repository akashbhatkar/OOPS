#include <iostream>
using namespace std;
class Demo
{
    public:
    
    void* operator new(size_t size)
    {
        cout<<"custom size added"<<endl;
        return malloc(size);
    }
    
    void operator delete (void* ptr)
    {
        cout<<"custom delete"<<endl;
        free(ptr);
    }
};

int main()
{
    Demo *dptr = new Demo();
    delete dptr;
}
