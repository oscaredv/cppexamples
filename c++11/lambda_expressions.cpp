// Examples showing lambda expressions
// Requires c++11
#include <random>
#include <array>
#include <algorithm>
#include <cmath>
#include <iostream>

using std::cout;
using std::mt19937_64;
using std::uniform_real_distribution;
using std::array;
using std::for_each;
using std::transform;
using std::cout;
using std::endl;

int main()
{
    mt19937_64 rng(time(nullptr));
    uniform_real_distribution<double> dist(-10, 10);

    array<double, 5> numbers =
    { };

    // Generate random numbers in array using range-based for loop
    for (auto& num : numbers)
    {
        num = dist(rng);
    }

    // A lambda expression lets you define functions locally from the place it is called
    // Lambda expression has the form: [capture](parameters)->return-type {body}

    cout << "Random numbers (printed using lambda in for_each):" << endl;
    // Print numbers using for_each and lambda function
    for_each(numbers.begin(), numbers.end(), [](double num)
    {   cout << num << endl;});

    // Round the numbers using transform and the function round
    transform(numbers.begin(), numbers.end(), numbers.begin(), round);

    cout << "Rounded numbers (printed using lambda defined as variable in for_each):" << endl;
    // Define lambda for printing as variable
    auto print = [](double num)
    {   cout << num << endl;};
    // Then print all numbers using the lambda above in a for_each
    for_each(numbers.begin(), numbers.end(), print);

    // Lambdas are cool, but often a simple range-based for loop is cleaner
    cout << "Rounded numbers (printed using range-based for loop):" << endl;
    for (auto num : numbers)
    {
        cout << num << endl;
    }

    return 0;
}
