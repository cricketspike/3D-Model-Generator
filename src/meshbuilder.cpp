#include "meshbuilder.h"


// Assumes access on 3D vector of ColoredVertex is matrix[z][y][x]
std::vector<std::vector<ColoredVertex>> MeshBuilder::getMatrixSlice(const int& index, const int& of, int& d, ColoredVertexMatrix& matrix)
{
    int i = 0;

    if (index <= 1) {
        i = 0;
    } else if (index >= of) {
        i = matrix.getDepth() - 1;
    } else {
        double a = matrix.getDepth() - 2;
        double b = of - 1;
        double i = floor(a / b);
        int increment = i;

        i = 1 + (index * increment);
    }

    d = i;

    return matrix.getVertices()[d];
}


void MeshBuilder::slopes(const int &count, double *array)
{
    double angle_rad = 0;
    double angle_rad_incr = 2.0*M_PI/(double)count;

    for (int i=0; i<count; i++) {
        array[i] = tan(angle_rad);

        angle_rad += angle_rad_incr;
    }
}

double MeshBuilder::lineSlope(const Point& p1, const Point& p2)
{
    return (p2.y-p1.y)/(p2.x-p1.x);
}

double MeshBuilder::perpendicular(const double& slope)
{
    return -1/slope;
}

void MeshBuilder::lineCenter(const Point& p1, const Point& p2, Point& p3)
{
    p3.x = p1.x + ((p2.x - p1.x) / 2);
    p3.y = p1.x + ((p2.x - p1.x) / 2);
}

// |x| < (width/2), |y| < (height/2)
void MeshBuilder::cartesian2array(const int& width, const int& height, const Point& p, Point& p_a)
{
    p_a.x =  p.x + (width / 2);
    p_a.y = -p.y + (height / 2);
}

void MeshBuilder::array2cartesian(const int& width, const int& height, const Point& p_a, Point& p)
{
    p.x = p_a.x - (width / 2);
    p.y = (height / 2) -  p_a.y;
}

bool MeshBuilder::trace_boundsCheck(const int& width, const int& height, const int& quadrant, const Point& p_a)
{
    if (quadrant == 1) {
        return p_a.x < width && p_a.y > 0;
    } else if (quadrant == 2) {
        return p_a.x > 0 && p_a.y > 0;
    } else if (quadrant == 3) {
        return p_a.x > 0 && p_a.y < height;
    } else if (quadrant == 4) {
        return p_a.x < width && p_a.y < height;
    }

    return false;
}

void MeshBuilder::trace_increment(const int& quadrant, const bool& vertical, const int& slope_abs, Point& p_a)
{
    if (quadrant == 1) {
        if (vertical) {
            p_a.x = p_a.x + slope_abs;
            p_a.y = p_a.y - 1;
        } else {
            p_a.x = p_a.x + 1;
            p_a.y -= slope_abs;
        }
    } else if (quadrant == 2) {
        if (vertical) {
            p_a.x = p_a.x - slope_abs;
            p_a.y = p_a.y - 1;
        } else {
            p_a.x = p_a.x - 1;
            p_a.y -= slope_abs;
        }
    } else if (quadrant == 3) {
        if (vertical) {
            p_a.x = p_a.x - slope_abs;
            p_a.y = p_a.y + 1;
        } else {
            p_a.x = p_a.x - 1;
            p_a.y += slope_abs;
        }
    } else if (quadrant == 4) {
        if (vertical) {
            p_a.x = p_a.x + slope_abs;
            p_a.y = p_a.y + 1;
        } else {
            p_a.x = p_a.x + 1;
            p_a.y += slope_abs;
        }
    }
}

// Assumes access on 2D vector of ColoredVertex is matrix[y][x]
// (cx, cy) & (imgX, imgY) in cartesian coordinates
void MeshBuilder::trace(std::vector<std::vector<ColoredVertex>>& image, const Point& p_c, const double& slope, Point& p_t)
{
    size_t image_width = image[0].size();
    size_t image_height = image.size();

    // Translate (cx, cy) to array coordinates

    Point p_a;
    cartesian2array((int)image_width, (int)image_height, p_c, p_a);

    // Determine quadrant in cartesian plane of image
    //      in which (cx, cy) falls
    //      in order to determine the outward direction

    int quadrant;
    if (p_a.y < image_height / 2) {
        if (p_a.x > image_width / 2)
            quadrant = 1;
        else
            quadrant = 2;
    } else {
        if (p_a.x < image_width / 2)
            quadrant = 3;
        else
            quadrant = 4;
    }

    // Get y distance per unit x
    // or vice versa

    int slope_abs = (int)floor(abs(slope));
    bool vertical = slope_abs == 0;
    if (vertical)
        slope_abs = (int)round(abs(1/slope));

    // Trace

    Point p_a_before;                                                                           // Bookkeeping
    bool solid_before = image[p_a.y][p_a.x].getValue()[3] != 0;

    p_t.x = MESHBUILDER_COORDINATE_NOTFOUND;                                                    // Loop below sets p_t.x, p_t.y
    p_t.y = MESHBUILDER_COORDINATE_NOTFOUND;                                                    //  to coordinates of a mesh vertex, if found

    while ( trace_boundsCheck((int)image_width, (int)image_height, quadrant, p_a) ) {           // While not out of bounds in direction of trace

        bool solid_now = image[p_a.y][p_a.x].getValue()[3] != 0;
        if (solid_before == !solid_now) {                                                       //      If alpha transition between this step of the line and the last
            lineCenter(p_a_before, p_a, p_t);                                                   //       return the vertex at the center of the area jumped over by this step
            return;
        }

        p_a_before = p_a;                                                                       // Bookkeeping
        trace_increment(quadrant, vertical, slope_abs, p_a);
        solid_before = solid_now;

    }
}
