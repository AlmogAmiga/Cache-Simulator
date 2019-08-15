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

	string getTag(string address, int sizeOfTag);

	string hexToBin(char hexDigit);

public:

	Block(int sizeOfData);

	~Block();

	void occupy(string address, string tag);

	string check(string address, int sizeOfTag);

	string toString();

};