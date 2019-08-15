#include "Block.h"
#include <math.h>
#include <bitset>
#include <sstream>
Block::Block(int sizeOfData)
{ // sizeOfData = offset
	offset = sizeOfData + 2;
	tag = "";
	valid = false;
	data = new string[(int)(pow(2, offset))]; // Creating an array of data according to the given block size (IN Bytes)
}

Block::~Block()
{

	delete[] data;
	data = NULL;

}

void Block::occupy(string address, string _tag)
{
	setTag(_tag); // Updating the tag
	setData(address); // Updating the data stored in the block
}

string Block::check(string address, int sizeOfTag) // Checking if the address is on the block
{


	if (!valid)
	{
		valid = true; // Making the block valid
		occupy(address, createTag(address, sizeOfTag)); //Occupying the block
		return "Miss Compulsory-valid"; // Returning the result of the check
		
	}


	else 
	{
		string tag = createTag(address, sizeOfTag);

		if (this->tag == tag) // If the block is valid and has the same tag it's a hit
		{

			return "Hit"; // Returning the result of the check

		}


		else // If block is valid but tags are not the same there's a miss tag
		{
			occupy(address, tag); //Occupying the block
			return "Miss Tag"; // Returning the result of the check
		}
	}

}

string Block::createTag(string address, int sizeOfTag)
{
	string tag = "";
	
	for (int i = 0; i < 8; i++)
	{

		tag.append(hexToBin(address[i]));

	}

	return tag.substr(0, sizeOfTag);
}

string Block::hexToBin(char hexDigit)
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

string Block::toString()
{
	string str = "Valid: ";

	if (valid) 
	{
		str.append("1"); 
	}

	else 
	{
		str.append("0");;
	}

	str = str + "; Tag: " + tag;
	str = str + "; Data: { ";

	for (int i = 0; i < (int)(pow(2, offset)); i++) // Adding the data segment; i++ 
	{
		str = str + data[i];

		if (i != (int)(pow(2, offset)) - 1)
		{
			str = str + ", ";
		}

	}

	str = str + " }";

	return str;
}



string* Block::getData()
{

	int size = (int)(pow(2, offset + 2));
	string* _data = new string[size]; // Creating a copy of the data
	
	for (int i = 0; i < size; i++)
	{

		_data[i] = this->data[i];

	}

	return _data;

}

string Block::getTag()
{

	return this->tag;
}

bool Block::isValid()
{

	return this->valid;

}

void Block::setTag(string tag)
{

	this->tag = tag;

}


void Block::setData(string address)
{

	unsigned int IAddress = 0; // Integer value of the address
	int size = (int)(pow(2, offset)); // Size of the data segment
	stringstream ss; // In order to convert between bases 

	ss << hex << address; // Saving the address in the string stream object
	ss >> hex >> IAddress; // Parsing to decimal and saving in an intger

	// Getting the first address
	IAddress = IAddress >> offset;
	IAddress = IAddress << offset;

	for (int i = 0; i < size; i++) // Occupying the data segment in the block
	{
		//address = IAddress + "";
		ss.str(""); // Reseting the stringstream object buffer
		ss.clear();
		ss << hex << IAddress; // Updating current address
		data[i] = ss.str(); // Putting data at current index
		IAddress++; // Getting next address
	}

}