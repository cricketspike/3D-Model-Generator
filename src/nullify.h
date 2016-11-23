#ifndef NULLIFY_H
#define NULLIFY_H
#include <vector>
#include <cmath>
using namespace std;

#include "coloredvertexmatrix.h"

//	takes two rgb colors
float color_diff(uint8_t* c1, uint8_t* c2) ;
//	takes two rgb colors
float color_diff_2(uint8_t* col1, uint8_t* col2) ;
//	thresh = [0, 100]
void nullify(ColoredVertexMatrix& image, uint8_t* c_null, float thresh);
#endif//NULLIFY_H
