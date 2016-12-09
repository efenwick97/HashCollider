#include "hash_functions/md5.h"
#include "HashFunction.h"

class MD5: public HashFunction {
public:
	MD5(unsigned long key) {
		MD5Init(&md5, key);
	}

	virtual std::string hash(std::string strToHash) {
		//Converts the string to an unsigned char array to conform with
		//the API style
		unsigned char *val = new unsigned char[strToHash.length() + 1];
		strcpy((char *)val, strToHash.c_str());

		//Generates the Hash for the string
		MD5Update(&md5, val, strToHash.length() + 1);
		MD5Final(&md5);
		
		//Converts the 16 unsigned char output bits into hex strings
		std::ostringstream os;
		static char convert[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		for(int i = 0; i < 16; i++) {
			os << convert[md5.digest[i] % 16] << convert[md5.digest[i] / 16];
		}

		//Deletes the generated dynamic memory and returns the string
		delete val;
		return os.str();
	}

	virtual std::string hashType() {
		return "MD5";
	}
private:
	MD5_CTX md5;
};