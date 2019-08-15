#pragma once

#include "Block.h"

using namespace std;

// A class that controls a cache


class cache {

private:
	Block** table;
	int _tag;
	int _index;
	int _offset;
	int _assoLevel;


public:
	cache(int index, int offset, int tag, int assoLevl);

	~cache();

	string load(string address);

	void showCacheStatus(); // Prints the whole cache
};