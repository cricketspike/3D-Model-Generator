#ifndef VERTEXLINKER_H
#define VERTEXLINKER_H


#pragma once
#include<vector>
#include"ColoredVertex.h"
#include"ColoredVertexMatrix.h"

class VertexLinker {
public:
    VertexLinker(ColoredVertexMatrix * matrix_in) {
        matrix = matrix_in;
        vertices = matrix->getVertices();
        matrix_width = matrix->getWidth();
        matrix_height = matrix->getHeight();
        matrix_depth = matrix->getDepth();
    }

    void addSquare(std::vector<ColoredVertex*> square) {
        squares.push_back(square);

    }
    void addTriangle(std::vector<ColoredVertex*> triangle) {
        triangles.push_back(triangle);

    }
    void addTriangle(ColoredVertex* vA, ColoredVertex* vB, ColoredVertex* vC) {


        std::vector<ColoredVertex*>flat = std::vector<ColoredVertex*>();
        flat.push_back(vA);
        flat.push_back(vB);
        flat.push_back(vC);
        addTriangle(flat); //adds a horizontal face
    }
    void makeShapes() {

        std::vector<std::vector<ColoredVertex>> loops = std::vector<std::vector<ColoredVertex>>();;//start empty and add loops on to it
                                                                                                   //taken: 3d matrix of bools corresponding to which vertice is taken by the loop making algorithm
        taken = std::vector<std::vector<std::vector<bool>>>(matrix->getWidth(), std::vector<std::vector<bool>>(matrix->getHeight(), std::vector<bool>(matrix->getDepth(), false)));
        for (int y = 0; y < matrix_height; y++) {
            for (int x = 0; x <matrix_width ; x++) {
                std::cout<<"LOOP"<<"x"<<x<<" "<<matrix_width<<"|y"<<y<<" "<<matrix_height<<std::endl;

                for (int z = 0; z < matrix_depth; z++) {

                    //if it finds a vertex at matrix[x][y][z]
                    //if the alpha not equal to 0 and equal to one: (if only one of those return an error)
                    uint8_t* color = (vertices[x][y][z].getValue());
                    uint8_t alpha = color[3];
                    if (alpha != 0) {
                        if (alpha == 1) {
                            //if it is not taken:
                            if (!taken[x][y][z]) {

                                cur_loop = std::vector<ColoredVertex>();
                                //reccursive check algorithm
                                reccurFindNextVertex(x, y, z);
                                loops.push_back(cur_loop);
                                cout<<loops.size()<<"------"<<cur_loop.size()<<"\n";
                            }
                        }
                        else {cout<<"NO"<<endl;
                            std::cerr << "ERROR: alpha=" << (int)alpha; }
                    }//else{cout<<"NULLIFIED"<<endl;}

                }
            }

        }

        int x, y, z;
        foreach(std::vector<ColoredVertex> loop, loops) {
            y = loop[0].getY();
            foreach(ColoredVertex v, loop) {
                x = v.getX();
                z = v.getZ();
                for (int i = 0; i < 4; i++) {

                    found_neighbors_above[i] = false;
                    found_neighbors_below[i] = false;
                    found_neighbors_same[i] = false;

                }
                found_neighbor_on_top = false;
                found_neighbor_on_bottom = false;


                //set all found values
                for (int x_offset = 0; x_offset < 2; x_offset++) {
                    for (int y_offset = -1; y_offset < 2; y_offset++) {
                        for (int z_offset = 0; z_offset < 2; z_offset++) {
                            if (x_offset == 0 && z_offset == 0) {
                                //up and down have their own bools
                                if (y_offset == -1) {
                                    setFoundStraightDown(x, y, z);
                                }
                                if (y_offset == 1) {
                                    setFoundStraightUp(x, y, z);
                                }
                                continue;//the vertex itself (all offsets=0) is always found so we dont need to check
                            }

                            setFoundAtOffset(x, y, z, x_offset, y_offset, z_offset);
                        }
                    }
                }

                //special case: check x+1 z-1 can conflict with another vertex's x+1,z+1
                //this fills in the last group minus the vertical which is already filled

                for (int y_offset = -1; y_offset < 2; y_offset++) {

                    setFoundIfNoCollision(x, y, z, y_offset);

                }
                //done setting founds




                //make faces
                std::vector<bool> flat_face_up = std::vector<bool>(4, false);//use to make horizontal faces, each bool represents an edge
                std::vector<bool> flat_face_down = std::vector<bool>(4, false);//use to make horizontal faces

                ColoredVertex* this_vertex;//0,0,0 offset
                ColoredVertex* vert_vertex;//0,1,0 offset


                for (int i = 0; i < 4; i++) {//for the 4 potential vertical/diagnol faces
                    bool hor_found = found_neighbors_same[i],
                        diag_up_found = found_neighbors_above[i],//-1to1,1,-1to1
                        vert_up_found = found_neighbor_on_top,//0,1,0
                        diag_down_found = found_neighbors_below[i],//-1to1,1,-1to1
                        vert_down_found = found_neighbor_on_bottom;//0,-1,0


                    if ((hor_found&&vert_up_found) || (diag_up_found&&vert_up_found) || (hor_found&&diag_up_found)) {//if more than 2 edges, make a face
                        std::vector<ColoredVertex*> face = std::vector<ColoredVertex*>();
                        this_vertex = &(vertices[x][y][z]);
                        if(y+1>=matrix_height){vert_vertex=nullptr;}else{
                            vert_vertex = &(vertices[x][y + 1][z]);
                        }
                        face.push_back(this_vertex);//always push self
                        switch (i) {
                        case(0): {

                            if (hor_found) {
                                face.push_back(&vertices[x][y][z + 1]);
                            }
                            if (diag_up_found) {
                                face.push_back(&vertices[x][y + 1][z + 1]);
                            }
                            else if (!vert_up_found) {
                                flat_face_up[i] = true;
                            }

                            if (!(vert_down_found || diag_down_found)) {
                                flat_face_down[i] = true;
                            }
                            break;


                        }
                        case(1): {

                            if (hor_found) {
                                face.push_back(&vertices[x + 1][y][z + 1]);
                            }
                            if (diag_up_found) {
                                face.push_back(&vertices[x + 1][y + 1][z + 1]);
                            }
                            else if (!vert_up_found) {
                                flat_face_up[i] = true;
                                if (flat_face_up[i - 1]) {
                                    addTriangle(this_vertex, &vertices[x][y][z + 1], &vertices[x + 1][y][z + 1]);
                                }

                            }
                            if (!(vert_down_found || diag_down_found)) {
                                  flat_face_down[i] = true;
                                  if(flat_face_down[i-1]){
                                addTriangle(this_vertex, &vertices[x][y][z + 1], &vertices[x + 1][y][z + 1]); //adds a horizontal face
                            }}


                            break;
                        }
                        case(2): {

                            if (hor_found) {
                                face.push_back(&vertices[x + 1][y][z]);

                            }
                            if (diag_up_found) {

                                face.push_back(&vertices[x + 1][y + 1][z]);
                            }
                            else if (!vert_up_found) {

                                flat_face_up[i] = true;
                                if (flat_face_up[i - 1]) {
                                    addTriangle(this_vertex, &vertices[x + 1][y][z + 1], &vertices[x + 1][y][z]);
std::cout<<"J2f\n";
                                    //adds a horizontal face
                                }

                            }
                            if (!(vert_down_found || diag_down_found)) {
                                  flat_face_down[i] = true;
                                  if(flat_face_down[i-1]){
                                addTriangle(this_vertex, &vertices[x+1][y][z + 1], &vertices[x+1][y][z]); //adds a horizontal face
                            }}
                            break;
                        }
                        case(3): {
                            if (hor_found) {
                                face.push_back(&vertices[x + 1][y][z - 1]);
                            }
                            if (diag_up_found) {
                                face.push_back(&vertices[x + 1][y + 1][z - 1]);
                            }
                            else if (!vert_up_found) {
                                flat_face_up[i] = true;
                                if (flat_face_up[i - 1]) {
                                    std::vector<ColoredVertex*>flat = std::vector<ColoredVertex*>();
                                    addTriangle(this_vertex, &vertices[x + 1][y][z], &vertices[x + 1][y][z - 1]);
                                    //adds a horizontal face
                                }

                            }
                            if (!(vert_down_found || diag_down_found)) {
                                  flat_face_down[i] = true;
                                  if(flat_face_down[i-1]){
                                addTriangle(this_vertex, &vertices[x+1][y][z ], &vertices[x+1][y][z-1]); //adds a horizontal face
                            }}
                            break;
                        }
                        }
                        if (vert_up_found) {
                            face.push_back(vert_vertex);
                        }
                        //add the vertical face
                        if (hor_found&&diag_up_found&&vert_up_found) {
                            addSquare(face);
                        }
                        else {
                            addTriangle(face);
                        }
                    }
                }
                //now check if it needs a bottom
            }

        }

    }





private:
    std::vector<std::vector<ColoredVertex*>> squares;
    std::vector<std::vector<ColoredVertex*>> triangles;
    std::vector<ColoredVertex> cur_loop;
    std::vector<std::vector<std::vector<ColoredVertex>>>vertices;
    ColoredVertexMatrix * matrix;

    bool found_neighbors_above[4];
    bool found_neighbors_below[4];
    bool found_neighbors_same[4];
    bool found_neighbor_on_top;
    bool found_neighbor_on_bottom;


    int matrix_width, matrix_height, matrix_depth;
    bool reccurFindNextVertex(int x, int y, int z) {//returns true if it reccurs or reaches the end
        if (x < 0 || y < 0 || z < 0 || x >= matrix_width || y >= matrix_height || z >= matrix_depth) {
            return false;//hit a side
        }
        ColoredVertex  active = vertices[x][y][z];
        int alpha = active.getValue()[3];

        if ((int)alpha != 1) {
            if (alpha == 0) {
                return false;
            }
            else { std::cerr << "ERROR: alpha=" << (int)alpha<<endl; }
        }

        if(taken[x][y][z]){return false;}//taken bit shouldnt need to be here after it is hollowed
        //from now on return true because this was added to the loop
        cur_loop.push_back(active);
        taken[x][y][z] = true;
        //should not branch out durring recursion, so only go down one reccurion path
        if (reccurFindNextVertex(x + 1, y, z)) {
            return true;
        }
        if (reccurFindNextVertex(x, y, z + 1)) {
            return true;
        }
        if (reccurFindNextVertex(x + 1, y, z + 1)) {
            return true;
        }
        if (reccurFindNextVertex(x + 1, y, z - 1)) {
            return true;
        }
        //end of path
        return true;
    }





    void setFoundAtOffset(int x, int y, int z, int x_offset, int y_offset, int z_offset) {
        int xD = x + x_offset;
        int yD = y + y_offset;
        int zD = z + z_offset;
        bool out_of_b = (xD < 0 || yD < 0 || zD < 0 || xD >= matrix_width || yD >= matrix_height || zD >= matrix_depth);
        int found_current = false;
        if (!out_of_b) {
            found_current = (vertices[xD][yD][zD].getValue()[3] == 1);//check alpha
        }
        int group_num = x_offset - z_offset + 1; //group order:xz+,x+z+,x+z,x+z-
        int member_num = y_offset;
        switch (member_num) {
        case(-1): {found_neighbors_below[group_num] = found_current; }
        case(0): {found_neighbors_same[group_num] = found_current; }
        case(1): {found_neighbors_above[group_num] = found_current; }
        }



    }

    void setFoundStraightUp(int x, int y, int z) {
        int yD = y + 1;
        bool out_of_b = (x < 0 || yD < 0 || z < 0 || x >= matrix_width || yD >= matrix_height || z >= matrix_depth);
        int found_current = false;
        if (!out_of_b) {
            found_current = (vertices[x][yD][z].getValue()[3] == 1);//check alpha
        }
        found_neighbor_on_top = found_current;



    }
    void setFoundStraightDown(int x, int y, int z) {
        int yD = y - 1;
        bool out_of_b = (x < 0 || yD < 0 || z < 0 || x >= matrix_width || yD >= matrix_height || z >= matrix_depth);
        int found_current = false;
        if (!out_of_b) {
            found_current = (vertices[x][yD][z].getValue()[3] == 1);//check alpha
        }
        found_neighbor_on_bottom = found_current;



    }
    void setFoundIfNoCollision(int x, int y, int z, int y_offset) {
        int xD = x + 1;
        int yD = y + y_offset;
        int zD = z - 1;
        bool found_current;
        bool out_of_b = (xD < 0 || yD < 0 || zD < 0 || xD >= matrix_width || yD >= matrix_height || zD >= matrix_depth);

        //if these vertices exist there is an edge that this edge will intersect

        //if there is a face that will collide with +x-z:
        if (out_of_b) {
            found_current = false;
        }
        else {
            ColoredVertex* v1 = &vertices[x+1][y+y_offset][z];
            ColoredVertex* v2 = &vertices[x][y + y_offset][z -1];

            if (v1 != nullptr && v1->getValue()[3] == 1
            && v2 != nullptr && v2->getValue()[3] == 1)
            {
                found_current = false; //set this to false so it doesnt fill in and collide
            } else {
            found_current = true;
        }
        }
        switch (y_offset) {
        case(-1): {found_neighbors_below[3] = found_current; }
        case(0): {found_neighbors_same[3] = found_current; }
        case(1): {found_neighbors_above[3] = found_current; }
        }

    }

    std::vector<std::vector<std::vector<bool>>> taken;
};
#endif // VERTEXLINKER_H
