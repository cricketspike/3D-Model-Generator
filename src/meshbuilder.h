#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#define MESHBUILDER_COORDINATE_NOTFOUND    -1
#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>

#include "ColoredVertexMatrix.h"
#include "ColoredVertex.h"

/* This class generates a subset of ColoredVertex objects from a ColoredVertexMatrix
 *  which correspond to mesh vertices of the model being generated.
 */

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  std::vector<Point> points;
  int d;
} PointsPlane;

typedef std::vector<std::vector<ColoredVertex>> ColoredVertex2DArray;

class MeshBuilder
{
public:

    /*******************/
    /* Primary methods */
    /*******************/


    // Returns planes of fixed depth value (depth within matrix) with mesh vertices
    static void getMeshVertices(ColoredVertexMatrix& matrix, int slices, int rays, int refinement, std::vector<PointsPlane>& pointsPlanes);

    // Probe for alpha transitions outward from the center, add vertices there
    static void getMeshVertices_base(ColoredVertex2DArray& image, int rays, std::vector<Point>& points);

    // Find alpha transitions in between those found in the base step, add vertices there
    static void getMeshVertices_refine(ColoredVertex2DArray& image, std::vector<Point>& points);


    /************************/
    /* Line-tracing methods */
    /************************/


    static void trace(ColoredVertex2DArray& image,           // Trace along a line of vertices
                      Point p_c, const double& angle, Point& p_t);              //  anchored at point 'p_c' toward angle 'angle'
                                                                                //  until reaching an alpha transition 'p_t'

    static bool trace_boundsCheck(int width,    int height,                     // Check if p_a.x and p_a.y have gone past
                                  int quadrant, Point p_a);                     //  the edges associated with 'quadrant'

    static void trace_increment(int quadrant,   bool run_over_rise,             // Increment p_a.x, p_a.y toward 'quadrant',
                                int slope_abs,  Point& p_a);                    //  using slope format, slope abs. value


    /*******************/
    /* Utility methods */
    /*******************/


    static ColoredVertex2DArray getMatrixSlice(ColoredVertexMatrix& matrix, int index, int count, int& d);
                                                                                // Return 'matrix' slice 'index' of 'count' (e.g. 1 of 8), store its
                                                                                //  calculated depth in 'd'. Note: 1-based index


    static void radialAngles(int count, double* array);                         // Returns in 'array' the angles of 'count' evenly-dist'd radial lines
    static double lineAngle(Point p1, Point p2);                                // Returns the angle of the line from p1 to p2
    static Point lineCenter(Point p1, Point p2);                                // Returns the center p3 of the line from p1 to p2

    static Point cartesianToArray(int width, int height,                        // Translate center-origin 2D coordinates to array coordinates
                                  Point p);
    static Point arrayToCartesian(int width, int height,                        // Translate array coordinates to center-origin 2D coordinates
                                  Point p_a);
    static double distance(Point p1, Point p2);                                 // Returns the distance between two points
};

#endif // MESHBUILDER_H
