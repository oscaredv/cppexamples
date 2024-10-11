// Example starting threads based on std::thread
// Threads are started with no arguments, with arguments, and finally
// std::async is used to capture the return value from a thread function
// A std::mutex is also used to protect a shared resource (cout) from
// concurrent access.
//
// References:
// https://en.cppreference.com/w/cpp/thread
//
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <future>

using namespace std;

mutex mtx; // Mutex used to protect shared resource cout

void thread_func1()
{
    lock_guard<mutex> lock(mtx);
    cout << "This is thread1!" << endl;
}

void thread_func2(int a, const string& s)
{
    lock_guard<mutex> lock(mtx);
    cout << "Thread2 got two arguments: a=" << a << " and s=" << s << endl;
}

class thread_class
{
public:
    void thread_func3()
    {
        lock_guard<mutex> lock(mtx);
        cout << "Thread3 is a class member functions" << endl;
    }
};

int thread_func4()
{
    cout << "Thread 4 returns the answer to the meaning of life..." << endl;
    return 42;
}
int main()
{
    cout << "Thread examples" << endl;

    thread t1(thread_func1);
    thread t2(thread_func2, 42, "String passed to thread function!");
    thread_class tc;
    thread t3(&thread_class::thread_func3, &tc);
    auto future = std::async(thread_func4);
    {
        lock_guard<mutex> lock(mtx);
        cout << "All threads started!" << endl;
    }

    t1.join();
    t2.join();
    t3.join();
    cout << "All threads joined!" << endl;

    int answer = future.get();
    cout << "The Almighty Answer to the Meaning of Life, the Universe, and Everything: " << answer << endl;
    return 0;
}

