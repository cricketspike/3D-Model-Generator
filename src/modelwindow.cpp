#include "modelwindow.h"
#include "ui_modelwindow.h"

ModelWindow::ModelWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ModelWindow)
{
    ui->setupUi(this);
}

ModelWindow::~ModelWindow()
{
    delete ui;
}

void ModelWindow::on_openGLWidget_resized()
{

}

void ModelWindow::createModel(box b,int density_split,int loop_dist,float bg_bias){
    ModelEditor * editor= new ModelEditor();
    connect(editor,SIGNAL(renderModel(vector<GLfloat>,vector<GLfloat>)),ui->openGLWidget,SLOT(renderModel(vector<GLfloat>,vector<GLfloat>)));
    editor->SetupModel(b,density_split,loop_dist,bg_bias);
    editor->defaultStart();
}


void ModelWindow::exportModel(box b,int density_split,int loop_dist,float bg_bias, string path){
    ModelEditor * editor= new ModelEditor();
    connect(editor,SIGNAL(renderModel(vector<GLfloat>,vector<GLfloat>)),ui->openGLWidget,SLOT(renderModel(vector<GLfloat>,vector<GLfloat>)));
    editor->SetupModel(b,density_split,loop_dist,bg_bias);
    editor->renderStart(path);
}



void ModelWindow::on_ModelWindow_accepted()
{

}




void ModelWindow::on_openGLWidget_destroyed()
{

}
