#ifndef LINE_FINDER_H
#define LINE_FINDER_H
#include "ColoredVertex.h"
#include "ColoredVertexMatrix.h"

class Vect3D{
public:
    Vect3D(int x_in,int y_in,int z_in){
        x=x_in;
        y=y_in;
        z=z_in;

    }
    Vect3D(){}
    int X(){return x;}
    int Y(){return y;}
    int Z(){return z;}
private:
    int x=-1,y=-1,z=-1;

};


class VertexLine{//this is used to measure straight lines when making a loop
    //lines that are pass trough by (not just touch) other lines need to be checked for removal think T, check the stem
    //criteria for removal (check on both sides and only remove the ones with these criteria)
    //  -check center of line from the intersecting path to another intersection or the end of line (whichever shows up first)
    //      -if it is surrounded on both flat (x if the line is z and vice versa)sides for the whole line then it is a horizontal surface and
    //       therefore should only check for horizontal surfaces, not vertical or diagnol surfaces
    //replace loops with these, unfortunately this will check the same vertices multiple times, causing a little bit of slowing, but shouldnt be too bad
public:
//    VertexLine();
    string name;
    bool dont_fill=false;
    VertexLine(){}
    VertexLine(Vect3D start , ColoredVertexMatrix* matrix_in,char dir_in);
    bool checkForPrune();
    std::vector<Vect3D>getLine(){return line;}

private:
    bool vertical;//make vertical faces from this line or horizontal?
    char direction;//x y or z
    void checkVert(int x,int y,int z,bool negative_dir);//recursive check of a vertex which checks the next one in a given direction
    ColoredVertexMatrix *matrix;
    std::vector<Vect3D> line;

};
#endif // LINE_FINDER_H
