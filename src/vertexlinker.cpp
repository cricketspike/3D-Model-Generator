#include "vertexlinker.h"

void VertexLinker::makeShapes(int loop_split) {
    all_verts=std::vector<std::vector<Vect3D>>();

    //First: find all lines of vertices

std::vector<std::vector<VertexLine>> levels =std::vector<std::vector<VertexLine>>();
    std::vector<VertexLine> lines; //start empty and add loops on to it
    std::vector<int*> this_level_verts;
    //taken: 3d matrix of bools corresponding to which vertice is taken by the loop making algorithm
    taken = std::vector<std::vector<std::vector<bool>>>(matrix->getWidth(), std::vector<std::vector<bool>>(matrix->getHeight(), std::vector<bool>(matrix->getDepth(), false)));
    for (int y = 0; y < matrix_height; y++) {
        lines=std::vector<VertexLine>();//lines on this level
        std::vector<Vect3D> this_level_verts=std::vector<Vect3D>();//all vertices on this level
        for (int x = 0; x < matrix_width; x++) {
            for (int z = 0; z < matrix_depth; z++) {
                Vect3D vert_pos(x,y,z);
                ColoredVertex* v=matrix->getValueRef(x,y,z);
                //if it finds a vertex at matrix[x][y][z]
                //if the alpha not equal to 0 and equal to one: (if only one of those return an error)
                if(matrix->isValid(x,y,z)){
                    this_level_verts.push_back(vert_pos);//add to list of verts
                   if((matrix->isValid(x+loop_split,y,z)||matrix->isValid(x-1,y,z))){
                       if(!(v->line_x)){
                        VertexLine x_line=VertexLine(vert_pos,matrix,'x', loop_split);//check for horizontal line
                        if(!x_line.checkForPrune( loop_split)){lines.push_back(x_line);}

                       }
                    }
                    if((matrix->isValid(x,y,z+loop_split)||matrix->isValid(x,y,z-1))&&!(v->line_z)){//check for vertical line
                         if(!(v->line_z)){
                        VertexLine z_line= VertexLine(vert_pos,matrix,'z', loop_split);
                       if(!z_line.checkForPrune( loop_split)){ lines.push_back(z_line);}
                         }
                    }
                    if((matrix->isValid(x+loop_split,y,z+loop_split)||matrix->isValid(x-1,y,z-1))&&!(v->line_a)){//check for matched diagnol line
                        if(!(v->line_a)){
                        VertexLine a_line= VertexLine(vert_pos,matrix,'a', loop_split);
                        if(!a_line.checkForPrune( loop_split)){lines.push_back(a_line);}
                        }
                    }
                    if((matrix->isValid(x+loop_split,y,z-1)||matrix->isValid(x-1,y,z+loop_split))&&!(v->line_b)){//check for oposite diagnol line
                         if(!(v->line_b)){
                        VertexLine b_line= VertexLine(vert_pos,matrix,'b', loop_split);
                        if(!b_line.checkForPrune( loop_split)){lines.push_back(b_line);}
                    }
                    }
                }
            }
            }
        levels.push_back(lines);
        all_verts.push_back(this_level_verts);
}

 //Second: go accross each loop and connect each vertex in the loop and the next vertex with the vertices closest to the ones right above each

    //Heigharcy: levels hold loops holds loop holds vertices
    int x, y, z;
    size_t levels_size = levels.size();
    VertexLine line;//holder to use later


    //for every level
    for (int i = 0; i < levels_size; i++) {


        lines = levels[i];//each level holds multiple lines
        size_t lines_size = lines.size();
        //for every loop in the level
         for (int j = 0; j < lines_size; j++) {

             std::vector<ColoredVertex>cur_face;
             //holds the face to be pushed if it holds all 4 verts
             //should be reset everytime we switch to another loop
             //however it should check every loop in the level above
        line=lines[j];
        y = i;
        //for every vertex in the line
        cout<<line.name<<endl<<endl;
        foreach(Vect3D v_coord, line.getLine()) {

            x = v_coord.X();
            z = v_coord.Z();

            //best match and distance will be replaced by the closest vertices to the one directly above the current that is not null
            Vect3D best_match;
            int best_match_distance = 1000000;

            ColoredVertex cur_vert=matrix->getValue(x,y,z);

            vector<int*> potential_buddies;//this will be the level above it tries to connect with


            if (i -loop_split <0||all_verts[i -loop_split].size()==0) {
                //no verts below it
                //only do one direction to prevent overlap
                //try to make faces on the bottom
                if(matrix->isValid(x+loop_split,y,z)&&matrix->isValid(x+loop_split,y,z+loop_split)&&matrix->isValid(x,y,z+loop_split)){
                    addSquare(matrix->getValue(x,y,z),matrix->getValue(x+loop_split,y,z),matrix->getValue(x,y,z+loop_split),matrix->getValue(x+loop_split,y,z+loop_split));
                }



            }
            if (i + loop_split >= levels_size||all_verts[i + loop_split].size()==0) {
                //no verts above it
                //only do one direction to prevent overlap
                //try to make faces on the top
                if(matrix->isValid(x+loop_split,y,z)&&matrix->isValid(x+loop_split,y,z+loop_split)&&matrix->isValid(x,y,z+loop_split)){
                    addSquare(matrix->getValue(x,y,z),matrix->getValue(x+loop_split,y,z),matrix->getValue(x,y,z+loop_split),matrix->getValue(x+loop_split,y,z+loop_split));
                }



            } else {//if there are verts above


                vector<Vect3D>next_level = all_verts[i + loop_split];


                //look trouhg every loop on the next level

                ColoredVertex matching_vert;
                if(matrix->isValid(x,y+loop_split,z)){

                    if((matrix->isValid(x+loop_split,y+loop_split,z))&&!(matrix->isValid(x+loop_split,y,z))){
                        addTriangle(cur_vert,matrix->getValue(x,y+loop_split,z), matrix->getValue(x+loop_split,y+loop_split,z));
                    }
                    if((matrix->isValid(x,y+loop_split,z+loop_split))&&!(matrix->isValid(x,y,z+loop_split))){
                        addTriangle(cur_vert,matrix->getValue(x,y+loop_split,z), matrix->getValue(x,y+loop_split,z+loop_split));
                    }
                    if((matrix->isValid(x-loop_split,y+loop_split,z))&&!(matrix->isValid(x-loop_split,y,z))){
                        addTriangle(cur_vert,matrix->getValue(x,y+loop_split,z), matrix->getValue(x-loop_split,y+loop_split,z));
                    }
                    if((matrix->isValid(x,y+loop_split,z-loop_split))&&!(matrix->isValid(x,y,z-loop_split))){
                        addTriangle(cur_vert,matrix->getValue(x,y+loop_split,z), matrix->getValue(x,y+loop_split,z-loop_split));
                    }

                }
                    foreach (Vect3D potential_partner,next_level) {//find the closest match
                    float x_dis = ((float)potential_partner.X()) -(float) x,
                          z_dis = ((float)potential_partner.Z()) - (float)z;
                    float dist = x_dis*x_dis + z_dis*z_dis;

                    if (dist < best_match_distance) {//< so it gives priority to earlier ones and takes less computation
                        best_match = potential_partner;
                        best_match_distance = dist;

                    }

                }


                    matching_vert=matrix->getValue(best_match.X(),best_match.Y(),best_match.Z());
                    //end of each vert in next level

                if (cur_face.size() == 0) {//initialize array,(only last 2 matter)
                    cur_face.push_back(cur_vert);//just need to fill first spot
                    cur_face.push_back(matching_vert);//just need to fill second spot
                    cur_face.push_back(cur_vert);
                    cur_face.push_back(matching_vert);


                }else {
                    //hold vertices gotten last round in the last 2
                    cur_face[2] = cur_face[0];
                    cur_face[3] = cur_face[1];

                    //hold this vertex and its match in the first 2
                    cur_face[0] =cur_vert;
                    cur_face[1] =matching_vert;
                    addSquare(cur_face);

                }

            }

        }     //end of foreach vertex v in loop

         }
    }
}
