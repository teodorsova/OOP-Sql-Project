# OOP-Sql-Project

This is a very basic remake of SQL Lite made in C++ using OOP concepts. 
The project was part of the university requirements at the C++ OOP seminar/labs.

***************************************************
COMMAND EXAMPLES THAT CAN BE USED WITH THIS PROGRAM
***************************************************

CREATE TABLE students ((id, integer, 1000, 0), (name, text, 128, ''), (group, text,50,'1000'))

DROP TABLE students

DISPLAY TABLE students //NOT a select. Displays the table properties (columns and their type)

INSERT INTO students VALUES (1,'John','1001')

SELECT (name) FROM students WHERE id > 5

SELECT ALL FROM students WHERE id = 1

SELECT ALL FROM students WHERE name = John

UPDATE students SET name = "Andrew" WHERE name = "John"

DELETE FROM students WHERE name = "Andrew"

IMPORT elevi elevi.csv //Comma separated value file with data for an already existing table

*********************************************************************************************************
The program can also run command from a command file called "comenzi.txt" (the program will ask at start)
