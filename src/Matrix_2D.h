#ifndef MATRIX_2D_H
#define MATRIX_2D_H

#include <cassert>
#include<vector>
#include<string.h>
#include<cstdint>
#include<stdio.h>
#include<iostream>
class Matrix_2D {
public:
	Matrix_2D(unsigned int width, unsigned int height, char u, char v, bool invert_u, bool invert_v, bool invert_depth);
	Matrix_2D() {}
	void resetArray();
	void initArray();
    uint8_t* getValue(unsigned int u, unsigned int v);
    void setValue(unsigned int u, unsigned int v, uint8_t* value);
	int getImageWidth();
	int getImageHeight();
	char getU();
	char getV();
	bool invertU();
	bool invertV();
	bool invertDepth();

protected:


private:
	std::vector<std::vector<uint8_t*>> matrix;
	unsigned int m_width;
	unsigned int m_height;
	char m_u;
	char m_v;
	bool m_invert_u;
	bool m_invert_v;
	bool m_invert_depth;

};

#endif // !MATRIX_2D_H
