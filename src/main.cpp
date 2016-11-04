#include <QGuiApplication>
#include <QSurfaceFormat>

#include <iostream>
#include <string>
#include <vector>
#include "nullify.h"
#include "src/ImportedImage.h"
#include "src/mainwaindow.h"
#include "src/importwindow.h"
#include "coloredvertexmatrix.h"
#include"vertexlinker.h"
#include"qstring.h"
#include"qfile.h"
#include<QApplication>


int main(int argc, char **argv) {
    uint8_t null_color[3] = {255, 255, 255};
    float threshold = 20;
    std::cout << "3D Model Builder " << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Commands: hello  " << std::endl;
    std::cout << "          render " << std::endl;
    std::cout << "          window " << std::endl;
    std::cout << "          image " << std::endl;
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

        } else if (input == "window") {
            QApplication app(argc, argv);

            //QSurfaceFormat format;
            //format.setSamples(16);
            importwindow import;
            //import.setFormat(format);
            //import.resize(640, 480);
            import.show();

            //app.setQuitOnLastWindowClosed(true);
            app.exec();
        } else if (input == "render") {

            QGuiApplication app(argc, argv);

            QSurfaceFormat format;
            format.setSamples(16);

            MainWindow window;
            window.setFormat(format);
            window.resize(640, 480);
            window.show();

            app.setQuitOnLastWindowClosed(true);
            app.exec();

        } else if (input == "image") {

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
                cout<<w<<" "<<h<<" "<<d<<" "<<endl;
                if(w!=-1){model_width=min(model_width,w);}
                if(h!=-1){model_height=min(model_height,h);}
                if(d!=-1){model_depth=min(model_depth,d);}


            }

            float resolution_split=10;

            cout<<endl<<"FINAL: "<<model_width<<" "<<model_height<<" "<<model_depth<<endl;

            vector<VotingMatrix> voters=vector<VotingMatrix>();
            for(int i=0;i<6;i++){
                cout<<"Voting Matrix"<<i<<":"<<endl;
                voters.push_back(VotingMatrix(
                                     model_width, model_height, model_depth,b.getSides()[i],resolution_split)
                                  );
            }
           ColoredVertexMatrix  vertices= ColoredVertexMatrix(model_width, model_height,model_depth, voters ,resolution_split );

           nullify(vertices, null_color, threshold);


           ColoredVertexMatrix *shell= vertices.getShell();

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
                  if((int)values[3]!=0){stream <<i<<" "<<j<<" "<<k<<" "<<endl;}


              }}}

           }

           VertexLinker vl=VertexLinker(shell);
           vl.makeShapes();

           float * vertArray= &shell->getListOfVertsAsFloats()[0];

           int wid=shell->getWidth();
           int hei=shell->getHeight();
           int dep=shell->getDepth();
           std::vector<GLfloat> facesByXYZ=std::vector<float>();
           std::vector<GLfloat> facesByRBG=std::vector<float>();
//print all triangles and add their raw data into the face arrays
           foreach (vector<ColoredVertex> face , vl.getTriangles()){
               cout<<"triangle\n";
               for (int i=0;i<3;i++){
               ColoredVertex vert=face[i];

               facesByXYZ.push_back(((float)vert.getX())/wid -.5);
               facesByXYZ.push_back(((float)vert.getY())/hei -.5);
               facesByXYZ.push_back(((float)vert.getZ())/hei -.5);

               uint8_t* colors=vert.getValue();
               facesByRBG.push_back(((float)colors[0])/256);
               facesByRBG.push_back(((float)colors[1])/256);
               facesByRBG.push_back(((float)colors[2])/256);

               face[i].printVert();

           }
               cout<<std::endl;

           }
           cout<<"faces\n";
           foreach (vector<ColoredVertex> face , vl.getSquares()){
               vector<ColoredVertex> triangles=vl.toTriangles(face);
               cout<<"square    "<<triangles.size()<<"\n";

               for (int i=0;i<6;i++){
                   ColoredVertex  vert=triangles[i];

               facesByXYZ.push_back(((float)vert.getX())/wid -.5);
               facesByXYZ.push_back(((float)vert.getY())/wid -.5);
               facesByXYZ.push_back(((float)vert.getZ())/wid -.5);

               uint8_t* colors=vert.getValue();
               facesByRBG.push_back(((float)colors[0])/256);
               facesByRBG.push_back(((float)colors[1])/256);
               facesByRBG.push_back(((float)colors[2])/256);
                   triangles[i].printVert();

           }
               cout<<std::endl;

           }
           QGuiApplication app(argc, argv);

           QSurfaceFormat format;
           format.setSamples(16);
           MainWindow window(&facesByXYZ[0],&facesByRBG[0],facesByXYZ.size()/3);
           window.setFormat(format);
           window.resize(640, 480);
           window.show();

           app.setQuitOnLastWindowClosed(true);
           app.exec();


        } else if (input == "exit" || input == "quit") {

            return 0;

        }

        std::cout << std::endl;
    }
}
