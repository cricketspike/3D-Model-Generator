#ifndef COLORMATRIX_H
#define COLORMATRIX_H

#include "Matrix_2D.h"
#include "MatrixNode.h"
#include <cassert>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include"VotingMatrix.h"
#include "ColoredVertex.h"
#include <vector>
class ColoredVertexMatrix {
public:

    ColoredVertexMatrix(unsigned int width, unsigned int height, unsigned int depth, std::vector<VotingMatrix> images,float resolution_split);
    ColoredVertex getValue(int x, int y, int z){
        return matrix[x][y][z];}
	void setValue(int x, int y, int z, MatrixNode value);
    void setNull(int x,int y,int z){
        matrix[x][y][z].getValue()[3]=0;
    }
    int getWidth(){return m_width;}
    int getHeight(){return m_height;}
    int getDepth(){return m_depth;}
	int color_contrast_tollerance;
    std::vector<std::vector<std::vector<ColoredVertex>>>  getVertices(){return matrix;}
protected:


private:
	std::vector<std::vector<std::vector<ColoredVertex>>> matrix;
	int m_width;
	int m_height;
	int m_depth;
	Matrix_2D m_image;
	MatrixNode *createElement(int wid, int hei, int dep);

};

#endif // !COLORMATRIX_H
