#ifndef IMPORTSIDE_H
#define IMPORTSIDE_H

using namespace std;
#include <vector>
#include<qimage.h>
#include <cstdint>
#include<iostream>

//Imported Images represent one side of the box
//and all the parts to it
class ImportedImage {
  private:
    QImage pic; //Original image
    int face;//0=front,1bottom,2back,3up,4left,5right
    vector<vector<uint8_t*>> pixels; //2D vector to represent pixels
    bool invert_u;
    bool invert_v;
    bool invert_depth; //Values to represent inversion to the array
    char u;//width
    char v;//height
    unsigned int img_width;
    unsigned int img_height;
    unsigned int max_depth;
    unsigned int depth_of_peak;//0 to min(depth - 2 , depth - 1 - the other side's depth_of_peak) replace this with a 2D array
    //when doing the paint tool its probably a good idea to mask any spot that matches the background color so it stays at the front for simplification
    uint8_t weight;//0 to 100 replace this with a 2D array
  public:
    //Initializeation functions
    ImportedImage(QImage image,uint8_t a_weight){
      pic=image;
      img_width=image.width();
      img_height=image.height();
      weight=a_weight;
    }
    ImportedImage(){}
    void setPic(QImage newPic) {pic = newPic;}
    void setFace(int newFace) {face = newFace;}
    void setInvertU(bool newValue) {invert_u = newValue;}
    void setInvertV(bool newValue) {invert_v = newValue;}
    void setInvertDepth(bool newValue){invert_depth= newValue;}
    void setU (char newU) {u = newU;}
    void setV (char newV) {v = newV;}
    void setMaxDepth(int image_depth){
        max_depth=image_depth;
        depth_of_peak=max_depth/3;
    }
    void setPixels();

    //View functions
    QImage getImage() {return pic;}
    unsigned int getImageWidth() {return img_width;}
    unsigned int getImageHeight() {return img_height;}
    unsigned int getFace() {return face;}
    uint8_t getWeight (int u, int v);
    uint8_t getDepthOfPeak (int u, int v);
    vector<vector<uint8_t*>> getPixels() {return pixels;}
    uint8_t* getValue (int u, int v);
    bool uIsInverted() {return invert_u;}
    bool vIsInverted() {return invert_v;}
    bool depthIsInverted(){return invert_depth;}
    char getU() {return u;}
    char getV() {return v;}
    int getMaxModelWidth(){
      if(u=='x'){return img_width;}else if(v=='x'){return img_height;}else{return -1;}
      }
    int getMaxModelHeight(){
      if(u=='y'){return img_width;}else if(v=='y'){return img_height;}else{return -1;}
      }
    int getMaxModelDepth(){
      if(u=='z'){return img_width;}else if(v=='z'){return img_height;}else{return -1;}
      }
};

//Box is the combination of all the sides of the box
class box {
  private:
    vector<ImportedImage> sides; //Vector to hold all sides
  public:
    void addSide(ImportedImage side){sides.push_back(side);} //add sides to the box
    box(vector<QImage> images);
    vector<ImportedImage> getSides() {return sides;} //Get the sides
};

#endif // IMPORTSIDE_H
