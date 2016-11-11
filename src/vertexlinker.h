#ifndef VERTEXLINKER_H
#define VERTEXLINKER_H


#pragma once
#include<vector>
#include"VertexLine.h"
#include<math.h>


class VertexLinker {
public:
    VertexLinker(ColoredVertexMatrix * matrix_in) {
        matrix = matrix_in;
        vertices = matrix->getVertices();
        matrix_width = matrix->getWidth();
        matrix_height = matrix->getHeight();
        matrix_depth = matrix->getDepth();
    }

    void addSquare(std::vector<ColoredVertex> square) {// add group of 4 vertices to the list "squares"

        squares.push_back(square);




    }
    void addSquare(ColoredVertex corner_a,ColoredVertex corner_b,ColoredVertex corner_c,ColoredVertex corner_d) {// add group of 4 vertices to the list "squares"
        vector<ColoredVertex>square{corner_a,corner_b,corner_c,corner_d};
        squares.push_back(square);




    }
    std::vector<ColoredVertex>  toTriangles(std::vector<ColoredVertex> square){
         std::vector<ColoredVertex> doubleTriangles=std::vector<ColoredVertex>();
        doubleTriangles.push_back(square[0]);
        doubleTriangles.push_back(square[1]);
        doubleTriangles.push_back(square[2]);

        doubleTriangles.push_back(square[1]);
        doubleTriangles.push_back(square[2]);
        doubleTriangles.push_back(square[3]);
        return doubleTriangles;


    }
    void addTriangle(std::vector<ColoredVertex> triangle) {// add group of 4 vertices to the list "triangles"
        triangles.push_back(triangle);

    }
    std::vector<std::vector<ColoredVertex>>  getTriangles(){return triangles;}

    std::vector<std::vector<ColoredVertex>>  getSquares(){return squares;}
    void addTriangle(ColoredVertex vA, ColoredVertex vB, ColoredVertex vC) {//group the 3 vertices passed in and add that group to the list "triangles"


        std::vector<ColoredVertex>flat = std::vector<ColoredVertex>();
        flat.push_back(vA);
        flat.push_back(vB);
        flat.push_back(vC);
        addTriangle(flat); //adds a horizontal face
    }
    void makeShapes(int loop_split) ;
private:
    std::vector<std::vector<Vect3D>> all_verts;
    std::vector<std::vector<ColoredVertex>> squares;
    std::vector<std::vector<ColoredVertex>> triangles;
    std::vector<ColoredVertex> cur_loop;
    std::vector<std::vector<std::vector<ColoredVertex>>>vertices;
    ColoredVertexMatrix * matrix;

    bool found_neighbors_above[4];
    bool found_neighbors_below[4];
    bool found_neighbors_same[4];
    bool found_neighbor_on_top;
    bool found_neighbor_on_bottom;


    int matrix_width, matrix_height, matrix_depth;
    bool reccurFindNextVertex(int x, int y, int z,int loop_split);//used to find loops by going through verices on the same y level
    void setFoundAtOffset(int x, int y, int z, int x_offset, int y_offset, int z_offset);

    void setFoundStraightUp(int x, int y, int z) ; //foundStraightUp holds bools based on edges bewtween the current vertex an vertices above it and to the front/right

    void setFoundStraightDown(int x, int y, int z); //foundStraightDown holds bools based on edges bewtween the current vertex an vertices below it and to the front/right
    //this is only used for the flat bottom faces

    void setFoundIfNoCollision(int x, int y, int z, int y_offset);// this is only for edges that have the possibility of been crossed by others (the right, backward direction)

    std::vector<std::vector<std::vector<bool>>> taken;
};
#endif // VERTEXLINKER_H
