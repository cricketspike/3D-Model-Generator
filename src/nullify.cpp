#include "nullify.h"

// Color Percent Difference
float colorPercentDifference(Color c1, Color c2) {
    float diff_r = 0;
	float diff_g = 0;
	float diff_b = 0;
	if(c1.r != c2.r)
		diff_r = abs(c1.r - c2.r) / ((c1.r + c2.r)/2.0);
	if(c1.g != c2.g)
		diff_g = abs(c1.g - c2.g) / ((c1.g + c2.g)/2.0);
	if(c1.b != c2.b)
		diff_b = abs(c1.b - c2.b) / ((c1.b + c2.b)/2.0);
    return (diff_r + diff_g + diff_b)/3.0 * 100.0;
}

float colorPercentError(Color c1, Color c2) {
    float diff_r = c2.r;
	float diff_g = c2.g;
	float diff_b = c2.b;
	if(c1.r != 0)
		diff_r = abs(c1.r - c2.r) / c1.r;
	if(c1.g != 0)
		diff_g = abs(c1.g - c2.g) / c1.g;
	if(c1.b != 0)
		diff_b = abs(c1.b - c2.b) / c1.b;
    return (diff_r + diff_g + diff_b)/3.0 * 100.0;
}

float colorVectorDifference(Color c1, Color c2) {
	return (sqrt( pow(c1.r - c2.r, 2) + pow(c1.g - c2.g, 2) + pow(c1.b - c2.b, 2) ))/3.0 * 100;
}

void nullify(ColoredVertexMatrix& image, uint8_t* c_null, float thresh) {
    Color color_null;
    color_null.r = c_null[0];
    color_null.g = c_null[1];
    color_null.b = c_null[2];

    nullify(image, color_null, thresh);
}

//	thresh = [0, 100]
void nullify(ColoredVertexMatrix& image, Color c_null, float thresh) {
     std::vector<std::vector<std::vector<ColoredVertex>>>verts=image.getVertices();
    for(unsigned long x=0; x<image.getWidth(); ++x) {
        for(unsigned long y=0; y<image.getHeight(); ++y) {
            for(unsigned long z=0; z<image.getDepth(); ++z) {
                // if color difference is less than threshold
                Color color;
                color.r = verts[x][y][z].getValue()[0];
                color.g = verts[x][y][z].getValue()[1];
                color.b = verts[x][y][z].getValue()[2];
                if( colorPercentDifference(color, c_null) < thresh )
                    image.setNull(x,y,z);//nullify
            }
        }
    }
}

