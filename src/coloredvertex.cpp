#include"ColoredVertex.h"
#include "ColoredVertexMatrix.h"

       ColoredVertex::ColoredVertex(int w, int h, int d, ColoredVertexMatrix *par_cvm) {
        width = w;
        height = h;
        depth = d;
                cvm=par_cvm;
    }
    uint8_t* ColoredVertex::getValue(){return value;}
    void ColoredVertex::addVoter(MatrixNode voter) { voters.push_back(voter); }
    void ColoredVertex::setValueFromVoters(int grouping_tollerance) {
        //group together nodes based on similar colors
        std::vector<VotingNode> groupedVoters;
        for (int i = 0; i < voters.size(); i++) {
            int closest_group_index = -1, closest_size = -1;//find the group that matches the color the best

            for (int j = 0; j < groupedVoters.size(); j++) {
                int contrast = (voters[i].colorContrast(groupedVoters[j].getColor(0), groupedVoters[j].getColor(1), groupedVoters[j].getColor(2)));
                if (contrast <= grouping_tollerance) {
                    if (contrast < closest_size || closest_size == -1) {
                        closest_size = contrast;
                        closest_group_index = j;
                    }
                }

            }
            if (closest_size == -1) {
                VotingNode temp = VotingNode();
                temp.addVoter(voters[i]);
                groupedVoters.push_back(temp);

            }
            else
            {
                groupedVoters[closest_group_index].addVoter(voters[i]);

            }
        }
        //compare the votes of the groups and chose the group with the highest combined weight
        int greatest_vote_weight = -1, index_of_vote = -1;
        for (int i = 0; i < groupedVoters.size(); i++) {
            if (groupedVoters[i].getWeight() > greatest_vote_weight) {
                greatest_vote_weight = groupedVoters[i].getWeight();
                index_of_vote = i;
            }
        }
        VotingNode winner = groupedVoters[index_of_vote];
        value = new uint8_t[4];
        value[0] = winner.getColor(0);
        value[1] = winner.getColor(1);
        value[2] = winner.getColor(2);
        value[3] = 1;
    }


    bool ColoredVertex::isInside(){
           int tot_w= cvm->getWidth() , tot_h= cvm->getHeight() , tot_d = cvm->getDepth() ;
           for ( int i = -1; i <=1; i++) {
               for ( int j = -1; j <=1; j++) {
                   for ( int k = -1; k <=1; k++) {
                      //make sure not out of bounds or the vertex itself
                       if(
                          width+i<0||height+j<0||depth+k<0||
                          width+i>=tot_w||height+j>=tot_h||depth+k>=tot_d||
                          (i==0&&j==0&&k==0)||(i!=0&&j!=0&&k!=0)||(smooth&&(i!=0&&j!=0)||(j!=0&&k!=0)||(i!=0&&k!=0))//dont want ones where only the very corner touches (maybe make this and this with only 2 non zeros options for smoothness later)
                          ){continue;}
                        else {
                       if(((int)cvm->getValue(width+i,height+j,depth+k).getValue()[3])==0){
                           //if in bounds and it finds a peice of background touching it,
                           //then it is not an inside and should not be nullified;
                           return false;
                       }
                   }
               }
           }
       }
       return true;
    }
    ColoredVertex ColoredVertex::copy(ColoredVertexMatrix* cvm){
        ColoredVertex cv=ColoredVertex(width,height,depth,cvm);
        cv.setValue(value);
        return cv;
    }

    void ColoredVertex::setValue(uint8_t* v){
        value=new uint8_t[4]{v[0],v[1],v[2],v[3]};}
    int ColoredVertex::getX(){return width;}
    int ColoredVertex::getY(){return height;}
    int ColoredVertex::getZ(){return depth;}
    void ColoredVertex::printVert(){std::cout<<"x: "<<width<<"y: "<<height<<"z: "<<depth<<" Color:"<<(int)value[0]<<":"<<(int)value[1]<<":"<<(int)value[2]<<":"<<(int)value[3]<<":"<<endl;}

