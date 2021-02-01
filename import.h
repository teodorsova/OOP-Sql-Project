#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "table.h"

using namespace std;


class IMPORT
{
	string name = "", command = "";
	char* storage = nullptr;
	ifstream table;
	ofstream output;

	/*ifstream inCSV;
	string numeCSV = p.getBuffer();
	numeCSV += ".csv";
	inCSV.open(numeCSV, ios::in);
	getline(inCSV, command);*/
public:

	IMPORT(char* name, string command)
	{
		if (name != nullptr)
			this->setName(name);
		else
		{
			cout << endl << "ERROR! Missing name.";
			return;
		}
		this->copyCommand(command);
		this->checkTableName();
	}

	char* getStorage()
	{
		return this->storage;
	}
	char* getChar(string chars) {
		char* x = new char[chars.length()];
		strcpy(x, chars.c_str());
		return x;
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
		string condition, numeFisier;
		int pos = 6, p = 0, no = 0, type = 0, tempPos = 0;
		output.open(name + ".bin", ios::app | ios::binary);
		char* variableToBeWritten;
		ifstream inCsv;
		nextWord(pos, this->getStorage());
		tempPos = pos;
		if(nextWord(pos, this->getStorage())!=nullptr)
		{
			numeFisier=this->storage+tempPos+1;
		}
		else
		{
			cout << endl << "ERROR! Missing file name.";
			return;
		}
		//numeFisier += ".csv";
		if (TABLE::fileExists(numeFisier) == 1)
		{
			inCsv.open(numeFisier, ios::in);
			/*= nextWord(pos, this->getStorage()),
			variableToBeWritten = nextWord(pos, this->getStorage());
			variableToBeWritten = nextWord(pos, this->getStorage());
			variableToBeWritten = nextWord(pos, this->getStorage());*/
			char* typeOrSize = nullptr;
			int ok = 0;
			string x = "";
			while (getline(inCsv, x))
			{
				if (ok == 1)
				{
					table.open(this->name + ".txt", ios::in);
					table >> condition;
				}
				table >> condition;
				pos = 0;
				while (true)
				{

					variableToBeWritten = nextWord(pos, getChar(x));
					//getline(table, condition);
					if (variableToBeWritten == NULL)
						break;

					table >> condition;
					table >> condition;
					typeOrSize = new char[condition.length()];
					strcpy(typeOrSize, condition.c_str());
					if (strcmp(typeOrSize, "integer") == 0)
					{
						type = 1;
						table >> condition;
						//delete typeOrSize;
						typeOrSize = new char[condition.length()];
						strcpy(typeOrSize, condition.c_str());
						if (atoi(variableToBeWritten) > atoi(typeOrSize))
						{
							cout << endl << "Numeric value too large, nothing written." << endl;
							break;
						}
						else
						{
							int var = atoi(variableToBeWritten);
							output.write((char*)&var, sizeof(int));
						}
					}
					else if (strcmp(typeOrSize, "text") == 0)
					{
						type = 0;
						table >> condition;
						//delete typeOrSize;
						typeOrSize = new char[condition.length()];
						strcpy(typeOrSize, condition.c_str());

						if (strlen(variableToBeWritten) > atoi(typeOrSize))
						{
							cout << endl << "Text too large, nothing written." << endl;
							break;
						}
						else
						{

							variableToBeWritten[strlen(variableToBeWritten) ] = '\0';
							
							int charSize = strlen(variableToBeWritten);
							output.write((char*)&charSize, sizeof(int));
							output.write((char*)(variableToBeWritten), charSize * sizeof(char));
						}
					}
					

					table >> condition;

				}
				table.close();
				ok = 1;

			}
		}
		else cout << endl << "Unfortunately, the file " << numeFisier << " doesn't exist. We're not able to import data from it." << endl;

		output.close();
		inCsv.close();


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
			return;
		}
		cout << endl << "Table not found" << endl;
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