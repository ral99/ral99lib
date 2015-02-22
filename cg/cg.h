#ifndef __CG__
#define __CG__

#include <math.h>
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

typedef struct _CGCircle *CGCircle;
struct _CGCircle {
    CGPoint center;
    double radius;
};

typedef struct _CGTriangle *CGTriangle;
struct _CGTriangle {
    CGPoint a, b, c;
};

typedef struct _CGPolygon *CGPolygon;
struct _CGPolygon {
    ADTList points;
};

typedef struct _CGShapeProjectionOnAxis *CGShapeProjectionOnAxis;
struct _CGShapeProjectionOnAxis {
    double min, max;
};

/* Return a new angle defined in radians. */
CGAngle angle_in_radians_new(double rad);

/* Return a new angle defined in degrees. */
CGAngle angle_in_degrees_new(double deg);

/* Free the memory used by angle. */
void angle_release(CGAngle angle);

/* Return 1 if the angles are equal. 0, otherwise. */
int angle_equals(CGAngle angle1, CGAngle angle2);

/* Return the duplicated angle. */
CGAngle angle_dup(CGAngle angle);

/* Return the string representation of the angle with the specified number of decimal
 * positions. */
char *angle_to_str(CGAngle angle, int decimal_positions);

/* Return angle from its string representation. */
CGAngle angle_from_str(char *str);

/* Sum angle2 to angle1. */
void angle_sum(CGAngle angle1, CGAngle angle2);

/* Subtract angle2 from angle1. */
void angle_subtract(CGAngle angle1, CGAngle angle2);

/* Return angle in radians. */
double angle_in_radians(CGAngle angle);

/* Return angle in degrees. */
double angle_in_degrees(CGAngle angle);

/* Converts an angle specified in radias to degrees. */
double rad_to_deg(double rad);

/* Converts an angle specified in degrees to radians. */
double deg_to_rad(double deg);

/* Return a new vector. */
CGVector vector_new(double x, double y);

/* Return a new vector from point a to point b. */
CGVector vector_from_point_to_point(CGPoint a, CGPoint b);

/* Free the memory used by vector. */
void vector_release(CGVector vector);

/* Return 1 if the vectors are equal. 0, otherwise. */
int vector_equals(CGVector vector1, CGVector vector2);

/* Return the duplicated vector. */
CGVector vector_dup(CGVector vector);

/* Return the string representation of the vector with the specified number of decimal
 * positions. */
char *vector_to_str(CGVector vector, int decimal_positions);

/* Return vector from its string representation. */
CGVector vector_from_str(char *str);

/* Return vector x component. */
double vector_x(CGVector vector);

/* Return vector y component. */
double vector_y(CGVector vector);

/* Return perpendicular vector using right hand rule. */
CGVector vector_right_perpendicular(CGVector vector);

/* Return perpendicular vector using left hand rule. */
CGVector vector_left_perpendicular(CGVector vector);

/* Normalize vector. */
void vector_normalize(CGVector vector);

/* Reverse vector. */
void vector_reverse(CGVector vector);

/* Sum vector 2 to vector 1. */
void vector_sum(CGVector vector1, CGVector vector2);

/* Subtract vector 2 from vector 1. */
void vector_subtract(CGVector vector1, CGVector vector2);

/* Multiply vector by a scalar factor. */
void vector_multiply(CGVector vector, double k);

/* Return vector magnitude. */
double vector_magnitude(CGVector vector);

/* Return the dot product between two vectors. */
double vector_dot(CGVector vector1, CGVector vector2);

/* Return the angle in radians between two vectors in range [0, PI]. */
double angle_between_vectors(CGVector vector1, CGVector vector2);

/* Return the angle in radians from vector1 to vector2 in counter-clockwise orientation in
 * range [0, 2* PI[. */
double angle_from_vector_to_vector(CGVector vector1, CGVector vector2);

/* Rotate the vector by the specified degrees in counter-clockwise orientation. */
void vector_rotate(CGVector vector, double deg);

/* Return a new point. */
CGPoint point_new(double x, double y);

/* Free the memory used by point. */
void point_release(CGPoint point);

/* Return 1 if the points are equal. 0, otherwise. */
int point_equals(CGPoint point1, CGPoint point2);

/* Return the duplicated point. */
CGPoint point_dup(CGPoint point);

/* Return the string representation of the point with the specified number of decimal
 * positions. */
char *point_to_str(CGPoint point, int decimal_positions);

/* Return point from its string representation. */
CGPoint point_from_str(char *str);

/* Return point x component. */
double point_x(CGPoint point);

/* Return point y component. */
double point_y(CGPoint point);

/* Return point vector from origin. */
CGVector point_vector_from_origin(CGPoint point);

/* Return point projection magnitude on axis. */
double point_projection_magnitude_on_axis(CGPoint point, CGVector axis);

/* Return point projection on axis. */
CGVector point_projection_on_axis(CGPoint point, CGVector axis);

/* Translate the point by the vector. */
void point_translate(CGPoint point, CGVector vector);

/* Rotate the point by the specified degrees in counter-clockwise orientation around a center
 * point. */
void point_rotate_around(CGPoint point, CGPoint center, double deg);

/* Return the midpoint between 2 points. */
CGPoint midpoint_between_points(CGPoint point1, CGPoint point2);

/* Normalize the point coordinates. */
void point_normalize(CGPoint point);

/* Return the distance between two points. */
double point_distance_to_point(CGPoint point1, CGPoint point2);

/* Return a new line defined by 2 points or NULL if points are equal. */
CGLine line_new(CGPoint a, CGPoint b);

/* Free the memory used by line. */
void line_release(CGLine line);

/* Return 1 if the lines are equal. 0, otherwise. */
int line_equals(CGLine line1, CGLine line2);

/* Return the duplicated line. */
CGLine line_dup(CGLine line);

/* Return the string representation of the line with the specified number of decimal
 * positions. */
char *line_to_str(CGLine line, int decimal_positions);

/* Return line from its string representation. */
CGLine line_from_str(char *str);

/* Return the perpendicular line which contains point. */
CGLine line_perpendicular(CGLine line, CGPoint point);

/* Return the point of intersection between 2 lines or NULL if they're parallel. */
CGPoint lines_intersection(CGLine line1, CGLine line2);

/* Normalize the line coefficients. */
void line_normalize(CGLine line);

/* Return 1 if the point is in line. 0, otherwise. */
int point_is_in_line(CGPoint point, CGLine line);

/* Return the distance from the point to the line. */
double point_distance_to_line(CGPoint point, CGLine line);

/* Return the angle in radians between two lines in range [0, PI / 2]. */
double angle_between_lines(CGLine line1, CGLine line2);

/* Return a segment defined by two points or NULL if points are equal. */
CGSegment segment_new(CGPoint a, CGPoint b);

/* Free the memory used by segment. */
void segment_release(CGSegment segment);

/* Return 1 if the segments are equal. 0, otherwise. */
int segment_equals(CGSegment segment1, CGSegment segment2);

/* Return the duplicated segment. */
CGSegment segment_dup(CGSegment segment);

/* Return the string representation of the segment with the specified number of decimal
 * positions. */
char *segment_to_str(CGSegment segment, int decimal_positions);

/* Return segment from its string representation. */
CGSegment segment_from_str(char *str);

/* Return a list of two points that defines the segment. */
ADTList segment_points(CGSegment segment);

/* Return the vector from segment point a to b. */
CGVector segment_vector(CGSegment segment);

/* Return the segment line. */
CGLine segment_line(CGSegment segment);

/* Return the segment length. */
double segment_length(CGSegment segment);

/* Translate the segment by the vector. */
void segment_translate(CGSegment segment, CGVector vector);

/* Rotate the segment by the specified degrees in counter-clockwise orientation around a
 * center point. */
void segment_rotate_around(CGSegment segment, CGPoint center, double deg);

/* Return segment projection on axis. */
CGShapeProjectionOnAxis segment_projection_on_axis(CGSegment segment, CGVector axis);

/* Return a list of segment collision detection axes. */
ADTList segment_collision_axes(CGSegment segment);

/* Return the point of intersection between 2 segments or NULL. */
CGPoint segments_intersection(CGSegment segment1, CGSegment segment2);

/* Return 1 if the point is in the segment. 0, otherwise. */
int point_is_in_segment(CGPoint point, CGSegment segment);

/* Return a new circle defined by its center point and radius or NULL if radius is less than
 * or equal to 0. */
CGCircle circle_new(CGPoint center, double radius);

/* Free the memory used by circle. */
void circle_release(CGCircle circle);

/* Return 1 if the circles are equal. 0, otherwise. */
int circle_equals(CGCircle circle1, CGCircle circle2);

/* Return the duplicated circle. */
CGCircle circle_dup(CGCircle circle);

/* Return the string representation of the circle with the specified number of decimal
 * positions. */
char *circle_to_str(CGCircle circle, int decimal_positions);

/* Return circle from its string representation. */
CGCircle circle_from_str(char *str);

/* Return circle center point. */
CGPoint circle_center(CGCircle circle);

/* Return circle center point x component. */
double circle_center_x(CGCircle circle);

/* Return circle center point y component. */
double circle_center_y(CGCircle circle);

/* Return circle radius. */
double circle_radius(CGCircle circle);

/* Return circle area. */
double circle_area(CGCircle circle);

/* Return a list of circle points with the specified size. */
ADTList circle_points(CGCircle circle, int n_points);

/* Translate the point by the vector. */
void circle_translate(CGCircle circle, CGVector vector);

/* Return circle projection on axis. */
CGShapeProjectionOnAxis circle_projection_on_axis(CGCircle circle, CGVector axis);

/* Return a list of circle collision detection axes. */
ADTList circle_collision_axes(CGCircle circle, ADTList points);

/* Return 1 if the point is inside the circle. 0, otherwise. */
int point_is_in_circle(CGPoint point, CGCircle circle);

/* Return a new triangle defined by 3 points that can be collinear. */
CGTriangle triangle_new(CGPoint a, CGPoint b, CGPoint c);

/* Free the memory used by triangle. */
void triangle_release(CGTriangle triangle);

/* Return 1 if the triangles are equal. 0, otherwise. */
int triangle_equals(CGTriangle triangle1, CGTriangle triangle2);

/* Return the duplicated triangle. */
CGTriangle triangle_dup(CGTriangle triangle);

/* Return the string representation of the triangle with the specified number of decimal
 * positions. */
char *triangle_to_str(CGTriangle triangle, int decimal_positions);

/* Return triangle from its string representation. */
CGTriangle triangle_from_str(char *str);

/* Return a list of triangle points. */
ADTList triangle_points(CGTriangle triangle);

/* Translate the triangle by the vector. */
void triangle_translate(CGTriangle triangle, CGVector vector);

/* Rotate the triangle by the specified degrees in counter-clockwise orientation around a
 * center point. */
void triangle_rotate_around(CGTriangle triangle, CGPoint center, double deg);

/* Return -1 if clockwise; 1 if counter-clockwise; 0 if the points are collinear. */
int triangle_orientation(CGTriangle triangle);

/* Return the area of triangle. */
double triangle_area(CGTriangle triangle);

/* Return triangle projection on axis. */
CGShapeProjectionOnAxis triangle_projection_on_axis(CGTriangle triangle, CGVector axis);

/* Return a list of triangle collision detection axes. */
ADTList triangle_collision_axes(CGTriangle triangle);

/* Return 1 if the point is inside the triangle. 0, otherwise. */
int point_is_in_triangle(CGPoint point, CGTriangle triangle);

/* Return a new polygon defined by a list of points or NULL if points are collinear. */
CGPolygon polygon_new(ADTList points);

/* Return a new polygon defined by a triangle specification. */
CGPolygon polygon_new_triangle(CGPoint a, CGPoint b, CGPoint c);

/* Return a new polygon defined by a rectangle specification. */
CGPolygon polygon_new_rectangle(CGPoint lower_left, double width, double height);

/* Return a new polygon defined by a square specification. */
CGPolygon polygon_new_square(CGPoint lower_left, double side);

/* Free the memory used by polygon. */
void polygon_release(CGPolygon polygon);

/* Return 1 if the polygons are equal. 0, otherwise. */
int polygon_equals(CGPolygon polygon1, CGPolygon polygon2);

/* Return the duplicated polygon. */
CGPolygon polygon_dup(CGPolygon polygon);

/* Return the string representation of the polygon with the specified number of decimal
 * positions. */
char *polygon_to_str(CGPolygon polygon, int decimal_positions);

/* Return polygon from its string representation. */
CGPolygon polygon_from_str(char *str);

/* Return a list of polygon points. */
ADTList polygon_points(CGPolygon polygon);

/* Translate the polygon by the vector. */
void polygon_translate(CGPolygon polygon, CGVector vector);

/* Rotate the polygon by the specified degrees in counter-clockwise orientation around a
 * center point. */
void polygon_rotate_around(CGPolygon polygon, CGPoint center, double deg);

/* Return the area of polygon. */
double polygon_area(CGPolygon polygon);

/* Return polygon projection on axis. */
CGShapeProjectionOnAxis polygon_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return a list of polygon collision detection axes. */
ADTList polygon_collision_axes(CGPolygon polygon);

/* Return 1 if the point is inside the polygon. 0, otherwise. */
int point_is_in_polygon(CGPoint point, CGPolygon polygon);

/* Return a new SPOA defined by a range. */
CGShapeProjectionOnAxis shape_projection_on_axis_new(double min, double max);

/* Free the memory used by SPOA. */
void shape_projection_on_axis_release(CGShapeProjectionOnAxis spoa);

/* Return 1 if the SPOAs are equal. 0, otherwise. */
int shape_projection_on_axis_equals(CGShapeProjectionOnAxis spoa1,
                                    CGShapeProjectionOnAxis spoa2);

/* Return the duplicated SPOA. */
CGShapeProjectionOnAxis shape_projection_on_axis_dup(CGShapeProjectionOnAxis spoa);

/* Return SPOA minimum value. */
double shape_projection_on_axis_min(CGShapeProjectionOnAxis spoa);

/* Return SPOA maximum value. */
double shape_projection_on_axis_max(CGShapeProjectionOnAxis spoa);

/* Return the minimum magnitude translation vector that applied to spoa2 separates it from
 * spoa1. */
double shape_projection_on_axis_tv(CGShapeProjectionOnAxis spoa1,
                                   CGShapeProjectionOnAxis spoa2);

/* Return a minimum translation vector to be applied on the second parameter to separate the
 * geometric shapes. */
CGVector segment_segment_collision_mtv(CGSegment segment1, CGSegment segment2);
CGVector segment_triangle_collision_mtv(CGSegment segment, CGTriangle triangle);
CGVector segment_polygon_collision_mtv(CGSegment segment, CGPolygon polygon);
CGVector segment_circle_collision_mtv(CGSegment segment, CGCircle circle);
CGVector triangle_segment_collision_mtv(CGTriangle triangle, CGSegment segment);
CGVector triangle_triangle_collision_mtv(CGTriangle triangle1, CGTriangle triangle2);
CGVector triangle_polygon_collision_mtv(CGTriangle triangle, CGPolygon polygon);
CGVector triangle_circle_collision_mtv(CGTriangle triangle, CGCircle circle);
CGVector polygon_segment_collision_mtv(CGPolygon polygon, CGSegment segment);
CGVector polygon_triangle_collision_mtv(CGPolygon polygon, CGTriangle triangle);
CGVector polygon_polygon_collision_mtv(CGPolygon polygon1, CGPolygon polygon2);
CGVector polygon_circle_collision_mtv(CGPolygon polygon, CGCircle circle);
CGVector circle_segment_collision_mtv(CGCircle circle, CGSegment segment);
CGVector circle_triangle_collision_mtv(CGCircle circle, CGTriangle triangle);
CGVector circle_polygon_collision_mtv(CGCircle circle, CGPolygon polygon);
CGVector circle_circle_collision_mtv(CGCircle circle1, CGCircle circle2);

#endif

