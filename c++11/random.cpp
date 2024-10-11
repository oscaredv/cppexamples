// Seeded random numbers generator using <random>
// Requires c++11
#include <random>
#include <array>
#include <iterator>
#include <iostream>

int main()
{
    using std::random_device;
    using std::array;
    using std::mt19937;
    using std::seed_seq;
    using std::uniform_real_distribution;
    using std::cout;
    using std::endl;

    // Source of randomness provided by operating system
    random_device rdev;

    // Seed array with proper size for the random numbers engine
    array<int, mt19937::state_size> seeds =
    { 0 };

    // generate seed and store in seeds array
    for (auto& seed : seeds)
    {
        seed = rdev();
    }

    // Wrap seeds array in a seed_seq, as required by random engine
    seed_seq seq(begin(seeds), end(seeds));

    // Random numbers engine based on the Mersenne Twister 19937
    mt19937 engine(seq);

    // Random numbers uniform distribution
    uniform_real_distribution<double> dist(-1.5, 1.5);

    // Generate random numbers
    for (int i = 0; i < 20; ++i)
    {
        cout << dist(engine) << '\n';
    }

    return 0;
}
