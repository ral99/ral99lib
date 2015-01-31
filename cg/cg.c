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
    list_append(str_list, str_dup("<"));
    list_append(str_list, double_to_str(vector->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(vector->y, decimal_positions));
    list_append(str_list, str_dup(">"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Vector vector_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 1,
                             strlen(list_at(str_list, 0)) - 1);
    char *str_y = str_substr(list_at(str_list, 1), 0,
                             strlen(list_at(str_list, 1)) - 1);
    Vector vector = vector_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return vector;
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
    list_append(str_list, str_dup("("));
    list_append(str_list,
                double_to_str(point->x / point->w, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list,
                double_to_str(point->y / point->w, decimal_positions));
    list_append(str_list, str_dup(")"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Point point_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_x = str_substr(list_at(str_list, 0), 1,
                             strlen(list_at(str_list, 0)) - 1);
    char *str_y = str_substr(list_at(str_list, 1), 0,
                             strlen(list_at(str_list, 1)) - 1);
    Point point = point_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return point;
}

void point_translate(Point point, double x, double y) {
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x + point->w * x;
    point->y = point_y + point->w * y;
}

void point_rotate(Point point, double deg) {
    double rad = deg_to_rad(deg);
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x * cos(rad) - point_y * sin(rad);
    point->y = point_x * sin(rad) + point_y * cos(rad);
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
    list_append(str_list, str_dup("<<"));
    list_append(str_list, double_to_str(line->w, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->x, decimal_positions));
    list_append(str_list, str_dup(", "));
    list_append(str_list, double_to_str(line->y, decimal_positions));
    list_append(str_list, str_dup(">>"));
    char *str = str_join(str_list, "");
    list_full_release(str_list, free);
    return str;
}

Line line_from_str(char *string) {
    List str_list = str_split(string, ", ");
    char *str_w = str_substr(list_at(str_list, 0), 2,
                             strlen(list_at(str_list, 0)) - 2);
    char *str_x = str_dup(list_at(str_list, 1));
    char *str_y = str_substr(list_at(str_list, 2), 0,
                             strlen(list_at(str_list, 2)) - 2);
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

double angle_between_lines(Line line1, Line line2) {
    Line normalized_line1 = line_dup(line1);
    Line normalized_line2 = line_dup(line2);
    line_normalize(normalized_line1);
    line_normalize(normalized_line2);
    double cos = normalized_line1->x * normalized_line2->x +
                 normalized_line1->y * normalized_line2->y;
    line_release(normalized_line1);
    line_release(normalized_line2);
    return acos(cos);
}

Circle circle_new(double x, double y, double radius) {
    Circle circle = memalloc(sizeof(*circle));
    circle->center = point_new(x, y);
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
    Circle circle = circle_new(atof(str_x), atof(str_y), atof(str_radius));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    free(str_radius);
    return circle;
}

void circle_translate(Circle circle, double x, double y) {
    point_translate(circle->center, x, y);
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
    if (double_equals(squared_dist, circle->radius * circle->radius))
        return 2;
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
    Line line1 = line_new(triangle->a, triangle->b);
    Line line2 = line_new(triangle->b, triangle->c);
    Line line3 = line_new(triangle->c, triangle->a);
    if ((triangle_orientation(triangle1) == 1 &&
         triangle_orientation(triangle2) == 1 &&
         triangle_orientation(triangle3) == 1) ||
        (triangle_orientation(triangle1) == -1 &&
         triangle_orientation(triangle2) == -1 &&
         triangle_orientation(triangle3) == -1))
        ret = 1;
    else if (point_is_in_line(point, line1) || point_is_in_line(point, line2) ||
             point_is_in_line(point, line3))
        ret = 2;
    else
        ret = 0;
    line_release(line1);
    line_release(line2);
    line_release(line3);
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    return ret;
}

