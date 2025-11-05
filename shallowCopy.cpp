#include <iostream
using namespace std;
class Shallow 
{
public:
    int i;
    int *ip; // Pointer to dynamically allocated memory


    // Default Constructor
    Shallow() : i(0), ip(nullptr) {
        cout << "Default constructor" << endl;
    }

    // Parameterized Constructor
    Shallow(int a) : i(a) {
        cout << "Parameterized constructor" << endl;
        // Allocate memory on the heap and store a dummy value
        ip = new int; 
        *ip = 500 + a; 
    }

    // Destructor (Crucial for demonstrating the double-free error)
    ~Shallow() {
        if (ip != nullptr) {
            cout << "Destructor freeing memory at: " << ip << endl;
            delete ip; // Clean up the dynamically allocated int
            ip = nullptr; // Set pointer to null after deletion
        }
    }

    // Corrected display to show the shared heap address
    void display() {
        cout << "Object value (i): " << i 
             << ", Pointer value (ip): " << ip 
             << ", Data at *ip: " << (ip ? *ip : 0) << endl;
    }
};

int main() {
    cout << "--- Initial Objects ---" << endl;
    Shallow obj;        // Default constructor
    Shallow obj1(10);   // Parameterized constructor (Allocates memory, e.g., at 12345)
    
    cout << "\n--- Before Copy Assignment ---" << endl;
    obj1.display();

    // The shallow copy occurs here via the default Copy Assignment Operator
    obj = obj1;
    
    cout << "\n--- After Shallow Copy Assignment ---" << endl;
    cout << "obj's state:" << endl;
    obj.display();
    cout << "obj1's state:" << endl;
    obj1.display();
    
    // Demonstrate shared modification
    if (obj.ip != nullptr) {
        *(obj.ip) = 999; // Change data through obj's pointer
    }
    
    cout << "\n--- After Modification via obj ---" << endl;
    cout << "obj's state:" << endl;
    obj.display();
    cout << "obj1's state:" << endl;
    obj1.display();
    
    cout << "\n--- Program Ending (Destructors Run) ---" << endl;
    // CRASH occurs here: Both destructors will try to delete the same memory address!
    return 0;
}

📝 Correct Explanation of Shallow Copy
The explanation of shallow copy according to the corrected program and C++ rules is as follows:

In the line obj = obj1; within the main function, we are performing a copy operation. Since we did not define a custom copy assignment operator for the Shallow class, the C++ compiler automatically generates a default one.

1. The Shallow Copy Action
The default copy assignment operator performs a member-wise copy:

The simple integer member i from obj1 is copied to obj (i.e., obj.i = obj1.i).

The pointer member ip from obj1 is copied to obj (i.e., obj.ip = obj1.ip).

2. The Resulting Error
If obj1's pointer (obj1.ip) was pointing to a memory location (e.g., 12345) in the heap, after the copy, obj's pointer (obj.ip) is now pointing to the exact same memory location (12345).

Shared Resource: Both objects are now managing (pointing to) the same dynamically allocated integer value on the heap.

Proof: When we modify the data using *(obj.ip) = 999;, the value changes for both obj and obj1 because they share the same memory.