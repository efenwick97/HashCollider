#include <iostream>
#include <string.h>
#include <sstream>

#ifndef HashFunction_H
#define HashFunction_H

class HashFunction {
	public:
	virtual std::string hash(std::string strToHash) = 0;
	virtual std::string hashType() = 0;
};

#endif /* HashFunction */