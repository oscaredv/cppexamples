// Example using binary literals
// Requires c++14
#include <iostream>
#include <bitset>
#include <cstdint>

using namespace std;

int main()
{
    // Before binary literals, a bitset would often be initialized using a string
    // We could also use uint8_t instead of bitset<8>, but bitsets works better with cout
    bitset<8> value(0b01010101);
    bitset<8> mask(0b00011111);
    bitset<8> masked_value = value & mask;

    cout << "value        = " << value << endl;
    cout << "mask         = " << mask << endl;
    cout << "masked value = " << masked_value << endl;

    return 0;
}
