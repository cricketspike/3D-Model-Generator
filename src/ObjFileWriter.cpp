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

    //prints out the neccessary info to the opened file in this format:
    //http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/


    objFile << "# Made in the UCSC cmps 116 Fall 16 3D Model Editor"<<endl;
    printVerticesToFile();
    printColorsToFile();
    printNormalsToFile(fm);
    objFile<<"usemtl allcolors.jpg"<<endl;
    if (smoothing_on){
            objFile<<"s on"<<endl;
        }else{
            objFile<<"s off"<<endl;
        }
    printFacesToFile(fm);
    objFile.close();
}
vector<float> getAverageNorm(vector<ColoredVertex> face){
    //get the normalized position of the center of a face
    float totalX=0,totalY=0,totalZ=0;
    int count=0;
    foreach (ColoredVertex vert, face) {
        count++;
        totalX+=vert.getNormalX();
        totalY+=vert.getNormalY();
        totalZ+=vert.getNormalZ();
    }
    vector<float> returner;
    returner.push_back(totalX/count);
    returner.push_back(totalY/count);
    returner.push_back(totalZ/count);

    return returner;
}
void ObjFileWriter::normalizeVertices(){//set a normalized position value for each vertex

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
void ObjFileWriter::printColorsToFile(){



    for(int x = 0; x < xMax; x++){
            for(int y = 0; y < yMax; y++){
                for(int z = 0; z < zMax; z++){
                    uint8_t* colors=CoordinateMatrix->getValue(x, y, z).getValue();
                    if (CoordinateMatrix->isFinal(x,y,z)){
                         float red=((float)colors[0]);
                         float green=((float)colors[1]);
                         float blue=((float)colors[2]);
                        objFile << "vt " << (green-red)/2 + 255/2 -1 << " "<< (red+blue+green)/3<< endl;
                    }
                }
            }
        }
}



void ObjFileWriter::printNormalsToFile(FaceMaker * fm){

    foreach (vector<ColoredVertex> face , fm->getSquares()){
        objFile << "vn ";
        vector<float>coords=getAverageNorm(face);
            objFile << coords[0]<<" "<<coords[1]<<" "<<coords[2]<<endl;
    }
    foreach (vector<ColoredVertex> face , fm->getTriangles()){
        objFile << "vn ";
        vector<float>coords=getAverageNorm(face);
            objFile << coords[0]<<" "<<coords[1]<<" "<<coords[2]<<endl;
    }
}

void ObjFileWriter::printFacesToFile(FaceMaker * fm){


    foreach (vector<ColoredVertex> face , fm->getSquares()){
        objFile << "f ";
        foreach (ColoredVertex vertex, face){
            //since each of these is printed in the same order we print out the same value
            ColoredVertex vertex_at_spot= CoordinateMatrix->getValue(vertex.getX(),vertex.getY(),vertex.getZ());
            objFile << vertex_at_spot.getLabel()<<"/";//pos vert number
            objFile << vertex_at_spot.getLabel()<<"/";//texture vert number
            objFile << vertex_at_spot.getLabel()<<" ";//normal number

        }
        objFile<<endl;


	}
    foreach (vector<ColoredVertex> face , fm->getTriangles()){
        objFile << "f ";
        foreach (ColoredVertex vertex, face){
            //since each of these is printed in the same order we print out the same value
            ColoredVertex vertex_at_spot= CoordinateMatrix->getValue(vertex.getX(),vertex.getY(),vertex.getZ());
            objFile << vertex_at_spot.getLabel()<<"/";//pos vert number
            objFile << vertex_at_spot.getLabel()<<"/";//texture vert number
            objFile << vertex_at_spot.getLabel()<<" ";//normal number


        }
        objFile<<endl;
    }
}
