#include <random>
#include <array>
#include <iostream>
#include <algorithm>
#include <cmath>

using std::cout;
using std::mt19937_64;
using std::uniform_real_distribution;
using std::array;
using std::for_each;
using std::cout;
using std::endl;

void print(double num)
{
    cout << num << endl;
}

int main()
{
    mt19937_64 rng(time(nullptr));
    uniform_real_distribution<double> dist(-10, 10);

    array<double, 5> numbers =
    { };

    cout << "Random numbers:" << endl;
    // Generate random numbers in array using range-based for loop
    for (auto& num : numbers)
    {
        num = dist(rng);
    }

    // A lambda expression lets you define functions locally from the place it is called
    // Lambda expression has the form: [capture](parameters)->return-type {body}

    // Print numbers using for_each and function
    for_each(numbers.begin(), numbers.end(), print);

    // Round the numbers using for_each and lambda expression
    for_each(numbers.begin(), numbers.end(), [](double& d)
    {   d = round(d);});

    cout << "Rounded numbers:" << endl;
    // Print numbers using for_each and lambda expression
    for_each(numbers.begin(), numbers.end(), [](double d)
    {   cout << d << endl;});

    return 0;
}
