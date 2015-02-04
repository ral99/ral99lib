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
    return (double_equals(vector1->x, vector2->x) &&
            double_equals(vector1->y, vector2->y));
}

Vector vector_dup(Vector vector) {
    Vector dup = memalloc(sizeof(*dup));
    dup->x = vector->x;
    dup->y = vector->y;
    return dup;
}

char *vector_to_str(Vector vector, int decimal_positions) {
    List str_list = list_new();
    list_append(str_list, str_dup("<< Vector: "));
    list_append(str_list, double_to_str(vector->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(vector->y, decimal_positions));
    list_append(str_list, str_dup(" >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Vector vector_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 11,
                             strlen(list_at(str_list, 0)) - 11);
    char *str_y = str_substr(list_at(str_list, 1), 0,
                             strlen(list_at(str_list, 1)) - 3);
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

void vector_normalize(Vector vector) {
    double magnitude = vector_magnitude(vector);
    vector->x /= magnitude;
    vector->y /= magnitude;
}

void vector_sum(Vector a, Vector b) {
    a->x += b->x;
    a->y += b->y;
}

void vector_subtract(Vector a, Vector b) {
    a->x -= b->x;
    a->y -= b->y;
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
    list_append(str_list, str_dup("<< Point: "));
    list_append(str_list,
                double_to_str(point->x / point->w, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list,
                double_to_str(point->y / point->w, decimal_positions));
    list_append(str_list, str_dup(" >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Point point_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 10,
                             strlen(list_at(str_list, 0)) - 10);
    char *str_y = str_substr(list_at(str_list, 1), 0,
                             strlen(list_at(str_list, 1)) - 3);
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

Line line_new(Point point1, Point point2) {
    Line line = memalloc(sizeof(*line));
    line->w = point1->x * point2->y - point2->x * point1->y;
    line->x = point2->w * point1->y - point1->w * point2->y;
    line->y = point1->w * point2->x - point2->w * point1->x;
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
    list_append(str_list, str_dup("<< Line: "));
    list_append(str_list, double_to_str(line->w, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->y, decimal_positions));
    list_append(str_list, str_dup(" >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Line line_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_w = str_substr(list_at(str_list, 0), 9,
                             strlen(list_at(str_list, 0)) - 9);
    char *str_x = str_dup(list_at(str_list, 1));
    char *str_y = str_substr(list_at(str_list, 2), 0,
                             strlen(list_at(str_list, 2)) - 3);
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
    return double_equals(line->w * point->w + line->x * point->x +
                         line->y * point->y, 0);
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
    line_release(normalized_line1);
    line_release(normalized_line2);
    double rad = acos(cos);
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

Segment segment_from_str(char *string) {
    List str_list = str_split(string, "; ");
    char *point_a = str_substr(list_at(str_list, 0), 12,
                               strlen(list_at(str_list, 0)) - 12);
    char *point_b = str_substr(list_at(str_list, 1), 0,
                               strlen(list_at(str_list, 1)) - 3);
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

void segment_translate(Segment segment, Vector vector) {
    point_translate(segment->a, vector);
    point_translate(segment->b, vector);
}

void segment_rotate_around(Segment segment, Point center, double deg) {
    point_rotate_around(segment->a, center, deg);
    point_rotate_around(segment->b, center, deg);
}

int point_is_in_segment(Point point, Segment segment) {
    int ret = 0;
    Line line = line_new(segment->a, segment->b);
    double min_x = (double_lt(point_x(segment->a), point_x(segment->b))) ?
                   point_x(segment->a) : point_x(segment->b);
    double max_x = (double_gt(point_x(segment->a), point_x(segment->b))) ? 
                   point_x(segment->a) : point_x(segment->b);
    if (point_is_in_line(point, line) &&
        (double_gt(point_x(point), min_x) ||
         double_equals(point_x(point), min_x)) &&
        (double_lt(point_x(point), max_x) ||
         double_equals(point_x(point), max_x)))
        ret = 1;
    line_release(line);
    return ret;
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
    list_append(str_list, str_dup("<< Circle: "));
    list_append(str_list,
                double_to_str(circle->center->x / circle->center->w,
                              decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list,
                double_to_str(circle->center->y / circle->center->w,
                              decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(circle->radius, decimal_positions));
    list_append(str_list, str_dup(" >>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Circle circle_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 11,
                             strlen(list_at(str_list, 0)) - 11);
    char *str_y = str_dup(list_at(str_list, 1));
    char *str_radius = str_substr(list_at(str_list, 2), 0,
                                  strlen(list_at(str_list, 1)) - 3);
    Point center = point_new(atof(str_x), atof(str_y));
    Circle circle = circle_new(center, atof(str_radius));
    point_release(center);
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    free(str_radius);
    return circle;
}

Point circle_center(Circle circle) {
    return point_dup(circle->center);
}

double circle_center_x(Circle circle) {
    return circle->center->x / circle->center->w;
}

double circle_center_y(Circle circle) {
    return circle->center->y / circle->center->w;
}

double circle_radius(Circle circle) {
    return circle->radius;
}

void circle_translate(Circle circle, Vector vector) {
    point_translate(circle->center, vector);
}

int point_is_in_circle(Point point, Circle circle) {
    double point_x = point->x / point->w;
    double point_y = point->y / point->w;
    double circle_center_x = circle->center->x / circle->center->w;
    double circle_center_y = circle->center->y / circle->center->w;
    double squared_dist = (point_x - circle_center_x) *
                          (point_x - circle_center_x) +
                          (point_y - circle_center_y) *
                          (point_y - circle_center_y);
    if (double_lt(squared_dist, circle->radius * circle->radius))
        return 1;
    return 0;
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

Triangle triangle_dup(Triangle triangle) {
    return triangle_new(triangle->a, triangle->b, triangle->c);
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

int point_is_in_triangle(Point point, Triangle triangle) {
    int ret;
    Triangle triangle1 = triangle_new(triangle->a, point, triangle->b);
    Triangle triangle2 = triangle_new(triangle->b, point, triangle->c);
    Triangle triangle3 = triangle_new(triangle->c, point, triangle->a);
    if ((triangle_orientation(triangle1) == 1 &&
         triangle_orientation(triangle2) == 1 &&
         triangle_orientation(triangle3) == 1) ||
        (triangle_orientation(triangle1) == -1 &&
         triangle_orientation(triangle2) == -1 &&
         triangle_orientation(triangle3) == -1))
        ret = 1;
    else
        ret = 0;
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    return ret;
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
    list_append(points, point_new(point_x(lower_left) + width,
                                  point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + width,
                                  point_y(lower_left) + height));
    list_append(points, point_new(point_x(lower_left),
                                  point_y(lower_left) + height));
    Polygon polygon = polygon_new(points);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

Polygon polygon_new_square(Point lower_left, double side) {
    List points = list_new();
    list_append(points, point_dup(lower_left));
    list_append(points, point_new(point_x(lower_left) + side,
                                  point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + side,
                                  point_y(lower_left) + side));
    list_append(points, point_new(point_x(lower_left),
                                  point_y(lower_left) + side));
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
        if (list_find_cmp(polygon2->points,
                          (int (*)(void *, void *)) point_equals,
                          point) == NULL)
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
        Point a = list_at(polygon->points, i);
        Point b = list_at(polygon->points, (i + 1) % n);
        double_area += point_x(a) * point_y(b) - point_x(b) * point_y(a);
    }
    return fabs(double_area) / 2;
}

int point_is_in_polygon(Polygon polygon, Point point) {
    int n = list_size(polygon->points);
    int point_is_in = 1;
    int orientation;
    for (int i = 0; i < n && point_is_in; i++) {
        Point a = list_at(polygon->points, i);
        Point c = list_at(polygon->points, (i + 1) % n);
        Triangle triangle = triangle_new(a, point, c);
        if (i == 0)
            orientation = triangle_orientation(triangle);
        else if (orientation != triangle_orientation(triangle))
            point_is_in = 0;
        triangle_release(triangle);
    }
    return point_is_in;
}

Vector circle_circle_intersection(Circle a, Circle b) {
    Vector vector = vector_from_point_to_point(a->center, b->center);
    double center_dist = vector_magnitude(vector);
    if (double_lt(center_dist, a->radius + b->radius)) {
        vector_normalize(vector);
        vector_multiply(vector, a->radius + b->radius - center_dist);
    }
    else {
        vector_release(vector);
        vector = vector_new(0, 0);
    }
    return vector;
}

