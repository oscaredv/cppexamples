// Example showing new class type enums
// Requires c++11
#include <iostream>

using namespace std;

// http://www.stroustrup.com/C++11FAQ.html#enum
//
// The enum classes ("new enums", "strong enums") address three problems with traditional C++ enumerations:
//
// - conventional enums implicitly convert to int, causing errors when someone does not want an enumeration to act as an
//   integer.
// - conventional enums export their enumerators to the surrounding scope, causing name clashes.
// - the underlying type of an enum cannot be specified, causing confusion, compatibility problems, and makes forward
//   declaration impossible.
//
// The new enums are "enum class" because they combine aspects of traditional enumerations (names values) with aspects
// of classes (scoped members and absence of conversions).

// Forward declaration allowed
enum class Beaufort
;

enum class Beaufort
{
    Calm = 0,
    LightAir,
    LightBreeze,
    GentleBreeze,
    ModerateBreeze,
    FreshBreeze,
    StrongBreeze,
    NearGale,
    Gale,
    StrongGale,
    Storm,
    ViolentStorm,
    Hurricane
};

int main()
{
    // Must use Beaufort::Storm
    //Beaufort currentWind = Storm;

    //Will not implicitly convert to int
    //int whatWePrayFor = Beaufort::Calm;

    cout << "Fresh breeze is " << static_cast<int>(Beaufort::FreshBreeze) << " and hurricane is "
            << static_cast<int>(Beaufort::Hurricane) << " on the Beaufort scale." << endl;

    return 0;
}
