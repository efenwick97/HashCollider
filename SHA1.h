#include "hash_functions/sha1.h"
#include "HashFunction.h"

class SHA1 {
public:
	SHA1(unsigned long key) {
		sha1_begin(&sha1);
	}

	virtual std::string hash(std::string strToHash) {
		//Converts the string to an unsigned char array to conform with
		//the API style
		unsigned char *val = new unsigned char[strToHash.length() + 1];
		strcpy((char *)val, strToHash.c_str());

		//Generates the Hash for the string
		unsigned char output[16];
		sha1_hash(val, strToHash.length() + 1, &sha1);
		sha1_end(output, &sha1);

		//Converts the 16 unsigned char output bits into hex strings
		std::ostringstream os;
		static char convert[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		for(int i = 0; i < 16; i++) {
			os << convert[output[i] % 16] << convert[output[i] / 16];
		}

		//Deletes the generated dynamic memory and returns the string
		delete val;
		return os.str();
		return "";
	}

	virtual std::string hashType() {
		return "SHA1";
	}

private:
	sha1_ctx sha1;
};