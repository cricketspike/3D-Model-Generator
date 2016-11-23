#include "modeleditor.h"

ModelEditor::ModelEditor()
{

}

void ModelEditor::SetupModel(box image_box,int resolution_split,int vert_loop_dist){
    m_image_box=image_box;
    m_resolution_split=resolution_split;//lower=slower, more accurate, more faces
    m_vertices_density_split=vert_loop_dist;//lower= more faces

}
void ModelEditor::createModel(){

    uint8_t null_col[3] = {255, 255, 255};
    m_null_color=null_col;
    m_threshold = 40;

    int model_width=INT_MAX;
    int model_height=INT_MAX;
    int model_depth=INT_MAX;
    foreach(ImportedImage side ,m_image_box.getSides()){

        int w=side.getMaxModelWidth();
        int h=side.getMaxModelHeight();
        int d=side.getMaxModelDepth();
        if(w!=-1){model_width=min(model_width,w);}
        if(h!=-1){model_height=min(model_height,h);}
        if(d!=-1){model_depth=min(model_depth,d);}


    }
    if (model_width<10||model_height<10*10||model_depth<10){
        cout<<"WARNING:Very small model, may cause crash if divided too much"<<endl;
    }


    vector<VotingMatrix> voters=vector<VotingMatrix>();
    for(int i=0;i<6;i++){
       voters.push_back(VotingMatrix(
            model_width, model_height, model_depth,m_image_box.getSides()[i],m_resolution_split)
        );

    }
   ColoredVertexMatrix  vertices= ColoredVertexMatrix(model_width, model_height,model_depth, voters ,m_resolution_split,m_null_color );

   tempNullify(vertices, m_null_color, m_threshold);
   smooth (vertices, m_vertices_density_split);

   ColoredVertexMatrix *shell= vertices.getShell(m_vertices_density_split);
   PreciseTrimming pt = PreciseTrimming(shell);

   QString filename="testVertsShell";
   QFile file(filename);
   if(file.open(QIODevice::ReadWrite)){
       QTextStream stream( &file );
       int width= shell->getWidth();
       int height= shell->getHeight();
       int depth= shell->getDepth();
      for (int i=0;i< width; i++){
       for (int j=0;j< height; j++){
        for (int k=0;k< depth;  k++){
          uint8_t* values= shell->getValue(i,j,k).getValue();
          vertices_by_XYZ.push_back(values);
          if((int)values[3]!=0){stream <<i<<" "<<j<<" "<<k<<" "<<endl;}


      }}}

   }


   FaceMaker fm=FaceMaker(shell);
   fm.makeFaces(m_vertices_density_split);

   int wid=shell->getWidth();
   int hei=shell->getHeight();
   int dep=shell->getDepth();
   std::vector<GLfloat> facesByXYZ=std::vector<float>();
   std::vector<GLfloat> facesByRBG=std::vector<float>();

   //print all triangles and add their raw data into the face arrays
              foreach (vector<ColoredVertex> face , fm.getTriangles()){

                  for (int i=0;i<3;i++){
                  ColoredVertex vert=face[i];

                  facesByXYZ.push_back(((float)vert.getX())/wid -.5);
                  facesByXYZ.push_back(((float)vert.getY())/hei -.5);
                  facesByXYZ.push_back(((float)vert.getZ())/hei -.5);

                  uint8_t* colors=vert.getValue();
                  facesByRBG.push_back(((float)colors[0])/256);
                  facesByRBG.push_back(((float)colors[1])/256);
                  facesByRBG.push_back(((float)colors[2])/256);


                  }

              }

     foreach (vector<ColoredVertex> face , fm.getSquares()){
         vector<ColoredVertex> triangles=fm.toTriangles(face);
         for (int i=0;i<6;i++){
             ColoredVertex  vert=triangles[i];

         facesByXYZ.push_back(((float)vert.getX())/wid -.5);
         facesByXYZ.push_back(((float)vert.getY())/wid -.5);
         facesByXYZ.push_back(((float)vert.getZ())/wid -.5);

         uint8_t* colors=vert.getValue();
         facesByRBG.push_back(((float)colors[0])/256);
         facesByRBG.push_back(((float)colors[1])/256);
         facesByRBG.push_back(((float)colors[2])/256);

     }


     }
     m_face_vertices_data=facesByXYZ;
     m_face_color_data=facesByRBG;


}


void ModelEditor::defaultStart(){
    //call a bunch of setters here or in cm's args
    createModel();
    GLfloat* f=&m_face_color_data[0];

    renderModel(m_face_vertices_data,m_face_color_data);




}


void ModelEditor::resetModel(){

}
