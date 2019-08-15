#pragma once

#include "Block.h"
#include <vector>

using namespace std;

// A class that controls a cache


class Cache {

private:
	vector<vector<Block*>> table; // The cahce itself
	int _sizeOfTag; // Number of Tag bits
	int _index; // Number of index bits
	int _offset; // Number of offset bits
	int _assoLevel; // Level of associativity


	string hexToBin(char hexDigit);
	int calcIndex(string addresss);


public:
	Cache(int index, int blockOffset, int tag, int size);

	~Cache();

	string load(string address);

	void showCacheStatus(); // Prints the whole cache

	string getAssoLvl();
};