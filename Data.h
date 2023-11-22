#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <map>
#include <regex>
using namespace std;

class Data {
	ifstream file;
	set<string> macros;
	map<string, vector<pair<string, int>>> ingredients;
public:
	Data() {}
	Data(string filename);
	void organize();

};

Data::Data(string filename) {
	file.open(filename);
	if (!file.is_open()) {
		cout << "file not open" << endl;
	}
}

void Data::organize() {
	string temp, ingredientCode, ingredientDescrip, nutrientCode;
	string nutrientDescrip, nutrientVal, nutrientValSource, fdcID;
	string sfAddModYear, foundationYearAcq;
	int numMacros = 0;

	regex numbers = regex("[0-9]");
	regex letters = regex("[A-Za-z]");

	getline(file, temp);
	getline(file, temp);
	getline(file, temp);
	for (int i = 0; i < 122330; i++) {
		getline(file, ingredientCode, ',');
		getline(file, ingredientDescrip, ',');
		getline(file, nutrientCode, ',');
		while (regex_search(nutrientCode, letters)) {
			ingredientDescrip += nutrientCode;
			getline(file, nutrientCode, ',');

		}
		getline(file, nutrientDescrip, ',');
		getline(file, nutrientVal, ',');
		while (regex_search(nutrientVal, letters)) {
			nutrientDescrip += nutrientVal;
			getline(file, nutrientVal, ',');

		}
		getline(file, nutrientValSource, ',');
		getline(file, fdcID, ',');
		getline(file, sfAddModYear, ',');
		getline(file, foundationYearAcq, ',');

		ingredientDescrip = ingredientDescrip.substr(1, ingredientDescrip.length() - 2);
		nutrientDescrip = nutrientDescrip.substr(1, nutrientDescrip.length() - 2);
		nutrientVal = nutrientVal.substr(1, nutrientVal.length() - 2);

		if (numMacros < 66) {
			macros.insert(nutrientDescrip);
			numMacros++;
		}
		cout << ingredientDescrip << " " << nutrientDescrip << " " << nutrientVal << endl;
		ingredients[ingredientDescrip].push_back(make_pair(nutrientDescrip, stoi(nutrientVal)));
	}
}