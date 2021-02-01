#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "column.h"
using namespace std;

class CRUD
{
protected:
	string cond = "";// id>1	ceva=1	altceva<=10
	string var = "";
	string sign = "";
	int value = 0;
	string text = "", command = "", storage = "", tableName = ""; //storage stores the column names that are in the select, if any; text stores the WHERE condition, if any
	char* buffer = nullptr;
	COLUMN** col = new COLUMN*;
	ifstream table, config, input;

public:
	CRUD()
	{
		
	}
	CRUD(string command)
	{
		this->setCommand(command);
		this->checkCondition();
	}

	virtual void checkCondition() = 0;
	virtual void readAndWrite(int status) = 0;

	void executeSelect(int status)  //Opens the table definition file and initiates the delete command
	{
		string temp;
		int noTables = 0;
		config.open("config.ini");
		config >> noTables;
		table.open(this->tableName + ".txt");
		table >> temp;
		if (temp == this->tableName)
		{
			this->readAndWrite(status);
			table.close();
			config.close();
			return;
		}
		table.close();
		config.close();
		cout << endl << "Table does not exist." << endl;
	}

	char* getBuffer(char* buffer)
	{
		return this->buffer;
	}

	string getStorage()
	{
		return this->storage;
	}

	void setValue(int value)
	{
		this->value = value;
	}


	void setCommand(string command)
	{
		this->command = command;
	}

	void setBuffer(char* buffer)
	{
		this->buffer = buffer;
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
	void parseCond(string cond) { //checks for the VARIABLE, SIGN and CONDITION after WHERE keyword
		char allSigns[] = "<=>";
		int i = 0, status = 0;
		while (strchr(allSigns, cond[i]) == nullptr && i < cond.length()) {
			this->var += cond[i];
			i++;
		}
		//i++;//trece peste spatiul din id = 1
		switch (cond[i]) {

		case '<': {
			if (cond[i + 1] == '=')
			{
				this->sign = "<=";
				i += 2;
				status = 1;
			}
			else {
				this->sign = '<';
				i++;
				status = 1;
			}
			break;
		}

		case '>': {
			if (cond[i + 1] == '=')
			{
				this->sign = ">=";
				i += 2;
				status = 1;
			}
			else {
				this->sign = '>';
				i++;
				status = 1;
			}
			break;
		}

		case '=': {
			{this->sign = "==";
			i++; }
			status = 1;
			break;
		}

		default: {
			cout << "No sign detected.";
			status = -1;
			break;
		}

		}

		//i++;//trece peste inca un spatiu
		if (isalpha(cond[i]) != 0)
		{
			char* txt = new char[100];
			strcpy(txt, cond.c_str() + i);
			this->text = txt;
			//delete[] txt;
		}
		else {
			char* txt = new char;
			strcpy(txt, cond.c_str() + i);
			this->setValue(atoi(txt));
		}

		//int j = i;
		/*while (cond[i] != '\n') {
			j++;
		}*/

		//temp[j] = '\n';
		this->showCondition();
		this->executeSelect(status);
	}

	void showCondition() {
		cout << endl << "The condition is: " << this->var << this->sign;
		if (this->text == "")
			cout << this->value << endl;
		else cout << this->text << endl;

	}
};