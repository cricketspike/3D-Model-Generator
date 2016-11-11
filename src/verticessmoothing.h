#ifndef VERTICESSMOOTHING_H
#define VERTICESSMOOTHING_H
#include "ColoredVertexMatrix.h"


void smooth(ColoredVertexMatrix& image, int smoothing_factor) {
     std::vector<std::vector<std::vector<ColoredVertex>>>verts=image.getVertices();
    unsigned int counter_x,counter_y, counter_z;
     for(unsigned long x=0; x<image.getWidth(); ++x) {
         counter_x++;
        for(unsigned long y=0; y<image.getHeight(); ++y) {
            counter_y++;
            for(unsigned long z=0; z<image.getDepth(); ++z) {
                counter_z++;
                // if color difference is less than threshold
                if( counter_x%smoothing_factor!=0||counter_y%smoothing_factor!=0||counter_z%smoothing_factor!=0){
                    image.setNull(x,y,z);//nullify
                }

            }
        }
    }
}

#endif // VERTICESSMOOTHING_H
