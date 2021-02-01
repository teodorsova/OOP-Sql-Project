#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "table.h"
#include "parse.h"
#include "insert.h"
#include "drop.h"
#include "column.h"
#include "config.h"
#include "import.h"
#include "display.h"
#include "delete.h"
#include "update.h"

using namespace std;

int main(int argc, char* argv[])
{
	string command, keyboard, choice;
	int status, noTables = 0, ok = 0;
	char* fileName = nullptr, * tableNames = nullptr;
	TABLE* table = nullptr;
	ifstream file;
	ofstream output;

	file.open(argv[1]);
	FILENAME fName;

	if (file.is_open() == true)
	{
		cout << "Program was opened with comenzi.txt file. Do you want to execute it? Y/N" << endl;
		
		getline(cin, choice);
		if (choice == "Y")
		{
			cout << "OPENING COMMANDS FILE AND EXECUTING IT..." << endl;
			while (getline(file, command))
			{
				PARSE p(command);
				status = p;

				switch (status)
				{
				case 1:
				{
					fileName = new char[fName.getName().length() + 4];
					strcpy(fileName, fName.getFileName().c_str());
					output.open(fileName, ios::out);
					table = new TABLE(command, fileName);
					output.close();//__________
					string renam = table->getNameInString();
					renam += ".txt";
					if (table->fileExists(renam) == 1)
					{
						cout << "The file " << renam << " already exists! Skipping..." << endl;//IF NOT EXISTS
						std::remove(fileName);

					}
					else
					{
						rename(fileName, renam.c_str());
						//output.open(renam, ios::out);
						noTables++;
						CONFIG conf(renam);
						//fName.setId(noTables, config)

					}
					//output.close();
					break;
				}

				case 3:
				{
					DROP dropF(p.getBuffer());

					break;
				}

				/*case 5:
				{
					for (int i = 0; i < noTables; i++)
					{
						if (strcmp(p.getBuffer(), (*tables[i]).getName()) == 0)

							//cout << *tables[i];
							ok = 1;

					}
					if (ok == 0)
						cout << endl << "Invalid name";
					ok = 0;
					break;
				}*/

				case 5:
				{
					DISPLAY dispF(p.getBuffer(), command);
					break;
				}

				case 6:
				{
					INSERT insF(p.getBuffer(), command);
					break;
				}

				case 7:
				{
					SELECT selF(command);
					break;
				}

				case 8:
				{
					UPDATE upF(command);
					break;
				}

				case 9:
				{
					DELETE delF(command);
					break;
				}

				case 10:
				{

					IMPORT impF(p.getBuffer(), command);
					break;
				}

				default:
				{
					//cout << endl << "Exiting program..." << endl;
					break;
				}
				}
			}
		cout << endl << "Done reading from file... Switching to keyboard mode..." << endl;
	}


	}


	cout << "Enter your command from keyboard or 0 to exit: " << endl;
	//cin >> command;
	while (getline(cin, keyboard))
	{
		if (keyboard == "0")
			break;
		PARSE p(keyboard);
		status = p;

		switch (status)
		{
		case 1:
		{
			fileName = new char[fName.getName().length() + 4];
			strcpy(fileName, fName.getFileName().c_str());
			output.open(fileName, ios::out);
			table = new TABLE(keyboard, fileName);
			output.close();//__________
			string renam=table->getNameInString();
			renam += ".txt";
			if (table->fileExists(renam) == 1)
			{
				cout << "The file " << renam << " already exists! Skipping...";//IF NOT EXISTS
				std::remove(fileName);

			}
			else
			{
				rename(fileName, renam.c_str());
				//output.open(renam, ios::out);
				noTables++;
				CONFIG conf(renam);
				//fName.setId(noTables, config)

			}
			//output.close();
			break;
		}

		case 3:
		{
			DROP dropK(p.getBuffer());

			break;
		}

		/*case 5:
		{
			for (int i = 0; i < noTables; i++)
			{
				if (strcmp(p.getBuffer(), (*tables[i]).getName()) == 0)

					//cout << *tables[i];
					ok = 1;

			}
			if (ok == 0)
				cout << endl << "Invalid name";
			ok = 0;
			break;
		}*/
		case 5:
		{
			DISPLAY dispK(p.getBuffer(), keyboard);
			break;
		}
		case 6:
		{
			INSERT insK(p.getBuffer(), keyboard);
			break;
		}

		case 7:
		{
			SELECT selK(keyboard);
			break;
		}

		case 8:
		{
			UPDATE upK(keyboard);
			break;
		}

		case 9:
		{
			DELETE delK(keyboard);
			break;
		}

		case 10:
		{

			IMPORT impK(p.getBuffer(), keyboard);
			break;
		}

		default:
		{
			break;
		}
		}
		cout << endl << "Done. Type another command or 0 to exit: " << endl;
	}
	file.close();
	return 0;
}