#ifndef VOTINGMATRIX_H
#define VOTINGMATRIX_H

#include <cassert>
#include<vector>
#include<string.h>
#include<stdio.h>
#include<iostream>
#include "ImportedImage.h"
#include "matrixnode.h"
class VotingMatrix {
public:
    VotingMatrix();
    VotingMatrix(int width, int height, int depth,ImportedImage image,float resolution_split);
	void initMatrix();
    MatrixNode getValue(int x, int y, int z);
	void setValue(int x, int y, int z, MatrixNode value);
	int getWidth();
	int getHeight();
	int getDepth();
    void print();
protected:


private:
    float m_resolution_split;
	std::vector<std::vector<std::vector<MatrixNode*>>> matrix;
	int m_width;
	int m_height;
	int m_depth;
    ImportedImage m_image;
	MatrixNode *createElement(int wid, int hei, int dep);

};

#endif // !VOTINGMATRIX_H
