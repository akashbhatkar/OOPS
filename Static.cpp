#include <iostream>
#include <string>

class Gadget {
public:
    // --- Static Member Variable ---
    // One copy shared by ALL Gadget objects.
    // We must define and initialize this outside the class.
    static int totalGadgets;

    // --- Regular (Non-static) Member Variable ---
    // Each object gets its OWN copy of this.
    std::string id;

    // --- Constructor ---
    // This runs every time a new object is created.
    Gadget(std::string id) : id(id) {
        // We increment the SHARED counter.
        totalGadgets++;
        std::cout << "Gadget " << this->id << " created." << std::endl;
    }

    // --- Regular (Non-static) Member Function ---
    // This works on a specific object (using 'this').
    void showID() {
        // It can access both regular and static members.
        std::cout << "My ID is: " << this->id << std::endl;
        std::cout << "(Total gadgets so far: " << totalGadgets << ")" << std::endl;
    }

    // --- Static Member Function ---
    // This belongs to the CLASS, not an object.
    // It has no 'this' pointer.
    static void getGadgetCount() {
        std::cout << "---" << std::endl;
        std::cout << "Total gadgets created: " << totalGadgets << std::endl;
        std::cout << "---" << std::endl;
        
        // **Important:** A static function can ONLY access
        // other static members.
        // The line below would cause a COMPILER ERROR:
        // std::cout << id; // ERROR: 'id' is non-static.
    }
};

// --- Initialization of the static member ---
// We must do this outside the class, in the global scope.
int Gadget::totalGadgets = 0;


// --- Main Function ---
int main() {
    // 1. We can call the static function BEFORE any objects exist.
    // We use the class name and the scope resolution operator (::).
    std::cout << "Starting program..." << std::endl;
    Gadget::getGadgetCount(); // totalGadgets is 0

    // 2. Create some objects.
    Gadget g1("A-123");
    Gadget g2("B-456");

    // 3. Call the static function again.
    // The count is shared and has been updated by the constructors.
    Gadget::getGadgetCount(); // totalGadgets is 2

    // 4. Create another object.
    Gadget g3("C-789");
    Gadget::getGadgetCount(); // totalGadgets is 3

    // 5. Call the non-static (regular) functions.
    // We must use an object (g1, g2, g3) and the dot operator (.).
    g1.showID();
    g2.showID();

    return 0;
}

Let's break down `static` members and functions in C++.

The most important concept is this: `static` members belong to the **class itself**, not to any **individual object** (or instance) of that class.

> Think of it this way:
> * **Regular (non-static) members** are like the personal properties of a *specific* car, like its `color` or `currentSpeed`. Every new car object has its own separate `color`.
> * A **`static` member** is like a shared piece of data for *all* cars of that model, like `totalCarsManufactured`. There is only **one copy** of this variable, and all car objects share it.

This "shared" nature is their main use. We can use `static` members to keep track of data for the *entire* class (like an object counter) or to create utility functions that don't need a specific object to run.

To get started, where would you like to focus first?

1.  **`static` Member Variables:** We can look at a classic example, like counting how many objects of a class exist.
2.  **`static` Member Functions:** We can explore what these functions can (and *can't*) do, and why they're different from regular member functions.
3.  **Code Comparison:** We can look at a C++ code snippet that shows `static` vs. non-static members in action.
