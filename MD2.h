#include "hash_functions/md2.h"
#include "HashFunction.h"

class MD2: public HashFunction {
public:
	MD2(unsigned long key) {
		md2.Init();
	}

	virtual std::string hash(std::string strToHash) {
		//Converts the string to an unsigned char array to conform with
		//the API style
		unsigned char *val = new unsigned char[strToHash.length() + 1];
		strcpy((char *)val, strToHash.c_str());

		//Generates the hash value
		md2.Update(val, strToHash.length() + 1);
		unsigned char output[16];
		md2.TruncatedFinal(output, 16);
	
		//Converts the 16 unsigned char output bits into hex strings
		std::ostringstream os;
		static char convert[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
		for(int i = 0; i < 16; i++) {
			os << convert[output[i] % 16] << convert[output[i] / 16];
		}

		delete val;
		return os.str();
	}

	virtual std::string hashType() {
		return "MD2";
	}
private:
	CMD2 md2;
};