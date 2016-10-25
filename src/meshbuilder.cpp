#include "meshbuilder.h"


void MeshBuilder::getMeshVertices(ColoredVertexMatrix& matrix, int slices, int rays, int refinement, std::vector<PointsPlane>& pointsPlanes)
{
    pointsPlanes.clear();

    for (int s=1; s<=slices; s++) {
        int d;
        ColoredVertex2DArray slice = getMatrixSlice(matrix, s, slices, d);

        std::vector<Point> points;
        getMeshVertices_base(slice, rays, points);
        if (!points.empty()) {
            for (int r=0; r<refinement; r++)
                getMeshVertices_refine(slice, points);
            pointsPlanes.push_back({points, d});
        }
    }
}

void MeshBuilder::getMeshVertices_base(ColoredVertex2DArray& image, int rays, std::vector<Point>& points)
{
    points.clear();

    size_t image_width = image[0].size();
    size_t image_height = image.size();

    Point p_origin = { 0, 0 };
    p_origin = cartesianToArray((int)image_width, (int)image_height, p_origin);

    double* angles = new double[rays];
    radialAngles(rays, angles);

    for (int i=0; i<rays; i++) {
        Point p_t;
        trace(image, p_origin, angles[i], p_t);
        if ( !(p_t.x == MESHBUILDER_COORDINATE_NOTFOUND || p_t.y == MESHBUILDER_COORDINATE_NOTFOUND) )
            points.push_back(p_t);
    }

    delete [] angles;
}

void MeshBuilder::getMeshVertices_refine(ColoredVertex2DArray& image, std::vector<Point>& points)
{
    for (int i=0; i<points.size()-1; i++) {
        Point p1 = points[i];
        Point p2 = points[i+1];

        Point p_t1, p_t2;

        Point p_c = lineCenter(p1, p2);
        double angle = lineAngle(p1, p2);

        trace(image, p_c, angle+(1.0*M_PI/2.0), p_t1);
        trace(image, p_c, angle+(3.0*M_PI/2.0), p_t2);

        if ( !(p_t1.x == MESHBUILDER_COORDINATE_NOTFOUND || p_t1.y == MESHBUILDER_COORDINATE_NOTFOUND) ) {
            if ( !(p_t2.x == MESHBUILDER_COORDINATE_NOTFOUND || p_t2.y == MESHBUILDER_COORDINATE_NOTFOUND) ) {

                double d1 = distance(p_t1, p_c);
                double d2 = distance(p_t2, p_c);

                if (d1 < d2) {
                    points.insert(points.begin()+i+1, p_t1);
                    i++;
                } else {
                    points.insert(points.begin()+i+1, p_t2);
                    i++;
                }
            } else {
                points.insert(points.begin()+i+1, p_t1);
                i++;
            }
        } else if ( !(p_t2.x == MESHBUILDER_COORDINATE_NOTFOUND || p_t2.y == MESHBUILDER_COORDINATE_NOTFOUND) ) {
            points.insert(points.begin()+i+1, p_t2);
            i++;
        }
    }
}

// Assumes access on 2D vector of ColoredVertex is matrix[y][x]
void MeshBuilder::trace(ColoredVertex2DArray& image, Point p_c, const double& angle, Point& p_t)
{
    size_t image_width = image[0].size();
    size_t image_height = image.size();

    Point p_a = p_c;
    Point p_a_before;                                                                               // Bookkeeping setup
    bool solid_before = image[p_a.y][p_a.x].getValue()[3] != 0;

    p_t.x = MESHBUILDER_COORDINATE_NOTFOUND;                                                        // Loop below sets p_t.x, p_t.y
    p_t.y = MESHBUILDER_COORDINATE_NOTFOUND;                                                        //  to coordinates of a mesh vertex, if found

    if (angle == M_PI/2.0 || angle == 3.0*M_PI/2.0) {

        // Trace up (M_PI/2.0) or down (3.0*M_PI/2.0)

        // Determine quadrant in plane of image
        //      to head toward (bounds checking only -- 2 : 3 will also work)

        int quadrant_toward = (angle == M_PI/2.0) ? 1 : 4;

        while ( trace_boundsCheck((int)image_width, (int)image_height, quadrant_toward, p_a) ) {    // While not out of bounds in direction of trace

            bool solid_now = image[p_a.y][p_a.x].getValue()[3] != 0;
            if (solid_before == !solid_now) {                                                       //      If alpha transition between this step of the line and the last
                p_t = lineCenter(p_a_before, p_a);                                                  //       return the vertex at the center of the area jumped over by this step
                return;
            }

            p_a_before = p_a;                                                                       //      Bookkeeping
            p_a.y = (angle == M_PI/2.0) ? p_a.y - 1 : p_a.y + 1;
            solid_before = solid_now;

        }

    } else {
        // Determine quadrant in plane of image
        //      to head toward

        int quadrant_toward = ceil(angle/(M_PI/2.0));

        // Get y distance per unit x
        // or vice versa

        int slope_abs = (int)abs(floor(tan(angle)));
        bool run_over_rise = (slope_abs == 0);
        if (run_over_rise)
            slope_abs = (int)abs(round(1/tan(angle)));

        // Trace

        while ( trace_boundsCheck((int)image_width, (int)image_height, quadrant_toward, p_a) ) {    // While not out of bounds in direction of trace

            bool solid_now = image[p_a.y][p_a.x].getValue()[3] != 0;
            if (solid_before == !solid_now) {                                                       //      If alpha transition between this step of the line and the last
                p_t = lineCenter(p_a_before, p_a);                                                  //       return the vertex at the center of the area jumped over by this step
                return;
            }

            p_a_before = p_a;                                                                       //      Bookkeeping
            trace_increment(quadrant_toward, run_over_rise, slope_abs, p_a);
            solid_before = solid_now;

        }
    }
}

bool MeshBuilder::trace_boundsCheck(int width, int height, int quadrant, Point p_a)
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

void MeshBuilder::trace_increment(int quadrant, bool run_over_rise, int slope_abs, Point& p_a)
{
    if (quadrant == 1) {
        if (run_over_rise) {
            p_a.x = p_a.x + slope_abs;
            p_a.y = p_a.y - 1;
        } else {
            p_a.x = p_a.x + 1;
            p_a.y -= slope_abs;
        }
    } else if (quadrant == 2) {
        if (run_over_rise) {
            p_a.x = p_a.x - slope_abs;
            p_a.y = p_a.y - 1;
        } else {
            p_a.x = p_a.x - 1;
            p_a.y -= slope_abs;
        }
    } else if (quadrant == 3) {
        if (run_over_rise) {
            p_a.x = p_a.x - slope_abs;
            p_a.y = p_a.y + 1;
        } else {
            p_a.x = p_a.x - 1;
            p_a.y += slope_abs;
        }
    } else if (quadrant == 4) {
        if (run_over_rise) {
            p_a.x = p_a.x + slope_abs;
            p_a.y = p_a.y + 1;
        } else {
            p_a.x = p_a.x + 1;
            p_a.y += slope_abs;
        }
    }
}

// Assumes access on 3D vector of ColoredVertex is matrix[z][y][x]
ColoredVertex2DArray MeshBuilder::getMatrixSlice(ColoredVertexMatrix& matrix, int index, int count, int& d)
{
    if (index <= 1) {
        d = 0;
    } else if (index >= count) {
        d = matrix.getDepth() - 1;
    } else {
        double a = matrix.getDepth() - 2;
        double b = count - 1;
        int increment = floor(a / b);

        d = 1 + ((index-1) * increment);
    }

    return matrix.getVertices()[d];
}


void MeshBuilder::radialAngles(int count, double* array)
{
    double angle_rad_incr = 2.0*M_PI/(double)count;

    for (int i=0; i<count; i++)
        array[i] = i * angle_rad_incr;

}

double MeshBuilder::lineAngle(Point p1, Point p2)
{
    if (p2.x == p1.x) {
        if (p2.y > p1.y) {
            return (3.0*M_PI)/2.0;
        } else {
            return M_PI/2.0;
        }
    } else {

        double slope = (p2.y-p1.y)/(p2.x-p1.x);
        double angle = atan(slope);

        // Range of atan limited to (-M_PI/2, M_PI/2). Adjust to [0, 2*M_PI)
        if (p2.x < p1.x) {
            if (p2.y > p1.y) {
                angle = M_PI - angle;
            } else {
                angle = M_PI + angle;
            }
        } else {
            if (p2.y > p1.y) {
                angle = (2.0*M_PI) + angle;
            }
        }

        return angle;
    }

}

Point MeshBuilder::lineCenter(Point p1, Point p2)
{
    Point p3;

    p3.x = p1.x + ((p2.x - p1.x) / 2);
    p3.y = p1.x + ((p2.x - p1.x) / 2);

    return p3;
}

// |x| < (width/2), |y| < (height/2)
Point MeshBuilder::cartesianToArray(int width, int height, Point p)
{
    Point p_a;

    p_a.x =  p.x + (width / 2);
    p_a.y = -p.y + (height / 2);

    return p_a;
}

Point MeshBuilder::arrayToCartesian(int width, int height, Point p_a)
{
    Point p;

    p.x = p_a.x - (width / 2);
    p.y = (height / 2) -  p_a.y;

    return p;
}

double MeshBuilder::distance(Point p1, Point p2)
{
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}
