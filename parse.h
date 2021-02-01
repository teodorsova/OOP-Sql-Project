#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "select.h"
#include "drop.h"

using namespace std;


class PARSE {
	string command = "";
	string storage = "";
	int status = 0;
	char* buffer = nullptr;
public:

	PARSE()
	{
		cout << endl << "Parser initialized." << endl;
	}

	PARSE(string command) {
		this->command = command;
		this->processCommand();
	}
	~PARSE()
	{
		if (buffer != nullptr)
			delete buffer;
	}

	char* getBuffer()
	{
		return this->buffer;
	}

	string getStorage()
	{
		return this->storage;
	}

	void setBuffer(char* buffer)
	{
		if (this->buffer != nullptr)
			delete this->buffer;
		this->buffer = buffer;
	}
	void setCommand(string command)
	{
		this->command = command;
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

	void processCommand()
	{
		int status = 0, pos = 0;
		char* temp = new char[command.length()];
		strcpy(temp, command.c_str());
		temp[strlen(temp)] = '\0';
		const char* cmd = "CREATE TABLE";
		if (command.find(cmd) == 0)
			status = 1;
		else if (command.find("CREATE INDEX") == 0)
			status = 2;

		else if (command.find("DROP TABLE") == 0)
			status = 3;
		else if (command.find("DROP INDEX") == 0)
			status = 4;

		else if (command.find("DISPLAY TABLE") == 0)
			status = 5;

		else if (command.find("INSERT INTO") == 0 && command.find("VALUES") != command.npos)
			status = 6;
		else if (command.find("SELECT") == 0 && command.find("FROM") != command.npos)
			status = 7;
		else if (command.find("UPDATE") == 0 && command.find("SET") != command.npos)
			status = 8;
		else if (command.find("DELETE FROM") == 0)
			status = 9;
		else if (command.find("IMPORT") == 0)
			status = 10;
		else cout << "Wrong command.";

		switch (status)
		{
		case 1:
		{
			cout << endl << "initializing CREATE TABLE..." << endl;
			break;
		}
		case 2:
		{
			cout << endl << "initializing CREATE INDEX...";
			pos = 13;
			this->setBuffer(this->nextWord(pos, temp));
			cout << endl << "Creating index " << this->buffer << endl;
			break;
		}
		case 3:
		{
			cout << endl << "initializing DROP TABLE...";
			pos = 11;
			this->setBuffer(this->nextWord(pos, temp));
			if (command.find_first_of(this->getBuffer())!=string::npos)
				cout << endl << "Dropping table " << this->buffer << endl;
			else
			{
				cout << "Invalid name" << endl;
				status = 100;
			}
			//DROP drop(this->buffer);
			break;
		}
		case 4:
		{
			cout << endl << "initializing DROP INDEX...";
			pos = 11;
			this->setBuffer(this->nextWord(pos, temp));
			if (this->buffer != nullptr)
				cout << endl << "Dropping index " << this->buffer << endl;
			else cout << endl << "I received no index to drop." << endl;
			break;
		}
		case 5:
		{
			cout << endl << "initializing DISPLAY TABLE..." << endl;
			pos = 14;
			this->setBuffer(this->nextWord(pos, temp));
			if (command.find_first_of(this->getBuffer()) != string::npos)
			cout << "Displaying table " << this->buffer << endl;
			else
			{
				cout << "Invalid name" << endl;
				status = 100;
			}

			break;
		}
		case 6:
		{
			cout << endl << "initializing INSERT INTO command..." << endl;
			pos = 11;
			this->setBuffer(this->nextWord(pos, temp));
			break;
		}
		case 7:
		{
			string tableName;
			pos = 6;
			int ok = 0;
			cout << endl << "initializing SELECT command...";
			break;
		}
		case 8:
		{
			cout << endl << "initializing UPDATE command...";
			pos = 6;
			this->setBuffer(this->nextWord(pos, temp));
			cout << endl << "Updating table " << this->buffer << endl;
			break;
		}
		case 9:
		{
			cout << endl << "initializing DELETE command...";
			pos = 11;
			this->setBuffer(this->nextWord(pos, temp));
			//cout << endl << "Deleteing from column " << this->buffer << endl;

			break;
		}
		case 10:
		{
			cout << endl << "initializing IMPORT command..." << endl;
			pos = 6;
			this->setBuffer(this->nextWord(pos, temp));
			break;
		}
		default:
		{
			cout << "You have entered a wrong command";
			break;
		}
		}
		this->status = status;
	}


	PARSE operator+(int value) {
		this->status += value;
		return *this;
	}

	PARSE operator=(const PARSE& x) {
		if (this != &x) {
			this->status = x.status;
			this->command = x.command;

		}
		return *this;
	}

	PARSE operator!() {
		PARSE x = *this;
		x.status = 0;
		return x;
	}

	operator int()
	{
		return this->status;
	}

	void operator+=(int value) {
		*this = *this + value;
	}

	PARSE operator++() {
		*this += 1;
		return *this;
	}
	PARSE operator++(int) {
		*this += 1;
		return *this;
	}

	int& operator[](int index) {
		this->status = index;
		return this->status;
	}



	friend PARSE operator+(int value, PARSE x);
	friend ostream& operator<<(ostream& out, const PARSE& x);
	friend void operator>>(istream& in, PARSE& x);
	friend bool operator<(PARSE x, PARSE y);
	/*bool operator == (char* name)
	{
		if (name, this->getBuffer() == 0)
			return true;

		return false;
	}*/

	friend class TABLE;
};


PARSE operator+(int value, PARSE x) {
	return x + value;
}

ostream& operator<<(ostream& out, const PARSE& x) {
	out << endl << "___________________________________________________ " << endl;
	out << "Parser Status: " << x.status << endl;
	out << "Parser's command: " << x.command << endl;
	return out;
}

void operator>>(istream& in, PARSE& x) {

	cout << endl << "Please input the command:" << endl;
	char* auxT = new char[500];
	cin.getline(auxT, 500);
	x.command = auxT;

}
bool operator<(PARSE x, PARSE y) {
	if (x.status < y.status) {
		return true;
	}
	else
		return false;
}