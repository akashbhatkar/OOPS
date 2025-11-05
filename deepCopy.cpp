#include <iostream>

using namespace std;

class Deep 
{
public:
    int i;
    int *ip; // Pointer to dynamically allocated memory

    // 1. Parameterized Constructor (Initial Allocation)
    Deep(int a) : i(a) {
        cout << "Parameterized constructor allocating memory..." << endl;
        ip = new int; 
        *ip = 500 + a; 
    }

    // 2. Deep Copy Constructor (Fixes copy initialization error)
    Deep(const Deep& other) 
: i(other.i)
 {
        cout << "--- Deep Copy Constructor called ---" << endl;
        // 1. Allocate a NEW block of memory
        ip = new int; 
        // 2. Copy the CONTENT (the value) from the old memory to the new memory
        *ip = *(other.ip); 
    }

    // 3. Deep Copy Assignment Operator (Fixes copy assignment error)
    Deep& operator=(const Deep& other) {
        cout << "--- Deep Copy Assignment Operator called ---" << endl;
        if (this != &other) { // Self-assignment check
            // 1. Clean up existing resource
            delete ip; 
            
            // 2. Allocate a NEW block of memory
            ip = new int;
            
            // 3. Copy the CONTENT and the simple member
            i = other.i;
            *ip = *(other.ip);
        }
        return *this;
    }

    // 4. Destructor (Essential for cleaning up *only* its own memory)
    ~Deep() {
        if (ip != nullptr) {
            cout << "Destructor safely freeing unique memory at: " << ip << endl;
            delete ip;
            ip = nullptr;
        }
    }

    void display() {
        cout << "Object value (i): " << i 
             << ", Pointer value (ip): " << ip 
             << ", Data at *ip: " << (ip ? *ip : 0) << endl;
    }
};

int main() {
    // Uses the Copy Assignment Operator
    Deep obj1(10);
    Deep obj2(20); 

    cout << "\n--- Before Assignment (obj1 & obj2) ---" << endl;
    obj1.display();
    obj2.display();

    // Deep Copy Assignment: obj1 = obj2
    obj1 = obj2; 

    cout << "\n--- After Deep Copy Assignment ---" << endl;
    cout << "obj1's state:" << endl;
    obj1.display(); // Has the *content* of obj2
    cout << "obj2's state:" << endl;
    obj2.display(); // Remains unchanged
    // NOTE: The 'Pointer value (ip)' for obj1 and obj2 will be DIFFERENT!

    // Demonstrate independent modification
    *(obj1.ip) = 999; // Change data through obj1's pointer

    cout << "\n--- After Independent Modification ---" << endl;
    cout << "obj1's state:" << endl;
    obj1.display(); // Value is 999
    cout << "obj2's state:" << endl;
    obj2.display(); // Value is 520 (unaffected)
    
    cout << "\n--- Program Ending (Destructors Run Safely) ---" << endl;
    // Safely deletes obj1's memory, then obj2's memory. NO CRASH.
    return 0;
}


Thinks to keep in mind 
1) Always write a copy constructor explicitely
2) In the copy construcor for handling of the memory issues create a separate memory and then assign the *of the preivious pointer