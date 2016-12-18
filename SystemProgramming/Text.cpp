#include"stdafx.h"
#include "Text.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <ctime>

using namespace std;

Text::Text(void)
{
	this->delimiters[0] = ' ';
	this->delimiters[1] = '.';
	this->delimiters[2] = '?';
	this->delimiters[3] = '!';
	this->delimiters[4] = '(';
	this->delimiters[5] = ')';
	for (int i = 65; i <= 122; i++) {
		if (i > 90 && i < 97) continue;
		if (i < 91) this->alphabet[i - 65] = i; 
		else this->alphabet[i - 71] = i;
	}
}


Text::~Text(void){
}

void inline Text::printWords(){
	for (auto word : this->words){
		cout << word << endl;
	}
}

void inline Text::printDistinctWords(vector<distinctWord> distinctWords){
	for (auto disWord : distinctWords){
		cout << disWord.count << ": " << disWord.word << endl;
	}
}

void Text::setText(long symCount, float alphaProb){
	ofstream fout;
	fout.open("Main.txt");
	srand(time(0));
	for (auto i = 0; i < symCount; i++){
		if ( ((double)rand() / RAND_MAX) < alphaProb) {
			fout << this->alphabet[rand() % (sizeof(this->alphabet)/sizeof(*this->alphabet))];
		} else {
			fout << this->delimiters[rand() % (sizeof(this->delimiters)/sizeof(*this->delimiters))];
		}
	}
	cout << "Main.txt created" << endl;
}

vector<string> Text::getWords(){
	int symbol = 0;
	bool isDelimiter = false;
	string word;  
 
	ifstream fin("Main.txt");
	while((symbol = fin.get()) != EOF) {   
		isDelimiter = false;
		for (int i = 0; i < 6; i++) {
			if (char(symbol) == delimiters[i]){
				isDelimiter = true;
				break;
			}
		}
		if (!isDelimiter) word = word + char(symbol);  
		else if (word != ""){
			this->words.push_back(word); 
			word.clear(); 
		}
	}
	if (word != "") words.push_back(word);
	fin.close(); 

	return this->words;
}

vector<distinctWord> Text::getDistinctWords () {
	vector<distinctWord> distinctWords;
	vector<long> distinctWordsCount;
	bool found = false;
	for (auto word : this->words){
		found = false;
		for (auto i = 0; i < distinctWords.size(); i++){
			if (distinctWords[i].word == word) {
				distinctWords[i].count++;
				found = true;
				break;
			}
		}
		if (!found){
			distinctWord newWord;
			newWord.word = word;
			newWord.count = 1;
			distinctWords.push_back(newWord);
		}
	}

	printDistinctWords(distinctWords);

	return distinctWords;
}
