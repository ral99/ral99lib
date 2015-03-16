#ifndef __CG__
#define __CG__

#include "adt/adt.h"

#ifndef M_PI
    #define M_PI 3.14159265358979323846
#endif

typedef struct _CGAngle *CGAngle;
struct _CGAngle {
    double rad;
};

typedef struct _CGVector *CGVector;
struct _CGVector {
    double x, y;
};

typedef struct _CGPoint *CGPoint;
struct _CGPoint {
    double w, x, y;
};

typedef struct _CGLine *CGLine;
struct _CGLine {
    double w, x, y;
};

typedef struct _CGSegment *CGSegment;
struct _CGSegment {
    CGPoint a, b;
};

typedef struct _CGTriangle *CGTriangle;
struct _CGTriangle {
    CGPoint a, b, c;
};

typedef struct _CGPolygon *CGPolygon;
struct _CGPolygon {
    ADTList vertices;
};

typedef struct _CGCircle *CGCircle;
struct _CGCircle {
    CGPoint center;
    double radius;
};

/**********************************************************************************************
 ******************************************* CGAngle ******************************************
 *********************************************************************************************/

/* Return a new angle specified in radians. */
CGAngle angle_in_radians_new(double rad);

/* Return a new angle specified in degrees. */
CGAngle angle_in_degrees_new(double deg);

/* Free the memory used by angle. */
void angle_release(CGAngle angle);

/* Return 1 if angle1 is equal to angle2. 0, otherwise. */
int angle_equals(CGAngle angle1, CGAngle angle2);

/* Return 1 if angle1 is lower than angle2. 0, otherwise. */
int angle_lt(CGAngle angle1, CGAngle angle2);

/* Return 1 if angle1 is lower than or equal to angle2. 0, otherwise. */
int angle_lte(CGAngle angle1, CGAngle angle2);

/* Return 1 if angle1 is greater than angle2. 0, otherwise. */
int angle_gt(CGAngle angle1, CGAngle angle2);

/* Return 1 if angle1 is greater than or equal to angle2. 0, otherwise. */
int angle_gte(CGAngle angle1, CGAngle angle2);

/* Return a copy of angle. */
CGAngle angle_dup(CGAngle angle);

/* Return the string representation of angle with the specified decimal positions. */
char *angle_to_str(CGAngle angle, int decimal_positions);

/* Return angle in radians. */
double angle_in_radians(CGAngle angle);

/* Return angle in degrees. */
double angle_in_degrees(CGAngle angle);

/* Sum angle2 to angle1. */
void angle_sum(CGAngle angle1, CGAngle angle2);

/* Subtract angle2 from angle1. */
void angle_subtract(CGAngle angle1, CGAngle angle2);

/**********************************************************************************************
 ****************************************** CGVector ******************************************
 *********************************************************************************************/

/* Return a new vector. */
CGVector vector_new(double x, double y);

/* Return a vector specified by two points. */
CGVector vector_from_point_to_point(CGPoint a, CGPoint b);

/* Return vector from origin to point. */
CGVector vector_from_origin_to_point(CGPoint point);

/* Free the memory used by vector. */
void vector_release(CGVector vector);

/* Return 1 if vector1 is equal to vector2. 0, otherwise. */
int vector_equals(CGVector vector1, CGVector vector2);

/* Return a copy of vector. */
CGVector vector_dup(CGVector vector);

/* Return the string representation of vector with the specified decimal positions. */
char *vector_to_str(CGVector vector, int decimal_positions);

/* Return vector x component. */
double vector_x(CGVector vector);

/* Return vector y component. */
double vector_y(CGVector vector);

/* Return a normalized perpendicular vector using the right hand rule, or NULL if vector has
 * magnitude 0. */
CGVector vector_right_perpendicular_axis(CGVector vector);

/* Return a normalized perpendicular vector using the left hand rule, or NULL if vector has
 * magnitude 0. */
CGVector vector_left_perpendicular_axis(CGVector vector);

/* Normalize vector. */
void vector_normalize(CGVector vector);

/* Reverse vector. */
void vector_reverse(CGVector vector);

/* Sum vector2 to vector1. */
void vector_sum(CGVector vector1, CGVector vector2);

/* Subtract vector2 from vector1. */
void vector_subtract(CGVector vector1, CGVector vector2);

/* Multiply vector by a factor. */
void vector_multiply(CGVector vector, double k);

/* Return vector magnitude. */
double vector_magnitude(CGVector vector);

/* Return the dot product between two vectors. */
double vector_dot(CGVector vector1, CGVector vector2);

/* Return the angle from vector1 to vector2 in counter-clockwise direction, or NULL if the
 * product of the magnitudes of the vectors is 0. */
CGAngle vector_angle_to(CGVector vector1, CGVector vector2);

/* Rotate vector in counter-clockwise direction. */
void vector_rotate(CGVector vector, CGAngle angle);

/**********************************************************************************************
 ******************************************* CGPoint ******************************************
 *********************************************************************************************/

/* Return a new point. */
CGPoint point_new(double x, double y);

/* Return the midpoint between two points. */
CGPoint midpoint_between(CGPoint point1, CGPoint point2);

/* Free the memory used by point. */
void point_release(CGPoint point);

/* Return 1 if point1 is equal to point2. 0, otherwise. */
int point_equals(CGPoint point1, CGPoint point2);

/* Return a copy of point. */
CGPoint point_dup(CGPoint point);

/* Return the string representation of point with the specified decimal positions. */
char *point_to_str(CGPoint point, int decimal_positions);

/* Return point x component. */
double point_x(CGPoint point);

/* Return point y component. */
double point_y(CGPoint point);

/* Return point projection vector on axis. */
CGVector point_projection_on_axis(CGPoint point, CGVector axis);

/* Translate point by vector. */
void point_translate(CGPoint point, CGVector vector);

/* Rotate point around a center point in counter-clockwise direction. */
void point_rotate_around(CGPoint point, CGPoint center, CGAngle angle);

/* Return distance between two points. */
double point_distance_to_point(CGPoint point1, CGPoint point2);

/* Return 1 if point is in line. 0, otherwise. */
int point_is_in_line(CGPoint point, CGLine line);

/* Return 1 if point is in segment. 0, otherwise. */
int point_is_in_segment(CGPoint point, CGSegment segment);

/* Return 1 if point is in triangle. 0, otherwise. */
int point_is_in_triangle(CGPoint point, CGTriangle triangle);

/* Return 1 if point is in polygon. 0, otherwise. */
int point_is_in_polygon(CGPoint point, CGPolygon polygon);

/* Return 1 if point is in circle. 0, otherwise. */
int point_is_in_circle(CGPoint point, CGCircle circle);

/* Return the point of intersection between two lines, or NULL if lines are parallel. */
CGPoint point_intersection_of_lines(CGLine line1, CGLine line2);

/**********************************************************************************************
 ******************************************* CGLine *******************************************
 *********************************************************************************************/

/* Return a new line, or NULL if points are equal. */
CGLine line_new(CGPoint a, CGPoint b);

/* Free the memory used by line. */
void line_release(CGLine line);

/* Return 1 if line1 is equal to line2. 0, otherwise. */
int line_equals(CGLine line1, CGLine line2);

/* Return a copy of line. */
CGLine line_dup(CGLine line);

/* Return the string representation of line with the specified decimal positions. */
char *line_to_str(CGLine line, int decimal_positions);

/* Return the perpendicular line which contains the specified point. */
CGLine line_perpendicular(CGLine line, CGPoint point);

/**********************************************************************************************
 ****************************************** CGSegment *****************************************
 *********************************************************************************************/

/* Return a new segment. */
CGSegment segment_new(CGPoint a, CGPoint b);

/* Free the memory used by segment. */
void segment_release(CGSegment segment);

/* Return 1 if segment1 is equal to segment2. 0, otherwise. */
int segment_equals(CGSegment segment1, CGSegment segment2);

/* Return a copy of segment. */
CGSegment segment_dup(CGSegment segment);

/* Return the string representation of segment with the specified decimal positions. */
char *segment_to_str(CGSegment segment, int decimal_positions);

/* Return segment a point. */
CGPoint segment_a(CGSegment segment);

/* Return segment b point. */
CGPoint segment_b(CGSegment segment);

/* Translate segment by a vector. */
void segment_translate(CGSegment segment, CGVector vector);

/* Rotate segment around a center point in counter-clockwise direction. */
void segment_rotate_around(CGSegment segment, CGPoint center, CGAngle angle);

/* Return segment length. */
double segment_length(CGSegment segment);

/**********************************************************************************************
 ***************************************** CGTriangle *****************************************
 *********************************************************************************************/

/* Return a new triangle. */
CGTriangle triangle_new(CGPoint a, CGPoint b, CGPoint c);

/* Free the memory used by triangle. */
void triangle_release(CGTriangle triangle);

/* Return 1 if triangle1 is equal to triangle2. 0, otherwise. */
int triangle_equals(CGTriangle triangle1, CGTriangle triangle2);

/* Return a copy of triangle. */
CGTriangle triangle_dup(CGTriangle triangle);

/* Return the triangle string representation with the specified decimal positions. */
char *triangle_to_str(CGTriangle triangle, int decimal_positions);

/* Return triangle a point. */
CGPoint triangle_a(CGTriangle triangle);

/* Return triangle b point. */
CGPoint triangle_b(CGTriangle triangle);

/* Return triangle c point. */
CGPoint triangle_c(CGTriangle triangle);

/* Translate triangle by a vector. */
void triangle_translate(CGTriangle triangle, CGVector vector);

/* Rotate triangle around a center in counter-clockwise direction. */
void triangle_rotate_around(CGTriangle triangle, CGPoint center, CGAngle angle);

/* Return 1 if triangle is in counter-clockwise orientation. -1, if in clockwise orientation.
 * 0, if vertices are collinear. */
int triangle_orientation(CGTriangle triangle);

/* Return triangle area. */
double triangle_area(CGTriangle triangle);

/**********************************************************************************************
 ****************************************** CGPolygon *****************************************
 *********************************************************************************************/

/* Return a new polygon, or NULL if there are less than three vertices, or if polygon is
 * not convex, or if there are coincident vertices, or if there are 3 collinear vertices. */
CGPolygon polygon_new(ADTList vertices);

/* Return a new triangle polygon, or NULL if two or more points are coincidents. */
CGPolygon polygon_new_triangle(CGPoint a, CGPoint b, CGPoint c);

/* Return a new rectangle polygon, or NULL if width or height is 0. */
CGPolygon polygon_new_rectangle(CGPoint lower_left, double width, double height);

/* Return a new square polygon, or NULL if side is 0. */
CGPolygon polygon_new_square(CGPoint lower_left, double side);

/* Free the memory used by polygon. */
void polygon_release(CGPolygon polygon);

/* Return 1 if polygon1 is equal to polygon2. 0, otherwise. */
int polygon_equals(CGPolygon polygon1, CGPolygon polygon2);

/* Return a copy of polygon. */
CGPolygon polygon_dup(CGPolygon polygon);

/* Return the string representation of polygon with the specified decimal positions. */
char *polygon_to_str(CGPolygon polygon, int decimal_positions);

/* Return a list of polygon vertices. */
ADTList polygon_vertices(CGPolygon polygon);

/* Return a list of polygon edges. */
ADTList polygon_edges(CGPolygon polygon);

/* Translate polygon by vector. */
void polygon_translate(CGPolygon polygon, CGVector vector);

/* Rotate polygon around a center point in counter-clockwise direction. */
void polygon_rotate_around(CGPolygon polygon, CGPoint center, CGAngle angle);

/* Return polygon area. */
double polygon_area(CGPolygon polygon);

/**********************************************************************************************
 ****************************************** CGCircle ******************************************
 *********************************************************************************************/

/* Return a new circle, or NULL if radius is lower than or equal to 0. */
CGCircle circle_new(CGPoint center, double radius);

/* Free the memory used by circle. */
void circle_release(CGCircle circle);

/* Return 1 if circle1 is equal to circle2. 0, otherwise. */
int circle_equals(CGCircle circle1, CGCircle circle2);

/* Return a copy of circle. */
CGCircle circle_dup(CGCircle circle);

/* Return the string representation of circle with the specified decimal positions. */
char *circle_to_str(CGCircle circle, int decimal_positions);

/* Return circle center. */
CGPoint circle_center(CGCircle circle);

/* Return x component of circle center. */
double circle_center_x(CGCircle circle);

/* Return y component of circle center. */
double circle_center_y(CGCircle circle);

/* Return circle radius. */
double circle_radius(CGCircle circle);

/* Translate circle by a vector. */
void circle_translate(CGCircle circle, CGVector vector);

/* Rotate circle around a center point in counter-clockwise direction. */
void circle_rotate_around(CGCircle circle, CGPoint center, CGAngle angle);

/* Return circle area. */
double circle_area(CGCircle circle);

#endif

