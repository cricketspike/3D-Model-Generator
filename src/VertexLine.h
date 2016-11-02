#ifndef LINE_FINDER_H
#define LINE_FINDER_H
#include "ColoredVertex.h"
class VertexLine{//this is used to measure straight lines when making a loop
    //lines that are pass trough by (not just touch) other lines need to be checked for removal think T, check the stem
    //criteria for removal (check on both sides and only remove the ones with these criteria)
    //  -check center of line from the intersecting path to another intersection or the end of line (whichever shows up first)
    //      -if it is surrounded on both flat (x if the line is z and vice versa)sides for the whole line then it is a horizontal surface and
    //       therefore should only check for horizontal surfaces, not vertical or diagnol surfaces
    //replace loops with these, unfortunately this will check the same vertices multiple times, causing a little bit of slowing, but shouldnt be too bad
public:
    VertexLine();
    VertexLine(ColoredVertex start, char direction);

private:
    bool vertical;//make vertical faces from this line or horizontal?
    char direction;//x y or z
    void checkVert(ColoredVertex target_vert,);//recursive check of a vertex which checks the next one in a given direction


};
#endif // LINE_FINDER_H
