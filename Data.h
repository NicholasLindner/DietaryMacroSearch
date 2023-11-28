#pragma once
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>
#include <set>
#include <string>
#include <map>
#include <vector>
#include <array>
#include <regex>
using namespace std;

class Data {
	ifstream file;
	vector<string> macros;
	map < string, vector <float>> ingredients;
public:
	Data() {}
	Data(string filename);
	void organizeData();
	vector<string> heapSort(string firstMacro, string secondMacro, string noMacro);
};

Data::Data(string filename) {
	file.open(filename);
	if (!file.is_open()) {
		cout << "File not open!" << endl;
	}
}

void Data::organizeData() {
	string temp, ingredientCode, ingredientDescrip, nutrientCode;
	string nutrientDescrip, nutrientVal, nutrientValSource, fdcID;
	string derivationCode, sfAddModYear, foundationYearAcq;
	int numMacros = 0;

	regex letters = regex("[A-Za-z]");

	//reads first 3 lines
	getline(file, temp);
	getline(file, temp);
	getline(file, temp);
	//reads all ingredients & macros into map 122330
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
		getline(file, derivationCode, ',');
		getline(file, sfAddModYear, ',');
		getline(file, foundationYearAcq);

		ingredientDescrip = ingredientDescrip.substr(1, ingredientDescrip.length() - 2);
		nutrientDescrip = nutrientDescrip.substr(1, nutrientDescrip.length() - 2);
		nutrientVal = nutrientVal.substr(1, nutrientVal.length() - 2);

		//65 distrinct macros considered for each ingredient
		if (numMacros < 66) {
			macros.push_back(nutrientDescrip);
			numMacros++;
		}
		ingredients[ingredientDescrip].push_back(stof(nutrientVal));
		//cout << ingredientDescrip << " " << nutrientVal << endl;
	}
}

vector<string> Data::heapSort(string firstMacro, string secondMacro = "None", string noMacro = "None") {
	vector<string> result;
	
	string* heap{new string[1882]};
	int numInserted = 0;
	int index = 0;
	int parent = floor((index - 1) / 2);

	auto iter = find(macros.begin(), macros.end(), firstMacro);
	int indexFirst = iter - macros.begin();

	for (auto i : ingredients) {
		index = numInserted;
		parent = floor((index - 1) / 2);
		heap[index] = i.first;
		string parentIngredient = heap[parent];

		while (index > -1 && heap[parent] == "" ? true : i.second[indexFirst] > ingredients[parentIngredient][indexFirst]) {
			string temp = heap[parent];
			heap[parent] = heap[index];
			heap[index] = temp;

			index = parent;
			parent = floor((index - 1) / 2);
			parentIngredient = heap[parent];
		}
		numInserted++;
	}
	for (int i = 0; i < 20; i++) {
		result.push_back(heap[i]);
	}
	return result;
}