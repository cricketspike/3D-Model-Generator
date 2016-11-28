
/*
 * ObjFileWriter.h
 * Henry Chang
 */

#ifndef OBJFILEWRITER_H
#define OBJFILEWRITER_H

#include "ColoredVertexMatrix.h"
#include "facemaker.h"
#include "stdlib.h"
#include <fstream>
#include <vector>

using namespace std;

class ObjFileWriter{
private:
    ColoredVertexMatrix * CoordinateMatrix;
    ColoredVertex * Coordinate;
    ofstream objFile;
    int vertexLabel;
    vector<int> faces;
    string m_path;


    // Helper Methods
    void normalizeVertices();
    void printVerticesToFile();
    void printFacesToFile(FaceMaker * fm);


    float xMax, yMax, zMax;
public:
    ObjFileWriter(ColoredVertexMatrix * CoordinateMap,string path);
    ~ObjFileWriter();

    void execute(FaceMaker * fm);

};

#endif //OBJFILEWRITER_H
