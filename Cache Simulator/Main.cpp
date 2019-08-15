// CPP Template.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <String>
#include <fstream>
#include <math.h>
#include "Block.h"
#include "Cache.h"
using namespace std;

int main()
{
	int index = 0; // Number of bits for the index
	int offset = 0; // Number of bits for the offset (Block/Word offset only without byte offset)
	int tag = 0; // Number of bits for the tag
	int assoLevel = 0; // The level of associativity of the cache
	int sizeOfCache = 0; // The size of cahce in bytes
	int accesses = 0; // Number of accesses to cache
	int hits = 0; // Number of hits
	fstream* input = NULL; // The file to read the address from
	string nameOfFile = "";


	// Address size is always 32-bit long

	cout << "Enter size of cache (IN BYTES): "; // Getting size of cahce
	cin >> sizeOfCache;

	cout << "Enter the number of sets: ";
	cin >> index;

	cout << "Enter the block offset: ";
	cin >> offset;

	tag = 32 - index - offset - 2; // Calculating the tag

	assoLevel = (int)(sizeOfCache/pow(2,offset+index+2)); // Calculating Level of associativity
	cout << assoLevel << "-way SA" << endl;

	//  Creating the cache




	cout << "Enter the path of the addresses file: " << endl;
	cin >> nameOfFile;

	input = new fstream();

	if (input->good()) 
	{ // Checking if the file has opened successfully
		Block bl = Block(offset);
		input->open(nameOfFile, ios::in); // Opening the file in input mode
		cout << "Accesses to the cache:" << endl;

		while ((!(input->eof())) && (nameOfFile != "") ) // While the file is not over
		{
			
			getline(*input, nameOfFile);
			cout << "0x" << nameOfFile;
			cout << " [" << bl.check(nameOfFile, tag) << "]" << endl;
			cout << bl.toString() << endl << endl;
		}


		system("pause");
		input->close(); // Closing the file
		delete input;
		return 0;

	}


	else 
	{ // If the file couldn't be open successfully

		cout << "Error opening the file!" << endl;
		return 1;
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
