#ifndef IMPORTSIDE_H
#define IMPORTSIDE_H

using namespace std;
#include <vector>

class importside {
    private:
        QImage pic;
        int face;
        vector<vector<uint8*>> pixels;
        boolean x;
        boolean y;
        char u;
        char v;
    public:
        void setPic(QImage newPic) {pic = newPic;}
        void setFace(int newFace) {face = newFace;}
        void setX(boolean newX) {x = newX;}
        void setY(boolean newY) {y = newY;}
        void setU (char newU) {u = newU;}
        void setV (char newV) {v = newV;}
        void setPixels();
        QImage getImage() {return pic;}
        int getFace() {return face;}
        vector<vector<uint8*>> getPixels() {return pixels;}
        boolean getX() {return x;}
        boolean getY() {return y;}
        char getU() {return u;}
        char getV() {return v;}
};

class box {
    private:
        vertor<importside> sides;
    public:
        void setUp (vector<QImage> images);
        vertor<importside> getSides() {return sides;}
};





#endif // IMPORTSIDE_H
