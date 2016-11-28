#include "verticessmoothing.h"


void smooth(ColoredVertexMatrix& image, int smoothing_factor) {
     std::vector<std::vector<std::vector<ColoredVertex>>>verts=image.getVertices();

     for(unsigned long x=0; x<image.getWidth(); ++x) {

        for(unsigned long y=0; y<image.getHeight(); ++y) {

            for(unsigned long z=0; z<image.getDepth(); ++z) {

                // if color difference is less than threshold
                if( y%smoothing_factor!=0){
                    image.setNull(x,y,z);//nullify
                }

            }
        }
    }
}
/*void smooth2(ColoredVertexMatrix& image,std::vector<std::vector<VertexLine>> levels) {
    //nullify all vertices in a line


}

*/

