#pragma once
#include <iostream>
#include <String>

using namespace std;

class Block {

private:
	string tag; // The tag of the block
	bool valid; // Valid bit
	string* data; // Data of the block
	int offset; // Size of offset

	string createTag(string address, int sizeOfTag);

	string hexToBin(char hexDigit);

	void setTag(string tag);

	void setData(string address);

public:

	Block(int sizeOfData);

	~Block();

	void occupy(string address, string tag);

	string check(string address, int sizeOfTag);

	string toString();

	string* getData();

	string getTag();

	bool isValid();
};