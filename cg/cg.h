#ifndef __CG__
#define __CG__

#include <math.h>
#include "adt/adt.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

typedef struct Vector *Vector;
struct Vector {
    double x, y;
};

typedef struct Point *Point;
struct Point {
    double w, x, y;
};

typedef struct Line *Line;
struct Line {
    double w, x, y;
};

typedef struct Segment *Segment;
struct Segment {
    Point a, b;
};

typedef struct Circle *Circle;
struct Circle {
    Point center;
    double radius;
};

typedef struct Triangle *Triangle;
struct Triangle {
    Point a, b, c;
};

typedef struct Polygon *Polygon;
struct Polygon {
    List points;
};

typedef struct ShapeProjectionOnAxis *ShapeProjectionOnAxis;
struct ShapeProjectionOnAxis {
    double min, max;
};

/* Converts an angle specified in degrees to radians. */
double deg_to_rad(double deg);

/* Return a new vector. */
Vector vector_new(double x, double y);

/* Return a new vector from point a to point b. */
Vector vector_from_point_to_point(Point a, Point b);

/* Free the memory used by vector. */
void vector_release(Vector vector);

/* Return 1 if the vectors are equal. 0, otherwise. */
int vector_equals(Vector vector1, Vector vector2);

/* Return the duplicated vector. */
Vector vector_dup(Vector vector);

/* Return the string representation of the vector with the specified number of
 * decimal positions. */
char *vector_to_str(Vector vector, int decimal_positions);

/* Return vector from its string representation. */
Vector vector_from_str(char *string);

/* Return vector x component. */
double vector_x(Vector vector);

/* Return vector y component. */
double vector_y(Vector vector);

/* Return perpendicular vector using right hand rule. */
Vector vector_right_perpendicular(Vector vector);

/* Return perpendicular vector using left hand rule. */
Vector vector_left_perpendicular(Vector vector);

/* Normalize vector. */
void vector_normalize(Vector vector);

/* Reverse vector. */
void vector_reverse(Vector vector);

/* Sum vector b to vector a. */
void vector_sum(Vector a, Vector b);

/* Subtract vector b from vector a. */
void vector_subtract(Vector a, Vector b);

/* Multiply vector by a scalar factor. */
void vector_multiply(Vector vector, double k);

/* Return vector magnitude. */
double vector_magnitude(Vector vector);

/* Return the dot product between two vectors. */
double vector_dot(Vector vector1, Vector vector2);

/* Return the angle in radians between two vectors in range [0, PI]. */
double angle_between_vectors(Vector vector1, Vector vector2);

/* Rotate the vector by the specified degrees in counter-clockwise orientation. */
void vector_rotate(Vector vector, double deg);

/* Return a new point. */
Point point_new(double x, double y);

/* Free the memory used by point. */
void point_release(Point point);

/* Return 1 if the points are equal. 0, otherwise. */
int point_equals(Point point1, Point point2);

/* Return the duplicated point. */
Point point_dup(Point point);

/* Return the string representation of the point with the specified number of
 * decimal positions. */
char *point_to_str(Point point, int decimal_positions);

/* Return point from its string representation. */
Point point_from_str(char *string);

/* Return point x component. */
double point_x(Point point);

/* Return point y component. */
double point_y(Point point);

/* Return point vector from origin. */
Vector point_vector_from_origin(Point point);

/* Return point projection magnitude on axis defined by direction. */
double point_projection_magnitude_on_axis(Point point, Vector direction);

/* Return point projection on axis defined by direction. */
Vector point_projection_on_axis(Point point, Vector direction);

/* Translate the point by the vector. */
void point_translate(Point point, Vector vector);

/* Rotate the point by the specified degrees in counter-clockwise orientation
 * around a center point. */
void point_rotate_around(Point point, Point center, double deg);

/* Return the midpoint between 2 points. */
Point midpoint_between_points(Point point1, Point point2);

/* Return 1 if the point is in infinite. 0, otherwise. */
int point_is_infinite(Point point);

/* Normalize the point coordinates. */
void point_normalize(Point point);

/* Return a new line defined by 2 points. */
Line line_new(Point point1, Point point2);

/* Free the memory used by line. */
void line_release(Line line);

/* Return 1 if the lines are equal. 0, otherwise. */
int line_equals(Line line1, Line line2);

/* Return the duplicated line. */
Line line_dup(Line line);

/* Return the string representation of the line with the specified number of
 * decimal positions. */
char *line_to_str(Line line, int decimal_positions);

/* Return line from its string representation. */
Line line_from_str(char *string);

/* Return the perpendicular line which contains point. */
Line line_perpendicular(Line line, Point point);

/* Return the point of intersection between 2 lines. */
Point line_intersection(Line line1, Line line2);

/* Normalize the line coefficients. */
void line_normalize(Line line);

/* Return 1 if the point is in line. 0, otherwise. */
int point_is_in_line(Point point, Line line);

/* Return the distance between two points. */
double point_distance_to_point(Point point1, Point point2);

/* Return the distance from the point to the line. */
double point_distance_to_line(Point point, Line line);

/* Return the angle in radians between two lines in range [0, PI / 2]. */
double angle_between_lines(Line line1, Line line2);

/* Return a segment defined by two points. */
Segment segment_new(Point a, Point b);

/* Free the memory used by segment. */
void segment_release(Segment segment);

/* Return 1 if the segments are equal. 0, otherwise. */
int segment_equals(Segment segment1, Segment segment2);

/* Return the duplicated segment. */
Segment segment_dup(Segment segment);

/* Return the string representation of the segment with the specified number of
 * decimal positions. */
char *segment_to_str(Segment segment, int decimal_positions);

/* Return segment from its string representation. */
Segment segment_from_str(char *string);

/* Return a list of two points that defines the segment. */
List segment_points(Segment segment);

/* Return the vector from segment point a to b. */
Vector segment_vector(Segment segment);

/* Return the segment line. */
Line segment_line(Segment segment);

/* Return the segment length. */
double segment_length(Segment segment);

/* Translate the segment by the vector. */
void segment_translate(Segment segment, Vector vector);

/* Rotate the segment by the specified degrees in counter-clockwise
 * orientation around a center point. */
void segment_rotate_around(Segment segment, Point center, double deg);

/* Return 1 if the point is in the segment. 0, otherwise. */
int point_is_in_segment(Point point, Segment segment);

/* Return a new circle defined by its center point and radius. */
Circle circle_new(Point center, double radius);

/* Free the memory used by circle. */
void circle_release(Circle circle);

/* Return 1 if the circles are equal. 0, otherwise. */
int circle_equals(Circle circle1, Circle circle2);

/* Return the duplicated circle. */
Circle circle_dup(Circle circle);

/* Return the string representation of the circle with the specified number of
 * decimal positions. */
char *circle_to_str(Circle circle, int decimal_positions);

/* Return circle from its string representation. */
Circle circle_from_str(char *string);

/* Return circle center point. */
Point circle_center(Circle circle);

/* Return circle center point x component. */
double circle_center_x(Circle circle);

/* Return circle center point y component. */
double circle_center_y(Circle circle);

/* Return circle radius. */
double circle_radius(Circle circle);

/* Translate the point by the vector. */
void circle_translate(Circle circle, Vector vector);

/* Return 1 if the point is inside the circle. 0, otherwise. */
int point_is_in_circle(Point point, Circle circle);

/* Return a new triangle defined by 3 points. */
Triangle triangle_new(Point a, Point b, Point c);

/* Free the memory used by triangle. */
void triangle_release(Triangle triangle);

/* Return the duplicated triangle. */
Triangle triangle_dup(Triangle triangle);

/* Return a list of triangle points. */
List triangle_points(Triangle triangle);

/* Translate the triangle by the vector. */
void triangle_translate(Triangle triangle, Vector vector);

/* Rotate the triangle by the specified degrees in counter-clockwise
 * orientation around a center point. */
void triangle_rotate_around(Triangle triangle, Point center, double deg);

/* Return -1 if clockwise; 1 if counter-clockwise; 0 if the points are
 * collinear. */
int triangle_orientation(Triangle triangle);

/* Return the area of triangle. */
double triangle_area(Triangle triangle);

/* Return 1 if the point is inside the triangle. 0, otherwise. */
int point_is_in_triangle(Point point, Triangle triangle);

/* Return a new polygon defined by a list of points. */
Polygon polygon_new(List points);

/* Return a new polygon defined by a triangle specification. */
Polygon polygon_new_triangle(Point a, Point b, Point c);

/* Return a new polygon defined by a rectangle specification. */
Polygon polygon_new_rectangle(Point lower_left, double width, double height);

/* Return a new polygon defined by a square specification. */
Polygon polygon_new_square(Point lower_left, double side);

/* Free the memory used by polygon. */
void polygon_release(Polygon polygon);

/* Return 1 if the polygons are equal. 0, otherwise. */
int polygon_equals(Polygon polygon1, Polygon polygon2);

/* Return the duplicated polygon. */
Polygon polygon_dup(Polygon polygon);

/* Return a list of polygon points. */
List polygon_points(Polygon polygon);

/* Translate the polygon by the vector. */
void polygon_translate(Polygon polygon, Vector vector);

/* Rotate the polygon by the specified degrees in counter-clockwise
 * orientation around a center point. */
void polygon_rotate_around(Polygon polygon, Point center, double deg);

/* Return the area of polygon. */
double polygon_area(Polygon polygon);

/* Return 1 if the point is inside the polygon. 0, otherwise. */
int point_is_in_polygon(Polygon polygon, Point point);

/* Return a new SPOA defined by a range. */
ShapeProjectionOnAxis shape_projection_on_axis_new(double min, double max);

/* Free the memory used by SPOA. */
void shape_projection_on_axis_release(ShapeProjectionOnAxis spoa);

/* Return 1 if the SPOAs are equal. 0, otherwise. */
int shape_projection_on_axis_equals(ShapeProjectionOnAxis spoa1,
                                    ShapeProjectionOnAxis spoa2);

/* Return the duplicated SPOA. */
ShapeProjectionOnAxis shape_projection_on_axis_dup(ShapeProjectionOnAxis spoa);

/* Return SPOA minimum value. */
double shape_projection_on_axis_min(ShapeProjectionOnAxis spoa);

/* Return SPOA maximum value. */
double shape_projection_on_axis_max(ShapeProjectionOnAxis spoa);

/* Return the minimum magnitude translation vector that applied to spoa2
 * separates it from spoa1. */
double shape_projection_on_axis_tv(ShapeProjectionOnAxis spoa1,
                                   ShapeProjectionOnAxis spoa2);

/* Return a minimum translation vector. */
/*
Vector segment_triangle_intersection();
Vector segment_polygon_intersection();
Vector segment_circle_intersection();
Vector triangle_triangle_intersection();
Vector triangle_polygon_intersection();
Vector triangle_circle_intersection();
Vector polygon_polygon_intersection();
Vector polygon_circle_intersection();
*/
Vector segment_segment_intersection(Segment segment1, Segment segment2);
Vector circle_circle_intersection(Circle circle1, Circle circle2);

#endif

