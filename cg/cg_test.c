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
    CGVector vector = vector_new(2, 3);
    g_assert(vector != NULL);
    g_assert(double_equals(vector->x, 2));
    g_assert(double_equals(vector->y, 3));
    vector_release(vector);
}

static void test_vector_from_point_to_point_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGVector vector1 = vector_from_point_to_point(a, b);
    CGVector vector2 = vector_from_point_to_point(b, a);
    g_assert(double_equals(vector1->x, 1));
    g_assert(double_equals(vector1->y, 1));
    g_assert(double_equals(vector2->x, -1));
    g_assert(double_equals(vector2->y, -1));
    vector_release(vector1);
    vector_release(vector2);
    point_release(a);
    point_release(b);
}

static void test_vector_release_1() {
    CGVector vector = vector_new(2, 3);
    vector_release(vector);
}

static void test_vector_equals_1() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(1, 1);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 1);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_equals_2() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(2, 2);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 0);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dup_1() {
    CGVector vector1 = vector_new(2, 3);
    CGVector vector2 = vector_dup(vector1);
    g_assert(vector1 != vector2);
    g_assert(double_equals(vector1->x, vector2->x));
    g_assert(double_equals(vector1->y, vector2->y));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_to_str_1() {
    char *vector_str = (char *) "<< Vector: (1.25, 2.00) >>";
    CGVector vector = vector_new(1.25, 2);
    char *str = vector_to_str(vector, 2);
    g_assert_cmpstr(str, ==, vector_str);
    free(str);
    vector_release(vector);
}

static void test_vector_from_str_1() {
    char *vector_str = (char *) "<< Vector: (1.25, 2.00) >>";
    CGVector vector1 = vector_from_str(vector_str);
    CGVector vector2 = vector_new(1.25, 2.00);
    g_assert(vector_equals(vector1, vector2));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_x_1() {
    CGVector vector = vector_new(1, 2);
    g_assert(double_equals(vector_x(vector), 1));
    vector_release(vector);
}

static void test_vector_y_1() {
    CGVector vector = vector_new(1, 2);
    g_assert(double_equals(vector_y(vector), 2));
    vector_release(vector);
}

static void test_vector_right_perpendicular_1() {
    CGVector vector = vector_new(1, 2);
    CGVector perpendicular = vector_right_perpendicular(vector);
    g_assert(double_equals(perpendicular->x, 2));
    g_assert(double_equals(perpendicular->y, -1));
    vector_release(vector);
    vector_release(perpendicular);
}

static void test_vector_left_perpendicular_1() {
    CGVector vector = vector_new(1, 2);
    CGVector perpendicular = vector_left_perpendicular(vector);
    g_assert(double_equals(perpendicular->x, -2));
    g_assert(double_equals(perpendicular->y, 1));
    vector_release(vector);
    vector_release(perpendicular);
}

static void test_vector_normalize_1() {
    CGVector vector = vector_new(2, 0);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_vector_normalize_2() {
    CGVector vector = vector_new(1, 1);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 1 / sqrt(2)));
    g_assert(double_equals(vector->y, 1 / sqrt(2)));
    vector_release(vector);
}

static void test_vector_reverse_1() {
    CGVector vector = vector_new(2, -3);
    vector_reverse(vector);
    g_assert(double_equals(vector->x, -2));
    g_assert(double_equals(vector->y, 3));
    vector_release(vector);
}

static void test_vector_sum_1() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(0, 0);
    vector_sum(vector1, vector2);
    g_assert(double_equals(vector1->x, 1));
    g_assert(double_equals(vector1->y, 1));
    g_assert(double_equals(vector2->x, 0));
    g_assert(double_equals(vector2->y, 0));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_sum_2() {
    CGVector vector1 = vector_new(0, 0);
    CGVector vector2 = vector_new(1, 1);
    vector_sum(vector1, vector2);
    g_assert(double_equals(vector1->x, 1));
    g_assert(double_equals(vector1->y, 1));
    g_assert(double_equals(vector2->x, 1));
    g_assert(double_equals(vector2->y, 1));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_subtract_1() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(0, 0);
    vector_subtract(vector1, vector2);
    g_assert(double_equals(vector1->x, 1));
    g_assert(double_equals(vector1->y, 1));
    g_assert(double_equals(vector2->x, 0));
    g_assert(double_equals(vector2->y, 0));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_subtract_2() {
    CGVector vector1 = vector_new(0, 0);
    CGVector vector2 = vector_new(1, 1);
    vector_subtract(vector1, vector2);
    g_assert(double_equals(vector1->x, -1));
    g_assert(double_equals(vector1->y, -1));
    g_assert(double_equals(vector2->x, 1));
    g_assert(double_equals(vector2->y, 1));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_multiply_1() {
    CGVector vector = vector_new(1, 1);
    vector_multiply(vector, 0);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_vector_multiply_2() {
    CGVector vector = vector_new(1, 1);
    vector_multiply(vector, 2);
    g_assert(double_equals(vector->x, 2));
    g_assert(double_equals(vector->y, 2));
    vector_release(vector);
}

static void test_vector_magnitude_1() {
    CGVector vector = vector_new(0, 0);
    g_assert(double_equals(vector_magnitude(vector), 0));
    vector_release(vector);
}

static void test_vector_magnitude_2() {
    CGVector vector = vector_new(3, 4);
    g_assert(double_equals(vector_magnitude(vector), 5));
    vector_release(vector);
}

static void test_vector_dot_1() {
    CGVector vector = vector_new(0, 1);
    g_assert(double_equals(vector_dot(vector, vector), 1));
    vector_release(vector);
}

static void test_vector_dot_2() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(0, -1);
    g_assert(double_equals(vector_dot(vector1, vector2), -1));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dot_3() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 0);
    g_assert(double_equals(vector_dot(vector1, vector2), 0));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dot_4() {
    CGVector vector1 = vector_new(-1, 1);
    CGVector vector2 = vector_new(1, 0);
    double magnitude1 = vector_magnitude(vector1);
    double magnitude2 = vector_magnitude(vector2);
    double dot = magnitude1 * magnitude2 * cos(deg_to_rad(135));
    g_assert(double_equals(vector_dot(vector1, vector2), dot));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dot_5() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(1, 0);
    double magnitude1 = vector_magnitude(vector1);
    double magnitude2 = vector_magnitude(vector2);
    double dot = magnitude1 * magnitude2 * cos(deg_to_rad(45));
    g_assert(double_equals(vector_dot(vector1, vector2), dot));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_angle_between_vectors_1() {
    CGVector vector = vector_new(1, 1);
    g_assert(double_equals(angle_between_vectors(vector, vector), 0));
    vector_release(vector);
}

static void test_angle_between_vectors_2() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 0);
    g_assert(double_equals(angle_between_vectors(vector1, vector2), M_PI / 2));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_angle_between_vectors_3() {
    CGVector vector1 = vector_new(1, 0);
    CGVector vector2 = vector_new(-1, 0);
    g_assert(double_equals(angle_between_vectors(vector1, vector2), M_PI));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_angle_between_vectors_4() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 1);
    g_assert(double_equals(angle_between_vectors(vector1, vector2), M_PI / 4));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_angle_between_vectors_5() {
    CGVector vector1 = vector_new(1, 0);
    CGVector vector2 = vector_new(-1, 1);
    g_assert(double_equals(angle_between_vectors(vector1, vector2), deg_to_rad(135)));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_rotate_1() {
    CGVector vector = vector_new(1, 0);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 1));
    vector_release(vector);
}

static void test_vector_rotate_2() {
    CGVector vector = vector_new(0, 1);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, -1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_vector_rotate_3() {
    CGVector vector = vector_new(-1, 0);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, -1));
    vector_release(vector);
}

static void test_vector_rotate_4() {
    CGVector vector = vector_new(0, -1);
    vector_rotate(vector, 90);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_point_new_1() {
    CGPoint point = point_new(2, 3);
    g_assert(point != NULL);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 2));
    g_assert(double_equals(point->y, 3));
    point_release(point);
}

static void test_point_release_1() {
    CGPoint point = point_new(2, 3);
    point_release(point);
}

static void test_point_equals_1() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(1, 1);
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_2() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(2, 2);
    g_assert_cmpint(point_equals(point1, point2), ==, 0);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_3() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(2, 2);
    point1->w = 1;
    point2->w = 2;
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_dup_1() {
    CGPoint point1 = point_new(2, 3);
    CGPoint point2 = point_dup(point1);
    g_assert(point1 != point2);
    g_assert(double_equals(point1->w, point2->w));
    g_assert(double_equals(point1->x, point2->x));
    g_assert(double_equals(point1->y, point2->y));
    point_release(point1);
    point_release(point2);
}

static void test_point_to_str_1() {
    char *p_str = (char *) "<< Point: (1.25, 2.00) >>";
    CGPoint point = point_new(1.25, 2);
    char *str = point_to_str(point, 2);
    g_assert_cmpstr(str, ==, p_str);
    free(str);
    point_release(point);
}

static void test_point_from_str_1() {
    char *p_str = (char *) "<< Point: (1.25, 2.00) >>";
    CGPoint point1 = point_from_str(p_str);
    CGPoint point2 = point_new(1.25, 2.00);
    g_assert(point_equals(point1, point2));
    point_release(point1);
    point_release(point2);
}

static void test_point_x_1() {
    CGPoint point = point_new(1, 2);
    g_assert(double_equals(point_x(point), 1));
    point_release(point);
}

static void test_point_x_2() {
    CGPoint point = point_new(1, 2);
    point->w *= 2;
    point->x *= 2;
    g_assert(double_equals(point_x(point), 1));
    point_release(point);
}

static void test_point_y_1() {
    CGPoint point = point_new(1, 2);
    g_assert(double_equals(point_y(point), 2));
    point_release(point);
}

static void test_point_y_2() {
    CGPoint point = point_new(1, 2);
    point->w *= 2;
    point->y *= 2;
    g_assert(double_equals(point_y(point), 2));
    point_release(point);
}

static void test_point_vector_from_origin_1() {
    CGPoint point = point_new(1, 2);
    CGVector vector = point_vector_from_origin(point);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 2));
    point_release(point);
    vector_release(vector);
}

static void test_point_projection_magnitude_on_axis_1() {
    CGPoint point = point_new(1, 1);
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, 1));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_magnitude_on_axis_2() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, 5));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_magnitude_on_axis_3() {
    CGPoint point = point_new(1, 1);
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, 1));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_magnitude_on_axis_4() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, 5));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_magnitude_on_axis_5() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(0, 2);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, 5));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_magnitude_on_axis_6() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(1, 1);
    vector_normalize(axis);
    double magnitude = point_projection_magnitude_on_axis(point, axis);
    g_assert(double_equals(magnitude, sqrt(50)));
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_1() {
    CGPoint point = point_new(1, 1);
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_2() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 5));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_3() {
    CGPoint point = point_new(1, 1);
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 1));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_4() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 5));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_5() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(0, 2);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 5));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_6() {
    CGPoint point = point_new(5, 5);
    CGVector axis = vector_new(1, 1);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 5));
    g_assert(double_equals(vector->y, 5));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_translate_1() {
    CGVector vector = vector_new(2, 2);
    CGPoint point = point_new(2, 4);
    point_translate(point, vector);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 4));
    g_assert(double_equals(point->y, 6));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_2() {
    CGVector vector = vector_new(2, 2);
    CGPoint point = point_new(2, 4);
    point->w = 2;
    point_translate(point, vector);
    g_assert(double_equals(point->w, 2));
    g_assert(double_equals(point->x, 6));
    g_assert(double_equals(point->y, 8));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_3() {
    CGVector vector = vector_new(0, 0);
    CGPoint point = point_new(1, 1);
    point_translate(point, vector);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 1));
    vector_release(vector);
    point_release(point);
}

static void test_point_rotate_around_1() {
    CGPoint point = point_new(1, 0);
    CGPoint center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 0));
    g_assert(double_equals(point->y, 1));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_2() {
    CGPoint point = point_new(0, 1);
    CGPoint center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, -1));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_3() {
    CGPoint point = point_new(-1, 0);
    CGPoint center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 0));
    g_assert(double_equals(point->y, -1));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_4() {
    CGPoint point = point_new(0, -1);
    CGPoint center = point_new(0, 0);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_5() {
    CGPoint point1 = point_new(1, 0);
    CGPoint point2 = point_new(1, 0);
    CGPoint center = point_new(0, 0);
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
    CGPoint point = point_new(0, 0);
    CGPoint center = point_new(1, 1);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 2));
    g_assert(double_equals(point->y, 0));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_7() {
    CGPoint point = point_new(1, 1);
    CGPoint center = point_new(1, 1);
    point_rotate_around(point, center, 90);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 1));
    point_release(center);
    point_release(point);
}

static void test_point_rotate_around_8() {
    CGPoint point = point_new(1, 1);
    CGPoint center = point_new(0, 0);
    point_rotate_around(point, center, 0);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 1));
    point_release(center);
    point_release(point);
}

static void test_midpoint_between_points_1() {
    CGPoint point1 = point_new(0, 0);
    CGPoint point2= point_new(2, 2);
    CGPoint midpoint = midpoint_between_points(point1, point2);
    g_assert(double_equals(midpoint->w, 2));
    g_assert(double_equals(midpoint->x, 2));
    g_assert(double_equals(midpoint->y, 2));
    point_release(point1);
    point_release(point2);
    point_release(midpoint);
}

static void test_point_normalize_1() {
    CGPoint point = (CGPoint) memalloc(sizeof(*point));
    point->w = 2;
    point->x = 2;
    point->y = 4;
    point_normalize(point);
    g_assert(double_equals(point->w, 1));
    g_assert(double_equals(point->x, 1));
    g_assert(double_equals(point->y, 2));
    point_release(point);
}

static void test_point_distance_to_point_1() {
    CGPoint point1 = point_new(0, 0);
    CGPoint point2 = point_new(1, 0);
    CGPoint point3 = point_new(0, 1);
    CGPoint point4 = point_new(1, 1);
    g_assert(double_equals(point_distance_to_point(point1, point1), 0));
    g_assert(double_equals(point_distance_to_point(point1, point2), 1));
    g_assert(double_equals(point_distance_to_point(point1, point3), 1));
    g_assert(double_equals(point_distance_to_point(point1, point4), sqrt(2)));
    g_assert(double_equals(point_distance_to_point(point2, point2), 0));
    g_assert(double_equals(point_distance_to_point(point2, point3), sqrt(2)));
    g_assert(double_equals(point_distance_to_point(point2, point4), 1));
    g_assert(double_equals(point_distance_to_point(point3, point3), 0));
    g_assert(double_equals(point_distance_to_point(point3, point4), 1));
    g_assert(double_equals(point_distance_to_point(point4, point4), 0));
    point_release(point1);
    point_release(point2);
    point_release(point3);
    point_release(point4);
}

static void test_line_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line = line_new(a, b);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, -1));
    g_assert(double_equals(line->y, 1));
    point_release(a);
    point_release(b);
    line_release(line);
}

static void test_line_new_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGLine line = line_new(a, b);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, 0));
    g_assert(double_equals(line->y, 1));
    point_release(a);
    point_release(b);
    line_release(line);
}

static void test_line_new_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGLine line = line_new(a, b);
    g_assert(double_equals(line->w, 0));
    g_assert(double_equals(line->x, -1));
    g_assert(double_equals(line->y, 0));
    point_release(a);
    point_release(b);
    line_release(line);
}

static void test_line_new_4() {
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(1, 1);
    g_assert(line_new(a, b) == NULL);
    point_release(a);
    point_release(b);
}

static void test_line_release_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line = line_new(a, b);
    point_release(a);
    point_release(b);
    line_release(line);
}

static void test_line_equals_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(2, 2);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert_cmpint(line_equals(line1, line2), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line1);
    line_release(line2);
}

static void test_line_equals_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(-1, -1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert_cmpint(line_equals(line1, line2), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line1);
    line_release(line2);
}

static void test_line_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_dup(line1);
    g_assert(line1 != line2);
    g_assert(double_equals(line1->w, line2->w));
    g_assert(double_equals(line1->x, line2->x));
    g_assert(double_equals(line1->y, line2->y));
    point_release(a);
    point_release(b);
    line_release(line1);
    line_release(line2);
}

static void test_line_to_str_1() {
    char *line_str = (char *) "<< Line: (0.00, -1.00, 1.00) >>";
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line = line_new(a, b);
    char *str = line_to_str(line, 2);
    g_assert_cmpstr(str, ==, line_str);
    free(str);
    point_release(a);
    point_release(b);
    line_release(line);
}

static void test_line_from_str_1() {
    char *line_str = (char *) "<< Line: (0.00, -1.00, 1.00) >>";
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_from_str(line_str);
    g_assert(line_equals(line1, line2));
    point_release(a);
    point_release(b);
    line_release(line1);
    line_release(line2);
}

static void test_line_perpendicular_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_perpendicular(line1, a);
    g_assert(double_equals(line2->w, 0));
    g_assert(double_equals(line2->x, -1));
    g_assert(double_equals(line2->y, -1));
    point_release(a);
    point_release(b);
    line_release(line1);
    line_release(line2);
}

static void test_lines_intersection_1() {
    CGPoint a = point_new(0, 1);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGLine line1 = line_new(a, c);
    CGLine line2 = line_new(b, c);
    CGPoint intersection = lines_intersection(line1, line2);
    g_assert(point_equals(intersection, c));
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(intersection);
    line_release(line1);
    line_release(line2);
}

static void test_lines_intersection_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(c, d);
    CGPoint intersection = lines_intersection(line1, line2);
    g_assert(intersection == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    line_release(line1);
    line_release(line2);
}

static void test_lines_intersection_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0.5, 0);
    CGPoint d = point_new(1.5, 0);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(c, d);
    CGPoint intersection = lines_intersection(line1, line2);
    g_assert(intersection == NULL);
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_line_normalize_1() {
    CGLine line = (CGLine) memalloc(sizeof(*line));
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
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 2);
    CGPoint c = point_new(1, 1);
    CGLine line = line_new(a, b);
    g_assert_cmpint(point_is_in_line(c, line), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_point_is_in_line_2() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 2);
    CGPoint c = point_new(0, 0);
    CGLine line = line_new(a, b);
    g_assert_cmpint(point_is_in_line(c, line), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_point_distance_to_line_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(1, 1);
    CGLine line = line_new(a, b);
    g_assert(double_equals(point_distance_to_line(c, line), 1));
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_point_distance_to_line_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(2, 2);
    CGPoint c = point_new(1, 1);
    CGLine line = line_new(a, b);
    g_assert(double_equals(point_distance_to_line(c, line), 0));
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_point_distance_to_line_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(1, 0);
    CGLine line = line_new(a, b);
    g_assert(double_equals(point_distance_to_line(c, line), sqrt(2) / 2));
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_angle_between_lines_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 2));
    g_assert(double_equals(angle_between_lines(line2, line1), M_PI / 2));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_angle_between_lines_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(-1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 2));
    g_assert(double_equals(angle_between_lines(line2, line1), M_PI / 2));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_angle_between_lines_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(0, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert(double_equals(angle_between_lines(line1, line2), M_PI / 4));
    g_assert(double_equals(angle_between_lines(line2, line1), M_PI / 4));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_angle_between_lines_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert(double_equals(angle_between_lines(line1, line2), 0));
    g_assert(double_equals(angle_between_lines(line2, line1), 0));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_angle_between_lines_5() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(1, 0);
    CGPoint point4 = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(c, point4);
    g_assert(double_equals(angle_between_lines(line1, line2), 0));
    g_assert(double_equals(angle_between_lines(line2, line1), 0));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(point4);
}

static void test_angle_between_lines_6() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 0.5);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(a, c);
    g_assert(double_lt(angle_between_lines(line1, line2), M_PI / 4));
    g_assert(double_lt(angle_between_lines(line2, line1), M_PI / 4));
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_angle_between_lines_7() {
    CGLine line1 = (CGLine) memalloc(sizeof(*line1));
    line1->w = 1;
    line1->x = -1;
    line1->y = 1;
    CGLine line2 = (CGLine) memalloc(sizeof(*line2));
    line2->w = 1;
    line2->x = 1;
    line2->y = 0.5;
    g_assert(double_equals(angle_between_lines(line1, line2), atan2(3, 1)));
    line_release(line1);
    line_release(line2);
}

static void test_segment_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    g_assert(segment->a != a);
    g_assert(segment->b != b);
    g_assert(point_equals(segment->a, a));
    g_assert(point_equals(segment->b, b));
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_new_2() {
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(1, 1);
    g_assert(segment_new(a, b) == NULL);
    point_release(a);
    point_release(b);
}

static void test_segment_release_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    segment_release(segment);
}

static void test_segment_equals_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 1); (0, 0) >>");
    CGSegment segment3 = segment_from_str((char *) "<< Segment: (0, 0); (2, 2) >>");
    g_assert_cmpint(segment_equals(segment1, segment1), ==, 1);
    g_assert_cmpint(segment_equals(segment1, segment2), ==, 0);
    g_assert_cmpint(segment_equals(segment1, segment3), ==, 0);
    segment_release(segment1);
    segment_release(segment2);
    segment_release(segment3);
}

static void test_segment_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_dup(segment1);
    g_assert(segment1 != segment2);
    g_assert(point_equals(segment1->a, segment2->a));
    g_assert(point_equals(segment1->b, segment2->b));
    point_release(a);
    point_release(b);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_to_str_1() {
    char *segment_str = (char *) "<< Segment: (1.00, 2.00); (3.00, 4.00) >>";
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment = segment_new(a, b);
    char *str = segment_to_str(segment, 2);
    g_assert_cmpstr(str, ==, segment_str);
    free(str);
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_from_str_1() {
    char *segment_str = (char *) "<< Segment: (1.00, 2.00); (3.00, 4.00) >>";
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_from_str(segment_str);
    g_assert(segment_equals(segment1, segment2));
    point_release(a);
    point_release(b);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_points_1() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment = segment_new(a, b);
    ADTList points = segment_points(segment);
    g_assert_cmpint(list_size(points), ==, 2);
    g_assert(point_equals((CGPoint) list_at(points, 0), a));
    g_assert(point_equals((CGPoint) list_at(points, 1), b));
    list_full_release(points, (void (*)(void *)) point_release);
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_vector_1() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment = segment_new(a, b);
    CGVector vector1 = segment_vector(segment);
    CGVector vector2 = vector_from_point_to_point(a, b);
    g_assert(vector_equals(vector1, vector2));
    vector_release(vector1);
    vector_release(vector2);
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_line_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGLine line1 = line_new(a, b);
    CGLine line2 = segment_line(segment);
    g_assert(line_equals(line1, line2));
    line_release(line1);
    line_release(line2);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_length_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (3, 0); (0, 4) >>");
    g_assert(double_equals(segment_length(segment), 5));
    segment_release(segment);
}

static void test_segment_translate_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 1); (2, 2) >>");
    CGVector vector = vector_new(1, 1);
    segment_translate(segment1, vector);
    g_assert(segment_equals(segment1, segment2));
    vector_release(vector);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_translate_2() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGVector vector = vector_new(0, 0);
    segment_translate(segment1, vector);
    g_assert(segment_equals(segment1, segment2));
    vector_release(vector);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_projection_on_axis_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (1, 1); (5, 1) >>");
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = segment_projection_on_axis(segment, axis);
    g_assert(double_equals(spoa->min, 1));
    g_assert(double_equals(spoa->max, 5));
    shape_projection_on_axis_release(spoa);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_projection_on_axis_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (1, 1); (5, 1) >>");
    CGVector axis = vector_new(-1, 0);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = segment_projection_on_axis(segment, axis);
    g_assert(double_equals(spoa->min, -5));
    g_assert(double_equals(spoa->max, -1));
    shape_projection_on_axis_release(spoa);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_projection_on_axis_3() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (1, 1); (5, 1) >>");
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = segment_projection_on_axis(segment, axis);
    g_assert(double_equals(spoa->min, 1));
    g_assert(double_equals(spoa->max, 1));
    shape_projection_on_axis_release(spoa);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_projection_on_axis_4() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGVector axis = vector_new(1, 0);
    CGShapeProjectionOnAxis spoa = segment_projection_on_axis(segment, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 1));
    shape_projection_on_axis_release(spoa);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_projection_on_axis_5() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGVector axis = vector_new(0, 1);
    CGShapeProjectionOnAxis spoa = segment_projection_on_axis(segment, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 1));
    shape_projection_on_axis_release(spoa);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_rotate_around_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGPoint center = point_new(0.5, 0.5);
    segment_rotate_around(segment1, center, 0);
    g_assert(segment_equals(segment1, segment2));
    point_release(center);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_rotate_around_2() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 0); (0, 1) >>");
    CGPoint center = point_new(0.5, 0.5);
    segment_rotate_around(segment1, center, 90);
    g_assert(segment_equals(segment1, segment2));
    point_release(center);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_rotate_around_3() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 1); (0, 0) >>");
    CGPoint center = point_new(0.5, 0.5);
    segment_rotate_around(segment1, center, 180);
    g_assert(segment_equals(segment1, segment2));
    point_release(center);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_rotate_around_4() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (2, 2); (1, 1) >>");
    CGPoint center = point_new(1, 1);
    segment_rotate_around(segment1, center, 180);
    g_assert(segment_equals(segment1, segment2));
    point_release(center);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_collision_axes_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (5, 0) >>");
    ADTList collision_axes = segment_collision_axes(segment);
    g_assert_cmpint(list_size(collision_axes), ==, 1);
    CGVector axis = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(axis->x, 0));
    g_assert(double_equals(axis->y, -1));
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
    segment_release(segment);
}

static void test_segment_collision_axes_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (0, 5) >>");
    ADTList collision_axes = segment_collision_axes(segment);
    g_assert_cmpint(list_size(collision_axes), ==, 1);
    CGVector vector = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
    segment_release(segment);
}

static void test_segments_intersection_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 0); (0, 1) >>");
    CGPoint intersection = segments_intersection(segment1, segment2);
    g_assert(double_equals(point_x(intersection), 0.5));
    g_assert(double_equals(point_y(intersection), 0.5));
    point_release(intersection);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segments_intersection_2() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 0) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 0); (1, 1) >>");
    CGPoint intersection = segments_intersection(segment1, segment2);
    g_assert(double_equals(point_x(intersection), 1));
    g_assert(double_equals(point_y(intersection), 0));
    point_release(intersection);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segments_intersection_3() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (1, 0) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0.5, 0); (1.5, 0) >>");
    CGPoint intersection = segments_intersection(segment1, segment2);
    g_assert(intersection == NULL);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segments_intersection_4() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (2, 0); (2, 2) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGPoint intersection = segments_intersection(segment1, segment2);
    g_assert(intersection == NULL);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_point_is_in_segment_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(0.5, 0.5);
    CGPoint e = point_new(2, 2);
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    g_assert_cmpint(point_is_in_segment(a, segment), ==, 1);
    g_assert_cmpint(point_is_in_segment(b, segment), ==, 1);
    g_assert_cmpint(point_is_in_segment(c, segment), ==, 0);
    g_assert_cmpint(point_is_in_segment(d, segment), ==, 1);
    g_assert_cmpint(point_is_in_segment(e, segment), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    segment_release(segment);
}

static void test_circle_new_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert(circle->center != center);
    g_assert(point_equals(circle->center, center));
    g_assert(double_equals(circle->radius, 1));
    point_release(center);
    circle_release(circle);
}

static void test_circle_new_2() {
    CGPoint center = point_new(1, 1);
    g_assert(circle_new(center, 0) == NULL);
    point_release(center);
}

static void test_circle_release_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    circle_release(circle);
}

static void test_circle_equals_1() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 1);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_2() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (1, 2); 4 >>");
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_3() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (1, 2); 1 >>");
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_4() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (2, 1); 1 >>");
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_dup_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle1 = circle_new(center, 3);
    CGCircle circle2 = circle_dup(circle1);
    g_assert(circle1 != circle2);
    g_assert(point_equals(circle1->center, circle2->center));
    g_assert(double_equals(circle1->radius, circle2->radius));
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_to_str_1() {
    char *circle_str = (char *) "<< Circle: (1.00, 2.00); 3.00 >>";
    CGPoint center = point_new(1, 2);
    CGCircle circle = circle_new(center, 3);
    char *str = circle_to_str(circle, 2);
    g_assert_cmpstr(str, ==, circle_str);
    free(str);
    point_release(center);
    circle_release(circle);
}

static void test_circle_from_str_1() {
    char *circle_str = (char *) "<< Circle: (1.00, 2.00); 3.00 >>";
    CGPoint center = point_new(1, 2);
    CGCircle circle1 = circle_new(center, 3);
    CGCircle circle2 = circle_from_str(circle_str);
    g_assert(circle_equals(circle1, circle2));
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_center_1() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle = circle_new(center1, 1);
    CGPoint center2 = circle_center(circle);
    g_assert(center1 != center2);
    g_assert(point_equals(center1, center2));
    point_release(center1);
    point_release(center2);
    circle_release(circle);
}

static void test_circle_center_x_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    g_assert(double_equals(circle_center_x(circle), 1));
    circle_release(circle);
}

static void test_circle_center_y_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    g_assert(double_equals(circle_center_y(circle), 2));
    circle_release(circle);
}

static void test_circle_radius_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 2); 3 >>");
    g_assert(double_equals(circle_radius(circle), 3));
    circle_release(circle);
}

static void test_circle_translate_1() {
    CGPoint center = point_new(1, 1);
    CGPoint new_center = point_new(2, 2);
    CGVector vector = vector_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    circle_translate(circle, vector);
    g_assert(point_equals(circle->center, new_center));
    g_assert(double_equals(circle->radius, 1));
    point_release(center);
    point_release(new_center);
    vector_release(vector);
    circle_release(circle);
}

static void test_circle_translate_2() {
    CGPoint center = point_new(1, 1);
    CGPoint new_center = point_new(1, 1);
    CGVector vector = vector_new(0, 0);
    CGCircle circle = circle_new(center, 1);
    circle_translate(circle, vector);
    g_assert(point_equals(circle->center, new_center));
    g_assert(double_equals(circle->radius, 1));
    point_release(center);
    point_release(new_center);
    vector_release(vector);
    circle_release(circle);
}

static void test_circle_projection_on_axis_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = circle_projection_on_axis(circle, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 2));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    circle_release(circle);
}

static void test_circle_projection_on_axis_2() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector axis = vector_new(-1, 0);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = circle_projection_on_axis(circle, axis);
    g_assert(double_equals(spoa->min, -2));
    g_assert(double_equals(spoa->max, 0));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    circle_release(circle);
}

static void test_circle_projection_on_axis_3() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector axis = vector_new(1, 1);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = circle_projection_on_axis(circle, axis);
    g_assert(double_equals(spoa->min, sqrt(2) - 1));
    g_assert(double_equals(spoa->max, sqrt(2) + 1));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    circle_release(circle);
}

static void test_circle_collision_axes_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    ADTList points = list_new();
    list_append(points, point_new(1, 5));
    ADTList collision_axes = circle_collision_axes(circle, points);
    g_assert_cmpint(list_size(collision_axes), ==, 1);
    CGVector axis = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(axis->x, 0));
    g_assert(double_equals(axis->y, 1));
    list_full_release(points, (void (*)(void *)) point_release);
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
    circle_release(circle);
}

static void test_circle_collision_axes_2() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    ADTList points = list_new();
    list_append(points, point_new(5, 1));
    ADTList collision_axes = circle_collision_axes(circle, points);
    g_assert_cmpint(list_size(collision_axes), ==, 1);
    CGVector axis = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(axis->x, 1));
    g_assert(double_equals(axis->y, 0));
    list_full_release(points, (void (*)(void *)) point_release);
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
    circle_release(circle);
}

static void test_point_is_in_circle_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGPoint point = point_new(2, 2);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 0);
    point_release(point);
    circle_release(circle);
}

static void test_point_is_in_circle_2() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGPoint point = point_new(1, 1);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 1);
    point_release(point);
    circle_release(circle);
}

static void test_point_is_in_circle_3() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGPoint point = point_new(0, 1);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 0);
    point_release(point);
    circle_release(circle);
}

static void test_triangle_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
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
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    triangle_release(triangle);
}

static void test_triangle_equals_1() {
    CGTriangle triangle1 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>"
    );
    CGTriangle triangle2 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (1, 1) >>"
    );
    g_assert_cmpint(triangle_equals(triangle1, triangle2), ==, 0);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_equals_2() {
    CGTriangle triangle1 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>"
    );
    CGTriangle triangle2 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>"
    );
    CGTriangle triangle3 = triangle_from_str(
            (char *) "<< Triangle: (1, 0); (0, 0); (0, 1) >>"
    );
    CGTriangle triangle4 = triangle_from_str(
            (char *) "<< Triangle: (1, 0); (0, 1); (0, 0) >>"
    );
    CGTriangle triangle5 = triangle_from_str(
            (char *) "<< Triangle: (0, 1); (0, 0); (1, 0) >>"
    );
    CGTriangle triangle6 = triangle_from_str(
            (char *) "<< Triangle: (0, 1); (1, 0); (0, 0) >>"
    );
    g_assert_cmpint(triangle_equals(triangle1, triangle1), ==, 1);
    g_assert_cmpint(triangle_equals(triangle1, triangle2), ==, 1);
    g_assert_cmpint(triangle_equals(triangle1, triangle3), ==, 1);
    g_assert_cmpint(triangle_equals(triangle1, triangle4), ==, 1);
    g_assert_cmpint(triangle_equals(triangle1, triangle5), ==, 1);
    g_assert_cmpint(triangle_equals(triangle1, triangle6), ==, 1);
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    triangle_release(triangle4);
    triangle_release(triangle5);
    triangle_release(triangle6);
}

static void test_triangle_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGTriangle triangle2 = triangle_dup(triangle1);
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

static void test_triangle_to_str_1() {
    char *triangle_str = (char *) "<< Triangle: (1.0, 2.0); (4.0, 5.0); (7.0, 8.0) >>";
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(4, 5);
    CGPoint c = point_new(7, 8);
    CGTriangle triangle = triangle_new(a, b, c);
    char *str = triangle_to_str(triangle, 1);
    g_assert_cmpstr(str, ==, triangle_str);
    free(str);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_from_str_1() {
    char *triangle_str = (char *) "<< Triangle: (1.0, 2.0); (4.0, 5.0); (7.0, 8.0) >>";
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(4, 5);
    CGPoint c = point_new(7, 8);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGTriangle triangle2 = triangle_from_str(triangle_str);
    g_assert(triangle_equals(triangle1, triangle2));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_points_1() {
    ADTList points1 = list_new();
    list_append(points1, point_new(0, 0));
    list_append(points1, point_new(1, 0));
    list_append(points1, point_new(0, 1));
    CGTriangle triangle = triangle_new((CGPoint) list_at(points1, 0),
                                       (CGPoint) list_at(points1, 1),
                                       (CGPoint) list_at(points1, 2));
    ADTList points2 = triangle_points(triangle);
    g_assert(list_equals_cmp(points1, points2, (int (*)(void *, void *)) point_equals));
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
    triangle_release(triangle);
}

static void test_triangle_translate_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector vector = vector_new(1, 1);
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

static void test_triangle_translate_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector vector = vector_new(0, 0);
    triangle_translate(triangle, vector);
    g_assert(double_equals(point_x(a), point_x(triangle->a)));
    g_assert(double_equals(point_y(a), point_y(triangle->a)));
    g_assert(double_equals(point_x(b), point_x(triangle->b)));
    g_assert(double_equals(point_y(b), point_y(triangle->b)));
    g_assert(double_equals(point_x(c), point_x(triangle->c)));
    g_assert(double_equals(point_y(c), point_y(triangle->c)));
    vector_release(vector);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_rotate_around_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint center = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
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
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint center = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
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
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint center = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
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
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    g_assert_cmpint(triangle_orientation(triangle), ==, 1);
    triangle_release(triangle);
}

static void test_triangle_orientation_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    g_assert_cmpint(triangle_orientation(triangle), ==, -1);
    triangle_release(triangle);
}

static void test_triangle_orientation_3() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (2, 0) >>");
    g_assert_cmpint(triangle_orientation(triangle), ==, 0);
    triangle_release(triangle);
}

static void test_triangle_area_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    g_assert(double_equals(triangle_area(triangle), 0.5));
    triangle_release(triangle);
}

static void test_triangle_projection_on_axis_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 1); (0, 2); (1, 2) >>");
    CGVector axis = vector_new(1, 0);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = triangle_projection_on_axis(triangle, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 1));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    triangle_release(triangle);
}

static void test_triangle_projection_on_axis_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 1); (0, 2); (1, 2) >>");
    CGVector axis = vector_new(0, 1);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = triangle_projection_on_axis(triangle, axis);
    g_assert(double_equals(spoa->min, 1));
    g_assert(double_equals(spoa->max, 2));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    triangle_release(triangle);
}

static void test_triangle_projection_on_axis_3() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 1); (0, 2); (1, 2) >>");
    CGVector axis = vector_new(1, 1);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa = triangle_projection_on_axis(triangle, axis);
    g_assert(double_equals(spoa->min, sqrt(2) / 2));
    g_assert(double_equals(spoa->max, 3 * sqrt(2) / 2));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    triangle_release(triangle);
}

static void test_triangle_collision_axes_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (5, 0); (0, 5) >>");
    ADTList collision_axes = triangle_collision_axes(triangle);
    g_assert_cmpint(list_size(collision_axes), ==, 3);
    CGVector axis = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(axis->x, 0));
    g_assert(double_equals(axis->y, -1));
    axis = (CGVector) list_at(collision_axes, 1);
    g_assert(double_equals(axis->x, sqrt(2) / 2));
    g_assert(double_equals(axis->y, sqrt(2) / 2));
    axis = (CGVector) list_at(collision_axes, 2);
    g_assert(double_equals(axis->x, -1));
    g_assert(double_equals(axis->y, 0));
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(a, triangle), ==, 0);
    g_assert_cmpint(point_is_in_triangle(b, triangle), ==, 0);
    g_assert_cmpint(point_is_in_triangle(c, triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    CGPoint point = point_new(0.1, 0.1);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 1);
    point_release(point);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_3() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    CGPoint point = point_new(1, 1);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 0);
    point_release(point);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_4() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>");
    CGPoint point = point_new(0.5, 0);
    g_assert_cmpint(point_is_in_triangle(point, triangle), ==, 0);
    point_release(point);
    triangle_release(triangle);
}

static void test_polygon_new_1() {
    ADTList points = list_new();
    list_append(points, point_new(0, 0));
    list_append(points, point_new(1, 0));
    list_append(points, point_new(1, 1));
    list_append(points, point_new(0, 1));
    CGPolygon polygon = polygon_new(points);
    g_assert(polygon->points != points);
    g_assert(list_equals_cmp(polygon->points, points, (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_new_2() {
    ADTList points1 = list_new();
    ADTList points2 = list_new();
    list_append(points1, point_new(0, 0));
    list_append(points1, point_new(1, 0));
    list_append(points1, point_new(1, 1));
    list_append(points1, point_new(0.5, 2));
    list_append(points1, point_new(0, 1));
    list_append(points1, point_new(-0.5, 0.1));
    list_append(points2, point_new(0, 1));
    list_append(points2, point_new(1, 1));
    list_append(points2, point_new(0, 0));
    list_append(points2, point_new(-0.5, 0.1));
    list_append(points2, point_new(1, 0));
    list_append(points2, point_new(0.5, 2));
    CGPolygon polygon = polygon_new(points2);
    g_assert(list_equals_cmp(polygon->points, points1,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_new_3() {
    ADTList points1 = list_new();
    list_append(points1, point_new(1, 1));
    list_append(points1, point_new(2, 2));
    g_assert(polygon_new(points1) == NULL);
    ADTList points2 = list_new();
    list_append(points2, point_new(1, 1));
    list_append(points2, point_new(2, 2));
    list_append(points2, point_new(3, 3));
    g_assert(polygon_new(points2) == NULL);
    list_full_release(points1, (void (*)(void *)) point_release);
    list_full_release(points2, (void (*)(void *)) point_release);
}

static void test_polygon_new_triangle_1() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(0, 0);
    CGPoint c = point_new(0, 1);
    CGPolygon polygon = polygon_new_triangle(a, b, c);
    g_assert_cmpint(list_size(polygon->points), ==, 3);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 1)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 2)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 2)), 1));
    polygon_release(polygon);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_polygon_new_rectangle_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_rectangle(lower_left, 1, 2);
    g_assert_cmpint(list_size(polygon->points), ==, 4);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 1)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 2)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 2)), 2));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 3)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 3)), 2));
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_new_square_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    g_assert_cmpint(list_size(polygon->points), ==, 4);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 1)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 2)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 2)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->points, 3)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->points, 3)), 1));
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_release_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    polygon_release(polygon);
}

static void test_polygon_equals_1() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (2, 0); (0, 2); (2, 2) >>"
    );
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 0);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_equals_2() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 1);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_equals_3() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    list_reverse(polygon1->points);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 1);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_dup_1() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_dup(polygon1);
    g_assert(polygon1 != polygon2);
    g_assert(polygon1->points != polygon2->points);
    g_assert(list_equals_cmp(polygon1->points, polygon2->points,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_to_str_1() {
    char *polygon_str =
        (char *) "<< Polygon: (0.0, 0.0); (1.0, 0.0); (1.0, 1.0); (0.0, 1.0) >>";
    ADTList points = list_new();
    list_append(points, point_new(0, 0));
    list_append(points, point_new(0, 1));
    list_append(points, point_new(1, 0));
    list_append(points, point_new(1, 1));
    CGPolygon polygon = polygon_new(points);
    char *str = polygon_to_str(polygon, 1);
    g_assert_cmpstr(str, ==, polygon_str);
    free(str);
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_from_str_1() {
    char *polygon_str = (char *) "<< Polygon: (1, 0); (0, 0); (1, 1); (0, 1) >>";
    ADTList points = list_new();
    list_append(points, point_new(0, 0));
    list_append(points, point_new(0, 1));
    list_append(points, point_new(1, 0));
    list_append(points, point_new(1, 1));
    CGPolygon polygon1 = polygon_from_str(polygon_str);
    CGPolygon polygon2 = polygon_new(points);
    g_assert(polygon_equals(polygon1, polygon2));
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_points_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    ADTList points = polygon_points(polygon);
    g_assert(polygon->points != points);
    g_assert(list_equals_cmp(polygon->points, points, (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_translate_1() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (1, 1); (2, 1); (1, 2); (2, 2) >>"
    );
    CGVector vector = vector_new(1, 1);
    polygon_translate(polygon1, vector);
    g_assert(polygon_equals(polygon1, polygon2));
    vector_release(vector);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_translate_2() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector vector = vector_new(0, 0);
    polygon_translate(polygon1, vector);
    g_assert(polygon_equals(polygon1, polygon2));
    vector_release(vector);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_rotate_around_1() {
    CGPoint center = point_new(1, 1);
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    polygon_rotate_around(polygon1, center, 0);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_rotate_around_2() {
    CGPoint center = point_new(0.5, 0.5);
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    polygon_rotate_around(polygon1, center, 90);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_rotate_around_3() {
    CGPoint center = point_new(1, 1);
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (1, 1); (2, 1); (1, 2); (2, 2) >>"
    );
    polygon_rotate_around(polygon1, center, 180);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_rotate_around_4() {
    CGPoint center = point_new(0, 0);
    CGPoint lower_left1 = point_new(-0.5, -0.5);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    ADTList points = list_new();
    list_append(points, point_new(0, -sqrt(2) / 2));
    list_append(points, point_new(0, sqrt(2) / 2));
    list_append(points, point_new(-sqrt(2) / 2, 0));
    list_append(points, point_new(sqrt(2) / 2, 0));
    CGPolygon polygon2 = polygon_new(points);
    polygon_rotate_around(polygon1, center, 45);
    g_assert(polygon_equals(polygon1, polygon2));
    point_release(center);
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_area_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    g_assert(double_equals(polygon_area(polygon), 1));
    polygon_release(polygon);
}

static void test_polygon_area_2() {
    CGPolygon polygon = polygon_from_str((char *) "<< Polygon: (0, 0); (1, 0); (1, 1) >>");
    g_assert(double_equals(polygon_area(polygon), 0.5));
    polygon_release(polygon);
}

static void test_polygon_projection_on_axis_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (2, 0); (2, 3); (0, 3) >>"
    );
    CGVector axis = vector_new(1, 0);
    CGShapeProjectionOnAxis spoa = polygon_projection_on_axis(polygon, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 2));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    polygon_release(polygon);
}

static void test_polygon_projection_on_axis_2() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (2, 0); (2, 3); (0, 3) >>"
    );
    CGVector axis = vector_new(0, 1);
    CGShapeProjectionOnAxis spoa = polygon_projection_on_axis(polygon, axis);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 3));
    shape_projection_on_axis_release(spoa);
    vector_release(axis);
    polygon_release(polygon);
}

static void test_polygon_collision_axes_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (2, 0); (2, 3); (0, 3) >>"
    );
    ADTList collision_axes = polygon_collision_axes(polygon);
    g_assert_cmpint(list_size(collision_axes), ==, 4);
    CGVector axis = (CGVector) list_at(collision_axes, 0);
    g_assert(double_equals(axis->x, 0));
    g_assert(double_equals(axis->y, -1));
    axis = (CGVector) list_at(collision_axes, 1);
    g_assert(double_equals(axis->x, 1));
    g_assert(double_equals(axis->y, 0));
    axis = (CGVector) list_at(collision_axes, 2);
    g_assert(double_equals(axis->x, 0));
    g_assert(double_equals(axis->y, 1));
    axis = (CGVector) list_at(collision_axes, 3);
    g_assert(double_equals(axis->x, -1));
    g_assert(double_equals(axis->y, 0));
    polygon_release(polygon);
    list_full_release(collision_axes, (void (*)(void *)) vector_release);
}

static void test_point_is_in_polygon_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    g_assert_cmpint(point_is_in_polygon((CGPoint) list_at(polygon->points, 0), polygon), ==,
                    0);
    g_assert_cmpint(point_is_in_polygon((CGPoint) list_at(polygon->points, 1), polygon), ==,
                    0);
    g_assert_cmpint(point_is_in_polygon((CGPoint) list_at(polygon->points, 2), polygon), ==,
                    0);
    g_assert_cmpint(point_is_in_polygon((CGPoint) list_at(polygon->points, 3), polygon), ==,
                    0);
    polygon_release(polygon);
}

static void test_point_is_in_polygon_2() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPoint point = point_new(2, 2);
    g_assert_cmpint(point_is_in_polygon(point, polygon), ==, 0);
    point_release(point);
    polygon_release(polygon);
}

static void test_point_is_in_polygon_3() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPoint point = point_new(0.5, 0.5);
    g_assert_cmpint(point_is_in_polygon(point, polygon), ==, 1);
    point_release(point);
    polygon_release(polygon);
}

static void test_point_is_in_polygon_4() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPoint point = point_new(0.5, 0);
    g_assert_cmpint(point_is_in_polygon(point, polygon), ==, 0);
    polygon_release(polygon);
    point_release(point);
}

static void test_shape_projection_on_axis_new_1() {
    CGShapeProjectionOnAxis spoa = shape_projection_on_axis_new(0, 10);
    g_assert(double_equals(spoa->min, 0));
    g_assert(double_equals(spoa->max, 10));
    shape_projection_on_axis_release(spoa);
}

static void test_shape_projection_on_axis_release_1() {
    CGShapeProjectionOnAxis spoa = shape_projection_on_axis_new(0, 10);
    shape_projection_on_axis_release(spoa);
}

static void test_shape_projection_on_axis_equals_1() {
    CGShapeProjectionOnAxis spoa1 = shape_projection_on_axis_new(0, 10);
    CGShapeProjectionOnAxis spoa2 = shape_projection_on_axis_new(0, 11);
    CGShapeProjectionOnAxis spoa3 = shape_projection_on_axis_new(1, 10);
    g_assert_cmpint(shape_projection_on_axis_equals(spoa1, spoa1), ==, 1);
    g_assert_cmpint(shape_projection_on_axis_equals(spoa2, spoa2), ==, 1);
    g_assert_cmpint(shape_projection_on_axis_equals(spoa3, spoa3), ==, 1);
    g_assert_cmpint(shape_projection_on_axis_equals(spoa1, spoa2), ==, 0);
    g_assert_cmpint(shape_projection_on_axis_equals(spoa1, spoa3), ==, 0);
    shape_projection_on_axis_release(spoa1);
    shape_projection_on_axis_release(spoa2);
    shape_projection_on_axis_release(spoa3);
}

static void test_shape_projection_on_axis_dup_1() {
    CGShapeProjectionOnAxis spoa1 = shape_projection_on_axis_new(0, 10);
    CGShapeProjectionOnAxis spoa2 = shape_projection_on_axis_dup(spoa1);
    g_assert(spoa1 != spoa2);
    g_assert(double_equals(spoa1->min, spoa2->min));
    g_assert(double_equals(spoa1->max, spoa2->max));
    shape_projection_on_axis_release(spoa1);
    shape_projection_on_axis_release(spoa2);
}

static void test_shape_projection_on_axis_min_1() {
    CGShapeProjectionOnAxis spoa = shape_projection_on_axis_new(0, 10);
    g_assert(double_equals(shape_projection_on_axis_min(spoa), 0));
    shape_projection_on_axis_release(spoa);
}

static void test_shape_projection_on_axis_max_1() {
    CGShapeProjectionOnAxis spoa = shape_projection_on_axis_new(0, 10);
    g_assert(double_equals(shape_projection_on_axis_max(spoa), 10));
    shape_projection_on_axis_release(spoa);
}

static void test_shape_projection_on_axis_tv_1() {
    CGShapeProjectionOnAxis spoa1 = shape_projection_on_axis_new(3, 6);
    CGShapeProjectionOnAxis spoa2 = shape_projection_on_axis_new(6, 9);
    CGShapeProjectionOnAxis spoa3 = shape_projection_on_axis_new(9, 12);
    CGShapeProjectionOnAxis spoa4 = shape_projection_on_axis_new(1, 13);
    CGShapeProjectionOnAxis spoa5 = shape_projection_on_axis_new(5, 10);
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa1, spoa1)), 3));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa1, spoa2), 0));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa1, spoa3), 0));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa1, spoa4), 5));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa1, spoa5), 1));
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa2, spoa2)), 3));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa2, spoa3), 0));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa2, spoa4), -7));
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa2, spoa5)), 4));
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa3, spoa3)), 3));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa3, spoa4), -4));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa3, spoa5), -1));
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa4, spoa4)), 12));
    g_assert(double_equals(shape_projection_on_axis_tv(spoa4, spoa5), 8));
    g_assert(double_equals(abs(shape_projection_on_axis_tv(spoa5, spoa5)), 5));
    shape_projection_on_axis_release(spoa1);
    shape_projection_on_axis_release(spoa2);
    shape_projection_on_axis_release(spoa3);
    shape_projection_on_axis_release(spoa4);
    shape_projection_on_axis_release(spoa5);
}

static void test_segment_segment_collision_mtv_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 0); (0, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 0); (1, 1) >>");
    CGVector mtv = segment_segment_collision_mtv(segment1, segment2);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_segment_collision_mtv_2() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (1, 0.5); (1, 2) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0, 1); (1.5, 1) >>");
    CGVector mtv1 = segment_segment_collision_mtv(segment1, segment2);
    g_assert(double_equals(mtv1->x, -0.5));
    g_assert(double_equals(mtv1->y, 0));
    CGVector mtv2 = segment_segment_collision_mtv(segment2, segment1);
    g_assert(double_equals(mtv2->x, 0));
    g_assert(double_equals(mtv2->y, 0.5));
    vector_release(mtv1);
    vector_release(mtv2);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_segment_collision_mtv_3() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 1); (1, 0) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (0.49, 0.49); (1, 1) >>");
    CGVector mtv1 = segment_segment_collision_mtv(segment1, segment2);
    g_assert(double_equals(mtv1->x, 0.01));
    g_assert(double_equals(mtv1->y, 0.01));
    CGVector mtv2 = segment_segment_collision_mtv(segment2, segment1);
    g_assert(double_equals(mtv2->x, -0.01));
    g_assert(double_equals(mtv2->y, -0.01));
    vector_release(mtv1);
    vector_release(mtv2);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_segment_collision_mtv_4() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (2, 1); (3, 1) >>");
    CGVector mtv = segment_segment_collision_mtv(segment1, segment2);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    segment_release(segment1);
    segment_release(segment2);
}

static void test_segment_triangle_collision_mtv_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 1); (1, 0) >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGVector mtv1 = segment_triangle_collision_mtv(segment1, triangle);
    g_assert(double_equals(mtv1->x, 0));
    g_assert(double_equals(mtv1->y, 0));
    CGVector mtv2 = segment_triangle_collision_mtv(segment2, triangle);
    g_assert(double_equals(mtv2->x, 0));
    g_assert(double_equals(mtv2->y, 0));
    vector_release(mtv1);
    vector_release(mtv2);
    segment_release(segment1);
    segment_release(segment2);
    triangle_release(triangle);
}

static void test_segment_triangle_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0.10, 0.10); (1.00, 0.10) >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGVector mtv = segment_triangle_collision_mtv(segment, triangle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0.10));
    vector_release(mtv);
    segment_release(segment);
    triangle_release(triangle);
}

static void test_segment_polygon_collision_mtv_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (0, 1) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (1, 1); (0, 1) >>"
    );
    CGVector mtv = segment_polygon_collision_mtv(segment, polygon);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    segment_release(segment);
}

static void test_segment_polygon_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0.10, 0.10); (0.10, 1.00) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (1, 1); (0, 1) >>"
    );
    CGVector mtv = segment_polygon_collision_mtv(segment, polygon);
    g_assert(double_equals(mtv->x, 0.10));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    segment_release(segment);
}

static void test_segment_circle_collision_mtv_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 3); (1, 3) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector mtv = segment_circle_collision_mtv(segment, circle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_segment_circle_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector mtv = segment_circle_collision_mtv(segment, circle);
    g_assert(double_equals(mtv->x, sqrt(2) / 2));
    g_assert(double_equals(mtv->y, -sqrt(2) / 2));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_segment_circle_collision_mtv_3() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 0.9 >>");
    CGVector mtv = segment_circle_collision_mtv(segment, circle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, -0.9));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_triangle_segment_collision_mtv_1() {
    CGSegment segment1 = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGSegment segment2 = segment_from_str((char *) "<< Segment: (1, 1); (1, 0) >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGVector mtv1 = triangle_segment_collision_mtv(triangle, segment1);
    g_assert(double_equals(mtv1->x, 0));
    g_assert(double_equals(mtv1->y, 0));
    CGVector mtv2 = triangle_segment_collision_mtv(triangle, segment2);
    g_assert(double_equals(mtv2->x, 0));
    g_assert(double_equals(mtv2->y, 0));
    vector_release(mtv1);
    vector_release(mtv2);
    segment_release(segment1);
    segment_release(segment2);
    triangle_release(triangle);
}

static void test_triangle_segment_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0.10, 0.10); (1.00, 0.10) >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGVector mtv = triangle_segment_collision_mtv(triangle, segment);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, -0.10));
    vector_release(mtv);
    segment_release(segment);
    triangle_release(triangle);
}

static void test_triangle_triangle_collision_mtv_1() {
    CGTriangle triangle1 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (1, 1) >>"
    );
    CGTriangle triangle2 = triangle_from_str(
            (char *) "<< Triangle: (1, 0); (2, 0); (1, 1) >>"
    );
    CGVector vector = triangle_triangle_collision_mtv(triangle1, triangle2);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_triangle_collision_mtv_2() {
    CGTriangle triangle1 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (0, 1) >>"
    );
    CGTriangle triangle2 = triangle_from_str(
            (char *) "<< Triangle: (0, 0); (1, 0); (1, 1) >>"
    );
    CGVector vector1 = triangle_triangle_collision_mtv(triangle1, triangle2);
    g_assert(double_equals(vector1->x, 0.5));
    g_assert(double_equals(vector1->y, 0.5));
    CGVector vector2 = triangle_triangle_collision_mtv(triangle2, triangle1);
    g_assert(double_equals(vector2->x, -0.5));
    g_assert(double_equals(vector2->y, 0.5));
    vector_release(vector1);
    vector_release(vector2);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_polygon_collision_mtv_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (1, 0); (1, 1); (2, 0) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = triangle_polygon_collision_mtv(triangle, polygon);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    triangle_release(triangle);
}

static void test_triangle_polygon_collision_mtv_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (1, 0); (0, 1); (0, 0) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = triangle_polygon_collision_mtv(triangle, polygon);
    g_assert(double_equals(mtv->x, 0.5));
    g_assert(double_equals(mtv->y, 0.5));
    vector_release(mtv);
    polygon_release(polygon);
    triangle_release(triangle);
}

static void test_triangle_circle_collision_mtv_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (5, 5); 1 >>");
    CGVector mtv = triangle_circle_collision_mtv(triangle, circle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    triangle_release(triangle);
}

static void test_triangle_circle_collision_mtv_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 5); (5, 0) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1.00, 1.00); 1.00 >>");
    CGVector mtv = triangle_circle_collision_mtv(triangle, circle);
    g_assert(double_equals(mtv->x, -2));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    triangle_release(triangle);
}

static void test_polygon_segment_collision_mtv_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (0, 1) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = polygon_segment_collision_mtv(polygon, segment);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    segment_release(segment);
}

static void test_polygon_segment_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0.10, 0.10); (0.10, 1.00) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = polygon_segment_collision_mtv(polygon, segment);
    g_assert(double_equals(mtv->x, -0.10));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    segment_release(segment);
}

static void test_polygon_triangle_collision_mtv_1() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (1, 0); (1, 1); (2, 0) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = polygon_triangle_collision_mtv(polygon, triangle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    triangle_release(triangle);
}

static void test_polygon_triangle_collision_mtv_2() {
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (1, 0); (0, 1); (0, 0) >>");
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGVector mtv = polygon_triangle_collision_mtv(polygon, triangle);
    g_assert(double_equals(mtv->x, -0.5));
    g_assert(double_equals(mtv->y, -0.5));
    vector_release(mtv);
    polygon_release(polygon);
    triangle_release(triangle);
}

static void test_polygon_polygon_collision_mtv_1() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (1, 0); (1, 1); (2, 0); (2, 1) >>"
    );
    CGVector mtv = polygon_polygon_collision_mtv(polygon1, polygon2);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_polygon_collision_mtv_2() {
    CGPolygon polygon1 = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGPolygon polygon2 = polygon_from_str(
            (char *) "<< Polygon: (0.9, 0.2); (0.9, 1.2); (1.9, 0.2); (1.9, 1.2) >>"
    );
    CGVector mtv = polygon_polygon_collision_mtv(polygon1, polygon2);
    g_assert(double_equals(mtv->x, 0.1));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_circle_collision_mtv_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGCircle circle = circle_from_str((char *) "<< Circle: (2, 1); 1 >>");
    CGVector mtv = polygon_circle_collision_mtv(polygon, circle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_circle_collision_mtv_2() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGCircle circle = circle_from_str((char *) "<< Circle: (1.10, 1); 1 >>");
    CGVector mtv = polygon_circle_collision_mtv(polygon, circle);
    g_assert(double_equals(mtv->x, 0.9));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_segment_collision_mtv_1() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 3); (1, 3) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector mtv = circle_segment_collision_mtv(circle, segment);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_circle_segment_collision_mtv_2() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 0); (1, 1) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGVector mtv = circle_segment_collision_mtv(circle, segment);
    g_assert(double_equals(mtv->x, -sqrt(2) / 2));
    g_assert(double_equals(mtv->y, sqrt(2) / 2));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_circle_segment_collision_mtv_3() {
    CGSegment segment = segment_from_str((char *) "<< Segment: (0, 1); (1, 1) >>");
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 0.9 >>");
    CGVector mtv = circle_segment_collision_mtv(circle, segment);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0.9));
    vector_release(mtv);
    circle_release(circle);
    segment_release(segment);
}

static void test_circle_triangle_collision_mtv_1() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (5, 5); 1 >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 1); (1, 0) >>");
    CGVector mtv = circle_triangle_collision_mtv(circle, triangle);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    triangle_release(triangle);
}

static void test_circle_triangle_collision_mtv_2() {
    CGCircle circle = circle_from_str((char *) "<< Circle: (1, 1); 1 >>");
    CGTriangle triangle = triangle_from_str((char *) "<< Triangle: (0, 0); (0, 5); (5, 0) >>");
    CGVector mtv = circle_triangle_collision_mtv(circle, triangle);
    g_assert(double_equals(mtv->x, 2));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle);
    triangle_release(triangle);
}

static void test_circle_polygon_collision_mtv_1() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGCircle circle = circle_from_str((char *) "<< Circle: (2, 1); 1 >>");
    CGVector mtv = circle_polygon_collision_mtv(circle, polygon);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_polygon_collision_mtv_2() {
    CGPolygon polygon = polygon_from_str(
            (char *) "<< Polygon: (0, 0); (1, 0); (0, 1); (1, 1) >>"
    );
    CGCircle circle = circle_from_str((char *) "<< Circle: (1.10, 1); 1 >>");
    CGVector mtv = circle_polygon_collision_mtv(circle, polygon);
    g_assert(double_equals(mtv->x, -0.9));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_circle_collision_mtv_1() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (0, 0); 1 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (2, 0); 1 >>");
    CGVector mtv = circle_circle_collision_mtv(circle1, circle2);
    g_assert(double_equals(mtv->x, 0));
    g_assert(double_equals(mtv->y, 0));
    vector_release(mtv);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_circle_collision_mtv_2() {
    CGCircle circle1 = circle_from_str((char *) "<< Circle: (0, 0); 1 >>");
    CGCircle circle2 = circle_from_str((char *) "<< Circle: (1, 0); 1 >>");
    CGVector mtv1 = circle_circle_collision_mtv(circle1, circle2);
    g_assert(double_equals(mtv1->x, 1));
    g_assert(double_equals(mtv1->y, 0));
    CGVector mtv2 = circle_circle_collision_mtv(circle2, circle1);
    g_assert(double_equals(mtv2->x, -1));
    g_assert(double_equals(mtv2->y, 0));
    vector_release(mtv1);
    vector_release(mtv2);
    circle_release(circle1);
    circle_release(circle2);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/gc/deg_to_rad", test_deg_to_rad_1);
    g_test_add_func("/gc/vector_new", test_vector_new_1);
    g_test_add_func("/gc/vector_from_point_to_point", test_vector_from_point_to_point_1);
    g_test_add_func("/gc/vector_release", test_vector_release_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_2);
    g_test_add_func("/gc/vector_dup", test_vector_dup_1);
    g_test_add_func("/gc/vector_to_str", test_vector_to_str_1);
    g_test_add_func("/gc/vector_from_str", test_vector_from_str_1);
    g_test_add_func("/gc/vector_x", test_vector_x_1);
    g_test_add_func("/gc/vector_y", test_vector_y_1);
    g_test_add_func("/gc/vector_right_perpendicular", test_vector_right_perpendicular_1);
    g_test_add_func("/gc/vector_left_perpendicular", test_vector_left_perpendicular_1);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_1);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_2);
    g_test_add_func("/gc/vector_reverse", test_vector_reverse_1);
    g_test_add_func("/gc/vector_sum", test_vector_sum_1);
    g_test_add_func("/gc/vector_sum", test_vector_sum_2);
    g_test_add_func("/gc/vector_subtract", test_vector_subtract_1);
    g_test_add_func("/gc/vector_subtract", test_vector_subtract_2);
    g_test_add_func("/gc/vector_multiply", test_vector_multiply_1);
    g_test_add_func("/gc/vector_multiply", test_vector_multiply_2);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_1);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_2);
    g_test_add_func("/gc/vector_dot", test_vector_dot_1);
    g_test_add_func("/gc/vector_dot", test_vector_dot_2);
    g_test_add_func("/gc/vector_dot", test_vector_dot_3);
    g_test_add_func("/gc/vector_dot", test_vector_dot_4);
    g_test_add_func("/gc/vector_dot", test_vector_dot_5);
    g_test_add_func("/gc/angle_between_vectors", test_angle_between_vectors_1);
    g_test_add_func("/gc/angle_between_vectors", test_angle_between_vectors_2);
    g_test_add_func("/gc/angle_between_vectors", test_angle_between_vectors_3);
    g_test_add_func("/gc/angle_between_vectors", test_angle_between_vectors_4);
    g_test_add_func("/gc/angle_between_vectors", test_angle_between_vectors_5);
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
    g_test_add_func("/gc/point_vector_from_origin", test_point_vector_from_origin_1);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_1);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_2);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_3);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_4);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_5);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_6);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_1);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_2);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_3);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_4);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_5);
    g_test_add_func("/gc/point_projection_magnitude_on_axis",
                    test_point_projection_magnitude_on_axis_6);
    g_test_add_func("/gc/point_translate", test_point_translate_1);
    g_test_add_func("/gc/point_translate", test_point_translate_2);
    g_test_add_func("/gc/point_translate", test_point_translate_3);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_1);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_2);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_3);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_4);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_5);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_6);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_7);
    g_test_add_func("/gc/point_rotate", test_point_rotate_around_8);
    g_test_add_func("/gc/midpoint_between_points", test_midpoint_between_points_1);
    g_test_add_func("/gc/point_normalize", test_point_normalize_1);
    g_test_add_func("/gc/point_distance_to_point", test_point_distance_to_point_1);
    g_test_add_func("/gc/line_new", test_line_new_1);
    g_test_add_func("/gc/line_new", test_line_new_2);
    g_test_add_func("/gc/line_new", test_line_new_3);
    g_test_add_func("/gc/line_new", test_line_new_4);
    g_test_add_func("/gc/line_release", test_line_release_1);
    g_test_add_func("/gc/line_equals", test_line_equals_1);
    g_test_add_func("/gc/line_equals", test_line_equals_2);
    g_test_add_func("/gc/line_dup", test_line_dup_1);
    g_test_add_func("/gc/line_to_str", test_line_to_str_1);
    g_test_add_func("/gc/line_from_str", test_line_from_str_1);
    g_test_add_func("/gc/line_perpendicular", test_line_perpendicular_1);
    g_test_add_func("/gc/lines_intersection", test_lines_intersection_1);
    g_test_add_func("/gc/lines_intersection", test_lines_intersection_2);
    g_test_add_func("/gc/lines_intersection", test_lines_intersection_3);
    g_test_add_func("/gc/line_normalize", test_line_normalize_1);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_1);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_2);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_1);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_2);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_3);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_1);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_2);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_3);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_4);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_5);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_6);
    g_test_add_func("/gc/angle_between_lines", test_angle_between_lines_7);
    g_test_add_func("/gc/segment_new", test_segment_new_1);
    g_test_add_func("/gc/segment_new", test_segment_new_2);
    g_test_add_func("/gc/segment_release", test_segment_release_1);
    g_test_add_func("/gc/segment_equals", test_segment_equals_1);
    g_test_add_func("/gc/segment_dup", test_segment_dup_1);
    g_test_add_func("/gc/segment_to_str", test_segment_to_str_1);
    g_test_add_func("/gc/segment_from_str", test_segment_from_str_1);
    g_test_add_func("/gc/segment_points", test_segment_points_1);
    g_test_add_func("/gc/segment_vector", test_segment_vector_1);
    g_test_add_func("/gc/segment_line", test_segment_line_1);
    g_test_add_func("/gc/segment_length", test_segment_length_1);
    g_test_add_func("/gc/segment_translate", test_segment_translate_1);
    g_test_add_func("/gc/segment_translate", test_segment_translate_2);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_1);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_2);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_3);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_4);
    g_test_add_func("/gc/segment_projection_on_axis", test_segment_projection_on_axis_1);
    g_test_add_func("/gc/segment_projection_on_axis", test_segment_projection_on_axis_2);
    g_test_add_func("/gc/segment_projection_on_axis", test_segment_projection_on_axis_3);
    g_test_add_func("/gc/segment_projection_on_axis", test_segment_projection_on_axis_4);
    g_test_add_func("/gc/segment_projection_on_axis", test_segment_projection_on_axis_5);
    g_test_add_func("/gc/segment_collision_axes", test_segment_collision_axes_1);
    g_test_add_func("/gc/segment_collision_axes", test_segment_collision_axes_2);
    g_test_add_func("/gc/segments_intersection", test_segments_intersection_1);
    g_test_add_func("/gc/segments_intersection", test_segments_intersection_2);
    g_test_add_func("/gc/segments_intersection", test_segments_intersection_3);
    g_test_add_func("/gc/segments_intersection", test_segments_intersection_4);
    g_test_add_func("/gc/point_is_in_segment", test_point_is_in_segment_1);
    g_test_add_func("/gc/circle_new", test_circle_new_1);
    g_test_add_func("/gc/circle_new", test_circle_new_2);
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
    g_test_add_func("/gc/circle_translate", test_circle_translate_2);
    g_test_add_func("/gc/circle_projection_on_axis", test_circle_projection_on_axis_1);
    g_test_add_func("/gc/circle_projection_on_axis", test_circle_projection_on_axis_2);
    g_test_add_func("/gc/circle_projection_on_axis", test_circle_projection_on_axis_3);
    g_test_add_func("/gc/circle_collision_axes", test_circle_collision_axes_1);
    g_test_add_func("/gc/circle_collision_axes", test_circle_collision_axes_2);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_1);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_2);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_3);
    g_test_add_func("/gc/triangle_new", test_triangle_new_1);
    g_test_add_func("/gc/triangle_release", test_triangle_release_1);
    g_test_add_func("/gc/triangle_equals", test_triangle_equals_1);
    g_test_add_func("/gc/triangle_equals", test_triangle_equals_2);
    g_test_add_func("/gc/triangle_dup", test_triangle_dup_1);
    g_test_add_func("/gc/triangle_to_str", test_triangle_to_str_1);
    g_test_add_func("/gc/triangle_from_str", test_triangle_from_str_1);
    g_test_add_func("/gc/triangle_points", test_triangle_points_1);
    g_test_add_func("/gc/triangle_translate", test_triangle_translate_1);
    g_test_add_func("/gc/triangle_translate", test_triangle_translate_2);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_1);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_2);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_3);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_1);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_2);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_3);
    g_test_add_func("/gc/triangle_area", test_triangle_area_1);
    g_test_add_func("/gc/triangle_projection_on_axis", test_triangle_projection_on_axis_1);
    g_test_add_func("/gc/triangle_projection_on_axis", test_triangle_projection_on_axis_2);
    g_test_add_func("/gc/triangle_projection_on_axis", test_triangle_projection_on_axis_3);
    g_test_add_func("/gc/triangle_collision_axes", test_triangle_collision_axes_1);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_1);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_2);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_3);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_4);
    g_test_add_func("/gc/polygon_new", test_polygon_new_1);
    g_test_add_func("/gc/polygon_new", test_polygon_new_2);
    g_test_add_func("/gc/polygon_new", test_polygon_new_3);
    g_test_add_func("/gc/polygon_new_triangle", test_polygon_new_triangle_1);
    g_test_add_func("/gc/polygon_new_rectangle", test_polygon_new_rectangle_1);
    g_test_add_func("/gc/polygon_new_square", test_polygon_new_square_1);
    g_test_add_func("/gc/polygon_release", test_polygon_release_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_2);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_3);
    g_test_add_func("/gc/polygon_dup", test_polygon_dup_1);
    g_test_add_func("/gc/polygon_to_str", test_polygon_to_str_1);
    g_test_add_func("/gc/polygon_from_str", test_polygon_from_str_1);
    g_test_add_func("/gc/polygon_points", test_polygon_points_1);
    g_test_add_func("/gc/polygon_translate", test_polygon_translate_1);
    g_test_add_func("/gc/polygon_translate", test_polygon_translate_2);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_1);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_2);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_3);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_4);
    g_test_add_func("/gc/polygon_area", test_polygon_area_1);
    g_test_add_func("/gc/polygon_area", test_polygon_area_2);
    g_test_add_func("/gc/polygon_projection_on_axis", test_polygon_projection_on_axis_1);
    g_test_add_func("/gc/polygon_projection_on_axis", test_polygon_projection_on_axis_2);
    g_test_add_func("/gc/polygon_collision_axes", test_polygon_collision_axes_1);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_1);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_2);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_3);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_4);
    g_test_add_func("/gc/shape_projection_on_axis_new", test_shape_projection_on_axis_new_1);
    g_test_add_func("/gc/shape_projection_on_axis_release",
                    test_shape_projection_on_axis_release_1);
    g_test_add_func("/gc/shape_projection_on_axis_equals",
                    test_shape_projection_on_axis_equals_1);
    g_test_add_func("/gc/shape_projection_on_axis_dup", test_shape_projection_on_axis_dup_1);
    g_test_add_func("/gc/shape_projection_on_axis_min", test_shape_projection_on_axis_min_1);
    g_test_add_func("/gc/shape_projection_on_axis_max", test_shape_projection_on_axis_max_1);
    g_test_add_func("/gc/shape_projection_on_axis_tv", test_shape_projection_on_axis_tv_1);
    g_test_add_func("/gc/segment_segment_collision_mtv", test_segment_segment_collision_mtv_1);
    g_test_add_func("/gc/segment_segment_collision_mtv", test_segment_segment_collision_mtv_2);
    g_test_add_func("/gc/segment_segment_collision_mtv", test_segment_segment_collision_mtv_3);
    g_test_add_func("/gc/segment_segment_collision_mtv", test_segment_segment_collision_mtv_4);
    g_test_add_func("/gc/segment_triangle_collision_mtv",
                    test_segment_triangle_collision_mtv_1);
    g_test_add_func("/gc/segment_triangle_collision_mtv",
                    test_segment_triangle_collision_mtv_2);
    g_test_add_func("/gc/segment_polygon_collision_mtv", test_segment_polygon_collision_mtv_1);
    g_test_add_func("/gc/segment_polygon_collision_mtv", test_segment_polygon_collision_mtv_2);
    g_test_add_func("/gc/segment_circle_collision_mtv", test_segment_circle_collision_mtv_1);
    g_test_add_func("/gc/segment_circle_collision_mtv", test_segment_circle_collision_mtv_2);
    g_test_add_func("/gc/segment_circle_collision_mtv", test_segment_circle_collision_mtv_3);
    g_test_add_func("/gc/triangle_segment_collision_mtv",
                    test_triangle_segment_collision_mtv_1);
    g_test_add_func("/gc/triangle_segment_collision_mtv",
                    test_triangle_segment_collision_mtv_2);
    g_test_add_func("/gc/triangle_triangle_collision_mtv",
                    test_triangle_triangle_collision_mtv_1);
    g_test_add_func("/gc/triangle_triangle_collision_mtv",
                    test_triangle_triangle_collision_mtv_2);
    g_test_add_func("/gc/triangle_polygon_collision_mtv",
                    test_triangle_polygon_collision_mtv_1);
    g_test_add_func("/gc/triangle_polygon_collision_mtv",
                    test_triangle_polygon_collision_mtv_2);
    g_test_add_func("/gc/triangle_circle_collision_mtv", test_triangle_circle_collision_mtv_1);
    g_test_add_func("/gc/triangle_circle_collision_mtv", test_triangle_circle_collision_mtv_2);
    g_test_add_func("/gc/polygon_segment_collision_mtv", test_polygon_segment_collision_mtv_1);
    g_test_add_func("/gc/polygon_segment_collision_mtv", test_polygon_segment_collision_mtv_2);
    g_test_add_func("/gc/polygon_triangle_collision_mtv",
                    test_polygon_triangle_collision_mtv_1);
    g_test_add_func("/gc/polygon_triangle_collision_mtv",
                    test_polygon_triangle_collision_mtv_2);
    g_test_add_func("/gc/polygon_polygon_collision_mtv", test_polygon_polygon_collision_mtv_1);
    g_test_add_func("/gc/polygon_polygon_collision_mtv", test_polygon_polygon_collision_mtv_2);
    g_test_add_func("/gc/polygon_circle_collision_mtv", test_polygon_circle_collision_mtv_1);
    g_test_add_func("/gc/polygon_circle_collision_mtv", test_polygon_circle_collision_mtv_2);
    g_test_add_func("/gc/circle_segment_collision_mtv", test_circle_segment_collision_mtv_1);
    g_test_add_func("/gc/circle_segment_collision_mtv", test_circle_segment_collision_mtv_2);
    g_test_add_func("/gc/circle_segment_collision_mtv", test_circle_segment_collision_mtv_3);
    g_test_add_func("/gc/circle_triangle_collision_mtv", test_circle_triangle_collision_mtv_1);
    g_test_add_func("/gc/circle_triangle_collision_mtv", test_circle_triangle_collision_mtv_2);
    g_test_add_func("/gc/circle_polygon_collision_mtv", test_circle_polygon_collision_mtv_1);
    g_test_add_func("/gc/circle_polygon_collision_mtv", test_circle_polygon_collision_mtv_2);
    g_test_add_func("/gc/circle_circle_collision_mtv", test_circle_circle_collision_mtv_1);
    g_test_add_func("/gc/circle_circle_collision_mtv", test_circle_circle_collision_mtv_2);
    return g_test_run();
}

