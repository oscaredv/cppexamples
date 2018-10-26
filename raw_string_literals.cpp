#include <iostream>

using std::cout;

int main()
{
    // Raw string literals eliminates the need for escaping special characters
    // They are written as: R"delimiter(raw string)delimiter"
    // Koan from "Tao of Programming" - by Geoffrey James, 1987
    cout
            << R"TAO(The Master was explaining the nature of Tao to one of his novices.
"The Tao is embodied in all software -- regardless of how insignificant," said the Master.
"Is the Tao in a hand-held calculator?" asked the novice.
"It is," came the reply.
"Is the Tao in a video game?" asked the novice.
"It is even in a video game," said the Master.
"Is the Tao in the DOS for a personal computer?" asked the novice.
The Master coughed and shifted his position slightly. "The lesson is over for today," he said.
)TAO";

    return 0;
}
