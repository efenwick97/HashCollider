#include "hash_functions/md4.h"
#include "HashFunction.h"

class MD4: public HashFunction {
public:
	MD4(unsigned long key) {
		MD4Init(&md4);
	}

	virtual std::string hash(std::string strToHash) {
		//Converts the string to an unsigned char array to conform with
		//the API style
		unsigned char *val = new unsigned char[strToHash.length() + 1];
		strcpy((char *)val, strToHash.c_str());

		//Generates the Hash for the string
		unsigned char output[16];
		MD4Update(&md4, val, strToHash.length() + 1);
		MD4Final(output, &md4);
		
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
		return "MD4";
	}
private:
	MD4_CTX md4;
};