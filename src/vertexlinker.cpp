#include "vertexlinker.h"

void VertexLinker::makeShapes() {


    //First: make loops
    //ISUE: the paths are being made in ways that lead to choppy short paths in the wrong direction.
    //      this occurs when the path can choose between x and z, I try to remedy this below but the results are unchanged*
std::vector<std::vector<std::vector<ColoredVertex>>> levels = std::vector<std::vector<std::vector<ColoredVertex>>>();
    std::vector<std::vector<ColoredVertex>> loops; //start empty and add loops on to it
    //taken: 3d matrix of bools corresponding to which vertice is taken by the loop making algorithm
    taken = std::vector<std::vector<std::vector<bool>>>(matrix->getWidth(), std::vector<std::vector<bool>>(matrix->getHeight(), std::vector<bool>(matrix->getDepth(), false)));
    for (int y = 0; y < matrix_height; y++) {
        loops= std::vector<std::vector<ColoredVertex>>();
        for (int x = 0; x < matrix_width; x++) {
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
                            if(cur_loop.size()>0)
                            loops.push_back(cur_loop);
                        }
                    }
                    else {
                        std::cerr << "ERROR: alpha=" << (int)alpha;
                    }
                }

            }
        }
        levels.push_back(loops);
    }



 //Second: go accross each loop and connect each vertex in the loop and the next vertex with the vertices closest to the ones right above each

    //Heigharcy: levels hold loops holds loop holds vertices
    int x, y, z;
    int levels_size = levels.size();

    std::vector<ColoredVertex>loop;//holder to use later


    //for every level
    for (int i = 0; i < levels_size; i++) {

        loops = levels[i];//each level holds multiple loops
        int loops_size = loops.size();

        //for every loop in the level
         for (int j = 0; j < loops_size; j++) {
             std::vector<ColoredVertex>cur_face;
             //holds the face to be pushed if it holds all 4 verts
             //should be reset everytime we switch to another loop
             //however it should check every loop in the level above
        loop=loops[j];
        if (loop.size()==0) {continue;}
        y = loop[0].getY();

        ColoredVertex oldv=ColoredVertex();
        bool old_set=false;

        //for every vertex in the loop
        foreach(ColoredVertex v, loop) {

            x = v.getX();
            z = v.getZ();

            //best match and distance will be replaced by the closest vertices to the one directly above the current that is not null
            ColoredVertex best_match;
            int best_match_distance = 1000000;

            vector<vector<ColoredVertex>> buddy_loops;//this will be the level above it tries to connect with
            if (i + 1 >= levels_size) {//no loop above it
                //add a function to take in the top faces
                //also do this for the bottom
            }
            else {
                buddy_loops = levels[i + 1];
                //look trouhg every loop on the next level
                foreach(std::vector<ColoredVertex>b_loop,buddy_loops){
                    foreach (ColoredVertex potential_partner,b_loop) {//find the closest match
                    float x_dis = potential_partner.getX() - x, z_dis = potential_partner.getZ() - z;
                    float dist = x_dis*x_dis + z_dis*z_dis;
                    if (dist < best_match_distance) {//< so it gives priority to earlier ones and takes less computation

                        best_match = potential_partner;

                        best_match_distance = dist;

                    }


                }
                    //end of each vert in buddy_loop

                }//end of each buddy_loop in buddy loops

                if(buddy_loops.size()>0){
                if (cur_face.size() == 0) {//initialize array,(only last 2 matter)
                    cur_face.push_back(v);
                    cur_face.push_back(best_match);
                    cur_face.push_back(v);
                    cur_face.push_back(best_match);


                }else {
                    //hold vertices gotten last round in the last 2
                    cur_face[2] = cur_face[0];
                    cur_face[3] = cur_face[1];

                    //hold this vertex and its match in the first 2
                    cur_face[0] = v;
                    cur_face[1] =best_match;
                    addSquare(cur_face);

                }

            }

            }
            if(old_set){
               int old_x=oldv.getX();
               int old_y=oldv.getY();
               int old_z=oldv.getZ();

                    if(old_x==x){
                        ColoredVertex px=matrix->getValue(x+1,y,z);//+x

                        ColoredVertex o_px=matrix->getValue(old_x+1,old_y,old_z);

                        if( !(px.isNull()||px.getValue()[3]==0||o_px.isNull()||o_px.getValue()[3]==0) ){//if spots are neither empty or OOB
                            vector<ColoredVertex>face={v,oldv,px,o_px};

                            addSquare(face);
                        }


                    }else if(old_z==z){

                        ColoredVertex pz=matrix->getValue(x,y,z+1);//+x

                        ColoredVertex o_pz=matrix->getValue(old_x,old_y,old_z+1);


                        if( !(pz.isNull()||pz.getValue()[3]==0||o_pz.isNull()||o_pz.getValue()[3]==0) ){//if spots are neither empty or OOB
                            vector<ColoredVertex>face={v,oldv,pz,o_pz};
                            addSquare(face);
                        }

                    }else if(old_x==x-1&&old_z==z+1){
                        ColoredVertex mxpz=matrix->getValue(x-1,y,z+1);//+x

                        ColoredVertex o_mxpz=matrix->getValue(old_x-1,old_y,old_z+1);
                        if( !(mxpz.isNull()||mxpz.getValue()[3]==0||o_mxpz.isNull()||o_mxpz.getValue()[3]==0) ){//if spots are neither empty or OOB
                            vector<ColoredVertex>face={v,oldv,mxpz,o_mxpz};
                            addSquare(face);
                        }


                    }else if(old_x==x+1&&old_z==z-1){

                        ColoredVertex pxmz=matrix->getValue(x+1,y,z-1);//+x

                        ColoredVertex o_pxmz=matrix->getValue(old_x+1,old_y,old_z-1);
                        if( !(pxmz.isNull()||pxmz.getValue()[3]==0||o_pxmz.isNull()||o_pxmz.getValue()[3]==0) ){//if spots are neither empty or OOB
                            vector<ColoredVertex>face={v,oldv,pxmz,o_pxmz};
                            addSquare(face);
                        }
                }
            }
            oldv=v;
            old_set=true;

        }     //end of foreach vertex v in loop

         }
    }
}

bool VertexLinker::reccurFindNextVertex(int x, int y, int z) {
    //returns true if it reccurs or reaches the end
    if (x < 0 || y < 0 || z < 0 || x >= matrix_width || y >= matrix_height || z >= matrix_depth) {

        return false;//hit a side
    }
    ColoredVertex  active = vertices[x][y][z];
    int alpha = active.getValue()[3];

    if ((int)alpha != 1) {
        if ((int)alpha == 0) {
            return false;
        }
        else { std::cerr << "ERROR: alpha=" << (int)alpha << endl; }
    }

    if (taken[x][y][z]) { return false; }//taken bit shouldnt need to be here after it is hollowed
    //from now on return true because this was added to the loop
    cur_loop.push_back(active);
    taken[x][y][z] = true;
    //should not branch out durring recursion, so only go down one reccurion path



    for (int i = 1; i < 5; i++) {
        for (int j = 0; j < 5; j++) {//find the shortest path up to 5 away
            float x_dist_from_center=abs((float)x-(float)matrix_width/2)/matrix_width;
            float z_dist_from_center=abs((float)z-(float)matrix_depth/2)/matrix_depth;

            if(x_dist_from_center>=z_dist_from_center){//try to keep loop convex by having a bias towards the outside
            if (reccurFindNextVertex(x + i, y, z)) {
                return true;
            }
            if (reccurFindNextVertex(x, y, z + j)) {
                return true;
            }
            }else{

                if (reccurFindNextVertex(x, y, z + j)) {

                    return true;
                }

                if (reccurFindNextVertex(x + i, y, z)) {

                    return true;
                }

            }
            if (reccurFindNextVertex(x + i, y, z + j)) {

                return true;
            }

            if (reccurFindNextVertex(x + i, y, z - j)) {

                return true;
            }
        }
    }
    //end of path
    return true;
}



void VertexLinker::setFoundAtOffset(int x, int y, int z, int x_offset, int y_offset, int z_offset) {
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

void VertexLinker::setFoundStraightUp(int x, int y, int z) {
    int yD = y + 1;
    bool out_of_b = (x < 0 || yD < 0 || z < 0 || x >= matrix_width || yD >= matrix_height || z >= matrix_depth);
    int found_current = false;
    if (!out_of_b) {
        found_current = (vertices[x][yD][z].getValue()[3] == 1);//check alpha
    }
    found_neighbor_on_top = found_current;



}
void VertexLinker::setFoundStraightDown(int x, int y, int z) {
    int yD = y - 1;
    bool out_of_b = (x < 0 || yD < 0 || z < 0 || x >= matrix_width || yD >= matrix_height || z >= matrix_depth);
    int found_current = false;
    if (!out_of_b) {
        found_current = (vertices[x][yD][z].getValue()[3] == 1);//check alpha
    }
    found_neighbor_on_bottom = found_current;



}
void VertexLinker::setFoundIfNoCollision(int x, int y, int z, int y_offset) {
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
        ColoredVertex* v1 = &vertices[x + 1][y + y_offset][z];
        ColoredVertex* v2 = &vertices[x][y + y_offset][z - 1];

        if (v1 != nullptr && v1->getValue()[3] == 1
            && v2 != nullptr && v2->getValue()[3] == 1)
        {
            found_current = false; //set this to false so it doesnt fill in and collide
        }
        else {
            found_current = (vertices[xD][yD][zD].getValue()[3] == 1);
        }
    }
    switch (y_offset) {
    case(-1): {found_neighbors_below[3] = found_current; }
    case(0): {found_neighbors_same[3] = found_current; }
    case(1): {found_neighbors_above[3] = found_current; }
    }

}
