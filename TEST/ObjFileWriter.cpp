/*
Henry Chang
ObjFileWriter.h
Header file for ObjFileWriter.cpp
ObjFileWriter currently takes a vector of ColoredVertex pointers,
convert the rgb their objects are holding to strings, and
print the strings to a .obj file in the approppriate format.
This class can be expanded to take other values and write them to .obj files.
*/

#include "ObjFileWriter.h"
#include <list>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// Constructor-Destructor
ObjFileWriter::ObjFileWriter() {
	fileName = "default.obj";
	construction();
}

ObjFileWriter::ObjFileWriter(string objFileName){
	fileName = objFileName;
	construction();
}

ObjFileWriter::~ObjFileWriter(){
}

// Access Methods
char * ObjFileWriter::getFileName(){
	return fileName;
}

// Manipulation Methods
void ObjFileWriter::addCoordinates(float xCoordinate, float yCoordinate, float zCoordinate) {
	coordinateValues[X].push_front(xCoordinate);
	coordinateValues[Y].push_front(yCoordinate);
	coordinateValues[Z].push_front(zCoordinate);
}

void ObjFileWriter::writeToObjFile(){
	string objLine;
	float xCoordinate, yCoordinate, zCoordinate;
	normalizeCoordinate(coordinateValues[X]);
	normalizeCoordinate(coordinateValues[Y]);
	normalizeCoordinate(coordinateValues[Z]);
	objFile.open(fileName);
	for (int i = 0; i < coordinateValues[X].size(); i++) {
		xCoordinate = popFrontAndLook(coordinateValues[X]);
		yCoordinate = popFrontAndLook(coordinateValues[Y]);
		zCoordinate = popFrontAndLook(coordinateValues[Z]);
		objLine = coordinatesConvertToString(xCoordinate, yCoordinate, zCoordinate);
		objFile << objLine;
	}
	objFile.close();
}

// Other or Helper Methods
string ObjFileWriter::coordinatesConvertToString(float xCoordinate, float yCoordinate, float zCoordinate){
	string xString = to_string(xCoordinate);
	string yString = to_string(yCoordinate);
	string zString = to_string(zCoordinate);
	string fileLine = "v " + xString + " " + yString + " " + zString + "\n";
	return fileLine;
}

void ObjFileWriter::normalizeCoordinate(list coordinateValue){
	float normal, max, min, target, normalizedTarget;
	if (coordinateValue.size() != EMPTY) {
		coordinateValue.sort(compareFloat);
		max = coordinateValue.front();
		min = coordinateValue.back();
		normal = max - min;
		for (int i = 0; i < coordinateValue.size(); i++) {
			target = coordinateValue.front();
			normalizedTarget = target / normal;
			coordinateValue.pop_front();
			coordinateValue.push_back(normalizedTarget);
		}
	}
}

void ObjFileWriter::construction() {
	coordinateValues = { xValue, yValue, zValue };
	objFile.open(fileName);
	objFile << "# " << fileName << ".obj File.\n" << "g\n";
	objFile.close();
}

bool ObjFileWriter::compareFloat(const float first, const float second) {
	if (first > second) 
		return true;
	else 
		return false;
}

float ObjFileWriter::popFrontAndLook(list thisList) {
	float front = thisList.front();
	thisList.pop_front();
	return front;
}