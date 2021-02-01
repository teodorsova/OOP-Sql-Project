#pragma once
#include <iostream>
#include <string>
#include "column.h"
#include "IOTable.h"
#include "file_name.h"

using namespace std;

class TABLE
{
	char* name = nullptr;
	string command = "";
	COLUMN* col = nullptr;
	int noOfColumns = 0;
	char* storage = nullptr;
	char* fileName = nullptr;
	ofstream outputFile;
	//FILENAME fName;

public:
	TABLE()
	{
		cout << "Default constructor";
	}

	TABLE(string command, char* fileName)
	{
		this->setCommand(command);
		this->copyCommand(command);
		this->setFile(fileName);
		this->createTable();
	}

	~TABLE()
	{
		delete this->name;
		delete this->col;
		delete this->storage;
		delete this->fileName;
	}

	string getCommand()
	{
		return this->command;
	}

	void setFile(char* fileName)
	{
		this->outputFile.open(fileName, ios::app);
	}

	void setCommand(string command)
	{
		this->command = command;
	}

	void copyCommand(string command)
	{
		if (this->storage != nullptr)
			delete this->storage;
		this->storage = new char[command.length()];
		command.copy(this->storage, command.length());
		this->storage[command.length()] = '\0';
	}
	char* getStorage()
	{
		return this->storage;
	}

	char* getName()
	{
		return this->name;
	}

	string getNameInString()
	{
		string tempName = this->getName();
		return tempName;
	}

	void setName(char* name)
	{
		this->name = name;
	}

	int getNoColumns()
	{
		return this->noOfColumns;
	}

	char* nextWord(int& cPos, char* str)
	{
		int k = 0, i = 0, j = 0;
		char* c = nullptr;
		if (str[cPos] != 0)
		{
			while (str[cPos] == ' ' || str[cPos] == '(' || str[cPos] == ')' || str[cPos] == ',' ||  str[cPos] == '\"')
				cPos++;
			i = cPos;
			while (str[i] != ' ' && str[i] != '(' && str[i] != ')' && str[i] != ','  && str[i] != '\"')
			{
				k++;
				i++;
				if (str[i] == ' ' || str[i] == '(' || str[i] == ')' || str[i] == ',' ||  str[i] == '\"' || str[i] == 0)
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

	static bool fileExists(const string& filename)
	{
		struct stat buf;
		if (stat(filename.c_str(), &buf) != -1)
		{
			return true;
		}
		return false;
	}

	void createTable()
	{
		int pos = 0, i = 0, size = 0, ok = 0; //0 for text, 1 for integer
		char* temp = this->nextWord(pos, this->getStorage()), * columnName = nullptr, * defaultValue = nullptr, * type = nullptr, * dataType = nullptr, * temp2;
		temp = this->nextWord(pos, this->getStorage());
		temp = this->nextWord(pos, this->getStorage());
		this->setName(temp);
		//cout << this->name;
		while (true)
		{
			temp = this->nextWord(pos, this->getStorage());
			if (strstr(temp, "integer") != NULL || strstr(temp, "text") != NULL)
			{
				cout << endl << "ERROR. Missing table name.";
				return;
			}
			if ((*temp) == NULL)
			{
				break;
			}
			temp = this->nextWord(pos, this->getStorage());
			temp = this->nextWord(pos, this->getStorage());
			temp = this->nextWord(pos, this->getStorage());
			this->noOfColumns++;
		}
		delete[] temp;
		temp = new char[this->command.size()];
		strcpy(temp, this->command.c_str());
		pos = 0;
		temp2 = this->nextWord(pos, temp);
		temp2 = this->nextWord(pos, temp);
		temp2 = this->nextWord(pos, temp);
		for (i = 0; i < this->noOfColumns; i++)
		{
			columnName = this->nextWord(pos, temp);
			dataType = this->nextWord(pos, temp);
			size = atoi(this->nextWord(pos, temp));
			defaultValue = this->nextWord(pos, temp);
			col = new COLUMN(columnName, dataType, size, defaultValue);
			if (ok == 0)
			{
				io_table* io = new io_table(*col, this->getName(), outputFile, false, this->noOfColumns);
				ok = 1;
			}
			else
				io_table* io = new io_table(*col, this->getName(), outputFile, true, this->noOfColumns);
		}
		this->outputFile.close();

	}


	friend class PARSE;
	/*friend ostream& operator <<(ostream& console, const TABLE& table);*/
	friend bool operator == (char* nume, TABLE table);
};

/*ostream& operator <<(ostream& console, const TABLE& table)
{
	unsigned i = 0;
	console << endl << "--------------------";
	if (table.name != nullptr)
	{
		console << endl << "Name: ";
		for (i = 0; i < strlen(table.name); i++)
			console << table.name[i];
		i = 0;
		while (i < table.noOfColumns)
		{
			cout << endl << *(table.col+(i*sizeof(TABLE)));
			i++;
		}

	}
	cout << endl << "--------------------" << endl;
	return console;
}*/

bool operator == (char* nume, TABLE table)
{
	if (strcmp(nume, table.getName()))
		return true;
	return false;
}
