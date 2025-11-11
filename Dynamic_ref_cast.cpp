#include <iostream>
#include <typeinfo> // For std::bad_cast

#include <iostream>
#include <vector>

class Animal {
public:
    // Must be virtual for dynamic_cast to work
    virtual ~Animal() {} 
    virtual void speak() { std::cout << "Animal sound.\n"; }
};

class Dog : public Animal {
public:
    void speak() override { std::cout << "Woof! Woof!\n"; }
    void train() { std::cout << "Dog is trained to sit.\n"; } // Dog-specific function
};
void try_train(Animal& a) {
    try {
        // Attempt to cast the reference
        Dog& d_ref = dynamic_cast<Dog&>(a);
        
        // If the cast succeeds, the code continues here
        d_ref.train(); 

    } catch (const std::bad_cast& e) {
        // If the cast fails (a is not a Dog), the exception is caught
        std::cout << "Exception: Cannot train this animal (not a Dog).\n";
    }
}

int main() {
    Dog my_dog;
    Animal unknown_animal;

    try_train(my_dog);         // Success
    try_train(unknown_animal); // Throws std::bad_cast
}
