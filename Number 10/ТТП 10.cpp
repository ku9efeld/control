﻿#include <fstream>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

	bool checkSubString(string s, string s1, int g) { // s - строка с точкой , s1 подстрока
	int sizeSubstring = size(s1);
	if (g < 5 && sizeSubstring >= 4) {
		g = 3;
		while (s[g] == s1[g]) {
			--g;
			if (g == -1) break;
		}
		if (g == -1) return 1;
		else return 0;
	}
	if (5 <= g && g <= 11 && sizeSubstring >= 5) {
		g = 4;
		while (s[g] == s1[g]) {
			--g;
			if (g == -1) break;
		}
		if (g == -1) return 1;
		else return 0;
	}
	if (g == 12 && sizeSubstring >= 7) {
		g = 6;
		while (s[g] == s1[g]) {
			--g;
			if (g == -1) break;
		}
		if (g == -1) return 1;
		else return 0;
	}
	return 0;
}

bool checkFile(string path) {
	int sizePath = size(path);
	char c;
	int sizeSubPath = 0, save = 0;
	char sym[] = { '*','<','?','>','"','|' };
	for (int i = 0; i < sizePath; i++) {
		for (int j = 0; j < 6; j++)
			if (path[i] == sym[j]) return 1;
	}
	//Уменьшаем регистр
	for (int i = 0; i < sizePath; i++) {
		c = path[i];
		path[i] = tolower(c);
	}
	sizePath = size(path);
	//Удаляем пробелы
	for (int i = sizePath - 1; i >= 0; --i) {
		if (path[i] == ' ') {
			path.erase(i, 1);
		}
	}
	sizePath = size(path);
	int j = 0, g = 0;
	for (int i = sizePath - 1; i >= 0; --i) {
		if (path[i] == '/') {
			j++;
		}
		if (path[i] == '\\') {
			g++;
		}
	}
	//
	string delim;
	if (j > g) {
		delim = "/";
	}
	else delim = "\\";
	//
	vector<string> arr;
	int n = 0, next, delta = 1;
	// Деление от слешей
	string reserved[] = { "con","aux","clock$","com1","com2","com3","com4","lpt1","lpt2","lpt3","nul","prn","com" };
	string reserved1[] = { "con.","aux.","nul.","prn.","com.","com1.", "com2.","com3.","com4.","lpt1.","lpt2.","lpt3.","clock$." };
	int l = 1;
	// Отделение на подстроки
	while ((next = path.find(delim, n)) != string::npos) {
		string tmp = path.substr(n, next - n);
		arr.push_back(path.substr(n, next - n));
		n = next + delta;
		l++;
	}
	//Проверка после последнего слеша
	string tmp = path.substr(n);
	arr.push_back(path.substr(n));
	//
	for (int k = 0; k < l; k++) {
		for (int s = 0; s < 13; s++) {
				if (reserved[s] == arr[k]) return 1;
			if (reserved1[s] == arr[k] || checkSubString(reserved1[s], arr[k], s)) return 1;
		}
	}
	return 0;
}

void outputVector(vector <string> a) {
	for (int i = 0; i < a.size(); i++) {
		cout << i+1 << ". " << a[i]  << endl;
	}
}

void toAdd(vector<string> &text,int n) {
	string addStr;
	cout << "Enter the addition for end: " << endl;
	cin.get();
	getline(cin, addStr);
	//
	if (n >= 1 && text.size() > 1 && n <= text.size() || (text.size() == 1  && n == 1)) text[n-1] += addStr;
	//if (n >= 1 && text.size() > 1 && n < text.size()) text.push_back(text[n-1]); // size = 2,3,4,5 n = 1,2,3,4,5
	//else  if (text.size() == 1 || n <= 0 || n >= text.size())	cout << endl << "Sorry..But it is not impossibly..." << endl;						// (n < 1 or size <= 1 ) n = 0, size = 1,0 | -1,-2
	//system("pause");
}

void toInputTxt(vector <string> &text) {
	string path = "example.txt";
	int selection;
	cout << "Do u wanna input way to file?" << endl << "1.Yes" << endl << "2.No" << endl;
	cin >> selection;
	switch (selection) {
	case 1: {
		do {
			cout << "Enter the way to file:" << endl;
			cin.get();
			getline(cin, path);
		} while (checkFile(path));
	}
	case 2: {
		ifstream file(path);
		int n;
		if (!file) {
			cout << "File does not exist..." << endl;
			break;
		}
		else cout << "File open!" << endl;
		do {
			cout << "Enter after which line to insert the addition" << endl;
			cin >> n;
		} while (n > text.size() || n <= 0);	
		n++;
		char end = '0';
		int  k = 0;
		do {
			string j;
			getline(file, j);
			if (text.size() >= n + k) text.insert(text.begin() + n + k - 1, j);
			else text.push_back(j);
			k++;
			end = file.peek();
		} while (end != EOF);
		break;
	}
	default: cout << "Error! Action does not exist..." << endl;
	}
	outputVector(text);
}


void toUpper(vector<string> &text,int n) {
	
	for (int i = n - 1; i < n  ; i++) {			// i - Строка
		int save = 0;
		for (int j = 0; j < text[i].size() ; j++) {		// j - Символ в i-ой строке
			if (!(isalpha(text[i][j])))  save = j;
			if (save != 0) {
				if (isalpha(text[i][j]) && islower(text[i][j]) && (j - save == 1 )) text[i][j] = toupper(text[i][j]);
			}
			else 
				if (isalpha(text[i][j]) && islower(text[i][j]) && j == 0) text[i][j] = toupper(text[i][j]);
		}
	}
}

void input(vector <string> &textInput) {
	cout << "Enter text (Type 'Y' when finished typing keys): " << endl;
	string str;
	int symbol = 13;
	int n = 1;
	bool end = false;
	do {
		if (symbol == 13) cout << n << ". ";
		symbol = _getch();
		if (symbol == 13) { // 13 - enter
			textInput.push_back(str);
			str = "";
			cout << endl;
			n++;
		}
		else if ((char)symbol == 'Y') {
			textInput.push_back(str);
			end = true;
		}
		else {
			str = str + (char)symbol;
			cout << (char)symbol;
		}

	} while (!end);
}


int main() {
	vector<string> textInput;
	input(textInput);
	cout << endl;
	while (1) {
		system("cls");
		cout << "Select the action: " << " | 1.Add to the end " << "| 2.Replace all first lowercase letters of words with uppercase ones " << "| 3.Insert text from file " << "| 4.Exit |" << endl;
		outputVector(textInput);
		int selection;
		cin >> selection;
		switch (selection) {
		case 1: {// 1.Добавление в конец
			int number;
			cout << "Input number of line: ";
			cin >> number;
			if (number <= 0 || number > textInput.size()) {
				break;
			}
			toAdd(textInput,number);
			break;
		}
		case 2: {// 2.Замена всех первых строчных букв слов прописными.
			int number;
			cout << "Input number of line: ";
			cin >> number;
			if (number <= 0 || number > textInput.size()) {
				break;
			}
			toUpper(textInput,number);
			break;
		}
		case 3:{ // 3.Вставка текста из файла
			toInputTxt(textInput);
			break;
		}
		case 4: return 0;
		default: cout << "Error! Action does not exist.." << endl;

		}
	}
	return 0;
}