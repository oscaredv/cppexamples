// Example showing virtual, override and final, and how they are used
// when deriving classes.
//
#include <iostream>
#include <string>

using namespace std;

class Animal //NOLINT(hicpp-special-member-functions,cppcoreguidelines-special-member-functions)
{
public:
    virtual ~Animal() = default; // Pure virtual classes needs virtual default destructors

    virtual string specis() const = 0;

    virtual string sound() const = 0;
};

class Cat final: public Animal
{
public:
    // Virtuality is inherited - virtual keyword not needed here
    // override protects from function renaming in Animal class
    string specis() const override
    {
        return "Cat";
    }

    string sound() const override
    {
        return "Mjau";
    }
};

// Can't derive class marked final
//class SmellyCat: public Cat {
//};

class Fox: public Animal
{
public:
    string specis() const override
    {
        return "Fox";
    }

    string sound() const final
    {
        return "Ring-ding-ding-ding-dingeringeding!";
    }
};

class PolarFox: public Fox
{
public:
    string specis() const override
    {
        return "Polarfox";
    }

    // Can't overload final function
    //string sound() const override
    //{
    //    return "Wa-pa-pa-pa-pa-pa-pow!";
    //}
};

int main()
{
    Cat cat;
    Fox fox;
    PolarFox polarfox;

    cout << cat.specis() << " says " << cat.sound() << endl;
    cout << fox.specis() << " says " << fox.sound() << endl;
    cout << polarfox.specis() << " says " << polarfox.sound() << endl;

    return 0;
}
