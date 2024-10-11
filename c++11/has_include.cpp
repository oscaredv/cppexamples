// Example using has_include to detect if an include file is available
#include <iostream>


using namespace std;

int main() {
#ifdef __has_include

#if __has_include(<experimental/filesystem>)
	cout << "Include file <experimental/filesystem> available." << endl;
#else
	cout << "Include file <experimental/filesystem> not available." << endl;
#endif

#if __has_include(<filesystem>)
	cout << "Include file <filesystem> available." << endl;
#else
	cout << "Include file <filesystem> not available." << endl;
#endif

#else
	cout << "Feature __has_include not available..." << endl;
#endif

	return 0;
}
