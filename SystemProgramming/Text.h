#pragma once
#include <vector>
#include <string>

using namespace std;

struct distinctWord
{
	string word;
	long count;
};

class Text
{
private:
	char alphabet[52];
	char delimiters[6];
	vector<string> words;
	void printWords();
	void printDistinctWords(vector<distinctWord> distinctWords);
	struct distinctWord disWords;

public:
	Text(void);
	~Text(void);
	void setText(long symCount, float alphaProb);
	vector<string> getWords();
	vector<distinctWord> getDistinctWords();
};

