#include "facemaker.h"

FaceMaker::FaceMaker(ColoredVertexMatrix * matrix_in) {
    m_matrix = matrix_in;
    m_vertices = m_matrix->getVertices();
    m_matrix_width = m_matrix->getWidth();
    m_matrix_height = m_matrix->getHeight();
    m_matrix_depth = m_matrix->getDepth();
    m_max_dist = (matrix_in->getWidth() + matrix_in->getDepth())/8;//TODO: make the 8 changable later

}


void FaceMaker::makeFaces(int vertices_density_split) {

    //Make loops
    std::vector<std::vector<ColoredVertex>> loops;//start empty and add loops on to it
    //taken: 3d matrix of bools corresponding to which vertice is taken by the loop making algorithm
    m_taken = std::vector<std::vector<std::vector<bool>>>(m_matrix->getWidth(),
                                                          std::vector<std::vector<bool>>(m_matrix->getHeight(),
                                                            std::vector<bool>(m_matrix->getDepth(),
                                                             false)));
    for (int y = 0; y < m_matrix_height; y++) {//for each level, keep making loops until all vertices are taken
        loops= std::vector<std::vector<ColoredVertex>>();
        for (int x = 0; x < m_matrix_width; x++) {
            for (int z = 0; z < m_matrix_depth; z++) {
                //if it finds a vertex at matrix[x][y][z]
                //if the alpha not equal to 0 and equal to one: (if only one of those return an error)
                //then start a new loop

                uint8_t* color = (m_vertices[x][y][z].getValue());
                uint8_t alpha = color[3];
                if (alpha != 0) {
                    if (alpha == 1) {
                        //if it is not taken:

                        if (!m_taken[x][y][z]) {
                            cur_loop = std::vector<ColoredVertex>();
                            //reccursive check algorithm
                            reccurFindNextVertex(x, y, z);
                            //cout<<"exited"<<endl;
                            if(cur_loop.size()>0){
                                cout<<endl<<endl<<"LOOP:";
                                foreach (ColoredVertex v, cur_loop) {
                                    v.printVert();
                                }
                                loops.push_back(cur_loop);//create and add loop to level

                            }
                        }
                    }
                    else {
                        std::cerr << "ERROR: alpha=" << (int)alpha;
                    }
                }
            }
        }
        m_levels_of_loops.push_back(loops);
    }

SetKeyPoints(vertices_density_split);







    //find key points in loops
    //link key points of closest loop on next level with matching indeces
    connectLoops(vertices_density_split);

}




void FaceMaker::SetKeyPoints(int vertices_density_split){
    ColoredVertex left;//get the leftmost vertex
     int left_amount=m_matrix_width;//start with furthest right possible

    ColoredVertex right;//get the rightmost vertex
     int right_amount=INT_MIN;//start with furthest left possible


    ColoredVertex back;//get the backmost vertex
     int back_amount=m_matrix_depth;//start with furthest forward possible

    ColoredVertex forward;//get the frontmost vertex
     int forward_amount=INT_MIN;//start with furthest back possible

    unsigned int level_num=0;
    foreach (std::vector<std::vector<ColoredVertex>> level, m_levels_of_loops) {

        vector<vector<ColoredVertex>>finished_level;

        foreach (std::vector<ColoredVertex> loop, level) {
            vector<unsigned int> center_position;

            //find center
            foreach (ColoredVertex vertex, loop) {
                if(vertex.getX()<left_amount ){
                    left_amount=vertex.getX();
                    left=vertex;
                }
                if(vertex.getX()>right_amount ){
                    right_amount=vertex.getX();
                    right=vertex;
                }

                if(vertex.getZ()<back_amount ){
                    back_amount=vertex.getZ();
                    back=vertex;
                }

                if(vertex.getZ()>forward_amount ){
                    forward_amount=vertex.getZ();
                    forward=vertex;
                }

                //cout<<"testtt"<<right_amount<<" "<<left_amount<<" "<<forward_amount<<" "<<back_amount<<" "<< endl;

                center_position.push_back((right_amount+left_amount)/2);//x
                center_position.push_back(level_num);//y
                center_position.push_back((forward_amount+back_amount)/2);//z
                //cout<<"loop center:"<<center_position[0]<<", "<<center_position[1]<<", "<<center_position[2]<<endl;
                //cout<<"testtttttt"<<endl;

            }


            //cout<<"testttt!1"<<endl;

            int  center_x=center_position[0],
                 center_z=center_position[2];
            //cout<<"testttt!2"<<endl;



            //<,^,>,V

            ColoredVertex  center_left;//get the leftmost vertex
            float center_left_amount=-1;//start with furthest right possible

            ColoredVertex  left_forward;
            float left_forward_amount=-1;//start with smallest value



            ColoredVertex  center_forward;//get the frontmost vertex
             float center_forward_amount=-1;//start with furthest back possible

             ColoredVertex   forward_right;
             float forward_right_amount=-1;//start with smallest value



             ColoredVertex  center_right;//get the rightmost vertex
              float center_right_amount=-1;//start with furthest left possible

              ColoredVertex right_back;
              float right_back_amount=-1;//start with smallest value



              ColoredVertex center_back;//get the backmost vertex
               float center_back_amount=-1;//start with furthest forward possible

               ColoredVertex back_left;
               float back_left_amount= -1;//start with smallest value

            //find key points in loop given the center

               int max_left_offset=max(center_x-left.getX(),1);

               int max_right_offset=max(right.getX()-center_x ,1);

               int max_back_offset=max(center_z-back.getZ() ,1);

               int max_forward_offset=max(forward.getZ()-center_z,1);





               float  cur_c_left_amount,
                    cur_c_right_amount,
                    cur_c_forward_amount,
                    cur_c_back_amount,

                    cur_back_left_amount,
                    cur_right_back_amount,
                    cur_left_forward_amount,
                    cur_forward_right_amount;






               float left_offset, right_offset, back_offset, forward_offset;


               //cout<<"CX= "<<center_x<<"     CZ= "<<center_z<<endl;
            foreach (ColoredVertex vertex, loop) {
                vertex.printVert();
                left_offset= ((float)(center_x-vertex.getX()))/(float) max_left_offset;
                right_offset= ((float)(vertex.getX()-center_x))/(float)max_right_offset;
                back_offset= ((float)(center_z-vertex.getZ()))/(float)max_back_offset;
                forward_offset= ((float)(vertex.getZ()-center_z))/(float)max_forward_offset;

                //cout<<center_x<<"-"<<vertex.getX()<<"/"<<(float) max_left_offset<<"="<<"l:"<<left_offset<<endl;
                //cout<<vertex.getX()<<"-"<<center_x<<"/"<<(float) max_right_offset<<"="<<"l:"<<right_offset<<endl;
                //cout<<"b:"<<back_offset<<endl;
                //cout<<"f:"<<forward_offset<<endl;


                cur_c_left_amount= (left_offset-(std::max(back_offset,forward_offset)/2));
                //cout<<cur_c_left_amount<<">"<<center_left_amount<<"?"<<endl;;
                if(cur_c_left_amount>center_left_amount){
                    center_left_amount=cur_c_left_amount;
                    center_left=vertex;
                    //cout<<"1!"<<endl;
                }

                cur_c_right_amount= (right_offset-(std::max(back_offset,forward_offset)/2));
                if(cur_c_right_amount>center_right_amount){
                    center_right_amount=cur_c_right_amount;
                    center_right=vertex;
                    //cout<<"2!"<<endl;

                }

                cur_c_back_amount= (back_offset-(std::max(left_offset,right_offset)/2));
                if(cur_c_back_amount>center_back_amount){
                    center_back_amount=cur_c_back_amount;
                    center_back=vertex;
                    //cout<<"3!"<<endl;

                }

                cur_c_forward_amount= (forward_offset-(std::max(left_offset,right_offset)/2));
                if(cur_c_forward_amount>center_forward_amount){
                    center_forward_amount=cur_c_forward_amount;
                    center_forward=vertex;
                    //cout<<"4!"<<endl;

                }

                cur_back_left_amount=back_offset+left_offset;

                if (cur_back_left_amount> back_left_amount){
                    back_left_amount=cur_back_left_amount;
                    back_left=vertex;
                    //cout<<"5!"<<endl;

                }

                cur_right_back_amount=back_offset+right_offset;

                if (cur_right_back_amount> right_back_amount){
                    right_back_amount=cur_right_back_amount;
                    right_back=vertex;
                    //cout<<"6!"<<endl;

                }


                cur_left_forward_amount=forward_offset+left_offset;
                //cout<<forward_offset<<"+"<<left_offset<<">"<<left_forward_amount<<"??"<<endl;;

                if (cur_left_forward_amount> left_forward_amount){
                    left_forward_amount=cur_left_forward_amount;
                    left_forward=vertex;
                    //cout<<"7!"<<endl;

                }

                cur_forward_right_amount=forward_offset+right_offset;

                if (cur_forward_right_amount> forward_right_amount){
                    forward_right_amount=cur_forward_right_amount;
                    forward_right=vertex;
                    //cout<<"8!"<<endl;

                }

            }

            //cout<<"testttt!3"<<endl;

            vector<ColoredVertex>key_loop=vector<ColoredVertex>();
            //add in the key vertices clockwise
            key_loop.push_back(center_left);
            key_loop.push_back(left_forward);
            key_loop.push_back(center_forward);
            key_loop.push_back(forward_right);
            key_loop.push_back(center_right);
            key_loop.push_back(right_back);
            key_loop.push_back(center_back);
            key_loop.push_back(back_left);

            finished_level.push_back(key_loop);
        }
        //cout<<"testttt!4"<<endl;
        m_finished_loops.push_back(finished_level);

        level_num++;
    }



}



bool FaceMaker::reccurFindNextVertex(int x, int y, int z) {
    //returns true if it reccurs or reaches the end
    //cout<<"asdf1"<<endl;
    if (!m_matrix->isValid(x,y,z)){
       //cout<<" OOB \n";
        return false;//hit a side
    }
    //cout<<"asdf2"<<endl;
    ColoredVertex  active = m_vertices[x][y][z];
    if((!m_matrix->isValid(x,y,z))||m_taken[x][y][z]){return false;}
    //taken bit shouldnt need to be here after it is hollowed
    //from now on return true because this was added to the loop
    //cout<<"added"<<x<<","<<y<<","<<z<<endl;

    cur_loop.push_back(active);
    m_taken[x][y][z] = true;
    //should not branch out durring recursion, so only go down one reccurion path




            for (int xo=-1;xo<=1;xo++){
                    for (int zo=-1;zo<=1;zo++){
                        if(xo==0&&zo==0){continue;}
                        if (reccurFindNextVertex(x + xo, y, z+zo)) {
                            return true;
                        }
                    }
                }

    //end of path
    return true;
}


void FaceMaker:: addVerticesBetweenKeys(vector<ColoredVertex> loop, vector<ColoredVertex> keys){//add this later




}




void FaceMaker::connectLoops(int vertices_density_split){//eventually use tween verts
    //takes in 2 sets of loops that hold 8*n elements each
    //loops are broken down into groups and then levels
    //pairs up loop with loop from the level above if their centers are close enough
    //does this one whole level at a time so it can compare which one best fits
    //each loop reaches out to as many as it can and orders them
    //then each loop states their first choice and they all compare.
    //If any have the same, the further one moves on to the next round or if it runs out, makes a flat face out of the loop
    //a bool vector will hold which of the next row have been paired off so you can face off those loops as well

    //note: to make this more accurate, you could check the unshelled vertex matrix, but this would take more time than I have to implement

    //this is very inefficient, but number of loops in each level should be very small here

    //for each level:


    //first go through each level to get the center of every loop
    vector<vector<unsigned int*>> loop_center_positions;//level: index: x,y,z this will hold the center of the loop on every level
    cout<<"Test !";
    for (int i=0;i< m_finished_loops.size();i+=vertices_density_split) {//for each level
            vector<unsigned int*>centers_of_this_level;//hold this until end of level then push it as the top level onto loop_center_positions
            for (int j=0; j< m_finished_loops[i].size();j++) {//for each loop
                cout<<"part1: level"<<i<<"loop num= "<<j<<"/"<<m_finished_loops[i].size()<<endl;
                unsigned int cur_total[3]={0,0,0} ;//used to calculate average
                unsigned int cur_avg[3]={-1,-1,-1} ;//used to calculate average
                for (int k=0;k< m_finished_loops[i][j].size();k++) {
                    ColoredVertex elem= m_finished_loops[i][j][k];
                    cur_total[0]+= elem.getX();
                    cur_total[1]+= elem.getY();
                    cur_total[2]+= elem.getZ();
                }
                cur_avg[0]=(cur_total[0]/m_finished_loops[i][j].size());
                cur_avg[1]=(cur_total[1]/m_finished_loops[i][j].size());
                cur_avg[2]=(cur_total[2]/m_finished_loops[i][j].size());
                centers_of_this_level.push_back(cur_avg);
                cout<<"average("<<cur_avg[0]<<", "<<cur_avg[1]<<", "<<cur_avg[2]<<")"<<endl;
            }
            loop_center_positions.push_back(centers_of_this_level);
        }






    //next go through each loop  by level and find all the loops from the next level that the current loop can connect to
    //and order by closeness (tie breaker the smallest Diameter ) by inserting the next loops index in the right place in a vector
    //if one has no matches make a flat face(first make a function to make flat faces)

    vector<vector<bool>> matched_with_above;//level:index:(is loop at index matched with one on next level?)
    vector<vector<bool>> matched_with_below;//level:index:(is loop at index matched with one on previous level?)

cout<<"Test @"<<endl;

    for (int i=0;i<m_finished_loops.size();i+=vertices_density_split) {//for each level
        vector<vector<unsigned int*>> match_lists;//loop_num: placement: match   -will hold all matches of each loop, in order, to be compared
        vector<vector<float>> distance_lists;//loop_num: placement: distance of match   -will hold distance to each match

        if(i+vertices_density_split>=m_finished_loops.size()){
            cout<<"TOP"<<endl;
            //if top level just make flat faces
        }else{
            for (int j=0; j< m_finished_loops[i].size();j++) {//for each loop find all matches
                cout<<"part2: level"<<i<<"loop num="<<j<<"/"<<m_finished_loops[i].size()<<endl;
                cout<<"LOOP finding all matches"<<endl;
                vector<unsigned int*> matches;//size 2: {level of loop, loop's index in level}
                vector<float> distances;//used for comparison of matches, will not cary over

                for (int jj=0; jj< m_finished_loops[i+vertices_density_split].size();jj++) {//for each loop in next level

                    vector<ColoredVertex>current_loop = m_finished_loops[i][j];
                    vector<ColoredVertex>next_loop = m_finished_loops[i+vertices_density_split][jj];
                     cout<<"index of this loop in loops: "<<i<<", "<<j<<"  size of this loop: "<<current_loop.size()<<endl;
                     cout<<"index of next loop in loops: "<<next_loop.size()<<endl;

                    float cur_distance=//diagonal distance
                        pow ((loop_center_positions[i/vertices_density_split][j][0]-loop_center_positions[(i+vertices_density_split)/vertices_density_split][jj][0]),2)+//x distance squared
                            pow ((loop_center_positions[i/vertices_density_split][j][2]-loop_center_positions[(i+vertices_density_split)/vertices_density_split][jj][2]),2);// + z distance squared
                    cout<<"is"<<cur_distance<<"<"<<m_max_dist<<endl;
                    bool closeEnough= cur_distance <m_max_dist;
                    if(closeEnough){
                        cout<<"Yes"<<endl;
                        unsigned int newMatch[2]={i+vertices_density_split,jj};
                        assert (matches.size()==distances.size());//distance is associated with the match at the same index
                        bool inserted=false;//used to check if we got to the end withour insetring
                        for ( int ranking = 0; ranking<matches.size();ranking++){
                            cout<<"competition1:"<<cur_distance<<" < "<<distances[ranking]<<endl;
                            if  (cur_distance < distances[ranking]||( //if closer
                                    cur_distance == distances[ranking]&&( //or the same distance and the diameter is smaller
                                        pow ((current_loop[0].getX()-current_loop[current_loop.size()/2].getX()),2)//X diameter of cur loop
                                        <pow ((next_loop[0].getX()-next_loop[next_loop.size()/2].getX()),2)//X diameter of next loop
                                    )
                                )
                            ){
                                //then: insert the curent match and distance before the indexed one and break from the loop

                                distances.insert(distances.begin() +ranking ,cur_distance);
                                matches.insert(matches.begin() +ranking ,newMatch);
                                cout<<"match("<<newMatch[0]<<", "<<newMatch[1]<<", "<<cur_distance<<")"<<" in place "<< ranking<<endl;
                                inserted=true;
                                break;
                            }
                        }
                        if(!inserted){//if it gets to the end without inserting, it is in last place so just add it to end;
                            distances.push_back(cur_distance);
                            matches.push_back(newMatch);
                            cout<<"match("<<newMatch[0]<<", "<<newMatch[1]<<", "<<cur_distance<<")"<<endl;
                        }
                    }


                }

                cout<<"Test #";
                match_lists.push_back(matches);//push the list of matches for the loop into a list of all the loops' matches
                distance_lists.push_back(distances);
            }

            //Now every loop has a first, second and third best match
            //we need co check the next level


            bool found_any_this_place=true; //will be false if we run off all vectors;
                vector<int> taken_list =vector<int> (m_finished_loops[i+vertices_density_split].size(), -1);
                //this is a list of -1s representing all the loops on the next level

                //if not -1 index is already best matched by the loop at index, so you need to compare them

                vector<bool> locked=vector<bool> (m_finished_loops[i+vertices_density_split].size(), false);
                //this is a list of bools representing which claims to an index on the taken list can be contested
                //taken list is locked each place so that every loop is more likely to get its first pick
                for (int placement=0;found_any_this_place ;placement++){//compare the first place of every loop then then second, etc
                cout<<"placement ="<<placement<<endl;
                if (match_lists.size()==0){ break;}
                found_any_this_place=false;



                for (int j=0; j< m_finished_loops[i].size();j++) {//for each loop given a certain placement (find best of all matches)
                    cout<<"part 3: level"<<i<<"loop num="<<j<<"/"<<m_finished_loops[i].size()<<endl;
                    if (match_lists[j].size()==0||placement>=match_lists[j].size()){
                        //if the list is empty or the algorithm runs off when looking for the next place, break
                        break;}


                    unsigned int* match= match_lists[j][placement]; //the nth best match of this loop where n=placement


                    if (distance_lists.size()<=0){break;}// no matches at all this level

                    vector<float>  cur_loop_distances=distance_lists[j];//the values of the nth best match of this loop where n=placement (lower = better)

                    int taken_index=taken_list[match[1]];//the index of this loops nth best match

                    if(!locked[match[1]]){//if not already taken in a previous round
                        cout<<"NOTLOCKED"<<endl;
                    if (taken_index==-1){//if no other loop has been matched with the loop above yet
                        cout<<"index= -1"<<endl;
                    taken_list[match[1]]=j;//this loop claims the one above
                        }else {

                        float cur_best_distance =distance_lists[taken_index][placement];



                        cout<<"index= "<<taken_index<<endl;
                            cout<<"current best match's level="<<match[0]<<", current best's index: "<<match[1]<<endl;

                            cout<<"current lowest distance="<<cur_best_distance<<endl;
                            vector<ColoredVertex> cur_best_match=m_finished_loops[match[0]][match[1]];


                            cout<<"contenders's level="<<i<<", contender's index: "<<j<<endl;
                             cout<<"contender's distance="<<cur_loop_distances[placement]<<endl;
                            vector<ColoredVertex> cur_contender_match=m_finished_loops[i][j];//note: at this point match[0] should = i


                            if(cur_loop_distances[placement]<cur_best_distance|| //if closer
                                    (cur_loop_distances[placement]==cur_best_distance)&& //or the same distance but it has a smaller diameter
                                    pow ((cur_contender_match[0].getX()-cur_contender_match[cur_contender_match.size()/2 ].getX()),2)//diameter of cur loop
                                    < pow ((cur_best_match[0].getX()-cur_best_match[cur_best_match.size()/2 ].getX()),2)//diameter of curent best loop
                            ){//then
                                cout<<"contender is closer"<<endl;
                                taken_list[match[1]]=j;//this loop claims the one above becoming the new best loop
                            }

                        }
                    }

                }
                for (int taken_index=0;taken_index<taken_list.size();taken_index++){
                    if(taken_list[taken_index]!=-1){
                        locked[taken_index]=true;

                    }
                }

            }


             cout<<"CONNECT FACES"<<"------------------------"<<endl;
            for (int e_index=0; e_index<taken_list.size();e_index++ ){//for each element e in taken list:
                cout<<"taken list size "<<taken_list.size()<<">0"<<endl;
                int e=taken_list[e_index];
                if(e!=-1){//if element was connected to
                    cout<<"element"<<e <<"in the taken list was taken"<<endl;
                    //connect loops[e] to loops[e's index] with 8*n faces (be sure to loop arround)
                    cout<<"Taken List:"<<e_index<<"/"<<taken_list.size();

                    cout<<e_index<<"/"<<m_finished_loops[i+vertices_density_split].size()<<endl;
                    vector<ColoredVertex> lower_loop=m_finished_loops[i][e];
                    cout<<e<<"/"<<m_finished_loops[i].size()<<endl;

                    vector<ColoredVertex> upper_loop=m_finished_loops[i+vertices_density_split][e_index];

                    assert(lower_loop.size()==upper_loop.size());
                    cout<<"test %";
                    for(int connecting_i=0; connecting_i<lower_loop.size()-1; connecting_i++){
                        cout<<"enter2"<<endl;
                            addSquare(lower_loop[connecting_i],upper_loop[connecting_i],upper_loop[connecting_i+1],lower_loop[connecting_i+1]);

                    }
                    addSquare(lower_loop[lower_loop.size()-1],upper_loop[lower_loop.size()-1],upper_loop[0],lower_loop[0]);//wrap arround to begining
                }

                string adss;


            }

        }
    }
}





    void FaceMaker:: addSquare(std::vector<ColoredVertex> square) {// add group of 4 vertices to the list "squares"
        cout<<"SQUARE ADDED0 "<<endl;
        squares.push_back(square);




    }
    void FaceMaker:: addSquare(ColoredVertex corner_a,ColoredVertex corner_b,ColoredVertex corner_c,ColoredVertex corner_d) {// add group of 4 vertices to the list "squares"
            cout<<"SQUARE ADDED"<<endl;
            corner_a.printVert();
            corner_b.printVert();
            corner_c.printVert();
            corner_d.printVert();
            cout<<endl;

        vector<ColoredVertex>square{corner_a,corner_b,corner_c,corner_d};
        squares.push_back(square);




    }
    std::vector<ColoredVertex>  FaceMaker::toTriangles(std::vector<ColoredVertex> square){
         std::vector<ColoredVertex> doubleTriangles=std::vector<ColoredVertex>();
         cout<<"in TT";
        doubleTriangles.push_back(square[0]);
        doubleTriangles.push_back(square[1]);
        doubleTriangles.push_back(square[2]);

        doubleTriangles.push_back(square[2]);
        doubleTriangles.push_back(square[3]);
        doubleTriangles.push_back(square[0]);
        cout<<"out TT";
        return doubleTriangles;


    }





