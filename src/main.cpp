#include <QGuiApplication>
#include <QSurfaceFormat>

#include <iostream>
#include <string>
#include <vector>
#include "nullify.h"
#include "src/ImportedImage.h"
#include "src/mainwaindow.h"
#include "ColoredVertexMatrix.h"
#include"vertexlinker.h"
#include"qstring.h"
#include"qfile.h"
int main(int argc, char **argv)
{

    uint8_t null_color[3] = {255, 255, 255};
    float threshold = 20;
    std::cout << "3D Model Builder " << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Commands: hello  " << std::endl;
    std::cout << "          render " << std::endl;
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
           cout<<"**************************";
           nullify(vertices, null_color, threshold);

           QString filename="testVerts";
           QFile file(filename);
           if(file.open(QIODevice::ReadWrite)){
               QTextStream stream( &file );
               int width=vertices.getWidth();
               int height=vertices.getHeight();
               int depth=vertices.getDepth();
              for (int i=0;i<width;i++){
              for (int j=0;j<height;j++){
              for (int k=0;k<depth;k++){
                  uint8_t* values= vertices.getValue(i,j,k).getValue();
              //std::cout<<endl<<i<<":"<<j<<":"<<k<<":           ";
                  if((int)values[3]!=0){stream <<i<<" "<<j<<" "<<k<<" "<<endl;}


              }}}

           }

           VertexLinker vl=VertexLinker(&vertices);
           vl.makeShapes();

        } else if (input == "exit" || input == "quit") {

            return 0;

        }

        std::cout << std::endl;
    }
}
