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
	MatrixNode getValue(int x, int y, int z);
	void setValue(int x, int y, int z, MatrixNode value);
	int getWidth();
	int getHeight();
	int getDepth();
	int color_contrast_tollerance;
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
