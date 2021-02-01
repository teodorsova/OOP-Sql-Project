#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "column.h"
#include "CRUD.h"
using namespace std;

class DELETE : public CRUD {
	
public:
	DELETE(string command)
	{
		this->setCommand(command);
		this->checkCondition();
	}

	


	void readAndWrite(int status)
	{
		char buffer[1000];
		char* colName = nullptr;
		int var, size = 0, fileSize, pos = 0, ok = 0;
		ofstream tempFile;
		string condition, temp;
		int noOfColumns;
		table >> noOfColumns;
		input.open(this->tableName + ".bin", ios::in | ios::binary);
		tempFile.open("temp.bin", ios::out | ios::binary);
		input.seekg(0, ios::end);
		fileSize = input.tellg();
		input.seekg(0, ios::beg);

		while (input.tellg() < fileSize)
		{
			char* tempValue = new char, * columnName = nullptr;
			for (int i = 0; i < noOfColumns; i++)       //reads a record COLUMN BY COLUMN
			{
				table >> condition;
				temp = condition; //name of the field
				columnName = new char[temp.length()];
				strcpy(columnName, temp.c_str());
				table >> condition;
				if (strcmp(condition.c_str(), "integer") == 0)
				{
					table >> condition;
					input.read((char*)&var, sizeof(int));
					this->col[i] = new COLUMN(columnName, 0, (int)condition.c_str(), var);
				}
				else if (strcmp(condition.c_str(), "text") == 0)
				{
					table >> condition;
					input.read((char*)&size, sizeof(int)); //size of string
					input.read((char*)buffer, size * sizeof(char));
					buffer[size] = '\0';
					this->col[i] = new COLUMN(columnName, 1, (int)condition.c_str(), buffer);
				}

				table >> condition;
			}

			for (int i = 0; i < noOfColumns; i++)	//checks each record for WHERE condition
			{
				if (this->sign == "<" && strcmp((*this->col[i]).getName(), this->var.c_str()) == 0)
				{
					var = (*this->col[i]).getInteger();
					if (var < this->value)
						ok = 1;
				}
				else if (this->sign == "<=" && strcmp((*this->col[i]).getName(), this->var.c_str()) == 0)
				{
					var = (*this->col[i]).getInteger();
					if (var <= this->value)
						ok = 1;
				}
				else if (this->sign == ">" && strcmp((*this->col[i]).getName(), this->var.c_str()) == 0)
				{
					var = (*this->col[i]).getInteger();
					if (var > this->value)
						ok = 1;
				}
				else if (this->sign == ">=" && strcmp((*this->col[i]).getName(), this->var.c_str()) == 0)
				{
					var = (*this->col[i]).getInteger();
					if (var > this->value)
						ok = 1;
				}
				else if (this->sign == "==" && strcmp((*this->col[i]).getName(), this->var.c_str()) == 0)
				{
					buffer[0] = *(*this->col[i]).getDataType();
					if (buffer[0] == 'i')
					{
						var = (*this->col[i]).getInteger();
						if (var == this->value)
							ok = 1;
					}
					else if (buffer[0] == 't')
					{
						tempValue = (*this->col[i]).getValue();
						if (strcmp(tempValue, this->text.c_str()) == 0)
							ok = 1;
					}
				}
			}
			if (ok == 0) //if record does not meet delete conidition, write it to temp.bin, else ignore it (so it gets deleted)
			{
				for (int i = 0; i < noOfColumns; i++)
				{
					cout << endl << (*this->col[i]).getName() << ": ";

					if ((*this->col[i]).getValue() != nullptr)
					{
						cout << (*this->col[i]).getValue();
						var = strlen((*this->col[i]).getValue());
						tempFile.write((char*)&var, sizeof(int));
						tempFile.write((char*)(*this->col[i]).getValue(), strlen((*this->col[i]).getValue()) * sizeof(char));
					}
					else
					{
						cout << (*this->col[i]).getInteger();
						var = (*this->col[i]).getInteger();
						tempFile.write((char*)&var, sizeof(int));
					}

				}
				cout << endl;
			}
			ok = 0;


			/*if (input.eof())
				break;*/
			table.clear();
			table.seekg(0);
			table >> condition;
			table >> condition;
		}
		input.close();
		tempFile.close();
		std::remove((this->tableName + ".bin").c_str());   //make temp.bin the new binary file for given table
		this->tableName += ".bin";
		rename("temp.bin", (this->tableName).c_str());
		cout << endl;

	}

	void checkCondition() //checks for keywords FROM, WHERE, stores table name
	{
		int pos = 6, status;
		string condition;
		char* tempCommand = new char[this->command.length()];
		strcpy(tempCommand, this->command.c_str());
		this->setBuffer(this->nextWord(pos, tempCommand));
		if (strcmp(this->buffer, "FROM") == 0)
		{
			status = 1;
			this->setBuffer(this->nextWord(pos, tempCommand));
			if(this->buffer!=nullptr)
			this->tableName = this->buffer;
			else
			{
				cout << endl << "ERROR! Missing table name.";
				return;
			}
			if (strcmp(this->buffer, "WHERE") == 0)
			{
				cout << endl << "ERROR! Missing table name.";
				return;
			}
			else
			{
				cout << endl << "Deleting from table " << this->buffer << endl;
				this->setBuffer(this->nextWord(pos, tempCommand));
			}
		}
		else
		{
			cout << endl << "Missing FROM..." << endl;
			return;
		}
		if (this->buffer != nullptr)
		{
			if (strstr(this->buffer, "WHERE") != NULL)
			{
				this->setBuffer(this->nextWord(pos, tempCommand));
				if (this->buffer != nullptr)
				{
					condition += this->buffer;
					cout << endl << "Where this condition is fulfilled: " << this->buffer;
					this->setBuffer(this->nextWord(pos, tempCommand));
				}
				else
				{
					cout << endl << "ERROR! Missing or partial condition.";
					return;
				}
				if (this->buffer != nullptr)
				{
					condition += this->buffer;
					cout << this->buffer;
					this->setBuffer(this->nextWord(pos, tempCommand));
				}
				else
				{
					cout << endl << "ERROR! Missing or partial condition.";
					return;
				}
				if (this->buffer != nullptr)
				{
					condition += this->buffer;
					cout << this->buffer;
					cond = true;
					this->parseCond(condition);
				}
				else
				{
					cout << endl << "ERROR! Missing or partial condition.";
					return;
				}

			}
		}
		else
		{
			cout << endl << "ERROR! Missing WHERE..." << endl;
			return;
		}

	}

};