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

void ModelWindow::createModel(box b){

    std::cout<<"TEST1"<<endl;
    ModelEditor * editor= new ModelEditor();
    connect(editor,SIGNAL(renderModel(vector<GLfloat>,vector<GLfloat>)),ui->openGLWidget,SLOT(renderModel(vector<GLfloat>,vector<GLfloat>)));

    editor->SetupModel(b);
    std::cout<<"TEST2"<<endl;


    editor->defaultStart();
    std::cout<<"TEST3"<<endl;




}

void ModelWindow::on_ModelWindow_accepted()
{

}




void ModelWindow::on_openGLWidget_destroyed()
{

}