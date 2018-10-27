// Example showing that curly brackets initialization is better
// because it prohibits narrowing
#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    // Curly brackets initialization prohibits narrowing
    int a(0.0);
    //int a2{0.0}; // narrowing
    uint16_t b(a);
    //uint16_t b2{a}; // narrowing

    // Curly brackets initialization is always better

    cout << "a=" << a << " b=" << b << endl;
    return 0;
}
