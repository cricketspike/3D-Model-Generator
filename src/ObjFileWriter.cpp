/*
 * ObjFileWriter.cpp
 * Henry Chang
 */

#include "ObjFileWriter.h"

ObjFileWriter::ObjFileWriter(){};
ObjFileWriter::~ObjFileWriter(){};

ColoredVertexMatrix & ObjFileWriter::initialize(ColoredVertexMatrix & CoordinateMap){
	CoordinateMatrix = CoordinateMap;
	vertexLabel = 1;
	normalizeVertices(CoordinateMatrix);
	return CoordinateMatrix;
}	

void ObjFileWriter::execute(string fileName, ColoredVertexMatrix & CoordinateMap, vector<int> faces){
	ColoredVertexMatrix normalCoordinateMap = initialize(CoordinateMap);
	printVerticesToFile(fileName, normalCoordinateMap);
	printFacesToFile(fileName, normalCoordinateMap, vl);
}

ColoredVertexMatrix & ObjFileWriter::normalizeVertices(ColoredVertexMatrix & CoordinateMap){
	float xMax, yMax, zMax;
	float normalWidth, normalHeight, normalDepth;
	
	
	xMax = CoordinateMap->getWidth();
	yMax = CoordinateMap->getHeight();
	zMax = CoordinateMap->getDepth();
	
	for(int x = 0; x < xMax; x++){
		for(int y = 0; y < yMax; y++){
		    for(int z = 0; z < zMax; z++){
		    	Coordinate = CoordinateMatrix->getValueRef(x, y, z);
		    	Coordinate->setLabel(vertexLabel++);
		    	normalWidth = (Coordinate->getX())/xMax;
		    	normalHeight = (Coordinate->getY())/yMax;
		    	normalDepth = (Coordinate->getZ())/zMax;
		    	Coordinate->setX(normalWidth);
		    	Coordinate->setY(normalHeight);
		    	Coordinate->setZ(normalDepth);
			}
		}
	}
	return CoordinateMap;
}

void ObjFileWriter::printVerticesToFile(string fileName, ColoredVertexMatrix & CoordinateMap){
	objFile.open(fileName);
	for(int x = 0; x < xMax; x++){
			for(int y = 0; y < yMax; y++){
			    for(int z = 0; z < zMax; z++){
			    	Coordinate = CoordinateMatrix->getValueRef(x, y, z);
			    	objFile << "v " << Coordinate->getNormalX() << " " << Coordinate->getNormalY() << " " << Coordinate->getNormalZ() << endl;
			    	
				}
			}
		}
}

void ObjFileWriter::printFacesToFile(string fileName, ColoredVertexMatrix & CoordinateMap, vertexlinker vl){
	foreach (vector<ColoredVertex> face , vl.getSquares()){
	    objFile << "f ";
		foreach (ColoredVertex vertex, face){
	        objFile << vertex->getLabel() <<"/";
	    }
		objFile << "\n";
	}
}
