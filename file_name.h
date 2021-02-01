#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;


class FILENAME {
	string name = "";
	string command = "";
	char* temp = new char;
	int id[10] = { 0 };
public:

	FILENAME()
	{

	}

	FILENAME(int status, ofstream& config) {
		this->setId(status, config);
	}
	/*~FILENAME() {
		delete temp;
	}*/
	int getId(int pos)
	{
		return this->id[pos];
	}
	string getName()
	{
		return this->name;
	}

	void setId(int status, ofstream& config)
	{

		if (status == 1)
		{
			this->command = "TABLE";
		}
		else if (status == 2)
			this->command = "INDEX";
		else if (status == 3)
			this->command = "DROP TABLE";
		else if (status == 4)
		{
			this->command = "DROP INDEX";
		}
		else if (status == 5)
			this->command = "DISPLAY TABLE";
		else if (status == 6)
			this->command = "INSERT";
		else if (status == 7)
			this->command = "SELECT";
		else if (status == 8)
			this->command = "UPDATE";
		else if (status == 9)
			this->command = "DELETE";
		this->id[status]++;
		_itoa(id[status], temp, 10);
		this->name += this->command + "_" + temp;

	}

	string getFileName() {
		//char* y = new char[name.length()];
		//strcpy(y, this->name.c_str());
		//strcat(y, ".txt");
		//this->name = "";
		string y = this->name + ".txt";
		this->name = "";
		return y;
	}
};
