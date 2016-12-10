#include <iostream>
#include <algorithm>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <sstream>

#include "thesaurus/mythes.hxx"

class Thesaurus {
public:
	Thesaurus() {
		pMT = new MyThes("thesaurus/th_en_US_new.idx",
						"thesaurus/th_en_US_new.dat");
	}

	~Thesaurus() {
		delete pMT;
	}

	std::vector<std::string> search(std::string word) {
		std::vector<std::string> output;
		mentry *pmean;
		

		int count = pMT->Lookup(word.c_str(), word.length() + 1, &pmean);
		mentry* pm = pmean;

		output.push_back(word);
		if (count != 0) {
			for (int  i=0; i < count; i++) {
				for (int j=0; j < pm->count; j++) {
					output.push_back(convertToString(pm->psyns[j]));
				}
			pm++;
			}
		}

		pMT->CleanUpAfterLookup(&pmean,count);

		removeDuplicates(output);
		return output;
	}

private:
	MyThes *pMT;

	std::string convertToString(char* cStr) {
		std::ostringstream os;

		int index = 0;
		while(cStr[index] != '\0') {
			os << cStr[index];
			index++;
		}
		return os.str();
	}

	void removeDuplicates(std::vector<std::string> &words) {
		std::sort(words.begin(), words.end());
  		words.erase(std::unique(words.begin(), words.end()), words.end());
	}
};