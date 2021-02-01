#pragma once
#include <fstream>

#include "table.h"

using namespace std;

class io_table
{
	//COLUMN* col = nullptr;
	char* tableName = nullptr;
	int noOfColumns = 0;
	bool wasNameWritten = false;
public:
	io_table()
	{

	}

	io_table(COLUMN& col, char* tableName, ofstream& file, bool wasNameWritten, int noOfColumns)
	{
		this->setName(tableName);
		this->setBool(wasNameWritten);
		this->setNoOfColumns(noOfColumns);
		this->writeTableToFile(col, file);

	}

	~io_table()
	{
		delete tableName;
	}

	void setNoOfColumns(int no)
	{
		this->noOfColumns = no;
	}

	void setBool(bool wasNameWritten)
	{
		this->wasNameWritten = wasNameWritten;
	}

	void setName(char* tableName)
	{
		if (this->tableName != nullptr)
			delete this->tableName;
		this->tableName = new char[strlen(tableName)];
		strcpy(this->tableName, tableName);
	}

	void writeTableToFile(COLUMN& col, ofstream& file)
	{
		if (file.is_open())
		{
			if (this->wasNameWritten == false)
				file << this->tableName << endl << this->noOfColumns << endl;


			file << col.getName() << " " << col.getDataType() << " " << col.getDim() << " " << col.getValue() << " " << endl;
		}

	}

};