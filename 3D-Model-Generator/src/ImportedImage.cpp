using namespace std;
#include <vector>
#include "ImportedImage.h"
#include <stdio.h>

void ImportedImage::setPixels() {
    if ( false == pic.isNull() )
    {
        std::cout << "Test" << std::endl;
        pixels = vector<vector<uint8_t*>>();
        for ( int col = 0; col < pic.width(); ++col ){
            pixels.push_back(vector<uint8_t*>());
            for ( int row = 0; row < pic.height(); ++row ){
                QColor clrCurrent( pic.pixel( col, row ) );
                uint8_t *data = new uint8_t [3] {((uint8_t)clrCurrent.red()),
                                             ((uint8_t)clrCurrent.green()),
                                            ((uint8_t) clrCurrent.blue())};
                pixels[col].push_back(data);
            }
        }
    }
}

box::box(vector<QImage> images) {
    for (int count = 0; count < 6; count++){
        //0=front,1bottom,2back,3up,4left,5right

        ImportedImage side = ImportedImage(images[count]);
        side.setFace(count);
        side.setPixels();
        if(count == 0){
            side.setInvertU(false);
            side.setInvertV(false);
            side.setInvertDepth(true);

            side.setU('x');

            side.setV('y');
        } else if (count == 1){
            side.setInvertU(false);
            side.setInvertV(false);
            side.setInvertDepth(false);
            side.setU('x');
            side.setV( 'z');
        }  else if (count == 2){
            side.setInvertU(true);
            side.setInvertV(false);
            side.setInvertDepth(false);

            side.setU('x');

            side.setV('y');
        } else if (count == 3){
            side.setInvertU(false);
            side.setInvertV(true);
            side.setInvertDepth(true);
            side.setU('x');

            side.setV('z');
        } else if (count == 4){
            side.setInvertU(true);
            side.setInvertV(false);

            side.setU('z');

            side.setV('y');
        } else if (count == 5){
            side.setInvertU(false);
            side.setInvertV(false);
            side.setU('z');

            side.setV('y');
        }
        sides.push_back(side);
    }
}

uint8_t* ImportedImage::getValue (int u, int v){
    if(u>=pixels.size())
    {std::cout<<"U="<<u<<endl;}
    if(v>=pixels.size())
    {std::cout<<"V="<<v<<endl;}

    return pixels[u][v];}
