// Examples showing various uses of range based for loops

#include "range_for.hpp"
#include <iostream>
#include <map>
#include <deque>

using namespace std;
using namespace cppexamples;

int main()
{
    // vector example
    vector<int> vec =
    { 1, 2, 3 };

    cout << "Range-based for (vector):";
    for (auto v : vec)
    {
        cout << " " << v;
    }
    cout << endl;

    // c-array example
    int arr[] =
    { 1, 2, 3 };

    cout << "Range-based for (c-array):";
    for (const auto &v : arr)
    {
        cout << " " << v;
    }
    cout << endl;

    // string
    string str
    { "one two three" };
    cout << "Range-based for (string):";
    for (const auto c : str)
    {
        cout << " " << c;
    }
    cout << endl;

    // braced init list
    cout << "Range-based for (braced-init-list):";
    for (const auto c :
    { 1, 2, 3 })
    {
        cout << " " << c;
    }
    cout << endl;

    // braced init list example
    cout << "Range-based for (var not used):";
    for (const auto c :
    { 1, 2, 3 })
    {
        (void) c; // Avoid unused variable warning
        cout << " blah";
    }
    cout << endl;

    // map example
    map<int, string> numbers(
    {
    { 1, "one" },
    { 2, "two" },
    { 3, "three" } });
    cout << "Range-based for (map):";
    for (const auto &num : numbers)
    {
        cout << " " << num.first << ":" << num.second;
    }
    cout << endl;

    // deque of pointers
    deque<string *> ptrs =
    { new string("one"), new string("two"), new string("three") };
    cout << "Range-based for (pointers):";
    for (auto &ptr : ptrs) // ptr is a reference to the pointer
    {
        cout << " " << *ptr;
        delete ptr; // NOLINT(cppcoreguidelines-owning-memory)
        ptr = nullptr;
    }
    cout << endl;

    // Custom container class forwarding iterators from private vector
    TemperatureSensor sensor("Cylinder 1");
    sensor.add_reading(1);
    sensor.add_reading(2);
    sensor.add_reading(3);
    cout << "Range-based for (custom class forwarding iterators):";
    for (auto temp : sensor)
    {
        cout << " " << temp;
    }
    cout << endl;

    // Custom container class with custom iterator
    VibrationSensor vibrations;
    vibrations.add_reading(.1, 10);
    vibrations.add_reading(.2, 20);
    vibrations.add_reading(.3, 30);
    cout << "Range-based for (custom class with custom iterator):";
    for (auto vib : vibrations)
    {
        cout << " " << vib.first << "mm/s " << vib.second << "Hz";
    }
    cout << endl;

    return 0;
}

namespace cppexamples
{
const pair<float, float>& VibrationIterator::operator*() const
{
    return m_sensor.get(m_pos);
}
}
