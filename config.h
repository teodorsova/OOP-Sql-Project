#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

using namespace std;

class CONFIG {
	string fileName = "";
	ofstream out;
	ifstream in;
public:
	CONFIG(string fileName) {
		//
		in.open("config.txt", ios::in);
		string search = "";
		bool isFound = 0;
		while (out.eof())
		{
			getline(in, search);
			if (search.find(fileName) != search.npos)
			{
				isFound = 1;
				break;
			}

		}
		in.close();
		if (isFound == 0)
		{
			out.open("config.txt", ios::app);
			out.write(fileName.c_str(), fileName.length() * sizeof(char));
			out << endl;
			out.close();
		}


	}

	static void deleteEntry(string fileName) {
		ifstream in;
		ofstream out;
		in.open("config.txt", ios::in);
		out.open("temp.txt", ios::app);
		string search = "";

		while (getline(in, search))
			if (search.find(fileName) == search.npos)
				out << search << endl;

		in.close();
		out.close();
		remove("config.txt");
		rename("temp.txt", "config.txt");
	}
};