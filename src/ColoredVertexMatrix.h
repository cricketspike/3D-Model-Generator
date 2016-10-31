#ifndef COLORMATRIX_H
#define COLORMATRIX_H

#include "Matrix_2D.h"
#include "matrixnode.h"
#include <cassert>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include"votingmatrix.h"
#include "coloredvertex.h"
#include <vector>
class ColoredVertexMatrix {
public:

    ColoredVertexMatrix(unsigned int width, unsigned int height, unsigned int depth, std::vector<VotingMatrix> images,float resolution_split);
    ColoredVertexMatrix(ColoredVertexMatrix * original);

    ColoredVertex getValue(int x, int y, int z){
        if(x>matrix.size()||y>matrix[0].size()||z>matrix[0][0].size()){return ColoredVertex();}
        return matrix[x][y][z];}
	void setValue(int x, int y, int z, MatrixNode value);
    void setNull(int x,int y,int z){
        matrix[x][y][z].getValue()[3]=0;
    }
    std::vector<float> getListOfVertsAsFloats();
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}
    int getDepth(){return m_depth;}
	int color_contrast_tollerance;
    std::vector<std::vector<std::vector<ColoredVertex>>>  getVertices(){return matrix;}
    ColoredVertexMatrix * getShell();

protected:


private:
	std::vector<std::vector<std::vector<ColoredVertex>>> matrix;
        unsigned int m_width;
        unsigned int m_height;
        unsigned int m_depth;
	Matrix_2D m_image;
	MatrixNode *createElement(int wid, int hei, int dep);
};

#endif // !COLORMATRIX_H
