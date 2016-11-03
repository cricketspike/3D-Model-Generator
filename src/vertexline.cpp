#include"VertexLine.h"






VertexLine:: VertexLine(Vect3D start , ColoredVertexMatrix* matrix_in,char dir_in){
    name="good";
    matrix=matrix_in;
    direction=dir_in;
    line=std::vector<Vect3D>();
    checkVert(start.X(),start.Y(),start.Z(),true);
    checkVert(start.X(),start.Y(),start.Z(),false);
    foreach (Vect3D a ,line)
        cout<<a.X()<<","<<a.Y()<<","<<a.Z()<<"----00------"<<endl;


}
void VertexLine::checkVert(int x,int y,int z,bool negative_dir){//recursive check of a vertex which checks the next one in a given direction

    if(!matrix->isValid(x,y,z)){
        return;
    }//reached end of line

    cout<<x<<","<<y<<","<<z<<"----------"<<endl;
    Vect3D pos= Vect3D(x,y,z);
cout<<pos.X()<<","<<pos.Y()<<","<<pos.Z()<<"------**----"<<endl;
    ColoredVertex *v=matrix->getValueRef(x,y,z);
    line.push_back(pos);
    name="great";

    if(direction=='x'){
        v->setLX();
        cout<<"1"<<endl;

        if(negative_dir){checkVert(x-1,y,z,true);}
        else{checkVert(x+1,y,z,false);}
    }else if(direction=='z'){
                v->setLZ();
        cout<<"2"<<endl;
       v->line_z=true;

       if(negative_dir){ checkVert(x,y,z-1,true);}
       else{checkVert(x,y,z+1,false);}
    }else if(direction=='a'){
                v->setLA();
        cout<<"3"<<endl;
        v->line_a=true;

    if(negative_dir){ checkVert(x-1,y,z-1,true);}
    else{checkVert(x+1,y,z+1,false);}
 }else if(direction=='b'){
                v->setLB();
        cout<<"4"<<endl;
        v->line_b=true;

    if(negative_dir){ checkVert(x-1,y,z+1,true);}
    else{checkVert(x+1,y,z-1,false);}
 }




}

bool VertexLine::checkForPrune(){//see if line fills in areas that dont need to be filled and if so remove them
    if(direction=='x'){//check if perpendicular vertices all the way trough
    foreach (Vect3D vert, line) {
        if(!(matrix->isValid(vert.X(),vert.Y(),vert.Z()-1)
                &&matrix->isValid(vert.X(),vert.Y(),vert.Z()+1))){
            return false;//not inside a flat face so keep it
        }
    }
    }else if(direction=='z'){//check if perpendicular vertices all the way trough
    foreach (Vect3D vert, line) {
        if(!(matrix->isValid(vert.X()-1,vert.Y(),vert.Z())
                &&matrix->isValid(vert.X()+1,vert.Y(),vert.Z()))){
            return false;//not inside a flat face so keep it
        }
    }
    }else if(direction=='a'){//cant realy do perpendicular so check +1+1 and -1-1
    foreach (Vect3D vert, line) {
        if(!(
             matrix->isValid(vert.X()-1,vert.Y(),vert.Z() && matrix->isValid(vert.X(),vert.Y(),vert.Z()-1))
           ||matrix->isValid(vert.X()+1,vert.Y(),vert.Z() && matrix->isValid(vert.X(),vert.Y(),vert.Z()+1)))){
            return false;//not inside a flat face so keep it
        }
    }
    }else if(direction=='b'){//cant realy do perpendicular so check +1-1 and -1+1
    foreach (Vect3D vert, line) {
        if(!(
             matrix->isValid(vert.X()+1,vert.Y(),vert.Z() && matrix->isValid(vert.X(),vert.Y(),vert.Z()-1))
             ||matrix->isValid(vert.X()-1,vert.Y(),vert.Z() && matrix->isValid(vert.X(),vert.Y(),vert.Z()+1)))){
            return false;//not inside a flat face so keep it
        }
    }
    }
    return true;
}
