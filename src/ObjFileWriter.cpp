/*
 * ObjFileWriter.cpp
 * Henry Chang
 */

#include "ObjFileWriter.h"

ObjFileWriter::ObjFileWriter(ColoredVertexMatrix * CoordinateMap,string path){
   CoordinateMatrix=CoordinateMap;
   m_path=path;
   vertexLabel = 1;
   xMax = CoordinateMatrix->getWidth();
   yMax = CoordinateMatrix->getHeight();
   zMax = CoordinateMatrix->getDepth();
   normalizeVertices();


}
ObjFileWriter::~ObjFileWriter(){}



void ObjFileWriter::execute(FaceMaker * fm){
    objFile.open(m_path);
    printVerticesToFile();
    printFacesToFile(fm);
    objFile.close();
}

void ObjFileWriter::normalizeVertices(){

	float normalWidth, normalHeight, normalDepth;
	for(int x = 0; x < xMax; x++){
		for(int y = 0; y < yMax; y++){
		    for(int z = 0; z < zMax; z++){
                if (CoordinateMatrix->isFinal(x,y,z)){
                    Coordinate = CoordinateMatrix->getValueRef(x, y, z);
                    cout<<"V LABEL:"<<vertexLabel<<endl;
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
	}
}

void ObjFileWriter::printVerticesToFile(){



    for(int x = 0; x < xMax; x++){
			for(int y = 0; y < yMax; y++){
			    for(int z = 0; z < zMax; z++){
			    	Coordinate = CoordinateMatrix->getValueRef(x, y, z);
                    if (CoordinateMatrix->isFinal(x,y,z)){
                        objFile << "v " << Coordinate->getNormalX() << " " << Coordinate->getNormalY() << " " << Coordinate->getNormalZ() << endl;
                    }
				}
			}
		}
}

void ObjFileWriter::printFacesToFile(FaceMaker * fm){
    foreach (vector<ColoredVertex> face , fm->getSquares()){
	    objFile << "f ";
		foreach (ColoredVertex vertex, face){
            ColoredVertex vertex_at_spot= CoordinateMatrix->getValue(vertex.getX(),vertex.getY(),vertex.getZ());
            objFile << vertex_at_spot.getLabel() <<"/";
	    }
		objFile << "\n";
	}
    foreach (vector<ColoredVertex> face , fm->getTriangles()){
        objFile << "f ";

        foreach (ColoredVertex vertex, face){
            ColoredVertex vertex_at_spot= CoordinateMatrix->getValue(vertex.getX(),vertex.getY(),vertex.getZ());

            objFile << vertex_at_spot.getLabel() <<"/";
        }
        objFile << "\n";
    }
}
