// Example using std::move and pass by value, and implementing move constructor
// and move assignment operator
//
#include <iostream>
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Person
{
public:
    Person() = default;

    // Passing string by value, and move it in place
    explicit Person(string name, int age) :
            m_name(move(name)), m_age(age)
    {
    }

    // Copy constructor
    Person(const Person& rhs) = default;

    // Default destructor
    ~Person() = default;

    // Default assign operator
    Person& operator=(const Person& rhs) = default;

    // Move constructor
    Person(Person&& rhs) noexcept :
            m_name(move(rhs.m_name)), m_age(rhs.m_age)
    {
        cout << "Move constructor called..." << endl;
    }

    // Move assignment operator
    Person& operator=(Person&& rhs) noexcept
    {
        swap(m_name, rhs.m_name);
        swap(m_age, rhs.m_age);
        cout << "Move assignment operator called..." << endl;
        return *this;
    }

    auto age() const
    {
        return m_age;
    }

    const string& name()
    {
        return m_name;
    }

protected:
    string m_name;
    int m_age = 0;
};

int main()
{
    Person p1("Albert", 8);
    cout << "Person1 created, name argument was moved in place instead of using const ref" << endl;
    cout << "Person1 name=" << p1.name() << " age=" << p1.age() << endl;

    vector<Person> vec;
    vec.emplace_back(Person("Skybert", 8));

    p1 = move(vec[0]);
    cout << "Person1 name=" << p1.name() << " age=" << p1.age() << endl;
    return 0;
}
