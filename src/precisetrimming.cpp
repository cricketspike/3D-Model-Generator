#include "precisetrimming.h"

PreciseTrimming::PreciseTrimming(ColoredVertexMatrix * M){
    converged=false;

    m_matrix=M;
    while(!converged){
        converged=true;

        for(unsigned int i=0;i<m_matrix->getWidth();i++){
            for(unsigned  int j=0;j<m_matrix->getHeight();j++){

                for(unsigned  int k=0;k<m_matrix->getWidth();k++){

                if(trimVertex(i,j,k)){converged=false; }
            }
            }

        }

    }
}

bool PreciseTrimming::trimVertex(int x,int y,int z){
    int neighbors=0;
    if(!m_matrix->isValid(x,y,z)){return false;}
    for( int i=-1;i<=1;i++){//for each neighbor
        for(  int k=-1;k<=1;k++){
            if(i==0&&k==0){continue;}
            if(m_matrix->isValid(x+i,y,z+k)){
                //if valid:
                //check if any other neighbor has an opposing value (ex if left up and left down or left and back right)
                //if so return
                //if not keep checking
                if(++neighbors > 3) {

                    return false;
                }//if it has more than 3 neighbors, its guarunteeed to not be trimmed
                if(i!=0){
                    for(int k2=-1;k2<=1;k2++){
                        if(m_matrix->isValid(x-i,y,z+k2)){
                            return false;}//check all with opoite X
                    }

                }
                if(k!=0){
                    for(int i2=-1;i2<=1;i2++){

                        if(m_matrix->isValid(x+i2,y,z-k)){

                            return false;

                        }//check all with oposite Z
                    }

                }



            }
        }
    }
    m_matrix->setNull(x,y,z);
    m_matrix->getValue(x,y,z).printVert();

    return true;
    //if it reaches the end:
        //remove the node



}







