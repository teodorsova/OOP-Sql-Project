#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "column.h"
#include "CRUD.h"
using namespace std;

class SELECT : public CRUD {
	
public:
	SELECT()
	{
		cout << endl << "No command passed to CRUD command.";
	}
	SELECT(string command)
	{
		this->setCommand(command);
		this->checkCondition();
	}

	void readAndWrite(int status)
	{
		char buffer[1000];
		char* colName = nullptr;
		int var, size = 0, fileSize, pos = 0, ok = 0;
		ofstream log;
		log.open("log.txt", ios::app);
		string condition, temp;
		int noOfColumns;
		table >> noOfColumns;
		input.open(this->tableName + ".bin", ios::in | ios::binary);
		input.seekg(0, ios::end);
		fileSize = (int)input.tellg();
		input.seekg(0, ios::beg);

		if (status == 100)
		{
			while (input.tellg() < fileSize) {

				for (int i = 0; i < noOfColumns; i++)
				{
					table >> condition;
					temp = condition; //name of the field
					table >> condition;
					if (strcmp(condition.c_str(), "integer") == 0)
					{
						table >> condition;
						input.read((char*)&var, sizeof(int));
						cout << endl << temp << ": " << var;
						log << endl << temp << ": " << var;

					}
					else if (strcmp(condition.c_str(), "text") == 0)
					{

						table >> condition;
						input.read((char*)&size, sizeof(int)); //size of string
						input.read((char*)buffer, size * sizeof(char));
						buffer[size] = '\0';
						cout << endl << temp << ": " << buffer;
						log << endl << temp << ": " << buffer;
					}
					table >> condition;

				}
				/*if (input.eof())
					break;*/
				table.clear();
				table.seekg(0);
				table >> condition;
				table >> condition;
				cout << endl;
			}
			//cout << "_____________________________________________";
		}


		else if (status == 2)
		{
			while (input.tellg() < fileSize)
			{

				for (int i = 0; i < noOfColumns; i++)
				{
					table >> condition;
					temp = condition; //name of the field
					if (storage.find(condition) != std::string::npos)
					{
						table >> condition;
						if (strcmp(condition.c_str(), "integer") == 0)
						{
							table >> condition;
							input.read((char*)&var, sizeof(int));
							cout << endl << temp << ": " << var;
							log << endl << temp << ": " << var;

						}
						else if (strcmp(condition.c_str(), "text") == 0)
						{

							table >> condition;
							input.read((char*)&size, sizeof(int)); //size of string
							input.read((char*)buffer, size * sizeof(char));
							buffer[size] = '\0';
							cout << endl << temp << ": " << buffer;
							log << endl << temp << ": " << buffer;
						}

						table >> condition;
					}
					else
					{
						table >> condition;
						if (strcmp(condition.c_str(), "integer") == 0)
						{
							table >> condition;
							input.read((char*)&var, sizeof(int));


						}
						else if (strcmp(condition.c_str(), "text") == 0)
						{

							table >> condition;
							input.read((char*)&size, sizeof(int)); //size of string
							input.read((char*)buffer, size * sizeof(char));
							buffer[size] = '\0';

						}

						table >> condition;
					}
				}
				/*if (input.eof())
					break;*/
				table.clear();
				table.seekg(0);
				table >> condition;
				table >> condition;

			}
		}

		else
		{

			if (storage == "ALL")
			{
				while (input.tellg() < fileSize) {



					char* tempValue = new char, * columnName = nullptr;
					for (int i = 0; i < noOfColumns; i++)
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

							/*cout << endl << temp << ": " << var;
							log << endl << temp << ": " << var;*/

						}
						else if (strcmp(condition.c_str(), "text") == 0)
						{

							table >> condition;
							input.read((char*)&size, sizeof(int)); //size of string
							input.read((char*)buffer, size * sizeof(char));
							buffer[size] = '\0';
							this->col[i] = new COLUMN(columnName, 1, (int)condition.c_str(), buffer);

							/*cout << endl << temp << ": " << buffer;
							log << endl << temp << ": " << buffer;*/
						}

						table >> condition;
					}

					for (int i = 0; i < noOfColumns; i++)
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
							if (var >= this->value)
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
					if (ok == 1)
					{
						for (int i = 0; i < noOfColumns; i++)
						{
							cout << endl << (*this->col[i]).getName() << ": ";
							if ((*this->col[i]).getValue() != nullptr)
								cout << (*this->col[i]).getValue();
							else
								cout << (*this->col[i]).getInteger();

						}
						cout << endl;
						ok = 0;
					}
					ok = 0;


					/*if (input.eof())
						break;*/
					table.clear();
					table.seekg(0);
					table >> condition;
					table >> condition;
				}
			}
			else
			{
				while (input.tellg() < fileSize) {



					char* tempValue = new char, * columnName = nullptr;
					for (int i = 0; i < noOfColumns; i++)
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

							/*cout << endl << temp << ": " << var;
							log << endl << temp << ": " << var;*/

						}
						else if (strcmp(condition.c_str(), "text") == 0)
						{

							table >> condition;
							input.read((char*)&size, sizeof(int)); //size of string
							input.read((char*)buffer, size * sizeof(char));
							buffer[size] = '\0';
							this->col[i] = new COLUMN(columnName, 1, (int)condition.c_str(), buffer);

							/*cout << endl << temp << ": " << buffer;
							log << endl << temp << ": " << buffer;*/
						}

						table >> condition;
					}

					for (int i = 0; i < noOfColumns; i++)
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
					if (ok == 1)
					{
						for (int i = 0; i < noOfColumns; i++)
						{
							if (this->storage.find((*this->col[i]).getName()) != storage.npos)
							{
								cout << endl << (*this->col[i]).getName() << ": ";
								if ((*this->col[i]).getValue() != nullptr)
									cout << (*this->col[i]).getValue();
								else
									cout << (*this->col[i]).getInteger();
							}

						}
						cout << endl;
						ok = 0;
					}
					ok = 0;


					/*if (input.eof())
						break;*/
					table.clear();
					table.seekg(0);
					table >> condition;
					table >> condition;
				}
			}
		}



		cout << endl;
		log.close();
		input.close();
	}



	

	void checkCondition()
	{
		int pos = 6, whatToSelect = 0;
		string condition = "";
		char* tempCommand = new char[this->command.length()];
		strcpy(tempCommand, this->command.c_str());
		this->setBuffer(this->nextWord(pos, tempCommand));
		if (strcmp(this->buffer, "ALL") == 0)
		{
			storage = "ALL";
			this->setBuffer(this->nextWord(pos, tempCommand));
			
			if (strstr(this->buffer, "FROM") != NULL)
			{
				whatToSelect = 1;
				this->setBuffer(this->nextWord(pos, tempCommand));

			}
			if (whatToSelect == 1) {
				if (this->buffer != nullptr)
				{
					cout << endl << "Searching in table " << this->buffer;
					tableName = this->buffer;
					this->setBuffer(this->nextWord(pos, tempCommand));
				}
				else
				{
					cout << endl << "ERROR! Missing table name!";
				}
			}
			else cout << endl << "Incomplete command, missing FROM" << endl;
			whatToSelect = 100; //100 - select ALL
			//executeSelect(whatToSelect);
			//this->setBuffer(this->nextWord(pos, tempCommand));

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
				condition = "No condition.";
				whatToSelect = 100;
				this->executeSelect((whatToSelect));
			}

		}
		else if (strcmp(this->buffer, "FROM") == 0)
		{
			cout << endl << "ERROR! Missing collumn names.";
		}
		else
		{
			cout << endl << "Searching for column(s) " << this->buffer;
			storage += this->buffer;
			while (tempCommand[pos] == ',') {
				this->setBuffer(this->nextWord(pos, tempCommand));
				cout << " ," << this->buffer;
				storage = storage + "," + this->buffer;
			}
			/*while (tempCommand[pos] == ')') {
				this->setBuffer(this->nextWord(pos, tempCommand));
				cout << " ," << this->buffer;
				storage = storage + "," + this->buffer;

			}*/
			this->setBuffer(this->nextWord(pos, tempCommand));
			if (strstr(this->buffer, "FROM") != NULL)
			{
				whatToSelect = 1;
				this->setBuffer(this->nextWord(pos, tempCommand));

			}
			if (whatToSelect == 1) {
				if (this->buffer != nullptr)
				{
					cout << endl << "Searching in table " << this->buffer;
					tableName = this->buffer;
					this->setBuffer(this->nextWord(pos, tempCommand));
				}
				else
				{
					cout << endl << "ERROR! Missing table name!";
				}
			}
			else cout << endl << "Incomplete command, missing FROM" << endl;
			bool cond = false;
			string condition = "";
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
				else
				{
					cout << endl << "ERROR! Missing WHERE.";
				}
			}
			else
			{
				condition = "No condition.";
				whatToSelect = 2;
				this->executeSelect((whatToSelect));
			}
		}

	}
};