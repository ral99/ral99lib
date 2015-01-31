#ifndef __CG__
#define __CG__

#include <math.h>

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

typedef struct Circle *Circle;
struct Circle {
    Point center;
    double radius;
};

typedef struct Triangle *Triangle;
struct Triangle {
    Point a, b, c;
};

/* Converts an angle specified in degrees to radians. */
double deg_to_rad(double deg);

/* Return a new vector. */
Vector vector_new(double x, double y);

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

/* Translate the point by the vector specified by x and y. */
void point_translate(Point point, double x, double y);

/* Rotate the point by the specified degrees in counter-clockwise orientation. */
void point_rotate(Point point, double deg);

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

/* Return the distance from the point to the line. */
double point_distance_to_line(Point point, Line line);

/* Return the angle in radians between two lines. */
double angle_between_lines(Line line1, Line line2);

/* Return a new circle defined by its center point and radius. */
Circle circle_new(double x, double y, double radius);

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

/* Translate the point by the vector specified by x and y. */
void circle_translate(Circle circle, double x, double y);

/* Return 1 if the point is inside the circle. 2, if on its frontier.
 * 0, otherwise. */
int point_is_in_circle(Point point, Circle circle);

/* Return a new triangle defined by 3 points. */
Triangle triangle_new(Point a, Point b, Point c);

/* Free the memory used by triangle. */
void triangle_release(Triangle triangle);

/* Return the duplicated triangle. */
Triangle triangle_dup(Triangle triangle);

/* Return -1 if clockwise; 1 if counter-clockwise; 0 if the points are collinear. */
int triangle_orientation(Triangle triangle);

/* Return the area of triangle. */
double triangle_area(Triangle triangle);

/* Return 1 if the point is inside the triangle. 2, if on its frontier.
 * 0, otherwise. */
int point_is_in_triangle(Point point, Triangle triangle);

#endif

