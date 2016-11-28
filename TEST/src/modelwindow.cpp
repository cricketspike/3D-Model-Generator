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

void ModelWindow::createModel(box b,int density_split,int loop_dist){

    std::cout<<"TEST1"<<endl;
    ModelEditor * editor= new ModelEditor();
    connect(editor,SIGNAL(renderModel(vector<GLfloat>,vector<GLfloat>)),ui->openGLWidget,SLOT(renderModel(vector<GLfloat>,vector<GLfloat>)));

    editor->SetupModel(b,density_split,loop_dist);
    std::cout<<"TEST2"<<endl;


    editor->defaultStart();
    std::cout<<"TEST3"<<endl;




}


void ModelWindow::exportModel(box b,int density_split,int loop_dist, string path){

    ModelEditor * editor= new ModelEditor();
    connect(editor,SIGNAL(renderModel(vector<GLfloat>,vector<GLfloat>)),ui->openGLWidget,SLOT(renderModel(vector<GLfloat>,vector<GLfloat>)));

    editor->SetupModel(b,density_split,loop_dist);


    editor->renderStart(path);




}



void ModelWindow::on_ModelWindow_accepted()
{

}




void ModelWindow::on_openGLWidget_destroyed()
{

}
