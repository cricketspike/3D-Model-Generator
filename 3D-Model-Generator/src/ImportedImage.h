#ifndef IMPORTSIDE_H
#define IMPORTSIDE_H

using namespace std;
#include <vector>
#include<qimage.h>
#include <cstdint>
#include<iostream>
class ImportedImage {
    private:
        QImage pic;
        int face;//0=front,1bottom,2back,3up,4left,5right
        vector<vector<uint8_t*>> pixels;
        bool invert_u;
        bool invert_v;
        bool invert_depth;
        char u;//width
        char v;//height
        int img_width;
        int img_height;

    public:
        ImportedImage(QImage image){
           pic=image;
           img_width=image.width();
           img_height=image.height();
        }
        ImportedImage(){}
        void setPic(QImage newPic) {pic = newPic;}
        void setFace(int newFace) {face = newFace;}
        void setInvertU(bool newValue) {invert_u = newValue;}
        void setInvertV(bool newValue) {invert_v = newValue;}
        void setInvertDepth(bool newValue){invert_depth= newValue;}
        void setU (char newU) {u = newU;}
        void setV (char newV) {v = newV;}
        void setPixels();
        QImage getImage() {return pic;}
        int getImageWidth() {return img_width;}
        int getImageHeight() {return img_height;}

        int getFace() {return face;}
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

class box {
    private:
        vector<ImportedImage> sides;
    public:
        void addSide(ImportedImage side){sides.push_back(side);}
        box(vector<QImage> images);
        vector<ImportedImage> getSides() {return sides;}
};





#endif // IMPORTSIDE_H
