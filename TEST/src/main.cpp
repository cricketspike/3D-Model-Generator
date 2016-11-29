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

#include "unit-tests/CubeMapEditorDisplay/cubemapeditordisplay_driver.h"
#include "unit-tests/CubeMapEditorImage/cubemapeditorimage_driver.h"
#include "unit-tests/CubeMapEditorRasterWidget/cubemapeditorrasterwidget_driver.h"
#include "unit-tests/CubePreviewWidget/cubepreviewwidget_driver.h"







void Test_2dMatrixTo3DVotingMatrix(){

    //this is intended to create a 3d projection of a 2d plane where colors in the same x and y are the same but the weights depend on z values
    //this just make sure that it is the same color and differtent weights throughout these projections

    //the image we use here should not matter but these cant be manually created***
    QImage test_q_image(":/images/TestImage.jpg");
    ImportedImage test_imported_image=ImportedImage(test_q_image);
    test_imported_image.setPixels();
    test_imported_image.setU('x');
    test_imported_image.setV('y');
    //*******
    //get hieght and depth to check aevery pixel without going over
    int model_width=test_imported_image.getImageWidth();
    int model_height=test_imported_image.getImageHeight();
    int model_depth=10;//arbitrary number

    VotingMatrix test_voting_matrix(model_width, model_height, model_depth,test_imported_image,2);
    for(int i=0;i<test_voting_matrix.getWidth();i++){
            for(int j=0;j<test_voting_matrix.getHeight();j++){
                //everything heres should be same color
                uint8_t pixel_red=test_voting_matrix.getValue(i,j,0).getColor(0),
                        pixel_green=test_voting_matrix.getValue(i,j,0).getColor(1),
                        pixel_blue=test_voting_matrix.getValue(i,j,0).getColor(2);


                    for(int k=0;k<test_voting_matrix.getDepth();k++){
                        int red_dif=pow(pixel_red-test_voting_matrix.getValue(i,j,0).getColor(0),2);
                        int green_dif=pow(pixel_green-test_voting_matrix.getValue(i,j,0).getColor(1),2);
                        int blue_dif=pow(pixel_blue-test_voting_matrix.getValue(i,j,0).getColor(2),2);
                        if(red_dif>0||green_dif>0||blue_dif>0){
                            cout<<"error: different colors accross same depth"<<endl;
                            exit(1);
                        }


                    }
            }
    }
    cout<<"passed test: convert 2d color matrix to 3d projection matrix"<<endl;

   //ColoredVertexMatrix  vertices= ColoredVertexMatrix(model_width, model_height,model_depth, voters ,m_resolution_split,m_null_color );
}


void Test_ImageTo2DMatrix(){
    //Put all tests here
    //Test that ImportedImage can turn a .jpg into a 2d Matrix of the appropriate color values
QImage test_q_image(":/images/TestImage.jpg");
if(test_q_image.isNull()){
        cout<<"test image does not exist"<<endl;
        exit(1);}
ImportedImage test_imported_image=ImportedImage(test_q_image);
test_imported_image.setPixels();
//the test image is 3x3 40 pixel squares of solid colors
uint8_t red[3]={255,0,0};
uint8_t green[3]={0,255,0};
uint8_t blue[3]={0,0,255};
uint8_t yellow[3]={255,255,0};
uint8_t cyan[3]={0,255,255};
uint8_t violet[3]={255,0,255};
uint8_t black[3]={0,0,0};
uint8_t grey[3]={100,100,100};
uint8_t white[3]={255,255,255};
vector<vector<uint8_t*>> intended_colors={{black,red,cyan},{grey,green,violet},{white,blue ,yellow}};
int w= test_imported_image.getImageWidth();
int h=test_imported_image.getImageHeight();
for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
        uint8_t * intended_color=intended_colors[i][j];
        uint8_t * actual_color=test_imported_image.getValue(i*40+40/2,j*40+40/2);
        for(int k=0;k<3;k++){
            int dif=intended_color[k]-actual_color[k];
           if((dif*dif)>4){//leave some room for noise of exterior image generating program
                cout<<"colors do not match at["<<i<<"]["<<j<<"]["<<k<<"]:"<<(int) intended_color[k] <<"vs"<< (int) actual_color[k];
               exit(1);
            }
        }
    }
}




cout<<"passed test convert image to 2d matrix of color values"<<endl;
}




void test_6_voters_to_matrix(){
    uint8_t null_col[3] = {255, 255, 255};
//manualy make a voter Matrix
//these already take rotation into account so the ones with matching names will be the ones voting together

    vector<vector<vector<MatrixNode*>>> matrixA={//2X2X2    lots of red voters on low x, lots of white voters on high y
        {

            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(0, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.1f), &MatrixNode (0, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.1f), &MatrixNode (0, 0, 0, 1)},

        }
};


    vector<vector<vector<MatrixNode*>>> matrixC={//2X2X2
        {

            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.2f), &MatrixNode (255, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.1f), &MatrixNode (0, 0, 0, 1)},

        }
};
    vector<vector<vector<MatrixNode*>>> matrixD={//2X2X2
        {

            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.2f), &MatrixNode (255, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 0.4f), &MatrixNode (0, 0, 0, 1)},

        }
};


    vector<vector<vector<MatrixNode*>>> matrixE={//2X2X2
        {

            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (0, 0, 0, 1), &MatrixNode (0, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (0, 0, 0, 1), &MatrixNode (0, 0, 0, 1)},

        }
};
    vector<vector<vector<MatrixNode*>>> matrixF={//2X2X2
        {

            {&MatrixNode(0,0,0,1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (0, 0, 0, 1), &MatrixNode (0, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (0, 0, 0, 0), &MatrixNode (0, 0, 0, 1)},

        }
};


    vector<vector<vector<MatrixNode*>>> matrixB={//2X2X2
        {

            {&MatrixNode(0, 0, 0, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 1), &MatrixNode (0, 0, 0, 1)},


            },
        {
            {&MatrixNode(255, 255, 255, 1), (&MatrixNode(255, 0, 0, 1))},
            {&MatrixNode (255, 0, 0, 1), &MatrixNode (0, 0, 0, 1)},

        }



};
    vector<VotingMatrix> voters={VotingMatrix(matrixA),
                                 VotingMatrix(matrixB),
                                 VotingMatrix(matrixC),
                                 VotingMatrix(matrixD),
                                 VotingMatrix(matrixE),
                                 VotingMatrix(matrixF)};
    ColoredVertexMatrix  vertices= ColoredVertexMatrix(2, 2, 2, voters ,1,null_col );
    vertices.getValue(0,0,0).printVert();//low x and low y so should be red since the majority will be red
    vertices.getValue(1,1,1).printVert();//high x and high y so should be white  since the majority will be white
}








int main(int argc, char **argv)
{
    std::string input;

    std::cout << "3D Model Builder " << std::endl;
    std::cout << "-----------------" << std::endl;
    std::cout << "Commands: connors-tests  " << std::endl;
    std::cout << "          ut-cubemapeditorimage" << std::endl;
    std::cout << "          ut-cubemapeditorrasterwidget" << std::endl;
    std::cout << "          ut-cubemapeditordisplay" << std::endl;
    std::cout << "          ut-cubepreviewwidget" << std::endl;
    std::cout << "          quit   " << std::endl << std::endl;

    while (true) {

        // Prompt

        std::cout << "> ";
        std::string input;
        std::getline(std::cin, input);

        // Command processing
        if (input == "connors-tests") {

            Test_ImageTo2DMatrix();
            Test_2dMatrixTo3DVotingMatrix();
            test_6_voters_to_matrix();

        } else if (input == "ut-cubemapeditorimage") {

            QApplication app(argc, argv);

            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            QSurfaceFormat::setDefaultFormat(format);

            CubeMapEditorImage_Driver widget;
            widget.show();

            app.exec();

        } else if (input == "ut-cubemapeditorrasterwidget") {

            QApplication app(argc, argv);

            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            QSurfaceFormat::setDefaultFormat(format);

            CubeMapEditorRasterWidget_Driver widget;
            widget.show();

            app.exec();


        } else if (input == "ut-cubemapeditordisplay") {

            QApplication app(argc, argv);

            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            QSurfaceFormat::setDefaultFormat(format);

            CubeMapEditorDisplay_Driver widget;
            widget.show();

            app.exec();


        } else if (input == "ut-cubepreviewwidget") {

            QApplication app(argc, argv);

            QSurfaceFormat format;
            format.setDepthBufferSize(24);
            format.setStencilBufferSize(8);
            QSurfaceFormat::setDefaultFormat(format);

            CubePreviewWidget_Driver widget;
            widget.show();

            app.exec();


        }
    }
}

