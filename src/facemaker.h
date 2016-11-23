//William C King 11/12/2016


#ifndef FACEMAKER_H
#define FACEMAKER_H

#include<vector>
#include<assert.h>
#include <math.h>
#include "ColoredVertexMatrix.h"

class FaceMaker
{
public:
    FaceMaker(ColoredVertexMatrix * matrix_in);
    void makeFaces(int vertices_density_split);

    std::vector<std::vector<ColoredVertex>>  getTriangles(){return triangles;}

    std::vector<std::vector<ColoredVertex>>  getSquares(){return squares;}
    std::vector<ColoredVertex>  toTriangles(std::vector<ColoredVertex> square);

private:
    unsigned int verts_between_keys;

    std::vector<std::vector<ColoredVertex>> squares;
    std::vector<std::vector<ColoredVertex>> triangles;
    std::vector<ColoredVertex> cur_loop;
    std::vector<std::vector<std::vector<ColoredVertex>>>m_vertices;
    ColoredVertexMatrix * m_matrix;

    unsigned int m_matrix_width, m_matrix_height, m_matrix_depth;
    float m_max_dist;
    vector<vector<vector<ColoredVertex>>> m_levels_of_loops;
    vector<vector<vector<ColoredVertex>>> m_finished_loops;//TODO: make FUNCTION THAT CONVERTS THESE INTO X<Y Z VALUES, as these are copys and have duplicate verts in them
    std::vector<std::vector<std::vector<bool>>> m_taken;
    void connectLoops(int vertices_density_split);

    bool reccurFindNextVertex(int x, int y, int z);
    void addVerticesBetweenKeys(vector<ColoredVertex> loop, vector<ColoredVertex> keys);//add this later
    void SetKeyPoints(int vertices_density_split);
    void addHorzFace(vector<ColoredVertex> loop);


    void addSquare(std::vector<ColoredVertex> square) ;
    void addSquare(ColoredVertex corner_a,ColoredVertex corner_b,ColoredVertex corner_c,ColoredVertex corner_d);
    void addTriangle(ColoredVertex vA, ColoredVertex vB, ColoredVertex vC);

};

#endif // FACEMAKER_H
