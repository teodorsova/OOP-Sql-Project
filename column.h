#pragma once
#include <iostream>
#include <string>


using namespace std;

class COLUMN
{
public:
	const int id = 0;

private:
	char* name = nullptr;
	char* defaultValue = nullptr;
	char* dataType = nullptr;
	int dim = 0;
	int integer = 0;
	static int noColumns;
	int type;

public:
	COLUMN() : id{ (++COLUMN::noColumns) }
	{
		cout << endl << "Creating column " << id << "..." << endl;
	}

	COLUMN(char* columnName, char* dataType, int dim, char* defaultValue) : id{ ++COLUMN::noColumns }
	{
		this->setName(columnName);
		this->setValue(defaultValue);
		this->setDim(dim);
		this->setDataType(dataType);
	}

	COLUMN(char* columnName, int dataType, int dim, char* defaultValue) : id{ ++COLUMN::noColumns }
	{
		this->setName(columnName);
		this->setValue(defaultValue);
		this->setDim(dim);
		this->setDataType(dataType);
	}
	COLUMN(char* columnName, int dataType, int dim, int integer) : id{ ++COLUMN::noColumns }
	{
		this->setName(columnName);
		this->setInteger(integer);
		this->setDim(dim);
		this->setDataType(dataType);
	}
	COLUMN( int dim, char* defaultValue, int dataType) : id{ ++COLUMN::noColumns }
	{
		this->setValue(defaultValue);
		this->setDim(dim);
		this->setType(dataType);
	}

	COLUMN( int dim, int integer, int dataType) : id{ ++COLUMN::noColumns }
	{
		this->setInteger(integer);
		this->setDim(dim);
		this->setType(dataType);
	}


	//~COLUMN()
	//{
	//	if (this->name != nullptr)
	//	delete this->name;
	//	if (this->defaultValue != nullptr)
	//	delete this->defaultValue;
	//	//if (this->dataType != nullptr)
	//		//delete this->dataType;
	//	//COLUMN::noColumns--;
	//}

	void setInteger(int integer)
	{
		this->integer = integer;
	}

	void setType(int type)
	{
		this->type = type;
	}

	int getType()
	{
		return this->type;
	}

	void setDataType(char* dataType)
	{
		if (this->dataType != nullptr)
			delete this->dataType;
		this->dataType = new char[strlen(dataType) + 1];
		strcpy(this->dataType, dataType);
		this->dataType[strlen(dataType)] = '\0';
	}

	void setDataType(int dataType)
	{
		delete this->dataType;
		if (dataType == 1)
		{
			this->dataType = new char[strlen("text") + 1];
			strcpy(this->dataType, "text");
		}
		else if (dataType == 0)
		{
			this->dataType = new char[strlen("integer") + 1];
			strcpy(this->dataType, "integer");
		}
	}


	void setValue(char* defaultValue)
	{
		if (this->defaultValue != nullptr)
			delete this->defaultValue;
		this->defaultValue = new char[strlen(defaultValue) + 1];
		strcpy(this->defaultValue, defaultValue);
		this->defaultValue[strlen(defaultValue)] = '\0';
	}

	char* getDataType()
	{
		return this->dataType;
	}

	char* getName()
	{
		return this->name;
	}

	char* getValue()
	{
		return this->defaultValue;
	}

	int getDim()
	{
		return this->dim;
	}

	int getInteger()
	{
		return this->integer;
	}

	void setName(char* columnName)
	{
		if (this->name != nullptr)
			delete this->name;
		this->name = new char[strlen(columnName) + 1];
		strcpy(this->name, columnName);
		columnName[strlen(columnName)] = '\0';
	}


	void setDim(int x) {
		this->dim = x;
	}
	friend class TABLE;
	/*friend ostream &operator <<(ostream& console, COLUMN& column);*/

};

int COLUMN::noColumns = 0;

/*ostream &operator <<(ostream& console, COLUMN& column)
{
	if (column.id)
		console << endl << "Column id: " << column.id;
	if (column.getName() != nullptr)
		console << endl << "Column name: " << column.getName();


	if (column.getText() == nullptr)
		console << endl << "Data type: number" << endl << "Value: " << column.getNumber();
	else
		console << endl << "Data type: text" << endl << "Value: " << column.getText();
	console << endl << "Size: " << column.getDim();
	return console;
}*/