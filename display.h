#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "table.h"

using namespace std;

class DISPLAY {
	string name = "";
	ifstream in;
	string command = "";


public:

	DISPLAY(char* name, string command)
	{
		this->display(name, command);
	}

	void display(char* name, string command)
	{
		int pos = 13;
		this->name = name;
		this->name += ".txt";
		if (TABLE::fileExists(this->name) == 0)
			cout << "The table " << name << " doesn't exist.";
		else {
			in.open(this->name, ios::in);
			cout << endl;
			string temp = "";
			getline(in, temp);
			getline(in, temp);
			while (getline(in, temp))
				cout << temp << endl;
			in.close();
		}
	}


};