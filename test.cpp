#include <iostream>
#include "Thesaurus.h"
#include "MD2.h"
#include "MD4.h"
#include "MD5.h"
#include "SHA1.h"

int main() {
	Thesaurus test;


	for(std::string i : test.search("adj")) {
		std::cout << i << std::endl;
	}
}