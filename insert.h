#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "column.h"
using namespace std;


class INSERT
{
	string name = "", command = "";
	char* storage = nullptr;
	ifstream table;
	ofstream output;
	vector <COLUMN> col;
public:

	INSERT(string name, string command)
	{

		this->setName(name);
		this->copyCommand(command);
		this->checkTableName();
	}

	char* getStorage()
	{
		return this->storage;
	}

	void copyCommand(string command)
	{
		if (this->storage != nullptr)
			delete this->storage;
		this->storage = new char[command.length()];
		command.copy(this->storage, command.length());
		this->storage[command.length()] = '\0';
	}

	void setName(string name)
	{
		this->name = name;
	}

	void writeToFile()
	{
		string condition;
		int pos = 0, p = 0, no = 0, type = 0, noStoredCol = 0, noCollumns = 0;
		output.open(name + ".bin", ios::app | ios::binary);
		char* variableToBeWritten = nextWord(pos, this->getStorage()), * typeOrSize = nullptr;
		variableToBeWritten = nextWord(pos, this->getStorage());
		variableToBeWritten = nextWord(pos, this->getStorage());
		variableToBeWritten = nextWord(pos, this->getStorage());
		table >> condition;
		noCollumns = atoi(condition.c_str());
		unsigned int noWrittenCharacters = 0;
		unsigned int pozCursor = 0;

		while (true)
		{
			variableToBeWritten = nextWord(pos, this->getStorage());
			if (strlen(variableToBeWritten) != 0 && noStoredCol == noCollumns)
			{
				cout << endl <<"ERROR! Too many columns provided in command.";
				return;
			}
			noWrittenCharacters += strlen(variableToBeWritten);
			//getline(table, condition);
			//if (*variableToBeWritten == NULL)
				//break;
			table >> condition;
			table >> condition;
			typeOrSize = new char[condition.length()];
			strcpy(typeOrSize, condition.c_str());
			if (strcmp(typeOrSize, "integer") == 0)
			{
				if (*variableToBeWritten == NULL)
				{
					cout << endl << "Missing integer column.";
					pozCursor = output.tellp();
					output.seekp(pozCursor - noWrittenCharacters);
					return;
				}

				type = 1;
				table >> condition;
				//delete typeOrSize;
				typeOrSize = new char[condition.length()];
				strcpy(typeOrSize, condition.c_str());
				if (atoi(variableToBeWritten) > atoi(typeOrSize))
				{
					cout << endl << "Numeric value too large, nothing written." << endl;
					pozCursor = output.tellp();
					output.seekp(pozCursor - noWrittenCharacters);
					return;
				}
				else
				{
					int var = atoi(variableToBeWritten);
					COLUMN* tempCol = new COLUMN(atoi(typeOrSize), atoi(variableToBeWritten), 0);
					col.push_back(*tempCol);
					noStoredCol++;
					//output.write((char*)&var, sizeof(int));
					
				}
			}
			else if (strcmp(typeOrSize, "text") == 0)
			{
				if (*variableToBeWritten == NULL)
				{
					cout << endl << "Missing text column.";
					pozCursor = output.tellp();
					output.seekp(pozCursor - noWrittenCharacters);
					return;
				}

				type = 0;
				table >> condition;
				//delete typeOrSize;
				typeOrSize = new char[condition.length()];
				strcpy(typeOrSize, condition.c_str());

				if (strlen(variableToBeWritten) > atoi(typeOrSize))
				{
					cout << endl << "Text too large, nothing written." << endl;
					pozCursor = output.tellp();
					output.seekp(pozCursor - noWrittenCharacters);
					return;
				}
				else
				{

					variableToBeWritten[strlen(variableToBeWritten)] = '\0';
					variableToBeWritten;
					int charSize = strlen(variableToBeWritten);
					COLUMN* tempCol = new COLUMN(charSize, variableToBeWritten, 1);
					col.push_back(*tempCol);
					noStoredCol++;
					/*output.write((char*)&charSize, sizeof(int));
					output.write((char*)(variableToBeWritten), charSize * sizeof(char));*/
				}
			}
			else
			{
				if (*variableToBeWritten != NULL)
					//cout << endl << "Invalid type." << endl;
				pozCursor = output.tellp();
				output.seekp(pozCursor - noWrittenCharacters);
				break;
			}

			table >> condition;

		}
		
		for (auto it = this->col.begin(); it < this->col.end(); it++)
		{
			if ((*it).getType() == 0)
			{
				int var = (*it).getInteger();
				output.write((char*)&var, sizeof(int));
			}
			else if ((*it).getType() == 1)
			{
				int var = (*it).getDim();
				output.write((char*)&var, sizeof(int));
				output.write((char*)(*it).getValue(), (*it).getDim() * sizeof(char));
			}
		}

		output.close();
		table.close();

	}

	void checkTableName()
	{
		string temp;
		char* no = new char;
		table.open(this->name + ".txt");
		table >> temp;
		if (temp == this->name)
		{
			this->writeToFile();
			table.close();
		}
		else cout << endl << "The aforementioned table does not exist. Cannot insert into a non-existing table." << endl;
		//table.close();

	}

	char* nextWord(int& cPos, char* str)
	{
		int k = 0, i = 0, j = 0;
		char* c = nullptr;
		if (str[cPos] != 0)
		{
			while (str[cPos] == ' ' || str[cPos] == '(' || str[cPos] == ')' || str[cPos] == ',' || str[cPos] == '\'' || str[cPos] == '\"')
				cPos++;
			i = cPos;
			while (str[i] != ' ' && str[i] != '(' && str[i] != ')' && str[i] != ',' && str[i] != '\'' && str[i] != '\"')
			{
				k++;
				i++;
				if (str[i] == ' ' || str[i] == '(' || str[i] == ')' || str[i] == ',' || str[i] == '\'' || str[i] == '\"' || str[i] == 0)
					break;
			}

			c = new char[k + 1];
			for (int m = cPos; m < cPos + k; m++)
			{
				c[j] = str[m];
				if (k > 0)
					j++;
			}
			c[k] = '\0';
			cPos = i;
			if (c[0] == 39 && c[1] == 39)
			{
				c[0] = '0';
				c[1] = '\0';

			}
			return c;
		}
		else return nullptr;

	}
};