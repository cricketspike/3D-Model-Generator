#ifndef PRECISETRIMMING_H
#define PRECISETRIMMING_H

#include"ColoredVertexMatrix.h"
class PreciseTrimming
{
    bool converged;
    ColoredVertexMatrix *m_matrix;
public:
    PreciseTrimming(ColoredVertexMatrix *M);
        bool trimVertex(int x,int y,int z);
};

#endif // PRECISETRIMMING_H
