#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>
#include "config.h"

using namespace std;

class DROP {
	string fileName = "";

public:

	DROP(string name) {
		this->wasTableRemoved(name);
	}

	bool wasTableRemoved(string name)
	{
		string fName = name + ".txt", bfName = name + ".bin";
		if (remove(fName.c_str()) != 0)
		{
			cout << "Failed dropping table " << name << ".";
			return false;
		}
		else
		{
			remove(bfName.c_str());
			CONFIG::deleteEntry(fName);
			cout << "Table " << name << " was dropped successfully";
			return true;
		}
	}


};