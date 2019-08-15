#include "Cache.h"
#include <fstream>

Cache::Cache(int index, int blockOffset, int tag, int sizeOfCache)
{ // C'tor
	this->_index = index;
	this->_offset = blockOffset + 2; // Adding the byte offset
	this->_sizeOfTag = tag;
	this->_assoLevel = (int)(sizeOfCache / pow(2, this->_offset + index)); // Calculating Level of associativity

	if (this->_assoLevel == 0) 
	{
		throw(new exception("Error while creating cache!"));
	}

	this->table = vector<vector<Block*>>((int)(pow(2,index)));
	
	for (int i = 0; i < table.size(); i++)
	{

		this->table[i] = vector<Block*>(_assoLevel);

		for (int j = 0; j < _assoLevel; j++)
		{
			(this->table[i])[j] = new Block((_offset - 2));

		}
	}
}


Cache::~Cache()
{ // D'tor


	for (int i = 0; i < table.size(); i++)
	{


		for (int j = 0; j < _assoLevel; j++)
		{
			delete (this->table[i])[j];
			(this->table[i])[j] = NULL ; 

		}

	}

}


string Cache::load(string address)
{
	int blockToReplace = 0; // Works by random policy
	int setIndex = 0;

	blockToReplace = rand() % _assoLevel; // Calculating block to replace

	setIndex = calcIndex(address); // Getting index from address

	return (this->table[setIndex][blockToReplace]->check(address, this->_sizeOfTag));

}


void Cache::showCacheStatus()
{

	fstream* output = new fstream();

	output->open("cache.txt", ios::out | ios::trunc);

	*output << "Cache Result:" << endl << endl;

	for (int i = 0; i < table.size(); i++)
	{


		for (int j = 0; j < _assoLevel; j++)
		{
			*output << " | " << this->table[i][j]->toString() << " | ";
			cout << " | " << this->table[i][j]->toString() << " | ";

		}

		cout << endl;
		*output << endl;
	}

	output->close(); // Closing the stream to the file
}


int Cache::calcIndex(string addresss)
{  // Calculates the index of the set by the given address

	string binAddress = "";
	int binIndex = 0;
	int indexVal = 0;

	for (int i = 0; i < 8; i++)
	{

		binAddress.append(hexToBin(addresss[i])); // Converting the address to binary from hex

	}

	binIndex =  stoi(binAddress.substr(31 - _index - _offset, 32 - _offset)); // Getting the bits of the index

	for (int i = 0; i < _index && binIndex > 0; i++) // Calculating the actual value of the index
	{
		indexVal = indexVal + pow(2, i)*(binIndex % 10);
		binIndex = binIndex / 10;
	}

	return indexVal; // Returning the calculated index
}



string Cache::hexToBin(char hexDigit)
{

	switch (toupper(hexDigit))
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}

}


string Cache::getAssoLvl()
{
	string str =  "" + to_string(this->_assoLevel);

	str.append("-Way SA");

	if (this->_assoLevel == 1)
	{

		str = str + " (Direct Mapped) ";

	}


	if (this->_index == 0)
	{

		str = str + " (Fully Associative) ";

	}

	return str;
}