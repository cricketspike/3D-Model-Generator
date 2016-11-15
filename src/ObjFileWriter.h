/*
 * ObjFileWriter.h
 * Henry Chang
 */

#ifndef OBJFILEWRITER_H
#define OBJFILEWRITER_H

#include "ColoredVertexMatrix.h"
#include "stdlib.h"
#include <ofstream>
#include <vector>

using namespace std;

class ObjFileWriter{
private:
	ColoredVertexMatrix * CoordinateMatrix;
    ColoredVertex * Coordinate;
    ofstream objFile;
    int vertexLabel;
    
    // Helper Methods
    ColoredVertexMatrix * normalizeVertices(ColoredVertexMatrix * CoordinateMap)

public:
    ObjFileWriter();
    ~ObjFileWriter();

    void initiliaze(string fileName, ColoredVertexMatrix * CoordinateList);
    void execute();
    
}

#endif //OBJFILEWRITER_H
