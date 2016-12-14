#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include "Thesaurus.h"
#include "MD2.h"
#include "MD4.h"
#include "MD5.h"
//#include "SHA1.h"	// c++14, not 11

using namespace std;

// Single sentence collision

typedef unordered_map<string, string> stringmap;

/* 	Requires: vector<vector> of strings holding all possible synonyms, 0, empty stringmap,
empty string, and the hash function
	Outputs the pairs of Messages that hash to the same value. */
void findCollision(vector<vector<string> > syns, int num, stringmap& targetHash, string newMsg, MD2 md){
	if(syns.size() == num){
		string newHash = md.hash(newMsg).substr(0,10);																// The substring here should be increased as you feel more confident/patient
		if (!(targetHash.emplace(newHash, newMsg).second)){
			cout << newMsg << "\n" << targetHash[newHash] << "\n" << newHash << "\n\n";
		}
// Remove trailing " " for another unique, hashable message.
		newMsg.pop_back();
		newHash = md.hash(newMsg).substr(0,10);																		// Same thing here
		if (!(targetHash.emplace(newHash, newMsg).second)){
			cout << newMsg << "\n" << targetHash[newHash] << "\n" << newHash << "\n\n";
		}
		return;
	}
	else {
		for(int i = 0; i < syns[num].size(); i++) {
			string msg;
			if (syns[num][i] == "." || syns[num][i] == "," || syns[num][i] == "?" || syns[num][i] == "!") {
				msg = newMsg;
				msg.pop_back();
				msg += syns[num][i] + " ";
			}
			else {
				msg = newMsg + syns[num][i] + " ";
			}
			findCollision(syns, num+1, targetHash, msg, md);
		}
	}
	return;
}

int main()
{
	string message;
	getline(cin, message);

	vector<string> words;
	words.push_back("");
	words[0] = tolower(message[0]);

// Create vector of words in message
	int count = 0;
	for(int i = 1; i < message.length(); i++){
		if(message[i] == ' '){
			count++;
			words.push_back("");
			words[count] = tolower(message[++i]);
		}
		else if((message[i] == ',' || message[i] == '.') || message[i] == '?' || message[i] == '!'){
			count++;
			words.push_back("");
			words[count] = message[i];
		}
		else
			words[count].push_back(tolower(message[i]));
	}

// Create vector<vector<string>> of synonyms
	Thesaurus dino;

	vector<vector<string> > syns;
	for(int i = 0; i < words.size(); i++){
		syns.push_back(dino.search(words[i]));
	}
	for(int i = 0; i < syns.size(); i++){
		for(int j = 0; j < syns[i].size(); j++){
			cout << syns[i][j] << " ";
		}
		cout << "\n";
	}


	MD2 hasher(4327543257);							// Generate random key?

	stringmap target;

	cout << "\n\nstart:\n\n";
	findCollision(syns, 0, target, "", hasher);


	


	return 0;
}


/* Trouble Words:
These words and their synonyms have this word >1 time in the thesaurus, so if they are the last word, every sentence hashes to the same thing.
Easy fix, just make sure to end all messages with punctuation.
"all"
"single"
"bad", "rugged", "tough"
"good", "sound", "righteous", "benevolent", "well"
*/
