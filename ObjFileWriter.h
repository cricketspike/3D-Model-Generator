/*
Henry Chang
ObjFileWriter.h
Header file for ObjFileWriter.cpp
ObjFileWriter currently takes float values of coordinates and parses them into .obj format.
The coordinates are normalized to a zero to one range.
This class can be expanded to take other values and write them to .obj files.
*/
#ifndef OBJFILEWRITER_H
#define OBJFILEWRITER_H

#include <list>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

const int EMPTY = 0;
const int X = 0;
const int Y = 1;
const int Z = 2;

class ObjFileWriter {
private:


	ofstream objFile;
	string fileName;
	list<float> * coordinateValues;


public:
	// Constructor-Destructor

	// Default constructor creates an output file named default.obj.
	ObjFileWriter::ObjFileWriter();

	// Constructor with a string parameter that specifies the .obj file name.
	ObjFileWriter::ObjFileWriter(string objFileName);
	
	ObjFileWriter::~ObjFileWriter();

	// Access Methods

	char* getFileName();

	// Manipulation Methods
	
	// Add coordinates to the writer ready to be printed onto the .obj file.
	void addCoordinates(float xCoordinate, float yCoordinate, float zCoordinate);
	
	// Processes the added coordinates and print them to the out file.
	void writeToObjFile();

	// Other and Helper Methods

	void coordinatesConvertToString(float xCoordinate, float yCoordinate, float zCoordinate);

	void normalizeCoordinate(list coordinateValue);

	bool compareFloat(const float first, const float second);

	float popFrontAndLook(list thisList);
};


#endif // OBJFILEWRITER_H


