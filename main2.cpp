#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include "Thesaurus.h"
#include "MD2.h"
#include "MD4.h"
#include "MD5.h"
//#include "SHA1.h"

using namespace std;

// Two sentence collision

typedef unordered_map<string, string> stringmap;

/* 	Requires: vector<vector> of strings holding all possible synonyms, 0, empty stringmap,
empty string, and the hash function
	Outputs the pairs of Messages that hash to the same value. */
void makeMap(vector<vector<string> > syns, int num, stringmap& targetHash, string newMsg, MD4 md){
	if(syns.size() == num){
		string newHash = md.hash(newMsg).substr(0,10);
		targetHash.emplace(newHash, newMsg);
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
			makeMap(syns, num+1, targetHash, msg, md);
		}
	}
	return;
}

void findCollision(vector<vector<string> > syns, int num, const stringmap& targetHash, string newMsg, MD4 md){
	if(syns.size() == num){
		string newHash = md.hash(newMsg).substr(0,10);
		stringmap::const_iterator got = targetHash.find(newHash);
		if (got != targetHash.end()){
			cout << newMsg << "\n" << got->second << "\n" << got->first << "\n";
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
	string message, newmessage;
cout << "Enter original sentence:" << endl;
	getline(cin, message);
cout << "New sentence:" << endl;
	getline(cin, newmessage);

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

	long unsigned int poss = 1;
// Create vector<vector<string>> of synonyms
	Thesaurus dino;

	vector<vector<string> > syns;
	for(int i = 0; i < words.size(); i++){
		syns.push_back(dino.search(words[i]));
	}
	for(int i = 0; i < syns.size(); i++){
		unsigned int subposs = 0;
		for(int j = 0; j < syns[i].size(); j++){
			cout << syns[i][j] << ", ";
			subposs++;
		}
		poss *= subposs;
		cout << "\n";
	}

// Create vector of words in newmessage
	words.clear();
	words.push_back("");
	words[0] = tolower(newmessage[0]);
	count = 0;
	for(int i = 1; i < newmessage.length(); i++){
		if(newmessage[i] == ' '){
			count++;
			words.push_back("");
			words[count] = tolower(newmessage[++i]);
		}
		else if((newmessage[i] == ',' || newmessage[i] == '.') || newmessage[i] == '?' || newmessage[i] == '!'){
			count++;
			words.push_back("");
			words[count] = newmessage[i];
		}
		else
			words[count].push_back(tolower(newmessage[i]));
	}
// Create vector<vector<string>> of synonyms of newmessage
	long unsigned int poss2 = 1;	
	vector<vector<string> > syns2;

	for(int i = 0; i < words.size(); i++){
		syns2.push_back(dino.search(words[i]));
	}
	for(int i = 0; i < syns2.size(); i++){
		unsigned int subposs = 0;
		for(int j = 0; j < syns2[i].size(); j++){
			
			<< syns2[i][j] << ", ";
			subposs++;
		}
		poss2 *= subposs;
		cout << "\n";
	}
	long long unsigned int posses = poss*poss2;
	cout << poss << " " << poss2 << " " << posses << "\n";
	MD4 hasher(4327543257);							// Generate random key

	stringmap target;

	long int n = 0;

	if(poss <= poss2) {
		makeMap(syns, 0, target, "", hasher);
		cout << "map1 made" << "\n";
		findCollision(syns2, 0, target, "", hasher);
	}
	else{
		makeMap(syns2, 0, target, "", hasher);
		cout << "map2 made" << "\n";
		findCollision(syns, 0, target, "", hasher);
	}



	return 0;
}
