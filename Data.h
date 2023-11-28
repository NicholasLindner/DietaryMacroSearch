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
		if (macros.size() < 66) {
			macros.push_back(nutrientDescrip);
		}
		ingredients[ingredientDescrip].push_back(stof(nutrientVal));
		//cout << ingredientDescrip << " " << nutrientVal << endl;
	}
}

vector<string> Data::heapSort(string firstMacro, string secondMacro = "None", string noMacro = "None") {
	string* heap{ new string[1882] };
	int numInserted = 0;
	int indexInserting = 0;
	int parent = floor((indexInserting - 1) / 2);
	int indexMacro = find(macros.begin(), macros.end(), firstMacro) - macros.begin();

	//build and insert into the heap
	for (auto i : ingredients) {
		indexInserting = numInserted;
		heap[indexInserting] = i.first;
		parent = floor((indexInserting - 1) / 2);

		while (parent > -1 && heap[parent] == "" ? false : i.second[indexMacro] > ingredients[heap[parent]][indexMacro]) {
			string temp = heap[parent];
			heap[parent] = heap[indexInserting];
			heap[indexInserting] = temp;

			indexInserting = parent;
			parent = floor((indexInserting - 1) / 2);
		}
		numInserted++;
	}
	/*for (int i = 0; i < 1882; i++) {
		cout << heap[i] << " " << ingredients[heap[i]][indexMacro] << endl;
	}*/

	vector<string> result;
	int indexRemoving = 0;
	int left = (2 * indexRemoving) + 1;
	int right = (2 * indexRemoving) + 2;
	int size = 1882;
	int indexNoMacro;
	noMacro == "None" ? indexNoMacro = -1 : indexNoMacro = find(macros.begin(), macros.end(), noMacro) - macros.begin();

	while (result.size() != 30) {
		indexRemoving = 0;
		left = (2 * indexRemoving) + 1;
		right = (2 * indexRemoving) + 2;

		if (noMacro == "None") {
			result.push_back(heap[0]);
		}
		else if (ingredients[heap[0]][indexNoMacro] == 0.00) {
			result.push_back(heap[0]);
		}

		heap[0] = heap[size - 1];
		size--;
		while ((right < size) && (heap[indexRemoving] < heap[left]) && (heap[indexRemoving] < heap[right])) {
			if (ingredients[heap[left]][indexMacro] > ingredients[heap[right]][indexMacro]) {
				string temp = heap[left];
				heap[left] = heap[indexRemoving];
				heap[indexRemoving] = temp;
				indexRemoving = left;
			}
			else {
				string temp = heap[right];
				heap[right] = heap[indexRemoving];
				heap[indexRemoving] = temp;
				indexRemoving = right;
			}
			left = (2 * indexRemoving) + 1;
			right = (2 * indexRemoving) + 2;
		}
		/*if (heap[indexRemoving] < heap[left] && right == size) {
			string temp = heap[left];
			heap[left] = heap[indexRemoving];
			heap[indexRemoving] = temp;
		}*/
	}
	for (int i = 0; i < 30; i++) {
		cout << result[i] << " " << ingredients[result[i]][indexMacro] << " " << ingredients[result[i]][indexNoMacro] << endl;
	}
	return {};
}