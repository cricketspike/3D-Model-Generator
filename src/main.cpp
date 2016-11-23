#include <QApplication>
#include <QSurfaceFormat>
#include <QTextStream>


#include"vertexlinker.h"
#include"qstring.h"
#include"qfile.h"
#include "precisetrimming.h"

#include <QApplication>
#include <QSurfaceFormat>
#include <QTextStream>

#include <iostream>
#include <string>
#include <vector>
#include "nullify.h"
#include "src/ImportedImage.h"
#include "src/CubeMapEditor.h"
#include "coloredvertexmatrix.h"
#include "facemaker.h"
#include "verticessmoothing.h"
#include"mainwaindow.h"
int main(int argc, char **argv)
{

    uint8_t null_color[3] = {255, 255, 255};
    float threshold = 40;
    std::cout << "3D Model Builder " << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Commands: hello  " << std::endl;
    std::cout << "          editor " << std::endl;
    std::cout << "          image  " << std::endl;
    std::cout << "          quit   " << std::endl << std::endl;

    while (true) {

        // Prompt

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        // Command processing
        //      Commands to affect variables
        //      to be passed into MainWindow constructor
        //      on "render" command

        if (input == "hello") {

            std::cout << "Hello" << std::endl;

        } else if (input == "editor") {

            QApplication app(argc, argv);

            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            QSurfaceFormat::setDefaultFormat(format);

            CubeMapEditor widget;
            widget.show();

            app.exec();

        }else if (input == "image") {

            QImage img0( ":/images/image0.jpg" );
            QImage img1( ":/images/image1.jpg" );
            QImage img2( ":/images/image2.jpg" );
            QImage img3( ":/images/image3.jpg" );
            QImage img4( ":/images/image4.jpg" );
            QImage img5( ":/images/image5.jpg" );

            vector<QImage> images;
            images.push_back(img0);
            images.push_back(img1);
            images.push_back(img2);
            images.push_back(img3);
            images.push_back(img4);
            images.push_back(img5);

            box b = box(images);
            int model_width=INT_MAX;
            int model_height=INT_MAX;
            int model_depth=INT_MAX;
            foreach(ImportedImage side ,b.getSides()){

                int w=side.getMaxModelWidth();
                int h=side.getMaxModelHeight();
                int d=side.getMaxModelDepth();
                if(w!=-1){model_width=min(model_width,w);}
                if(h!=-1){model_height=min(model_height,h);}
                if(d!=-1){model_depth=min(model_depth,d);}


            }

            float resolution_split=4;//lower=slower, more accurate
            int vertices_density_split=4;//lower= more loops

            vector<VotingMatrix> voters=vector<VotingMatrix>();
            for(int i=0;i<6;i++){
               voters.push_back(VotingMatrix(
                    model_width, model_height, model_depth,b.getSides()[i],resolution_split)
                );



            }
           ColoredVertexMatrix  vertices= ColoredVertexMatrix(model_width, model_height,model_depth, voters ,resolution_split,null_color );

           tempNullify(vertices, null_color, threshold);

           smooth (vertices, vertices_density_split);

           ColoredVertexMatrix *shell= vertices.getShell(vertices_density_split);

           PreciseTrimming pt = PreciseTrimming(shell);


           QString filename="testVertsShell";

            QFile file(filename);
           if(file.open(QIODevice::ReadWrite)){
               QTextStream stream( &file );
               int width= shell->getWidth();
               int height= shell->getHeight();
               int depth= shell->getDepth();
              for (int i=0;i<width;i++){
              for (int j=0;j<height;j++){
              for (int k=0;k<depth;k++){
                  uint8_t* values=  shell->getValue(i,j,k).getValue();

                  if((int)values[3]!=0){

                      std::cout<<endl<<i<<":"<<j<<":"<<k<<": "<<values[3];
                      stream <<i<<" "<<j<<" "<<k<<" "<<endl;}


              }}}

           }



           FaceMaker fm=FaceMaker(shell);
           fm.makeFaces(vertices_density_split);

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


             QGuiApplication app(argc, argv);

             QSurfaceFormat format;
             format.setSamples(16);
             MainWindow window(&facesByXYZ[0],&facesByRBG[0],facesByXYZ.size()/3 );
             window.setFormat(format);
             window.resize(640, 480);
             window.show();

             app.setQuitOnLastWindowClosed(true);
             app.exec();




        } else if (input == "exit" || input == "quit") {

            return 0;

        }

    }
}
