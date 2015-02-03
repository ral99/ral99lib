#include <glib.h>
#include <math.h>
#include <stdlib.h>

#include "cg/cg.h"
#include "mem/mem.h"
#include "num/num.h"

static void test_deg_to_rad_1() {
    g_assert(double_equals(deg_to_rad(0), 0));
    g_assert(double_equals(deg_to_rad(90), M_PI / 2));
    g_assert(double_equals(deg_to_rad(180), M_PI));
    g_assert(double_equals(deg_to_rad(360), 0));
    g_assert(double_equals(deg_to_rad(450), M_PI / 2));
    g_assert(double_equals(deg_to_rad(540), M_PI));
}

static void test_vector_new_1() {
    Vector vector = vector_new(2, 3);
    g_assert(vector != NULL);
    g_assert(double_equals(vector->x, 2));
    g_assert(double_equals(vector->y, 3));
    vector_release(vector);
}

static void test_vector_release_1() {
    Vector vector = vector_new(2, 3);
    vector_release(vector);
}

static void test_vector_equals_1() {
    Vector vector1 = vector_new(1, 1);
    Vector vector2 = vector_new(1, 1);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 1);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_equals_2() {
    Vector vector1 = vector_new(1, 1);
    Vector vector2 = vector_new(2, 2);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 0);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dup_1() {
    Vector vector1 = vector_new(2, 3);
    Vector vector2 = vector_dup(vector1);
    g_assert(vector1 != vector2);
    g_assert(double_equals(vector1->x, vector2->x));
    g_assert(double_equals(vector1->y, vector2->y));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_to_str_1() {
    Vector vector = vector_new(1.25, 2);
    char *str = vector_to_str(vector, 2);
    g_assert_cmpstr(str, ==, "<< Vector: 1.25, 2.00 >>");
    free(str);
    vector_release(vector);
}

static void test_vector_from_str_1() {
    Vector vector1 = vector_from_str("<< Vector: 1.25, 2.00 >>");
    Vector vector2 = vector_new(1.25, 2.00);
    g_assert(vector_equals(vector1, vector2));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_x_1() {
    Vector vector = vector_new(1, 2);
    g_assert(double_equals(vector_x(vector), 1));
    vector_release(vector);
}

static void test_vector_y_1() {
    Vector vector = vector_new(1, 2);
    g_assert(double_equals(vector_y(vector), 2));
    vector_release(vector);
}

static void test_vector_magnitude_1() {
    Vector vector = vector_new(0, 0);
    g_assert(double_equals(vector_magnitude(vector), 0));
    vector_release(vector);
}

static void test_vector_magnitude_2() {
    Vector vector = vector_new(3, 4);
    g_assert(double_equals(vector_magnitude(vector), 5));
    vector_release(vector);
}

static void test_vector_rotate_1() {
    Vector vector = vector_new(1, 0);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 1));
    vector_release(vector);
}

static void test_vector_rotate_2() {
    Vector vector = vector_new(0, 1);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, -1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_vector_rotate_3() {
    Vector vector = vector_new(-1, 0);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, -1));
    vector_release(vector);
}

static void test_vector_rotate_4() {
    Vector vector = vector_new(0, -1);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_point_new_1() {
    Point point = point_new(2, 3);
    g_assert(point != NULL);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 2));
    g_assert(double_equals(point->y, 3));
    point_release(point);
}

static void test_point_release_1() {
    Point point = point_new(2, 3);
    point_release(point);
}

static void test_point_equals_1() {
    Point point1 = point_new(1, 1);
    Point point2 = point_new(1, 1);
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_2() {
    Point point1 = point_new(1, 1);
    Point point2 = point_new(2, 2);
    g_assert_cmpint(point_equals(point1, point2), ==, 0);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_3() {
    Point point1 = point_new(1, 1);
    Point point2 = point_new(2, 2);
    point1->w = 1;
    point2->w = 2;
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_dup_1() {
    Point point1 = point_new(2, 3);
    Point point2 = point_dup(point1);
    g_assert(point1 != point2);
    g_assert(double_equals(point1->w, point2->w));
    g_assert(double_equals(point1->x, point2->x));
    g_assert(double_equals(point1->y, point2->y));
    point_release(point1);
    point_release(point2);
}

static void test_point_to_str_1() {
    Point point = point_new(1.25, 2);
    char *str = point_to_str(point, 2);
    g_assert_cmpstr(str, ==, "<< Point: 1.25, 2.00 >>");
    free(str);
    point_release(point);
}

static void test_point_from_str_1() {
    Point point1 = point_from_str("<< Point: 1.25, 2.00 >>");
    Point point2 = point_new(1.25, 2.00);
    g_assert(point_equals(point1, point2));
    point_release(point1);
    point_release(point2);
}

static void test_point_x_1() {
    Point point = point_new(1, 2);
    g_assert(double_equals(point_x(point), 1));
    point_release(point);
}

static void test_point_x_2() {
    Point point = point_new(1, 2);
    point->w *= 2;
    point->x *= 2;
    g_assert(double_equals(point_x(point), 1));
    point_release(point);
}

static void test_point_y_1() {
    Point point = point_new(1, 2);
    g_assert(double_equals(point_y(point), 2));
    point_release(point);
}

static void test_point_y_2() {
    Point point = point_new(1, 2);
    point->w *= 2;
    point->y *= 2;
    g_assert(double_equals(point_y(point), 2));
    point_release(point);
}

static void test_point_translate_1() {
    Vector vector = vector_new(2, 2);
    Point point = point_new(2, 4);
    point_translate(point, vector);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 4));
    g_assert(double_equals(point->y, 6));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_2() {
    Vector vector = vector_new(2, 2);
    Point point = point_new(2, 4);
    point->w = 2;
    point_translate(point, vector);
    g_assert(double_equals(point->w, 2));
    g_assert(double_equals(point->x, 6));
    g_assert(double_equals(point->y, 8));
    vector_release(vector);
    point_release(point);
}

static void test_point_rotate_around_1() {
    Point point = point_new(1, 0);
    Point center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 0));
    g_assert(double_equals(point->y, 1));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_2() {
    Point point = point_new(0, 1);
    Point center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, -1));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_3() {
    Point point = point_new(-1, 0);
    Point center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 0));
    g_assert(double_equals(point->y, -1));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_4() {
    Point point = point_new(0, -1);
    Point center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_5() {
    Point point1 = point_new(1, 0);
    Point point2 = point_new(1, 0);
    Point center = point_new(0, 0);
    point2->w *= 2;
    point2->x *= 2;
    point2->y *= 2;
    point_rotate_around(point1, center, 90);
    point_rotate_around(point2, center, 90);
    g_assert(point_equals(point1, point2));
    point_release(center);
    point_release(point1);
    point_release(point2);
}

static void test_point_rotate_around_6() {
    Point point = point_new(0, 0);
    Point center = point_new(1, 1);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 2));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_midpoint_between_points_1() {
    Point point1 = point_new(0, 0);
    Point point2= point_new(2, 2);
    Point midpoint = midpoint_between_points(point1, point2);
    g_assert(double_equals(midpoint->w, 2));
    g_assert(double_equals(midpoint->x, 2));
    g_assert(double_equals(midpoint->y, 2));
    point_release(point1);
    point_release(point2);
    point_release(midpoint);
}

static void test_point_is_infinite_1() {
    Point point = point_new(1, 1);
    g_assert_false(point_is_infinite(point));
    point_release(point);
}

static void test_point_is_infinite_2() {
    Point point = point_new(1, 1);
    point->w = 0;
    g_assert(point_is_infinite(point));
    point_release(point);
}

static void test_point_normalize_1() {
    Point point = memalloc(sizeof(*point));
    point->w = 2;
    point->x = 2;
    point->y = 4;
    point_normalize(point);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 2));
    point_release(point);
}

static void test_line_new_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line = line_new(point1, point2);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, -1));
    g_assert(double_equals(line->y, 1));
    point_release(point1);
    point_release(point2);
    line_release(line);
}

static void test_line_new_2() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Line line = line_new(point1, point2);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, 0));
    g_assert(double_equals(line->y, 1));
    point_release(point1);
    point_release(point2);
    line_release(line);
}

static void test_line_new_3() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(0, 1);
    Line line = line_new(point1, point2);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, -1));
    g_assert(double_equals(line->y, 0));
    point_release(point1);
    point_release(point2);
    line_release(line);
}

static void test_line_release_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line = line_new(point1, point2);
    point_release(point1);
    point_release(point2);
    line_release(line);
}

static void test_line_equals_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(2, 2);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert(line_equals(line1, line2));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line1);
    line_release(line2);
}

static void test_line_equals_2() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(-1, -1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert_false(line_equals(line1, line2));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line1);
    line_release(line2);
}

static void test_line_dup_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_dup(line1);
    g_assert(double_equals(line1->w, line2->w));
    g_assert(double_equals(line1->x, line2->x));
    g_assert(double_equals(line1->y, line2->y));
    point_release(point1);
    point_release(point2);
    line_release(line1);
    line_release(line2);
}

static void test_line_to_str_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line = line_new(point1, point2);
    char *str = line_to_str(line, 2);
    g_assert_cmpstr(str, ==, "<< Line: 0.00, -1.00, 1.00 >>");
    free(str);
    point_release(point1);
    point_release(point2);
    line_release(line);
}

static void test_line_from_str_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_from_str("<< Line: 0.00, -1.00, 1.00 >>");
    g_assert(line_equals(line1, line2));
    point_release(point1);
    point_release(point2);
    line_release(line1);
    line_release(line2);
}

static void test_line_perpendicular_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_perpendicular(line1, point1);
    g_assert(double_equals(line2->w, 0));
    g_assert(double_equals(line2->x, -1));
    g_assert(double_equals(line2->y, -1));
    point_release(point1);
    point_release(point2);
    line_release(line1);
    line_release(line2);
}

static void test_line_intersection_1() {
    Point point1 = point_new(0, 1);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Line line1 = line_new(point1, point3);
    Line line2 = line_new(point2, point3);
    Point intersection = line_intersection(line1, line2);
    g_assert(point_equals(intersection, point3));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(intersection);
    line_release(line1);
    line_release(line2);
}

static void test_line_intersection_2() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(0, 1);
    Point point4 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point3, point4);
    Point intersection = line_intersection(line1, line2);
    g_assert(point_is_infinite(intersection));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
    point_release(intersection);
    line_release(line1);
    line_release(line2);
}

static void test_line_normalize_1() {
    Line line = memalloc(sizeof(*line));
    line->w = 1;
    line->x = 2;
    line->y = 0;
    line_normalize(line);
    g_assert(double_equals(line->w, 0.5));
    g_assert(double_equals(line->x, 1));
    g_assert(double_equals(line->y, 0));
    line_release(line);
}

static void test_point_is_in_line_1() {
    Point point1 = point_new(1, 0);
    Point point2 = point_new(1, 2);
    Point point3 = point_new(1, 1);
    Line line = line_new(point1, point2);
    g_assert(point_is_in_line(point3, line));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line);
}

static void test_point_is_in_line_2() {
    Point point1 = point_new(1, 0);
    Point point2 = point_new(1, 2);
    Point point3 = point_new(0, 0);
    Line line = line_new(point1, point2);
    g_assert_false(point_is_in_line(point3, line));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line);
}

static void test_point_distance_to_line_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(0, 1);
    Point point3 = point_new(1, 1);
    Line line = line_new(point1, point2);
    g_assert(double_equals(point_distance_to_line(point3, line), 1));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line);
}

static void test_point_distance_to_line_2() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(2, 2);
    Point point3 = point_new(1, 1);
    Line line = line_new(point1, point2);
    g_assert(double_equals(point_distance_to_line(point3, line), 0));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line);
}

static void test_point_distance_to_line_3() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(1, 0);
    Line line = line_new(point1, point2);
    g_assert(double_equals(point_distance_to_line(point3, line), sqrt(2) / 2));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    line_release(line);
}

static void test_angle_between_lines_1() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(0, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 2));
    line_release(line1);
    line_release(line2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
}

static void test_angle_between_lines_2() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(-1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 2));
    line_release(line1);
    line_release(line2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
}

static void test_angle_between_lines_3() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(0, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 4));
    line_release(line1);
    line_release(line2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
}

static void test_angle_between_lines_4() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 1);
    Point point3 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point1, point3);
    g_assert(double_equals(angle_between_lines(line1, line2), 0));
    line_release(line1);
    line_release(line2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
}

static void test_angle_between_lines_5() {
    Point point1 = point_new(0, 0);
    Point point2 = point_new(0, 1);
    Point point3 = point_new(1, 0);
    Point point4 = point_new(1, 1);
    Line line1 = line_new(point1, point2);
    Line line2 = line_new(point3, point4);
    g_assert(double_equals(angle_between_lines(line1, line2), 0));
    line_release(line1);
    line_release(line2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
}

static void test_circle_new_1() {
    Point center = point_new(1, 1);
    Circle circle = circle_new(center, 1);
    g_assert(circle->center != center);
    g_assert(point_equals(circle->center, center));
    g_assert(double_equals(circle->radius, 1));
    point_release(center);
    circle_release(circle);
}

static void test_circle_release_1() {
    Point center = point_new(1, 1);
    Circle circle = circle_new(center, 1);
    point_release(center);
    circle_release(circle);
}

static void test_circle_equals_1() {
    Point center = point_new(1, 1);
    Circle circle1 = circle_new(center, 1);
    Circle circle2 = circle_new(center, 1);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 1);
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_2() {
    Point center = point_new(1, 1);
    Circle circle1 = circle_new(center, 1);
    Circle circle2 = circle_new(center, 2);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_3() {
    Point center1 = point_new(1, 1);
    Point center2 = point_new(1, 2);
    Circle circle1 = circle_new(center1, 1);
    Circle circle2 = circle_new(center2, 1);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    point_release(center1);
    point_release(center2);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_4() {
    Point center1 = point_new(1, 1);
    Point center2 = point_new(2, 1);
    Circle circle1 = circle_new(center1, 1);
    Circle circle2 = circle_new(center2, 1);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    point_release(center1);
    point_release(center2);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_dup_1() {
    Point center = point_new(1, 1);
    Circle circle1 = circle_new(center, 1);
    Circle circle2 = circle_dup(circle1);
    g_assert(point_equals(circle2->center, center));
    g_assert(double_equals(circle2->radius, 1));
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_to_str_1() {
    Point center = point_new(1, 2);
    Circle circle = circle_new(center, 3);
    char *str = circle_to_str(circle, 2);
    g_assert_cmpstr(str, ==, "<< Circle: 1.00, 2.00, 3.00 >>");
    free(str);
    point_release(center);
    circle_release(circle);
}

static void test_circle_from_str_1() {
    Point center = point_new(1, 2);
    Circle circle1 = circle_new(center, 3);
    Circle circle2 = circle_from_str("<< Circle: 1.00, 2.00, 3.00 >>");
    g_assert(circle_equals(circle1, circle2));
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_center_1() {
    Point center1 = point_new(1, 1);
    Circle circle = circle_new(center1, 1);
    Point center2 = circle_center(circle);
    g_assert(point_equals(center1, center2));
    g_assert(center1 != center2);
    point_release(center1);
    point_release(center2);
    circle_release(circle);
}

static void test_circle_center_x_1() {
    Point center = point_new(1, 2);
    Circle circle = circle_new(center, 3);
    g_assert(double_equals(circle_center_x(circle), 1));
    point_release(center);
    circle_release(circle);
}

static void test_circle_center_y_1() {
    Point center = point_new(1, 2);
    Circle circle = circle_new(center, 3);
    g_assert(double_equals(circle_center_y(circle), 2));
    point_release(center);
    circle_release(circle);
}

static void test_circle_radius_1() {
    Point center = point_new(1, 2);
    Circle circle = circle_new(center, 3);
    g_assert(double_equals(circle_radius(circle), 3));
    point_release(center);
    circle_release(circle);
}

static void test_circle_translate_1() {
    Point center = point_new(1, 1);
    Point new_center = point_new(2, 2);
    Vector vector = vector_new(1, 1);
    Circle circle = circle_new(center, 1);
    circle_translate(circle, vector);
    g_assert(point_equals(circle->center, new_center));
    g_assert(double_equals(circle->radius, 1));
    point_release(center);
    point_release(new_center);
    vector_release(vector);
    circle_release(circle);
}

static void test_point_is_in_circle_1() {
    Point point = point_new(2, 2);
    Point center = point_new(1, 1);
    Circle circle = circle_new(center, 1);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 0);
    point_release(center);
    point_release(point);
    circle_release(circle);
}

static void test_point_is_in_circle_2() {
    Point point = point_new(1, 1);
    Point center = point_new(1, 1);
    Circle circle = circle_new(center, 1);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 1);
    point_release(center);
    point_release(point);
    circle_release(circle);
}

static void test_point_is_in_circle_3() {
    Point point = point_new(0, 1);
    Point center = point_new(1, 1);
    Circle circle = circle_new(center, 1);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 0);
    point_release(center);
    point_release(point);
    circle_release(circle);
}

static void test_triangle_new_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert(a != triangle->a);
    g_assert(point_equals(a, triangle->a));
    g_assert(b != triangle->b);
    g_assert(point_equals(b, triangle->b));
    g_assert(c != triangle->c);
    g_assert(point_equals(c, triangle->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_release_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_dup_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle1 = triangle_new(a, b, c);
    Triangle triangle2 = triangle_dup(triangle1);
    g_assert(triangle1 != triangle2);
    g_assert(triangle1->a != triangle2->a);
    g_assert(point_equals(triangle1->a, triangle2->a));
    g_assert(triangle1->b != triangle2->b);
    g_assert(point_equals(triangle1->b, triangle2->b));
    g_assert(triangle1->c != triangle2->c);
    g_assert(point_equals(triangle1->c, triangle2->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_points_1() {
    List points1 = list_new();
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    list_append(points1, a);
    list_append(points1, b);
    list_append(points1, c);
    Triangle triangle = triangle_new(a, b, c);
    List points2 = triangle_points(triangle);
    g_assert(list_equals_cmp(points1, points2,
                             (int (*)(void *, void *)) point_equals));
    list_release(points1);
    list_full_release(points2, (void (*)(void *)) point_release);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_translate_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    Vector vector = vector_new(1, 1);
    triangle_translate(triangle, vector);
    g_assert(double_equals(point_x(a) + 1, point_x(triangle->a)));
    g_assert(double_equals(point_y(a) + 1, point_y(triangle->a)));
    g_assert(double_equals(point_x(b) + 1, point_x(triangle->b)));
    g_assert(double_equals(point_y(b) + 1, point_y(triangle->b)));
    g_assert(double_equals(point_x(c) + 1, point_x(triangle->c)));
    g_assert(double_equals(point_y(c) + 1, point_y(triangle->c)));
    vector_release(vector);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_rotate_around_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point center = point_new(1, 1);
    Triangle triangle = triangle_new(a, b, c);
    triangle_rotate_around(triangle, center, 0);
    g_assert(double_equals(point_x(triangle->a), 0));
    g_assert(double_equals(point_y(triangle->a), 0));
    g_assert(double_equals(point_x(triangle->b), 1));
    g_assert(double_equals(point_y(triangle->b), 0));
    g_assert(double_equals(point_x(triangle->c), 0));
    g_assert(double_equals(point_y(triangle->c), 1));
    triangle_release(triangle);
    point_release(center);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_rotate_around_2() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point center = point_new(1, 1);
    Triangle triangle = triangle_new(a, b, c);
    triangle_rotate_around(triangle, center, 90);
    g_assert(double_equals(point_x(triangle->a), 2));
    g_assert(double_equals(point_y(triangle->a), 0));
    g_assert(double_equals(point_x(triangle->b), 2));
    g_assert(double_equals(point_y(triangle->b), 1));
    g_assert(double_equals(point_x(triangle->c), 1));
    g_assert(double_equals(point_y(triangle->c), 0));
    triangle_release(triangle);
    point_release(center);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_rotate_around_3() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point center = point_new(1, 1);
    Triangle triangle = triangle_new(a, b, c);
    triangle_rotate_around(triangle, center, 180);
    g_assert(double_equals(point_x(triangle->a), 2));
    g_assert(double_equals(point_y(triangle->a), 2));
    g_assert(double_equals(point_x(triangle->b), 1));
    g_assert(double_equals(point_y(triangle->b), 2));
    g_assert(double_equals(point_x(triangle->c), 2));
    g_assert(double_equals(point_y(triangle->c), 1));
    triangle_release(triangle);
    point_release(center);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_orientation_2() {
    Point a = point_new(0, 0);
    Point b = point_new(0, 1);
    Point c = point_new(1, 0);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, -1);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_orientation_3() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(2, 0);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_area_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert(double_equals(triangle_area(triangle), 0.5));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_1() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(a, triangle), ==, 0);
    g_assert_cmpint(point_is_in_triangle(b, triangle), ==, 0);
    g_assert_cmpint(point_is_in_triangle(c, triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_2() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point point = point_new(0.1, 0.1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(point);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_3() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point point = point_new(1, 1);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(point);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_4() {
    Point a = point_new(0, 0);
    Point b = point_new(1, 0);
    Point c = point_new(0, 1);
    Point point = point_new(0.5, 0);
    Triangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(point);
    triangle_release(triangle);
}

static void test_polygon_new_1() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert(polygon->points != points);
    g_assert(list_equals_cmp(polygon->points, points,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_new_2() {
    List points1 = list_new();
    List points2 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    list_append(points2, point2);
    list_append(points2, point3);
    list_append(points2, point1);
    list_append(points2, point4);
    Polygon polygon = polygon_new(points2);
    g_assert(list_equals_cmp(polygon->points, points1,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_release(points1);
    list_release(points2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
}

static void test_polygon_release_1() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_equals_1() {
    List points1 = list_new();
    List points2 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    Point point5 = point_new(0, 0.5);
    list_append(points1, point1);
    list_append(points2, point1);
    list_append(points1, point2);
    list_append(points2, point2);
    list_append(points1, point3);
    list_append(points2, point3);
    list_append(points1, point4);
    list_append(points2, point5);
    Polygon polygon1 = polygon_new(points1);
    Polygon polygon2 = polygon_new(points2);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 0);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_release(points1);
    list_release(points2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
    point_release(point5);
}

static void test_polygon_equals_2() {
    List points1 = list_new();
    List points2 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points2, point1);
    list_append(points1, point2);
    list_append(points2, point2);
    list_append(points1, point3);
    list_append(points2, point3);
    list_append(points1, point4);
    list_append(points2, point4);
    Polygon polygon1 = polygon_new(points1);
    Polygon polygon2 = polygon_new(points2);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 1);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_release(points1);
    list_release(points2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
}

static void test_polygon_equals_3() {
    List points1 = list_new();
    List points2 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points2, point4);
    list_append(points1, point2);
    list_append(points2, point3);
    list_append(points1, point3);
    list_append(points2, point2);
    list_append(points1, point4);
    list_append(points2, point1);
    Polygon polygon1 = polygon_new(points1);
    Polygon polygon2 = polygon_new(points2);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 1);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_release(points1);
    list_release(points2);
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
}

static void test_polygon_dup_1() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon1 = polygon_new(points);
    Polygon polygon2 = polygon_dup(polygon1);
    g_assert(polygon1->points != polygon2->points);
    g_assert(list_equals_cmp(polygon1->points, polygon2->points,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_points_1() {
    List points1 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    Polygon polygon = polygon_new(points1);
    List points2 = polygon_points(polygon);
    g_assert(points2 != polygon->points);
    g_assert(list_equals_cmp(polygon->points, points2,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_translate_1() {
    List points1 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    Polygon polygon1 = polygon_new(points1);
    List points2 = list_new();
    Point point5 = point_new(1, 1);
    Point point6 = point_new(2, 1);
    Point point7 = point_new(2, 2);
    Point point8 = point_new(1, 2);
    list_append(points2, point5);
    list_append(points2, point6);
    list_append(points2, point7);
    list_append(points2, point8);
    Polygon polygon2 = polygon_new(points2);
    Vector vector = vector_new(1, 1);
    polygon_translate(polygon1, vector);
    g_assert(polygon_equals(polygon1, polygon2));
    vector_release(vector);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_rotate_around_1() {
    Point center = point_new(1, 1);
    List points1 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    Polygon polygon1 = polygon_new(points1);
    List points2 = list_new();
    Point point5 = point_new(0, 0);
    Point point6 = point_new(1, 0);
    Point point7 = point_new(1, 1);
    Point point8 = point_new(0, 1);
    list_append(points2, point5);
    list_append(points2, point6);
    list_append(points2, point7);
    list_append(points2, point8);
    Polygon polygon2 = polygon_new(points2);
    polygon_rotate_around(polygon1, center, 0);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_rotate_around_2() {
    Point center = point_new(0.5, 0.5);
    List points1 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    Polygon polygon1 = polygon_new(points1);
    List points2 = list_new();
    Point point5 = point_new(0, 0);
    Point point6 = point_new(1, 0);
    Point point7 = point_new(1, 1);
    Point point8 = point_new(0, 1);
    list_append(points2, point5);
    list_append(points2, point6);
    list_append(points2, point7);
    list_append(points2, point8);
    Polygon polygon2 = polygon_new(points2);
    polygon_rotate_around(polygon1, center, 90);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_rotate_around_3() {
    Point center = point_new(1, 1);
    List points1 = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points1, point1);
    list_append(points1, point2);
    list_append(points1, point3);
    list_append(points1, point4);
    Polygon polygon1 = polygon_new(points1);
    List points2 = list_new();
    Point point5 = point_new(1, 1);
    Point point6 = point_new(2, 1);
    Point point7 = point_new(2, 2);
    Point point8 = point_new(1, 2);
    list_append(points2, point5);
    list_append(points2, point6);
    list_append(points2, point7);
    list_append(points2, point8);
    Polygon polygon2 = polygon_new(points2);
    polygon_rotate_around(polygon1, center, 180);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_area_1() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert(double_equals(polygon_area(polygon), 1));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_area_2() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    Polygon polygon = polygon_new(points);
    g_assert(double_equals(polygon_area(polygon), 0.5));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_point_is_in_polygon_1() {
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert_cmpint(point_is_in_polygon(polygon, point1), ==, 0);
    g_assert_cmpint(point_is_in_polygon(polygon, point2), ==, 0);
    g_assert_cmpint(point_is_in_polygon(polygon, point3), ==, 0);
    g_assert_cmpint(point_is_in_polygon(polygon, point4), ==, 0);
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_point_is_in_polygon_2() {
    Point point = point_new(2, 2);
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert_cmpint(point_is_in_polygon(polygon, point), ==, 0);
    polygon_release(polygon);
    point_release(point);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_point_is_in_polygon_3() {
    Point point = point_new(0.5, 0.5);
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert_cmpint(point_is_in_polygon(polygon, point), ==, 1);
    polygon_release(polygon);
    point_release(point);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_point_is_in_polygon_4() {
    Point point = point_new(0.5, 0);
    List points = list_new();
    Point point1 = point_new(0, 0);
    Point point2 = point_new(1, 0);
    Point point3 = point_new(1, 1);
    Point point4 = point_new(0, 1);
    list_append(points, point1);
    list_append(points, point2);
    list_append(points, point3);
    list_append(points, point4);
    Polygon polygon = polygon_new(points);
    g_assert_cmpint(point_is_in_polygon(polygon, point), ==, 0);
    polygon_release(polygon);
    point_release(point);
    list_full_release(points, (void (*)(void *)) point_release);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/gc/deg_to_rad", test_deg_to_rad_1);
    g_test_add_func("/gc/vector_new", test_vector_new_1);
    g_test_add_func("/gc/vector_release", test_vector_release_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_2);
    g_test_add_func("/gc/vector_dup", test_vector_dup_1);
    g_test_add_func("/gc/vector_to_str", test_vector_to_str_1);
    g_test_add_func("/gc/vector_from_str", test_vector_from_str_1);
    g_test_add_func("/gc/vector_x", test_vector_x_1);
    g_test_add_func("/gc/vector_y", test_vector_y_1);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_1);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_2);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_1);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_2);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_3);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_4);
    g_test_add_func("/gc/point_new", test_point_new_1);
    g_test_add_func("/gc/point_release", test_point_release_1);
    g_test_add_func("/gc/point_equals", test_point_equals_1);
    g_test_add_func("/gc/point_equals", test_point_equals_2);
    g_test_add_func("/gc/point_equals", test_point_equals_3);
    g_test_add_func("/gc/point_dup", test_point_dup_1);
    g_test_add_func("/gc/point_to_str", test_point_to_str_1);
    g_test_add_func("/gc/point_from_str", test_point_from_str_1);
    g_test_add_func("/gc/point_x", test_point_x_1);
    g_test_add_func("/gc/point_x", test_point_x_2);
    g_test_add_func("/gc/point_y", test_point_y_1);
    g_test_add_func("/gc/point_y", test_point_y_2);
    g_test_add_func("/gc/point_translate", test_point_translate_1);
    g_test_add_func("/gc/point_translate", test_point_translate_2);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_1);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_2);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_3);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_4);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_5);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_6);
    g_test_add_func("/gc/midpoint_between_points", test_midpoint_between_points_1);
    g_test_add_func("/gc/point_is_infinite", test_point_is_infinite_1);
    g_test_add_func("/gc/point_is_infinite", test_point_is_infinite_2);
    g_test_add_func("/gc/point_normalize", test_point_normalize_1);
    g_test_add_func("/gc/line_new", test_line_new_1);
    g_test_add_func("/gc/line_new", test_line_new_2);
    g_test_add_func("/gc/line_new", test_line_new_3);
    g_test_add_func("/gc/line_release", test_line_release_1);
    g_test_add_func("/gc/line_equals", test_line_equals_1);
    g_test_add_func("/gc/line_equals", test_line_equals_2);
    g_test_add_func("/gc/line_dup", test_line_dup_1);
    g_test_add_func("/gc/line_to_str", test_line_to_str_1);
    g_test_add_func("/gc/line_from_str", test_line_from_str_1);
    g_test_add_func("/gc/line_perpendicular", test_line_perpendicular_1);
    g_test_add_func("/gc/line_intersection", test_line_intersection_1);
    g_test_add_func("/gc/line_intersection", test_line_intersection_2);
    g_test_add_func("/gc/line_normalize", test_line_normalize_1);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_1);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_2);
    g_test_add_func("/gc/point_distance_to_line",
                    test_point_distance_to_line_1);
    g_test_add_func("/gc/point_distance_to_line",
                    test_point_distance_to_line_2);
    g_test_add_func("/gc/point_distance_to_line",
                    test_point_distance_to_line_3);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_1);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_2);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_3);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_4);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_5);
    g_test_add_func("/gc/circle_new", test_circle_new_1);
    g_test_add_func("/gc/circle_release", test_circle_release_1);
    g_test_add_func("/gc/circle_equals", test_circle_equals_1);
    g_test_add_func("/gc/circle_equals", test_circle_equals_2);
    g_test_add_func("/gc/circle_equals", test_circle_equals_3);
    g_test_add_func("/gc/circle_equals", test_circle_equals_4);
    g_test_add_func("/gc/circle_dup", test_circle_dup_1);
    g_test_add_func("/gc/circle_to_str", test_circle_to_str_1);
    g_test_add_func("/gc/circle_from_str", test_circle_from_str_1);
    g_test_add_func("/gc/circle_center", test_circle_center_1);
    g_test_add_func("/gc/circle_center_x", test_circle_center_x_1);
    g_test_add_func("/gc/circle_center_y", test_circle_center_y_1);
    g_test_add_func("/gc/circle_radius", test_circle_radius_1);
    g_test_add_func("/gc/circle_translate", test_circle_translate_1);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_1);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_2);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_3);
    g_test_add_func("/gc/triangle_new", test_triangle_new_1);
    g_test_add_func("/gc/triangle_release", test_triangle_release_1);
    g_test_add_func("/gc/triangle_dup", test_triangle_dup_1);
    g_test_add_func("/gc/triangle_points", test_triangle_points_1);
    g_test_add_func("/gc/triangle_translate", test_triangle_translate_1);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_1);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_2);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_3);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_1);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_2);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_3);
    g_test_add_func("/gc/triangle_area", test_triangle_area_1);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_1);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_2);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_3);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_4);
    g_test_add_func("/gc/polygon_new", test_polygon_new_1);
    g_test_add_func("/gc/polygon_new", test_polygon_new_2);
    g_test_add_func("/gc/polygon_release", test_polygon_release_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_2);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_3);
    g_test_add_func("/gc/polygon_dup", test_polygon_dup_1);
    g_test_add_func("/gc/polygon_points", test_polygon_points_1);
    g_test_add_func("/gc/polygon_translate", test_polygon_translate_1);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_1);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_2);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_3);
    g_test_add_func("/gc/polygon_area", test_polygon_area_1);
    g_test_add_func("/gc/polygon_area", test_polygon_area_2);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_1);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_2);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_3);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_4);
    return g_test_run();
}

