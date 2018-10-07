// Example using has_include to detect if an include file is available
#include <iostream>
#include <string>

#if __has_include(<cryptopp/base64.h>)
#define __HAS_CRYPTOPP__
#include <cryptopp/base64.h>
#endif

using namespace std;

string decode(const string& encoded) {
	string decoded;
#ifdef __HAS_CRYPTOPP__
	CryptoPP::StringSource ss(encoded, true, new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded))); //NOLINT
#else
	(void) encoded;
	decoded = "Unable to decode because <cryptopp/base64.h> not available!";
#endif
	return decoded;
}

int main() {

	string encoded = "SSBjYW1lIGhlcmUgdG8ga2ljayBhc3MgYW5kIGNoZXcgYnViYmxlZ3VtLCBhbmQgSSdtIGFsbCBvdXQgb2YgZ3VtLi4u";

	cout << "base64decode: " << decode(encoded) << endl; // NOLINT
	return 0;
}
