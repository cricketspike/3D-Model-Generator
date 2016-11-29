#ifndef MODELEDITOR_H
#define MODELEDITOR_H
#include <QApplication>
#include <QSurfaceFormat>
#include <QTextStream>


#include"vertexlinker.h"
#include"qstring.h"
#include"qfile.h"


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
#include "precisetrimming.h"

#include "verticessmoothing.h"
#include"mainwaindow.h"
#include "objfilewriter.h"
class ModelEditor: public QObject
{
    Q_OBJECT

signals:
    void renderModel(vector<GLfloat> faces,vector<GLfloat> colors);

public:

    ModelEditor();
    void SetupModel(box image_box,int resolution_split,int vert_loop_dist);//set all the variables
    void setImageAccuracy(unsigned int newAmmount);
    void setVertexSparseness(unsigned int newAmmount);
    void setBackgroundColor(uint8_t* color);
    void setColorTollerance(unsigned int newAmmount);
    void setBackgroundTrimmingWeight(float newAmmount);
    //void setPictures(box b); this should take in input from previous class
    void defaultStart();
    void renderStart(string path);
    void createModel(bool exprt=false,string path_in="exported_image");//generate infromation for model and run opengl
    void resetModel();//recalculate and apply changes
    void setResolution(    float resolution_split){   m_resolution_split= resolution_split;}
    void setDesnitySplit(    int vertices_density_split){   m_levels_density_split= vertices_density_split;}

private:
    box m_image_box;
    uint8_t * m_null_color;
    float m_threshold;
    std::vector<uint8_t*> vertices_by_XYZ;
    std::vector<GLfloat> m_face_vertices_data;
    std::vector<GLfloat> m_face_color_data;
    float m_resolution_split;
    int m_levels_density_split;

};

#endif // MODELEDITOR_H
