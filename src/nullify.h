#ifndef NULLIFY_H
#define NULLIFY_H

#include <vector>
#include <cmath>
using namespace std;

#include "color.h"
#include "coloredvertexmatrix.h"

float colorPercentDifference(Color c1, Color c2);
float colorPercentError(Color col1, Color col2);
float colorVectorDifference(Color col1, Color col2);

void nullify(ColoredVertexMatrix& image, uint8_t* c_null, float thresh);
void nullify(ColoredVertexMatrix& image, Color c_null, float thresh);

#endif//NULLIFY_H
