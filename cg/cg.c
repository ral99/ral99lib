#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cg/cg.h"
#include "adt/adt.h"
#include "num/num.h"
#include "mem/mem.h"
#include "str/str.h"

double deg_to_rad(double deg) {
    deg = deg - (((int) (deg) / 360) * 360);
    return (deg * M_PI) / 180;
}

Vector vector_new(double x, double y) {
    Vector vector = memalloc(sizeof(*vector));
    vector->x = x;
    vector->y = y;
    return vector;
}

Vector vector_from_point_to_point(Point a, Point b) {
    double x = point_x(b) - point_x(a);
    double y = point_y(b) - point_y(a);
    return vector_new(x, y);
}

void vector_release(Vector vector) {
    free(vector);
}

int vector_equals(Vector vector1, Vector vector2) {
    return (double_equals(vector1->x, vector2->x) && double_equals(vector1->y, vector2->y));
}

Vector vector_dup(Vector vector) {
    Vector dup = memalloc(sizeof(*dup));
    dup->x = vector->x;
    dup->y = vector->y;
    return dup;
}

char *vector_to_str(Vector vector, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Vector: ("));
    list_append(str_list, double_to_str(vector->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(vector->y, decimal_positions));
    list_append(str_list, str_dup(") >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Vector vector_from_str(char *str) {
    List str_list = str_split(str, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 12, strlen(list_at(str_list, 0)) - 12);
    char *str_y = str_substr(list_at(str_list, 1), 0, strlen(list_at(str_list, 1)) - 4);
    Vector vector = vector_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return vector;
}

double vector_x(Vector vector) {
    return vector->x;
}

double vector_y(Vector vector) {
    return vector->y;
}

Vector vector_right_perpendicular(Vector vector) {
    return vector_new(vector->y, -vector->x);
}

Vector vector_left_perpendicular(Vector vector) {
    return vector_new(-vector->y, vector->x);
}

void vector_normalize(Vector vector) {
    double magnitude = vector_magnitude(vector);
    vector->x /= magnitude;
    vector->y /= magnitude;
}

void vector_reverse(Vector vector) {
    vector->x = -vector->x;
    vector->y = -vector->y;
}

void vector_sum(Vector vector1, Vector vector2) {
    vector1->x += vector2->x;
    vector1->y += vector2->y;
}

void vector_subtract(Vector vector1, Vector vector2) {
    vector1->x -= vector2->x;
    vector1->y -= vector2->y;
}

void vector_multiply(Vector vector, double k) {
    vector->x *= k;
    vector->y *= k;
}

double vector_magnitude(Vector vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y);
}

double vector_dot(Vector vector1, Vector vector2) {
    return vector1->x * vector2->x + vector1->y * vector2->y;
}

double angle_between_vectors(Vector vector1, Vector vector2) {
    double dot = vector_dot(vector1, vector2);
    double magnitude1 = vector_magnitude(vector1);
    double magnitude2 = vector_magnitude(vector2);
    return acos(dot / (magnitude1 * magnitude2));
}

void vector_rotate(Vector vector, double deg) {
    double rad = deg_to_rad(deg);
    double vector_x = vector->x;
    double vector_y = vector->y;
    vector->x = vector_x * cos(rad) - vector_y * sin(rad);
    vector->y = vector_x * sin(rad) + vector_y * cos(rad);
}

Point point_new(double x, double y) {
    Point point = memalloc(sizeof(*point));
    point->w = 1;
    point->x = x;
    point->y = y;
    return point;
}

void point_release(Point point) {
    free(point);
}

int point_equals(Point point1, Point point2) {
    return (double_equals(point1->x * point2->w, point2->x * point1->w) &&
            double_equals(point1->y * point2->w, point2->y * point1->w));
}

Point point_dup(Point point) {
    Point dup = memalloc(sizeof(*dup));
    dup->w = point->w;
    dup->x = point->x;
    dup->y = point->y;
    return dup;
}

char *point_to_str(Point point, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Point: ("));
    list_append(str_list, double_to_str(point_x(point), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(point), decimal_positions));
    list_append(str_list, str_dup(") >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Point point_from_str(char *str) {
    List str_list = str_split(str, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 11, strlen(list_at(str_list, 0)) - 11);
    char *str_y = str_substr(list_at(str_list, 1), 0, strlen(list_at(str_list, 1)) - 4);
    Point point = point_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return point;
}

double point_x(Point point) {
    return point->x / point->w;
}

double point_y(Point point) {
    return point->y / point->w;
}

Vector point_vector_from_origin(Point point) {
    return vector_new(point_x(point), point_y(point));
}

double point_projection_magnitude_on_axis(Point point, Vector axis) {
    Vector projection = vector_dup(axis);
    Vector vector = point_vector_from_origin(point);
    double projection_magnitude = vector_dot(vector, projection);
    vector_release(vector);
    vector_release(projection);
    return projection_magnitude;
}

Vector point_projection_on_axis(Point point, Vector axis) {
    Vector projection = vector_dup(axis);
    Vector vector = point_vector_from_origin(point);
    double projection_magnitude = vector_dot(vector, projection);
    vector_multiply(projection, projection_magnitude);
    vector_release(vector);
    return projection;
}

void point_translate(Point point, Vector vector) {
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x + point->w * vector->x;
    point->y = point_y + point->w * vector->y;
}

void point_rotate_around(Point point, Point center, double deg) {
    double rad = deg_to_rad(deg);
    Vector vector1 = vector_new(-point_x(center), -point_y(center));
    Vector vector2 = vector_new(point_x(center), point_y(center));
    point_translate(point, vector1);
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x * cos(rad) - point_y * sin(rad);
    point->y = point_x * sin(rad) + point_y * cos(rad);
    point_translate(point, vector2);
    vector_release(vector1);
    vector_release(vector2);
}

Point midpoint_between_points(Point point1, Point point2) {
    Point midpoint = memalloc(sizeof(*midpoint));
    midpoint->w = 2 * point1->w * point2->w;
    midpoint->x = point1->x * point2->w + point2->x * point1->w;
    midpoint->y = point1->y * point2->w + point2->y * point1->w;
    return midpoint;
}

int point_is_infinite(Point point) {
    return double_equals(point->w, 0);
}

void point_normalize(Point point) {
    point->x /= point->w;
    point->y /= point->w;
    point->w = 1;
}

double point_distance_to_line(Point point, Line line) {
    Point normalized_point = point_dup(point);
    Line normalized_line = line_dup(line);
    point_normalize(normalized_point);
    line_normalize(normalized_line);
    double dist = fabs(normalized_point->w * normalized_line->w +
                       normalized_point->x * normalized_line->x +
                       normalized_point->y * normalized_line->y);
    line_release(normalized_line);
    point_release(normalized_point);
    return dist;
}

Line line_new(Point a, Point b) {
    Line line = memalloc(sizeof(*line));
    line->w = a->x * b->y - b->x * a->y;
    line->x = b->w * a->y - a->w * b->y;
    line->y = a->w * b->x - b->w * a->x;
    return line;
}

void line_release(Line line) {
    free(line);
}

int line_equals(Line line1, Line line2) {
    return (double_equals(line1->x / line1->w, line2->x / line2->w) &&
            double_equals(line1->y / line1->w, line2->y / line2->w));
}

Line line_dup(Line line) {
    Line dup = memalloc(sizeof(*dup));
    dup->w = line->w;
    dup->x = line->x;
    dup->y = line->y;
    return dup;
}

char *line_to_str(Line line, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Line: ("));
    list_append(str_list, double_to_str(line->w, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->y, decimal_positions));
    list_append(str_list, str_dup(") >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Line line_from_str(char *str) {
    List str_list = str_split(str, ", ");
    char *str_w = str_substr(list_at(str_list, 0), 10, strlen(list_at(str_list, 0)) - 10);
    char *str_x = str_dup(list_at(str_list, 1));
    char *str_y = str_substr(list_at(str_list, 2), 0, strlen(list_at(str_list, 2)) - 4);
    Line line = memalloc(sizeof(*line));
    line->w = atof(str_w);
    line->x = atof(str_x);
    line->y = atof(str_y);
    list_full_release(str_list, free);
    free(str_w);
    free(str_x);
    free(str_y);
    return line;
}

Line line_perpendicular(Line line, Point point) {
    Line perpendicular = memalloc(sizeof(*perpendicular));
    perpendicular->w = (line->y * point->x - line->x * point->y) / point->w;
    perpendicular->x = -line->y;
    perpendicular->y = line->x;
    return perpendicular;
}

Point line_intersection(Line line1, Line line2) {
    Point point = memalloc(sizeof(*point));
    point->w = line1->x * line2->y - line1->y * line2->x;
    point->x = line1->y * line2->w - line1->w * line2->y;
    point->y = line1->w * line2->x - line1->x * line2->w;
    return point;
}

void line_normalize(Line line) {
    double div = sqrt(line->x * line->x + line->y * line->y);
    line->w /= div;
    line->x /= div;
    line->y /= div;
}

int point_is_in_line(Point point, Line line) {
    return double_equals(line->w * point->w + line->x * point->x + line->y * point->y, 0);
}

double point_distance_to_point(Point point1, Point point2) {
    double x_dist = point_x(point1) - point_x(point2);
    double y_dist = point_y(point1) - point_y(point2);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

double angle_between_lines(Line line1, Line line2) {
    Line normalized_line1 = line_dup(line1);
    Line normalized_line2 = line_dup(line2);
    line_normalize(normalized_line1);
    line_normalize(normalized_line2);
    double cos = normalized_line1->x * normalized_line2->x +
                 normalized_line1->y * normalized_line2->y;
    double rad = acos(cos);
    line_release(normalized_line1);
    line_release(normalized_line2);
    return double_gt(rad, M_PI / 2) ? M_PI - rad : rad;
}

Segment segment_new(Point a, Point b) {
    Segment segment = memalloc(sizeof(*segment));
    segment->a = point_dup(a);
    segment->b = point_dup(b);
    return segment;
}

void segment_release(Segment segment) {
    point_release(segment->a);
    point_release(segment->b);
    free(segment);
}

int segment_equals(Segment segment1, Segment segment2) {
    return (point_equals(segment1->a, segment2->a) &&
            point_equals(segment1->b, segment2->b)) ? 1 : 0;
}

Segment segment_dup(Segment segment) {
    return segment_new(segment->a, segment->b);
}

char *segment_to_str(Segment segment, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Segment: ("));
    list_append(str_list, double_to_str(point_x(segment->a), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(segment->a), decimal_positions));
    list_append(str_list, str_dup("); ("));
    list_append(str_list, double_to_str(point_x(segment->b), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(segment->b), decimal_positions));
    list_append(str_list, str_dup(") >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Segment segment_from_str(char *str) {
    List str_list = str_split(str, "; ");
    char *point_a = str_substr(list_at(str_list, 0), 12, strlen(list_at(str_list, 0)) - 12);
    char *point_b = str_substr(list_at(str_list, 1), 0, strlen(list_at(str_list, 1)) - 3);
    List a_list = str_split(point_a, ", ");
    List b_list = str_split(point_b, ", ");
    char *a_x = str_substr(list_at(a_list, 0), 1, strlen(list_at(a_list, 0)) - 1);
    char *a_y = str_substr(list_at(a_list, 1), 0, strlen(list_at(a_list, 1)) - 1);
    char *b_x = str_substr(list_at(b_list, 0), 1, strlen(list_at(b_list, 0)) - 1);
    char *b_y = str_substr(list_at(b_list, 1), 0, strlen(list_at(b_list, 1)) - 1);
    Point a = point_new(atof(a_x), atof(a_y));
    Point b = point_new(atof(b_x), atof(b_y));
    Segment segment = segment_new(a, b);
    point_release(a);
    point_release(b);
    list_full_release(str_list, free);
    free(point_a);
    free(point_b);
    list_full_release(a_list, free);
    list_full_release(b_list, free);
    free(a_x);
    free(a_y);
    free(b_x);
    free(b_y);
    return segment;
}

List segment_points(Segment segment) {
    List points = list_new();
    list_append(points, point_dup(segment->a));
    list_append(points, point_dup(segment->b));
    return points;
}

Vector segment_vector(Segment segment) {
    return vector_from_point_to_point(segment->a, segment->b);
}

Line segment_line(Segment segment) {
    return line_new(segment->a, segment->b);
}

double segment_length(Segment segment) {
    double x_dist = point_x(segment->a) - point_x(segment->b);
    double y_dist = point_y(segment->a) - point_y(segment->b);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

ShapeProjectionOnAxis segment_projection_on_axis(Segment segment, Vector axis) {
    double magnitude1 = point_projection_magnitude_on_axis(segment->a, axis);
    double magnitude2 = point_projection_magnitude_on_axis(segment->b, axis);
    double min = (double_lte(magnitude1, magnitude2)) ? magnitude1 : magnitude2;
    double max = (double_gte(magnitude1, magnitude2)) ? magnitude1 : magnitude2;
    return shape_projection_on_axis_new(min, max);
}

List segment_collision_axes(Segment segment) {
    List collision_axes = list_new();
    Vector seg_vec = segment_vector(segment);
    Vector axis = vector_right_perpendicular(seg_vec);
    vector_normalize(axis);
    list_append(collision_axes, axis);
    vector_release(seg_vec);
    return collision_axes;
}

void segment_translate(Segment segment, Vector vector) {
    point_translate(segment->a, vector);
    point_translate(segment->b, vector);
}

void segment_rotate_around(Segment segment, Point center, double deg) {
    point_rotate_around(segment->a, center, deg);
    point_rotate_around(segment->b, center, deg);
}

int point_is_in_segment(Point point, Segment segment) {
    int is_in = 0;
    Line line = line_new(segment->a, segment->b);
    double min_x = (double_lt(point_x(segment->a), point_x(segment->b))) ?
                   point_x(segment->a) : point_x(segment->b);
    double max_x = (double_gt(point_x(segment->a), point_x(segment->b))) ? 
                   point_x(segment->a) : point_x(segment->b);
    if (point_is_in_line(point, line) && double_gte(point_x(point), min_x) &&
        double_lte(point_x(point), max_x))
        is_in = 1;
    line_release(line);
    return is_in;
}

Circle circle_new(Point center, double radius) {
    Circle circle = memalloc(sizeof(*circle));
    circle->center = point_dup(center);
    circle->radius = radius;
    return circle;
}

void circle_release(Circle circle) {
    point_release(circle->center);
    free(circle);
}

int circle_equals(Circle circle1, Circle circle2) {
    if (point_equals(circle1->center, circle2->center) &&
        double_equals(circle1->radius, circle2->radius))
        return 1;
    return 0;
}

Circle circle_dup(Circle circle) {
    Circle dup = memalloc(sizeof(*dup));
    dup->center = point_dup(circle->center);
    dup->radius = circle->radius;
    return dup;
}

char *circle_to_str(Circle circle, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Circle: ("));
    list_append(str_list, double_to_str(point_x(circle->center), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(circle->center), decimal_positions));
    list_append(str_list, str_dup("); "));
    list_append(str_list, double_to_str(circle->radius, decimal_positions));
    list_append(str_list, str_dup(" >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Circle circle_from_str(char *str) {
    List str_list = str_split(str, "; ");
    char *str_center = str_substr(list_at(str_list, 0), 11, strlen(list_at(str_list, 0)) - 11);
    char *str_radius = str_substr(list_at(str_list, 1), 0, strlen(list_at(str_list, 1)) - 3);
    List center_list = str_split(str_center, ", ");
    char *str_x = str_substr(list_at(center_list, 0), 1, strlen(list_at(center_list, 0)) - 1);
    char *str_y = str_substr(list_at(center_list, 1), 0, strlen(list_at(center_list, 1)) - 1);
    Point center = point_new(atof(str_x), atof(str_y));
    Circle circle = circle_new(center, atof(str_radius));
    point_release(center);
    free(str_x);
    free(str_y);
    free(str_center);
    free(str_radius);
    list_full_release(center_list, free);
    list_full_release(str_list, free);
    return circle;
}

Point circle_center(Circle circle) {
    return point_dup(circle->center);
}

double circle_center_x(Circle circle) {
    return point_x(circle->center);
}

double circle_center_y(Circle circle) {
    return point_y(circle->center);
}

double circle_radius(Circle circle) {
    return circle->radius;
}

void circle_translate(Circle circle, Vector vector) {
    point_translate(circle->center, vector);
}

ShapeProjectionOnAxis circle_projection_on_axis(Circle circle, Vector axis) {
    double magnitude = point_projection_magnitude_on_axis(circle->center, axis);
    return shape_projection_on_axis_new(magnitude - circle->radius,
                                        magnitude + circle->radius);
}

List circle_collision_axes(Circle circle, List points) {
    List collision_axes = list_new();
    for (ListItem it = list_head(points); it; it = list_next(it)) {
        Point point = list_value(it);
        Vector axis = vector_from_point_to_point(circle->center, point);
        vector_normalize(axis);
        list_append(collision_axes, axis);
    }
    return collision_axes;
}

int point_is_in_circle(Point point, Circle circle) {
    double circle_center_x = point_x(circle->center);
    double circle_center_y = point_y(circle->center);
    double point_x = point->x / point->w;
    double point_y = point->y / point->w;
    double squared_dist = (point_x - circle_center_x) * (point_x - circle_center_x) +
                          (point_y - circle_center_y) * (point_y - circle_center_y);
    return (double_lt(squared_dist, circle->radius * circle->radius)) ? 1 : 0;
}

Triangle triangle_new(Point a, Point b, Point c) {
    Triangle triangle = memalloc(sizeof(*triangle));
    triangle->a = point_dup(a);
    triangle->b = point_dup(b);
    triangle->c = point_dup(c);
    return triangle;
}

void triangle_release(Triangle triangle) {
    point_release(triangle->a);
    point_release(triangle->b);
    point_release(triangle->c);
    free(triangle);
}

int triangle_equals(Triangle triangle1, Triangle triangle2) {
    if ((point_equals(triangle1->a, triangle2->a) &&
         point_equals(triangle1->b, triangle2->b) &&
         point_equals(triangle1->c, triangle2->c)) ||
        (point_equals(triangle1->a, triangle2->a) &&
         point_equals(triangle1->b, triangle2->c) &&
         point_equals(triangle1->c, triangle2->b)) ||
        (point_equals(triangle1->a, triangle2->b) &&
         point_equals(triangle1->b, triangle2->a) &&
         point_equals(triangle1->c, triangle2->c)) ||
        (point_equals(triangle1->a, triangle2->b) &&
         point_equals(triangle1->b, triangle2->c) &&
         point_equals(triangle1->c, triangle2->a)) ||
        (point_equals(triangle1->a, triangle2->c) &&
         point_equals(triangle1->b, triangle2->a) &&
         point_equals(triangle1->c, triangle2->b)) ||
        (point_equals(triangle1->a, triangle2->c) &&
         point_equals(triangle1->b, triangle2->b) &&
         point_equals(triangle1->c, triangle2->a)))
        return 1;
    return 0;
}

Triangle triangle_dup(Triangle triangle) {
    return triangle_new(triangle->a, triangle->b, triangle->c);
}

char *triangle_to_str(Triangle triangle, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Triangle: ("));
    list_append(str_list, double_to_str(point_x(triangle->a), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(triangle->a), decimal_positions));
    list_append(str_list, str_dup("); ("));
    list_append(str_list, double_to_str(point_x(triangle->b), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(triangle->b), decimal_positions));
    list_append(str_list, str_dup("); ("));
    list_append(str_list, double_to_str(point_x(triangle->c), decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(point_y(triangle->c), decimal_positions));
    list_append(str_list, str_dup(") >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Triangle triangle_from_str(char *str) {
    List str_list = str_split(str, "; ");
    char *str_a = str_substr(list_at(str_list, 0), 14, strlen(list_at(str_list, 0)) - 15);
    List str_a_list = str_split(str_a, ", ");
    Point a = point_new(atof(list_at(str_a_list, 0)), atof(list_at(str_a_list, 1)));
    char *str_b = str_substr(list_at(str_list, 1), 1, strlen(list_at(str_list, 1)) - 2);
    List str_b_list = str_split(str_b, ", ");
    Point b = point_new(atof(list_at(str_b_list, 0)), atof(list_at(str_b_list, 1)));
    char *str_c = str_substr(list_at(str_list, 2), 1, strlen(list_at(str_list, 2)) - 5);
    List str_c_list = str_split(str_c, ", ");
    Point c = point_new(atof(list_at(str_c_list, 0)), atof(list_at(str_c_list, 1)));
    Triangle triangle = triangle_new(a, b, c);
    point_release(a);
    point_release(b);
    point_release(c);
    free(str_a);
    free(str_b);
    free(str_c);
    list_full_release(str_list, free);
    list_full_release(str_a_list, free);
    list_full_release(str_b_list, free);
    list_full_release(str_c_list, free);
    return triangle;
}

List triangle_points(Triangle triangle) {
    List points = list_new();
    list_append(points, point_dup(triangle->a));
    list_append(points, point_dup(triangle->b));
    list_append(points, point_dup(triangle->c));
    return points;
}

void triangle_translate(Triangle triangle, Vector vector) {
    point_translate(triangle->a, vector);
    point_translate(triangle->b, vector);
    point_translate(triangle->c, vector);
}

void triangle_rotate_around(Triangle triangle, Point center, double deg) {
    point_rotate_around(triangle->a, center, deg);
    point_rotate_around(triangle->b, center, deg);
    point_rotate_around(triangle->c, center, deg);
}

int triangle_orientation(Triangle triangle) {
    double value = triangle->a->w * triangle->b->x * triangle->c->y +
                   triangle->a->x * triangle->b->y * triangle->c->w +
                   triangle->a->y * triangle->b->w * triangle->c->x -
                   triangle->a->y * triangle->b->x * triangle->c->w -
                   triangle->a->w * triangle->b->y * triangle->c->x -
                   triangle->a->x * triangle->b->w * triangle->c->y;
    return double_equals(value, 0) ? 0 : double_gt(value, 0) ? 1 : -1;
}

double triangle_area(Triangle triangle) {
    return fabs(triangle->a->w * triangle->b->x * triangle->c->y +
                triangle->a->x * triangle->b->y * triangle->c->w +
                triangle->a->y * triangle->b->w * triangle->c->x -
                triangle->a->y * triangle->b->x * triangle->c->w -
                triangle->a->w * triangle->b->y * triangle->c->x -
                triangle->a->x * triangle->b->w * triangle->c->y) / 2;
}

ShapeProjectionOnAxis triangle_projection_on_axis(Triangle triangle, Vector axis) {
    double min, max;
    List points = triangle_points(triangle);
    for (ListItem it = list_head(points); it; it = list_next(it)) {
        Point point = list_value(it);
        double magnitude = point_projection_magnitude_on_axis(point, axis);
        min = (it == list_head(points) || double_lt(magnitude, min)) ? magnitude : min;
        max = (it == list_head(points) || double_gt(magnitude, max)) ? magnitude : max;
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return shape_projection_on_axis_new(min, max);
}

List triangle_collision_axes(Triangle triangle) {
    List collision_axes = list_new();
    List points = triangle_points(triangle);
    for (int i = 0; i < 3; i++) {
        Point point1 = list_at(points, i);
        Point point2 = list_at(points, (i + 1) % 3);
        Vector vector = vector_from_point_to_point(point1, point2);
        Vector axis = vector_right_perpendicular(vector);
        vector_normalize(axis);
        list_append(collision_axes, axis);
        vector_release(vector);
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return collision_axes;
}

int point_is_in_triangle(Point point, Triangle triangle) {
    int is_in = 0;
    Triangle triangle1 = triangle_new(triangle->a, point, triangle->b);
    Triangle triangle2 = triangle_new(triangle->b, point, triangle->c);
    Triangle triangle3 = triangle_new(triangle->c, point, triangle->a);
    if ((triangle_orientation(triangle1) == 1 &&
         triangle_orientation(triangle2) == 1 &&
         triangle_orientation(triangle3) == 1) ||
        (triangle_orientation(triangle1) == -1 &&
         triangle_orientation(triangle2) == -1 &&
         triangle_orientation(triangle3) == -1))
        is_in = 1;
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    return is_in;
}

Polygon polygon_new(List points) {
    Polygon polygon = memalloc(sizeof(*polygon));
    polygon->points = list_new();
    points = list_dup(points);
    Point base_point = NULL;
    for (ListItem it = list_head(points); it; it = list_next(it)) {
        Point point = list_value(it);
        if (!base_point ||
            double_lt(point_y(point), point_y(base_point)) ||
            (double_equals(point_y(point), point_y(base_point)) &&
             double_lt(point_x(point), point_x(base_point))))
            base_point = point;
    }
    list_append(polygon->points, point_dup(base_point));
    list_remove(points, base_point);
    Vector base_vector = vector_new(1, 0);
    while (list_size(points)) {
        Point next_point = NULL;
        double next_angle;
        for (ListItem it = list_head(points); it; it = list_next(it)) {
            Point point = list_value(it);
            Vector vector = vector_new(point_x(point) - point_x(base_point),
                                       point_y(point) - point_y(base_point));
            double angle = angle_between_vectors(base_vector, vector);
            if (!next_point || double_lt(angle, next_angle)) {
                next_angle = angle;
                next_point = point;
            }
            vector_release(vector);
        }
        list_append(polygon->points, point_dup(next_point));
        list_remove(points, next_point);
    }
    vector_release(base_vector);
    list_release(points);
    return polygon;
}

Polygon polygon_new_triangle(Point a, Point b, Point c) {
    List points = list_new();
    list_append(points, a);
    list_append(points, b);
    list_append(points, c);
    Polygon polygon = polygon_new(points);
    list_release(points);
    return polygon;
}

Polygon polygon_new_rectangle(Point lower_left, double width, double height) {
    List points = list_new();
    list_append(points, point_dup(lower_left));
    list_append(points, point_new(point_x(lower_left) + width, point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + width, point_y(lower_left) + height));
    list_append(points, point_new(point_x(lower_left), point_y(lower_left) + height));
    Polygon polygon = polygon_new(points);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

Polygon polygon_new_square(Point lower_left, double side) {
    List points = list_new();
    list_append(points, point_dup(lower_left));
    list_append(points, point_new(point_x(lower_left) + side, point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + side, point_y(lower_left) + side));
    list_append(points, point_new(point_x(lower_left), point_y(lower_left) + side));
    Polygon polygon = polygon_new(points);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

void polygon_release(Polygon polygon) {
    list_full_release(polygon->points, (void (*)(void *)) point_release);
    free(polygon);
}

int polygon_equals(Polygon polygon1, Polygon polygon2) {
    if (list_size(polygon1->points) != list_size(polygon2->points))
        return 0;
    for (ListItem it = list_head(polygon1->points); it; it = list_next(it)) {
        Point point = list_value(it);
        if (!list_find_cmp(polygon2->points, (int (*)(void *, void *)) point_equals, point))
            return 0;
    }
    return 1;
}

Polygon polygon_dup(Polygon polygon) {
    Polygon dup = memalloc(sizeof(*dup));
    dup->points = list_new();
    for (ListItem it = list_head(polygon->points); it; it = list_next(it))
        list_append(dup->points, point_dup(list_value(it)));
    return dup;
}

char *polygon_to_str(Polygon polygon, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Polygon: ("));
    for (ListItem it = list_head(polygon->points); it; it = list_next(it)) {
        Point point = list_value(it);
        list_append(str_list, double_to_str(point_x(point), decimal_positions));
        list_append(str_list, str_dup(", "));
        list_append(str_list, double_to_str(point_y(point), decimal_positions));
        if (list_next(it))
            list_append(str_list, str_dup("); ("));
        else
            list_append(str_list, str_dup(") >>"));
    }
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Polygon polygon_from_str(char *str) {
    List str_list = str_split(str, "; ");
    List points = list_new();
    int n_points = list_size(str_list);
    for (int i = 1; i < n_points - 1; i++) {
        List point_list = str_split(list_at(str_list, i), ", ");
        char *point_x = str_substr(list_at(point_list, 0), 1,
                                   strlen(list_at(point_list, 0)) - 1);
        char *point_y = str_substr(list_at(point_list, 1), 0,
                                   strlen(list_at(point_list, 1)) - 1);
        list_append(points, point_new(atof(point_x), atof(point_y)));
        list_full_release(point_list, free);
        free(point_x);
        free(point_y);
    }
    List point_0_list = str_split(list_at(str_list, 0), ", ");
    List point_n_list = str_split(list_at(str_list, n_points - 1), ", ");
    char *point_0_x = str_substr(list_at(point_0_list, 0), 13,
                                 strlen(list_at(point_0_list, 0)) - 13);
    char *point_0_y = str_substr(list_at(point_0_list, 1), 0,
                                 strlen(list_at(point_0_list, 1)) - 1);
    char *point_n_x = str_substr(list_at(point_n_list, 0), 1,
                                 strlen(list_at(point_n_list, 0)) - 1);
    char *point_n_y = str_substr(list_at(point_n_list, 1), 0,
                                 strlen(list_at(point_n_list, 1)) - 4);
    list_append(points, point_new(atof(point_0_x), atof(point_0_y)));
    list_append(points, point_new(atof(point_n_x), atof(point_n_y)));
    Polygon polygon = polygon_new(points);
    list_full_release(str_list, free);
    list_full_release(point_0_list, free);
    list_full_release(point_n_list, free);
    free(point_0_x);
    free(point_0_y);
    free(point_n_x);
    free(point_n_y);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

List polygon_points(Polygon polygon) {
    List points = list_new();
    for (ListItem it = list_head(polygon->points); it; it = list_next(it))
        list_append(points, point_dup(list_value(it)));
    return points;
}

void polygon_translate(Polygon polygon, Vector vector) {
    for (ListItem it = list_head(polygon->points); it; it = list_next(it)) {
        Point point = list_value(it);
        point_translate(point, vector);
    }
}

void polygon_rotate_around(Polygon polygon, Point center, double deg) {
    for (ListItem it = list_head(polygon->points); it; it = list_next(it)) {
        Point point = list_value(it);
        point_rotate_around(point, center, deg);
    }
}

double polygon_area(Polygon polygon) {
    double double_area = 0;
    int n = list_size(polygon->points);
    for (int i = 0; i < n; i++) {
        Point point1 = list_at(polygon->points, i);
        Point point2 = list_at(polygon->points, (i + 1) % n);
        double_area += point_x(point1) * point_y(point2) - point_x(point2) * point_y(point1);
    }
    return fabs(double_area) / 2;
}

ShapeProjectionOnAxis polygon_projection_on_axis(Polygon polygon, Vector axis) {
    double min, max;
    List points = polygon_points(polygon);
    for (ListItem it = list_head(points); it; it = list_next(it)) {
        Point point = list_value(it);
        double magnitude = point_projection_magnitude_on_axis(point, axis);
        min = (it == list_head(points) || double_lt(magnitude, min)) ? magnitude : min;
        max = (it == list_head(points) || double_gt(magnitude, max)) ? magnitude : max;
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return shape_projection_on_axis_new(min, max);
}

List polygon_collision_axes(Polygon polygon) {
    List collision_axes = list_new();
    List points = polygon_points(polygon);
    int n_points = list_size(points);
    for (int i = 0; i < n_points; i++) {
        Point point1 = list_at(points, i);
        Point point2 = list_at(points, (i + 1) % n_points);
        Vector side_vec = vector_from_point_to_point(point1, point2);
        Vector axis = vector_right_perpendicular(side_vec);
        vector_normalize(axis);
        list_append(collision_axes, axis);
        vector_release(side_vec);
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return collision_axes;
}

int point_is_in_polygon(Point point, Polygon polygon) {
    int point_is_in = 1;
    int n = list_size(polygon->points);
    int orientation;
    for (int i = 0; i < n && point_is_in; i++) {
        Point point1 = list_at(polygon->points, i);
        Point point2 = list_at(polygon->points, (i + 1) % n);
        Triangle triangle = triangle_new(point1, point, point2);
        if (i == 0)
            orientation = triangle_orientation(triangle);
        else if (orientation != triangle_orientation(triangle))
            point_is_in = 0;
        triangle_release(triangle);
    }
    return point_is_in;
}

ShapeProjectionOnAxis shape_projection_on_axis_new(double min, double max) {
    ShapeProjectionOnAxis spoa = memalloc(sizeof(*spoa));
    spoa->min = min;
    spoa->max = max;
    return spoa;
}

void shape_projection_on_axis_release(ShapeProjectionOnAxis spoa) {
    free(spoa);
}

int shape_projection_on_axis_equals(ShapeProjectionOnAxis spoa1, ShapeProjectionOnAxis spoa2) {
    return (double_equals(spoa1->min, spoa2->min) &&
            double_equals(spoa1->max, spoa2->max)) ? 1 : 0;
}

ShapeProjectionOnAxis shape_projection_on_axis_dup(ShapeProjectionOnAxis spoa) {
    return shape_projection_on_axis_new(spoa->min, spoa->max);
}

double shape_projection_on_axis_min(ShapeProjectionOnAxis spoa) {
    return spoa->min;
}

double shape_projection_on_axis_max(ShapeProjectionOnAxis spoa) {
    return spoa->max;
}

double shape_projection_on_axis_tv(ShapeProjectionOnAxis spoa1, ShapeProjectionOnAxis spoa2) {
    if (double_gte(spoa1->min, spoa2->max) || double_gte(spoa2->min, spoa1->max))
        return 0;
    if (double_lte(spoa1->max - spoa2->min, spoa2->max - spoa1->min))
        return spoa1->max - spoa2->min;
    return spoa1->min - spoa2->max;
}

Vector segment_segment_intersection(Segment segment1, Segment segment2) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = segment_collision_axes(segment1);
    List axes2 = segment_collision_axes(segment2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment1, axis);
        ShapeProjectionOnAxis spoa2 = segment_projection_on_axis(segment2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector segment_triangle_intersection(Segment segment, Triangle triangle) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = segment_collision_axes(segment);
    List axes2 = triangle_collision_axes(triangle);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        ShapeProjectionOnAxis spoa2 = triangle_projection_on_axis(triangle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector segment_polygon_intersection(Segment segment, Polygon polygon) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = segment_collision_axes(segment);
    List axes2 = polygon_collision_axes(polygon);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        ShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector segment_circle_intersection(Segment segment, Circle circle) {
    Vector mtv;
    double mtv_magnitude;
    List seg_points = segment_points(segment);
    List axes = list_new();
    List axes1 = segment_collision_axes(segment);
    List axes2 = circle_collision_axes(circle, seg_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        ShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_full_release(seg_points, (void (*)(void *)) point_release);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector triangle_segment_intersection(Triangle triangle, Segment segment) {
    Vector mtv = segment_triangle_intersection(segment, triangle);
    vector_reverse(mtv);
    return mtv;
}

Vector triangle_triangle_intersection(Triangle triangle1, Triangle triangle2) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = triangle_collision_axes(triangle1);
    List axes2 = triangle_collision_axes(triangle2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle1, axis);
        ShapeProjectionOnAxis spoa2 = triangle_projection_on_axis(triangle2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector triangle_polygon_intersection(Triangle triangle, Polygon polygon) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = triangle_collision_axes(triangle);
    List axes2 = polygon_collision_axes(polygon);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle, axis);
        ShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector triangle_circle_intersection(Triangle triangle, Circle circle) {
    Vector mtv;
    double mtv_magnitude;
    List tri_points = triangle_points(triangle);
    List axes = list_new();
    List axes1 = triangle_collision_axes(triangle);
    List axes2 = circle_collision_axes(circle, tri_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle, axis);
        ShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_full_release(tri_points, (void (*)(void *)) point_release);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector polygon_segment_intersection(Polygon polygon, Segment segment) {
    Vector mtv = segment_polygon_intersection(segment, polygon);
    vector_reverse(mtv);
    return mtv;
}

Vector polygon_triangle_intersection(Polygon polygon, Triangle triangle) {
    Vector mtv = triangle_polygon_intersection(triangle, polygon);
    vector_reverse(mtv);
    return mtv;
}

Vector polygon_polygon_intersection(Polygon polygon1, Polygon polygon2) {
    Vector mtv;
    double mtv_magnitude;
    List axes = list_new();
    List axes1 = polygon_collision_axes(polygon1);
    List axes2 = polygon_collision_axes(polygon2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = polygon_projection_on_axis(polygon1, axis);
        ShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

Vector polygon_circle_intersection(Polygon polygon, Circle circle) {
    Vector mtv;
    double mtv_magnitude;
    List poly_points = polygon_points(polygon);
    List axes = list_new();
    List axes1 = polygon_collision_axes(polygon);
    List axes2 = circle_collision_axes(circle, poly_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ListItem it = list_head(axes); it; it = list_next(it)) {
        Vector axis = list_value(it);
        ShapeProjectionOnAxis spoa1 = polygon_projection_on_axis(polygon, axis);
        ShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    list_full_release(poly_points, (void (*)(void *)) point_release);
    return mtv;
}

Vector circle_segment_intersection(Circle circle, Segment segment) {
    Vector mtv = segment_circle_intersection(segment, circle);
    vector_reverse(mtv);
    return mtv;
}

Vector circle_triangle_intersection(Circle circle, Triangle triangle) {
    Vector mtv = triangle_circle_intersection(triangle, circle);
    vector_reverse(mtv);
    return mtv;
}

Vector circle_polygon_intersection(Circle circle, Polygon polygon) {
    Vector mtv = polygon_circle_intersection(polygon, circle);
    vector_reverse(mtv);
    return mtv;
}

Vector circle_circle_intersection(Circle circle1, Circle circle2) {
    Vector axis = vector_from_point_to_point(circle1->center, circle2->center);
    vector_normalize(axis);
    ShapeProjectionOnAxis spoa1 = circle_projection_on_axis(circle1, axis);
    ShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle2, axis);
    double mtv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
    vector_multiply(axis, mtv_magnitude);
    shape_projection_on_axis_release(spoa1);
    shape_projection_on_axis_release(spoa2);
    return axis;
}

