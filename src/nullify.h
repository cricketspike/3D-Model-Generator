#ifndef NULLIFY_H
#define NULLIFY_H
#include <vector>
#include <cmath>
using namespace std;

#include "color.h"
#include "coloredvertexmatrix.h"

//	takes two rgb colors
float color_diff(Color c1, Color c2) ;
//	takes two rgb colors
float color_diff_2(Color col1, Color col2) ;
//	thresh = [0, 100]
void nullify(ColoredVertexMatrix& image, uint8_t* c_null, float thresh);
void nullify(ColoredVertexMatrix& image, Color c_null, float thresh);
#endif//NULLIFY_H
