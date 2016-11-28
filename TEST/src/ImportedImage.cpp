using namespace std;
#include <vector>
#include "ImportedImage.h"
#include <stdio.h>

//setPixels function goes through an image file
//and goes through every pixel and grabs the
//RGB data and sets a uint8 array to those color
//values. Once done it will push it back on the
//pixels vector that is held by the importside class
//Array Example: [Red, Green, Blue]

void ImportedImage::setPixels() {
  //Check to see if the picture is exists
  if ( false == pic.isNull() ) {

    //initiate a 2D vector of uint8 to represent all the pixels
    pixels = vector<vector<uint8_t*>>();

    //Go through every pixel in the picture
    for ( int col = 0; col < pic.width(); ++col ) {

      pixels.push_back(vector<uint8_t*>());
      for ( int row = 0; row < pic.height(); ++row ) {
        QColor clrCurrent( pic.pixel( col, row ) ); //Grab color Data
        //Set color data
        uint8_t *data = new uint8_t [3] {((uint8_t)clrCurrent.red()),
                                         ((uint8_t)clrCurrent.green()),
                                         ((uint8_t) clrCurrent.blue())};
        pixels[col].push_back(data);
      }
    }
  }
}

//Box initializes all the values in the class.
//Sets up all the values of the side and then
//adds it to the box. Check header for all the
//values that are intialized
//0=front,1bottom,2back,3up,4left,5right
//direction corresponds to side camera is on

box::box(vector<QImage> images) {
  //Go through all the images and set all the data
  for (int count = 0; count < 6; count++) {

    ImportedImage side= ImportedImage(images[count]);
    side.setFace(count);
    side.setPixels();
    if(count == 0) {//front
      side.setInvertU(false);//right=+x
      side.setInvertV(false);//up=+y
      side.setInvertDepth(false);//forward(towards screen in opengl)=+z
      side.setU('x');
      side.setV('y');
    } else if (count == 1) {//bottom
      side.setInvertU(false);//right=+x
      side.setInvertV(false);//up=+z
      side.setInvertDepth(true);//forward(towards screen in opengl)=-y
      side.setU('x');
      side.setV( 'z');
    } else if (count == 2) {//2back
      side.setInvertU(true);//right=-x
      side.setInvertV(false);//up=+y
      side.setInvertDepth(true);//forward(towards screen in opengl)=-z
      side.setU('x');
      side.setV('y');
    } else if (count == 3) {//up
      side.setInvertU(false);//right=x
      side.setInvertV(true);//up=-z
      side.setInvertDepth(false);//forward(towards screen in opengl)=+y
      side.setU('x');
      side.setV('z');
    } else if (count == 4) {//left
      side.setInvertU(false);//right=+z
      side.setInvertV(false);//up=+y
      side.setInvertDepth(true);//forward(towards screen in opengl)=-x
      side.setU('z');
      side.setV('y');
    } else if (count == 5) {//right
      side.setInvertU(true);//right=-z
      side.setInvertV(false);//up=+y
      side.setInvertDepth(false);//forward(towards screen in opengl)=+x
      side.setU('z');
      side.setV('y');
    }
    sides.push_back(side);
  }
}

//returns the color value of a spot on the image
uint8_t* ImportedImage::getValue (int u, int v){
    if(u>=pixels.size())
    {std::cout<<"U="<<u<<endl;}
    if(v>=pixels.size())
    {std::cout<<"V="<<v<<endl;}

    return pixels[u][v];
}
uint8_t ImportedImage::getWeight (int u, int v){
    if(u>=pixels.size())
    {std::cout<<"U="<<u<<endl;}
    if(v>=pixels.size())
    {std::cout<<"V="<<v<<endl;}

return weight;}//later factor in u and v


uint8_t ImportedImage::getDepthOfPeak(int u, int v){
    if(u>=pixels.size())
    {std::cout<<"U="<<u<<endl;}
    if(v>=pixels.size())
    {std::cout<<"V="<<v<<endl;}
    return depth_of_peak;}//later factor in u and v

