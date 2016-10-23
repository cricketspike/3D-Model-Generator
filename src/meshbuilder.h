#ifndef MESHBUILDER_H
#define MESHBUILDER_H

#define MESHBUILDER_COORDINATE_NOTFOUND    -1
#define _USE_MATH_DEFINES

#include <vector>
#include <math.h>

#include "ColoredVertexMatrix.h"
#include "ColoredVertex.h"

/* This class alters ColoredVertex objects on the very outside
 * of the item rendered in the ColoredVertexMatrix, so that the
 * inMesh property of these ColoredVertex objects is 'true'.
 *
 */

typedef struct {
  int x;
  int y;
} Point;

class MeshBuilder
{
public:

    /*******************/
    /* Primary methods */
    /*******************/


    // Sets inMesh=true on appropriate ColoredVertex objects in 'matrix'
    static void assignVerticesToMesh(ColoredVertexMatrix& matrix);

    // Probe for alpha transitions outward from the center
    static void assignVerticesToMesh_base(std::vector<std::vector<ColoredVertex>>& image, const int& rays, std::vector<Point>& points);

    // Find alpha transitions in between those found in the base step
    static void assignVerticesToMesh_refine(std::vector<std::vector<ColoredVertex>>& image, std::vector<Point>& points);


    /************************/
    /* Line-tracing methods */
    /************************/


    static void trace(std::vector<std::vector<ColoredVertex>>& image,      // Trace along a line of vertices
                      const Point& p_c, const double& slope, Point& p_t);  //  anchored at point 'p_c' and with slope 'slope'
                                                                           //  for an alpha transition 'p_t'

    static bool trace_boundsCheck(const int& width, const int& height,     // Check if p_a.x and p_a.y have gone past
                                  const int& quadrant, const Point& p_a);  //  the corner determined from 'quadrant'

    static void trace_increment(const int& quadrant,const bool& vertical,  // Increment p_a.x, p_a.y based on quadrant, traversal direction, slope
                                const int& slope_abs,     Point& p_a);


    /*******************/
    /* Utility methods */
    /*******************/


    static std::vector<std::vector<ColoredVertex>> getMatrixSlice(const int& index, const int& count, int& d, ColoredVertexMatrix &matrix);
                                                                           // Return 'matrix' slice 'index' of 'count' (e.g. 1 of 8), store its calculated depth in 'd'
                                                                           // Note: 1-based index


    static void slopes(const int& count, double* array);                   // Returns in 'array' the slopes of 'count' radial lines
    static double lineSlope(const Point& p1, const Point& p2);             // Returns the slope of the line from p1 to p2
    static double perpendicular(const double& slope);                      // Returns the slope of the line perpendicular to a line with slope 'slope'
    static void lineCenter(const Point& p1, const Point& p2, Point& p3);   // Returns the center 'p3' of the line from p1 to p2

    static void cartesian2array(const int& width, const int& height,       // Translate center-origin 2D coordinates to array coordinates
                                const Point& p,
                                      Point& p_a);
    static void array2cartesian(const int& width, const int& height,       // Translate array coordinates to center-origin 2D coordinates
                                const Point& p_a,
                                      Point& p);
};

#endif // MESHBUILDER_H
