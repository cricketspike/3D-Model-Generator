/*
 * ObjFileWriter.cpp
 * Henry Chang
 */

#include "ObjFileWriter.h"

ObjFileWriter::ObjFileWriter(){};
ObjFileWriter::~ObjFileWriter(){};

void ObjFileWriter::initialize(string fileName, ColoredVertexMatrix * CoordinateMap){
	objFile.open(fileName);
	CoordinateMatrix = CoordinateMap;
	vertexLabel = 1
	normalizeVertices(CoordinateMatrix);
	for(int x = 0; x < CoordinateMatrix->getWidth(); x++){
		for(int y = 0; y < CoordinateMatrix->getHeight(); y++){
			for(int z = 0; z < CoordinateMatrix->getDepth(); z++){
                Coordinate = CoordinateMatrix->getValueRef(x, y, z);
			    Coordinate->setLabel(vertexLabel++);

			}
		}
	}
}

ColoredVertexMatrix * ObjFileWriter::normalizeVertices(ColoredVertexMatrix * CoordinateMap){
	float xMax, yMax, zMax;
	xMax = CoordinateMap->getWidth();
	yMax = CoordinateMap->getHeight();
	zMax = CoordinateMap->getDepth();

}
