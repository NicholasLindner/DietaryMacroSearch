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
	vector<string> heapSort(string firstMacro, string noMacro);
};

Data::Data(string filename) {
	file.open(filename, ios::in);
	if (!file.is_open()) {
		cout << "File not open!" << endl;
	}
}

void Data::organizeData() {
	string temp, ingredientCode, ingredientDescrip, nutrientCode;
	string nutrientDescrip, nutrientVal, nutrientValSource, fdcID;
	string derivationCode, sfAddModYear, foundationYearAcq;

	regex letters = regex("[A-Za-z]");

	//reads first 3 lines
	getline(file, temp);
	getline(file, temp);
	getline(file, temp);
	//reads all ingredients & macro vals into map
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
		if (macros.size() < 65) {
			macros.push_back(nutrientDescrip);
		}
		ingredients[ingredientDescrip].push_back(stof(nutrientVal));
		//cout << ingredientDescrip << " " << macros[ingredients[ingredientDescrip].size() - 1] << " " << nutrientVal << endl;
	}
}

vector<string> Data::heapSort(string macro, string noMacro = "None") {
	string* heap{ new string[1882] };
	int size = 0;
	int indexBuild = 0;
	int parent = floor((indexBuild - 1) / 2.0);
	int indexMacro = find(macros.begin(), macros.end(), macro) - macros.begin();

	//build and insert into heap
	for (auto i : ingredients) {
		indexBuild = size;
		heap[indexBuild] = i.first;
		parent = floor((indexBuild - 1) / 2.0);

		while (parent > - 1 && ingredients[heap[indexBuild]][indexMacro] > ingredients[heap[parent]][indexMacro]) {
			swap(heap[parent], heap[indexBuild]);
			indexBuild = parent;
			parent = floor((indexBuild - 1) / 2.0);
		}
		size++;
	}
	/*for (int i = 0; i < 1882; i++) {
		cout << i << " " << heap[i] << " " << ingredients[heap[i]][indexMacro] << endl;
	}*/
	vector<string> result;
	int indexExtract = 0;
	int left = (2 * indexExtract) + 1;
	int right = (2 * indexExtract) + 2;
	int indexNoMacro;
	noMacro == "None" ? indexNoMacro = -1 : indexNoMacro = find(macros.begin(), macros.end(), noMacro) - macros.begin();
	
	//extract max from heap
	while (size > - 1) {
		if (noMacro == "None" || ingredients[heap[0]][indexNoMacro] == 0.00) {
			result.push_back(heap[0]);
		}
		if (size == 0) { break; }

		indexExtract = 0, left = 1, right = 2;
		heap[indexExtract] = heap[size - 1];
		size--;

		while (right < size && (ingredients[heap[indexExtract]][indexMacro] < ingredients[heap[left]][indexMacro] || ingredients[heap[indexExtract]][indexMacro] < ingredients[heap[right]][indexMacro])) {
			if (ingredients[heap[left]][indexMacro] > ingredients[heap[right]][indexMacro]) {
				swap(heap[left], heap[indexExtract]);
			}
			else {
				swap(heap[right], heap[indexExtract]);
				indexExtract = right;
			}
			left = (2 * indexExtract) + 1;
			right = (2 * indexExtract) + 2;
		}
		if (right == size && ingredients[heap[indexExtract]][indexMacro] < ingredients[heap[left]][indexMacro]) {
			swap(heap[left], heap[indexExtract]);
		}
	}
	/*for (int i = 0; i < 200; i++) {
		cout << result[i] << " " << ingredients[result[i]][indexMacro] << " " << ingredients[result[i]][0] << endl;
	}*/
	return result;
}