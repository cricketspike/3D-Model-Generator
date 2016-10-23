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

class MeshBuilder
{
public:

    /*******************/
    /* Primary methods */
    /*******************/


    // Returns planes of fixed depth value (depth within matrix) with mesh vertices
    static void getMeshVertices(ColoredVertexMatrix& matrix, const int& slices, const int& rays, const int& refinement, std::vector<PointsPlane>& pointsPlanes);

    // Probe for alpha transitions outward from the center, add vertices there
    static void getMeshVertices_base(std::vector<std::vector<ColoredVertex>>& image, const int& rays, std::vector<Point>& points);

    // Find alpha transitions in between those found in the base step, add vertices there
    static void getMeshVertices_refine(std::vector<std::vector<ColoredVertex>>& image, std::vector<Point>& points);


    /************************/
    /* Line-tracing methods */
    /************************/


    static void trace(std::vector<std::vector<ColoredVertex>>& image,      // Trace along a line of vertices
                      const Point& p_c, const double& angle, Point& p_t);  //  anchored at point 'p_c' toward angle 'angle'
                                                                           //  until reaching an alpha transition 'p_t'

    static bool trace_boundsCheck(const int& width,    const int& height,  // Check if p_a.x and p_a.y have gone past
                                  const int& quadrant, const Point& p_a);  //  the edges associated with 'quadrant'

    static void trace_increment(const int& quadrant, const bool& vertical, // Increment p_a.x, p_a.y toward quadrant 'quadrant',
                                const int& slope_abs,      Point& p_a);    //  using slope format, slope abs. value


    /*******************/
    /* Utility methods */
    /*******************/


    static std::vector<std::vector<ColoredVertex>> getMatrixSlice(const int& index, const int& count, int& d, ColoredVertexMatrix &matrix);
                                                                           // Return 'matrix' slice 'index' of 'count' (e.g. 1 of 8), store its
                                                                           //  calculated depth in 'd'
                                                                           //  Note: 1-based index


    static void radialAngles(const int& count, double* array);             // Returns in 'array' the angles of 'count' evenly-dist'd radial lines
    static double lineAngle(const Point& p1, const Point& p2);             // Returns the angle of the line from p1 to p2
    static Point lineCenter(const Point& p1, const Point& p2);             // Returns the center p3 of the line from p1 to p2

    static Point cartesian2array(const int& width, const int& height,      // Translate center-origin 2D coordinates to array coordinates
                                const Point& p);
    static Point array2cartesian(const int& width, const int& height,      // Translate array coordinates to center-origin 2D coordinates
                                const Point& p_a);
};

#endif // MESHBUILDER_H
