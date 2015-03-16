#include <glib.h>
#include <math.h>
#include <stdlib.h>

#include "cg/cg.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

static void test_angle_in_radians_new_1() {
    CGAngle angle = angle_in_radians_new(M_PI);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, M_PI));
    angle_release(angle);
}

static void test_angle_in_radians_new_2() {
    CGAngle angle = angle_in_radians_new(2 * M_PI);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, 0));
    angle_release(angle);
}

static void test_angle_in_radians_new_3() {
    CGAngle angle = angle_in_radians_new(-M_PI / 2);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, 3 * M_PI / 2));
    angle_release(angle);
}

static void test_angle_in_degrees_new_1() {
    CGAngle angle = angle_in_degrees_new(180);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, M_PI));
    angle_release(angle);
}

static void test_angle_in_degrees_new_2() {
    CGAngle angle = angle_in_degrees_new(360);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, 0));
    angle_release(angle);
}

static void test_angle_in_degrees_new_3() {
    CGAngle angle = angle_in_degrees_new(-90);
    g_assert(angle != NULL);
    g_assert(double_equals(angle->rad, 3 * M_PI / 2));
    angle_release(angle);
}

static void test_angle_release_1() {
    CGAngle angle = angle_in_radians_new(M_PI);
    angle_release(angle);
}

static void test_angle_equals_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(2 * M_PI);
    g_assert_cmpint(angle_equals(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_equals_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_equals(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_equals_3() {
    CGAngle angle1 = angle_in_radians_new(0);
    CGAngle angle2 = angle_in_radians_new(2 * M_PI);
    g_assert_cmpint(angle_equals(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lt_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    g_assert_cmpint(angle_lt(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lt_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_lt(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lt_3() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_lt(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lte_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    g_assert_cmpint(angle_lte(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lte_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_lte(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_lte_3() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_lte(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gt_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_gt(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gt_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_gt(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gt_3() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    g_assert_cmpint(angle_gt(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gte_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_gte(angle1, angle2), ==, 0);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gte_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    g_assert_cmpint(angle_gte(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_gte_3() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    g_assert_cmpint(angle_gte(angle1, angle2), ==, 1);
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_dup_1() {
    CGAngle angle = angle_in_radians_new(M_PI);
    CGAngle dup = angle_dup(angle);
    g_assert(dup != NULL);
    g_assert(dup != angle);
    g_assert(double_equals(angle->rad, dup->rad));
    angle_release(angle);
    angle_release(dup);
}

static void test_angle_to_str_1() {
    char *angle_str = (char *) "<< Angle: 3.14 >>";
    CGAngle angle = angle_in_radians_new(M_PI);
    char *str = angle_to_str(angle, 2);
    g_assert_cmpstr(str, ==, angle_str);
    free(str);
    angle_release(angle);
}

static void test_angle_sum_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    angle_sum(angle1, angle2);
    g_assert(double_equals(angle1->rad, 3 * M_PI / 2));
    g_assert(double_equals(angle2->rad, M_PI / 2));
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_sum_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    angle_sum(angle1, angle2);
    g_assert(double_equals(angle1->rad, 0));
    g_assert(double_equals(angle2->rad, M_PI));
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_subtract_1() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI / 2);
    angle_subtract(angle1, angle2);
    g_assert(double_equals(angle1->rad, 0));
    g_assert(double_equals(angle2->rad, M_PI / 2));
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_subtract_2() {
    CGAngle angle1 = angle_in_radians_new(M_PI / 2);
    CGAngle angle2 = angle_in_radians_new(M_PI);
    angle_subtract(angle1, angle2);
    g_assert(double_equals(angle1->rad, 3 * M_PI / 2));
    g_assert(double_equals(angle2->rad, M_PI));
    angle_release(angle1);
    angle_release(angle2);
}

static void test_angle_in_radians_1() {
    CGAngle angle = angle_in_degrees_new(180);
    g_assert(double_equals(angle_in_radians(angle), M_PI));
    angle_release(angle);
}

static void test_angle_in_degrees_1() {
    CGAngle angle = angle_in_radians_new(M_PI);
    g_assert(double_equals(angle_in_degrees(angle), 180));
    angle_release(angle);
}

static void test_vector_new_1() {
    CGVector vector = vector_new(1, 2);
    g_assert(vector != NULL);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 2));
    vector_release(vector);
}

static void test_vector_from_point_to_point_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGVector vector1 = vector_from_point_to_point(a, b);
    CGVector vector2 = vector_from_point_to_point(b, a);
    g_assert(vector1 != NULL);
    g_assert(double_equals(vector1->x, 1));
    g_assert(double_equals(vector1->y, 1));
    g_assert(vector2 != NULL);
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
    CGVector vector2 = vector_new(2, 2);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 0);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_equals_2() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(2, 1);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 0);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_equals_3() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(1, 2);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 0);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_equals_4() {
    CGVector vector1 = vector_new(1, 1);
    CGVector vector2 = vector_new(1, 1);
    g_assert_cmpint(vector_equals(vector1, vector2), ==, 1);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dup_1() {
    CGVector vector = vector_new(2, 3);
    CGVector dup = vector_dup(vector);
    g_assert(dup != NULL);
    g_assert(dup != vector);
    g_assert(double_equals(dup->x, vector->x));
    g_assert(double_equals(dup->y, vector->y));
    vector_release(vector);
    vector_release(dup);
}

static void test_vector_to_str_1() {
    char *vector_str = (char *) "<< Vector: (1.25, 2.00) >>";
    CGVector vector = vector_new(1.25, 2);
    char *str = vector_to_str(vector, 2);
    g_assert_cmpstr(str, ==, vector_str);
    free(str);
    vector_release(vector);
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

static void test_vector_right_perpendicular_axis_1() {
    CGVector vector = vector_new(3, 4);
    CGVector axis = vector_right_perpendicular_axis(vector);
    g_assert(double_equals(axis->x, 4 / 5.0));
    g_assert(double_equals(axis->y, -3 / 5.0));
    vector_release(vector);
    vector_release(axis);
}

static void test_vector_right_perpendicular_axis_2() {
    CGVector vector = vector_new(0, 0);
    g_assert(vector_right_perpendicular_axis(vector) == NULL);
    vector_release(vector);
}

static void test_vector_left_perpendicular_axis_1() {
    CGVector vector = vector_new(3, 4);
    CGVector axis = vector_left_perpendicular_axis(vector);
    g_assert(double_equals(axis->x, -4 / 5.0));
    g_assert(double_equals(axis->y, 3 / 5.0));
    vector_release(vector);
    vector_release(axis);
}

static void test_vector_left_perpendicular_axis_2() {
    CGVector vector = vector_new(0, 0);
    g_assert(vector_left_perpendicular_axis(vector) == NULL);
    vector_release(vector);
}

static void test_vector_normalize_1() {
    CGVector vector = vector_new(2, 0);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
}

static void test_vector_normalize_2() {
    CGVector vector = vector_new(0, 2);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 1));
    vector_release(vector);
}

static void test_vector_normalize_3() {
    CGVector vector = vector_new(1, 1);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 1 / sqrt(2)));
    g_assert(double_equals(vector->y, 1 / sqrt(2)));
    vector_release(vector);
}

static void test_vector_normalize_4() {
    CGVector vector = vector_new(0.05, 0.05);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 1 / sqrt(2)));
    g_assert(double_equals(vector->y, 1 / sqrt(2)));
    vector_release(vector);
}

static void test_vector_normalize_5() {
    CGVector vector = vector_new(0, 0);
    vector_normalize(vector);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 0));
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

static void test_vector_magnitude_3() {
    CGVector vector = vector_new(-3, -4);
    g_assert(double_equals(vector_magnitude(vector), 5));
    vector_release(vector);
}

static void test_vector_dot_1() {
    CGVector vector = vector_new(0, 1);
    g_assert(double_equals(vector_dot(vector, vector), 1));
    vector_release(vector);
}

static void test_vector_dot_2() {
    CGVector vector = vector_new(1, 0);
    g_assert(double_equals(vector_dot(vector, vector), 1));
    vector_release(vector);
}

static void test_vector_dot_3() {
    CGVector vector1 = vector_new(1, 2);
    CGVector vector2 = vector_new(3, 4);
    g_assert(double_equals(vector_dot(vector1, vector2), 11));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_dot_4() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 0);
    g_assert(double_equals(vector_dot(vector1, vector2), 0));
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_angle_to_1() {
    CGVector vector = vector_new(1, 1);
    CGAngle angle = vector_angle_to(vector, vector);
    g_assert(double_equals(angle_in_radians(angle), 0));
    angle_release(angle);
    vector_release(vector);
}

static void test_vector_angle_to_2() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 0);
    CGAngle angle1 = vector_angle_to(vector1, vector2);
    CGAngle angle2 = vector_angle_to(vector2, vector1);
    g_assert(double_equals(angle_in_radians(angle1), 3 * M_PI / 2));
    g_assert(double_equals(angle_in_radians(angle2), M_PI / 2));
    angle_release(angle1);
    angle_release(angle2);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_angle_to_3() {
    CGVector vector1 = vector_new(1, 0);
    CGVector vector2 = vector_new(-1, 0);
    CGAngle angle1 = vector_angle_to(vector1, vector2);
    CGAngle angle2 = vector_angle_to(vector2, vector1);
    g_assert(double_equals(angle_in_radians(angle1), M_PI));
    g_assert(double_equals(angle_in_radians(angle2), M_PI));
    angle_release(angle1);
    angle_release(angle2);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_angle_to_4() {
    CGVector vector1 = vector_new(0, 1);
    CGVector vector2 = vector_new(1, 1);
    CGAngle angle1 = vector_angle_to(vector1, vector2);
    CGAngle angle2 = vector_angle_to(vector2, vector1);
    g_assert(double_equals(angle_in_radians(angle1), 7 * M_PI / 4));
    g_assert(double_equals(angle_in_radians(angle2), M_PI / 4));
    angle_release(angle1);
    angle_release(angle2);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_angle_to_5() {
    CGVector vector1 = vector_new(1, 0);
    CGVector vector2 = vector_new(-1, 1);
    CGAngle angle1 = vector_angle_to(vector1, vector2);
    CGAngle angle2 = vector_angle_to(vector2, vector1);
    g_assert(double_equals(angle_in_degrees(angle1), 135));
    g_assert(double_equals(angle_in_degrees(angle2), 225));
    angle_release(angle1);
    angle_release(angle2);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_angle_to_6() {
    CGVector vector1 = vector_new(0, 0);
    CGVector vector2 = vector_new(1, 1);
    g_assert(vector_angle_to(vector1, vector2) == NULL);
    g_assert(vector_angle_to(vector2, vector1) == NULL);
    vector_release(vector1);
    vector_release(vector2);
}

static void test_vector_rotate_1() {
    CGVector vector = vector_new(1, 0);
    CGAngle angle = angle_in_degrees_new(0);
    vector_rotate(vector, angle);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    angle_release(angle);
    vector_release(vector);
}

static void test_vector_rotate_2() {
    CGVector vector = vector_new(1, 0);
    CGAngle angle = angle_in_degrees_new(90);
    vector_rotate(vector, angle);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, 1));
    angle_release(angle);
    vector_release(vector);
}

static void test_vector_rotate_3() {
    CGVector vector = vector_new(0, 1);
    CGAngle angle = angle_in_degrees_new(90);
    vector_rotate(vector, angle);
    g_assert(double_equals(vector->x, -1));
    g_assert(double_equals(vector->y, 0));
    angle_release(angle);
    vector_release(vector);
}

static void test_vector_rotate_4() {
    CGVector vector = vector_new(-1, 0);
    CGAngle angle = angle_in_degrees_new(90);
    vector_rotate(vector, angle);
    g_assert(double_equals(vector->x, 0));
    g_assert(double_equals(vector->y, -1));
    angle_release(angle);
    vector_release(vector);
}

static void test_vector_rotate_5() {
    CGVector vector = vector_new(0, -1);
    CGAngle angle = angle_in_degrees_new(90);
    vector_rotate(vector, angle);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 0));
    angle_release(angle);
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

static void test_midpoint_between_1() {
    CGPoint point1 = point_new(0, 0);
    CGPoint point2= point_new(2, 2);
    CGPoint midpoint = midpoint_between(point1, point2);
    g_assert(double_equals(point_x(midpoint), 1));
    g_assert(double_equals(point_y(midpoint), 1));
    point_release(point1);
    point_release(point2);
    point_release(midpoint);
}

static void test_point_release_1() {
    CGPoint point = point_new(2, 3);
    point_release(point);
}

static void test_point_equals_1() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(2, 2);
    g_assert_cmpint(point_equals(point1, point2), ==, 0);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_2() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(1, 2);
    g_assert_cmpint(point_equals(point1, point2), ==, 0);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_3() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(2, 1);
    g_assert_cmpint(point_equals(point1, point2), ==, 0);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_4() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = point_new(1, 1);
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_equals_5() {
    CGPoint point1 = point_new(1, 1);
    CGPoint point2 = memalloc(sizeof(*point2));
    point2->w = 2;
    point2->x = 2;
    point2->y = 2;
    g_assert_cmpint(point_equals(point1, point2), ==, 1);
    point_release(point1);
    point_release(point2);
}

static void test_point_dup_1() {
    CGPoint point = point_new(2, 3);
    CGPoint dup = point_dup(point);
    g_assert(dup != NULL);
    g_assert(dup != point);
    g_assert(double_equals(dup->w, point->w));
    g_assert(double_equals(dup->x, point->x));
    g_assert(double_equals(dup->y, point->y));
    point_release(point);
    point_release(dup);
}

static void test_point_to_str_1() {
    char *point_str = (char *) "<< Point: (1.25, 2.00) >>";
    CGPoint point = point_new(1.25, 2);
    char *str = point_to_str(point, 2);
    g_assert_cmpstr(str, ==, point_str);
    free(str);
    point_release(point);
}

static void test_point_x_1() {
    CGPoint point = point_new(1, 2);
    g_assert(double_equals(point_x(point), 1));
    point_release(point);
}

static void test_point_x_2() {
    CGPoint point = memalloc(sizeof(*point));
    point->x = 1;
    point->y = 2;
    point->w = 2;
    g_assert(double_equals(point_x(point), 0.5));
    point_release(point);
}

static void test_point_y_1() {
    CGPoint point = point_new(1, 2);
    g_assert(double_equals(point_y(point), 2));
    point_release(point);
}

static void test_point_y_2() {
    CGPoint point = memalloc(sizeof(*point));
    point->x = 1;
    point->y = 2;
    point->w = 2;
    g_assert(double_equals(point_y(point), 1));
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

static void test_point_vector_from_origin_2() {
    CGPoint point = memalloc(sizeof(*point));
    point->x = 2;
    point->y = 4;
    point->w = 2;
    CGVector vector = point_vector_from_origin(point);
    g_assert(double_equals(vector->x, 1));
    g_assert(double_equals(vector->y, 2));
    point_release(point);
    vector_release(vector);
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
    CGVector axis = vector_new(2, 0);
    vector_normalize(axis);
    CGVector vector = point_projection_on_axis(point, axis);
    g_assert(double_equals(vector->x, 5));
    g_assert(double_equals(vector->y, 0));
    vector_release(vector);
    vector_release(axis);
    point_release(point);
}

static void test_point_projection_on_axis_7() {
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
    CGVector vector = vector_new(0, 0);
    CGPoint point = point_new(1, 1);
    point_translate(point, vector);
    g_assert(double_equals(point_x(point), 1));
    g_assert(double_equals(point_y(point), 1));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_2() {
    CGVector vector = vector_new(1, 0);
    CGPoint point = point_new(1, 1);
    point_translate(point, vector);
    g_assert(double_equals(point_x(point), 2));
    g_assert(double_equals(point_y(point), 1));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_3() {
    CGVector vector = vector_new(0, 1);
    CGPoint point = point_new(1, 1);
    point_translate(point, vector);
    g_assert(double_equals(point_x(point), 1));
    g_assert(double_equals(point_y(point), 2));
    vector_release(vector);
    point_release(point);
}

static void test_point_translate_4() {
    CGVector vector = vector_new(1, 1);
    CGPoint point = point_new(1, 1);
    point_translate(point, vector);
    g_assert(double_equals(point_x(point), 2));
    g_assert(double_equals(point_y(point), 2));
    vector_release(vector);
    point_release(point);
}

static void test_point_rotate_around_1() {
    CGPoint point = point_new(1, 0);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 0));
    g_assert(double_equals(point_y(point), 1));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_2() {
    CGPoint point = point_new(0, 1);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), -1));
    g_assert(double_equals(point_y(point), 0));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_3() {
    CGPoint point = point_new(-1, 0);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 0));
    g_assert(double_equals(point_y(point), -1));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_4() {
    CGPoint point = point_new(0, -1);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 1));
    g_assert(double_equals(point_y(point), 0));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_5() {
    CGPoint point = point_new(0, 0);
    CGPoint center = point_new(1, 1);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 2));
    g_assert(double_equals(point_y(point), 0));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_6() {
    CGPoint point = point_new(0, 0);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(90);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 0));
    g_assert(double_equals(point_y(point), 0));
    point_release(center);
    point_release(point);
    angle_release(angle);
}

static void test_point_rotate_around_7() {
    CGPoint point = point_new(1, 1);
    CGPoint center = point_new(0, 0);
    CGAngle angle = angle_in_degrees_new(0);
    point_rotate_around(point, center, angle);
    g_assert(double_equals(point_x(point), 1));
    g_assert(double_equals(point_y(point), 1));
    point_release(center);
    point_release(point);
    angle_release(angle);
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

static void test_point_is_in_line_1() {
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

static void test_point_is_in_line_2() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 2);
    CGPoint c = point_new(1, 1);
    CGLine line = line_new(a, b);
    g_assert_cmpint(point_is_in_line(a, line), ==, 1);
    g_assert_cmpint(point_is_in_line(b, line), ==, 1);
    g_assert_cmpint(point_is_in_line(c, line), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    line_release(line);
}

static void test_point_is_in_segment_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    g_assert_cmpint(point_is_in_segment(c, segment), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    segment_release(segment);
}

static void test_point_is_in_segment_2() {
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(1, 2);
    CGPoint c = point_new(1, 0);
    CGSegment segment = segment_new(a, b);
    g_assert_cmpint(point_is_in_segment(c, segment), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    segment_release(segment);
}

static void test_point_is_in_segment_3() {
    CGPoint a = point_new(2, 1);
    CGPoint b = point_new(3, 1);
    CGPoint c = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    g_assert_cmpint(point_is_in_segment(c, segment), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    segment_release(segment);
}

static void test_point_is_in_segment_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(0.5, 0.5);
    CGSegment segment = segment_new(a, b);
    g_assert_cmpint(point_is_in_segment(a, segment), ==, 1);
    g_assert_cmpint(point_is_in_segment(b, segment), ==, 1);
    g_assert_cmpint(point_is_in_segment(c, segment), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    segment_release(segment);
}

static void test_point_is_in_triangle_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(d, triangle), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    triangle_release(triangle);
}

static void test_point_is_in_triangle_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(0.5, 0.5);
    CGPoint e = point_new(0.1, 0.1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(point_is_in_triangle(a, triangle), ==, 1);
    g_assert_cmpint(point_is_in_triangle(b, triangle), ==, 1);
    g_assert_cmpint(point_is_in_triangle(c, triangle), ==, 1);
    g_assert_cmpint(point_is_in_triangle(d, triangle), ==, 1);
    g_assert_cmpint(point_is_in_triangle(e, triangle), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    triangle_release(triangle);
}

static void test_point_is_in_polygon_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGPoint e = point_new(2, 2);
    ADTList vertices = list_new();
    list_append(vertices, a);
    list_append(vertices, b);
    list_append(vertices, c);
    list_append(vertices, d);
    CGPolygon polygon = polygon_new(vertices);
    g_assert_cmpint(point_is_in_polygon(e, polygon), ==, 0);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    list_release(vertices);
    polygon_release(polygon);
}

static void test_point_is_in_polygon_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGPoint e = point_new(0.5, 0);
    CGPoint f = point_new(0.5, 0.5);
    ADTList vertices = list_new();
    list_append(vertices, a);
    list_append(vertices, b);
    list_append(vertices, c);
    list_append(vertices, d);
    CGPolygon polygon = polygon_new(vertices);
    g_assert_cmpint(point_is_in_polygon(a, polygon), ==, 1);
    g_assert_cmpint(point_is_in_polygon(b, polygon), ==, 1);
    g_assert_cmpint(point_is_in_polygon(c, polygon), ==, 1);
    g_assert_cmpint(point_is_in_polygon(d, polygon), ==, 1);
    g_assert_cmpint(point_is_in_polygon(e, polygon), ==, 1);
    g_assert_cmpint(point_is_in_polygon(f, polygon), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    list_release(vertices);
    polygon_release(polygon);
}

static void test_point_is_in_circle_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint point = point_new(2, 2);
    g_assert_cmpint(point_is_in_circle(point, circle), ==, 0);
    point_release(point);
    point_release(center);
    circle_release(circle);
}

static void test_point_is_in_circle_2() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(2, 1);
    CGPoint d = point_new(1, 2);
    CGPoint e = point_new(0, 1);
    CGPoint f = point_new(1.1, 1.1);
    g_assert_cmpint(point_is_in_circle(a, circle), ==, 1);
    g_assert_cmpint(point_is_in_circle(b, circle), ==, 1);
    g_assert_cmpint(point_is_in_circle(c, circle), ==, 1);
    g_assert_cmpint(point_is_in_circle(d, circle), ==, 1);
    g_assert_cmpint(point_is_in_circle(e, circle), ==, 1);
    g_assert_cmpint(point_is_in_circle(f, circle), ==, 1);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    point_release(center);
    circle_release(circle);
}

static void test_point_intersection_of_lines_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(c, d);
    CGPoint intersection = point_intersection_of_lines(line1, line2);
    g_assert(intersection == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    line_release(line1);
    line_release(line2);
}

static void test_point_intersection_of_lines_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(2, 0);
    CGPoint c = point_new(1, 0);
    CGPoint d = point_new(3, 0);
    CGLine line1 = line_new(a, b);
    CGLine line2 = line_new(c, d);
    CGPoint intersection = point_intersection_of_lines(line1, line2);
    g_assert(intersection == NULL);
    line_release(line1);
    line_release(line2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_point_intersection_of_lines_3() {
    CGPoint a = point_new(0, 1);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGLine line1 = line_new(a, c);
    CGLine line2 = line_new(b, c);
    CGPoint intersection = point_intersection_of_lines(line1, line2);
    g_assert(point_equals(intersection, c));
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(intersection);
    line_release(line1);
    line_release(line2);
}

static void test_point_intersection_of_segments_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(2, 0);
    CGPoint d = point_new(3, 0);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGPoint intersection = point_intersection_of_segments(segment1, segment2);
    g_assert(intersection == NULL);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_point_intersection_of_segments_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(2, 0);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(b, c);
    CGPoint intersection = point_intersection_of_segments(segment1, segment2);
    g_assert(double_equals(point_x(intersection), 1));
    g_assert(double_equals(point_y(intersection), 0));
    point_release(intersection);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
}


static void test_point_intersection_of_segments_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(2, 0);
    CGPoint d = point_new(3, 0);
    CGSegment segment1 = segment_new(a, c);
    CGSegment segment2 = segment_new(b, d);
    CGPoint intersection = point_intersection_of_segments(segment1, segment2);
    g_assert(intersection == NULL);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_point_intersection_of_segments_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(b, c);
    CGPoint intersection = point_intersection_of_segments(segment1, segment2);
    g_assert(double_equals(point_x(intersection), 1));
    g_assert(double_equals(point_y(intersection), 0));
    point_release(intersection);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_point_intersection_of_segments_5() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(1, 0);
    CGPoint d = point_new(0, 1);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGPoint intersection = point_intersection_of_segments(segment1, segment2);
    g_assert(double_equals(point_x(intersection), 0.5));
    g_assert(double_equals(point_y(intersection), 0.5));
    point_release(intersection);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
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

static void test_line_equals_2() {
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

static void test_line_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGLine line = line_new(a, b);
    CGLine dup = line_dup(line);
    g_assert(dup != NULL);
    g_assert(dup != line);
    g_assert(double_equals(dup->w, line->w));
    g_assert(double_equals(dup->x, line->x));
    g_assert(double_equals(dup->y, line->y));
    point_release(a);
    point_release(b);
    line_release(line);
    line_release(dup);
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

static void test_segment_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    g_assert(segment != NULL);
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
    CGSegment segment = segment_new(a, b);
    g_assert(segment != NULL);
    g_assert(segment->a != a);
    g_assert(segment->b != b);
    g_assert(point_equals(segment->a, a));
    g_assert(point_equals(segment->b, b));
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_release_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_equals_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(2, 2);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(b, a);
    CGSegment segment3 = segment_new(a, c);
    g_assert_cmpint(segment_equals(segment1, segment1), ==, 1);
    g_assert_cmpint(segment_equals(segment1, segment2), ==, 1);
    g_assert_cmpint(segment_equals(segment1, segment3), ==, 0);
    segment_release(segment1);
    segment_release(segment2);
    segment_release(segment3);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_segment_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGSegment dup = segment_dup(segment);
    g_assert(dup != NULL);
    g_assert(dup != segment);
    g_assert(dup->a != segment->a);
    g_assert(dup->b != segment->b);
    g_assert(point_equals(dup->a, segment->a));
    g_assert(point_equals(dup->b, segment->b));
    point_release(a);
    point_release(b);
    segment_release(segment);
    segment_release(dup);
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

static void test_segment_a_1() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment = segment_new(a, b);
    CGPoint a_copy = segment_a(segment);
    g_assert(a_copy != a);
    g_assert(point_equals(a_copy, a));
    point_release(a_copy);
    point_release(a);
    point_release(b);
    segment_release(segment);
}

static void test_segment_b_1() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 4);
    CGSegment segment = segment_new(a, b);
    CGPoint b_copy = segment_b(segment);
    g_assert(b_copy != b);
    g_assert(point_equals(b_copy, b));
    point_release(b_copy);
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

static void test_segment_line_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 0);
    CGSegment segment = segment_new(a, b);
    g_assert(segment_line(segment) == NULL);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_translate_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGVector vector = vector_new(1, 1);
    segment_translate(segment, vector);
    g_assert(double_equals(point_x(segment->a), 1));
    g_assert(double_equals(point_y(segment->a), 1));
    g_assert(double_equals(point_x(segment->b), 2));
    g_assert(double_equals(point_y(segment->b), 2));
    vector_release(vector);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_translate_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGVector vector = vector_new(0, 0);
    segment_translate(segment, vector);
    g_assert(double_equals(point_x(segment->a), 0));
    g_assert(double_equals(point_y(segment->a), 0));
    g_assert(double_equals(point_x(segment->b), 1));
    g_assert(double_equals(point_y(segment->b), 1));
    vector_release(vector);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_rotate_around_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(0.5, 0.5);
    CGAngle angle = angle_in_degrees_new(0);
    segment_rotate_around(segment, center, angle);
    g_assert(double_equals(point_x(segment->a), 0));
    g_assert(double_equals(point_y(segment->a), 0));
    g_assert(double_equals(point_x(segment->b), 1));
    g_assert(double_equals(point_y(segment->b), 1));
    point_release(center);
    angle_release(angle);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_rotate_around_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(0.5, 0.5);
    CGAngle angle = angle_in_degrees_new(90);
    segment_rotate_around(segment, center, angle);
    g_assert(double_equals(point_x(segment->a), 1));
    g_assert(double_equals(point_y(segment->a), 0));
    g_assert(double_equals(point_x(segment->b), 0));
    g_assert(double_equals(point_y(segment->b), 1));
    point_release(center);
    angle_release(angle);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_rotate_around_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(0.5, 0.5);
    CGAngle angle = angle_in_degrees_new(180);
    segment_rotate_around(segment, center, angle);
    g_assert(double_equals(point_x(segment->a), 1));
    g_assert(double_equals(point_y(segment->a), 1));
    g_assert(double_equals(point_x(segment->b), 0));
    g_assert(double_equals(point_y(segment->b), 0));
    point_release(center);
    angle_release(angle);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_rotate_around_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGAngle angle = angle_in_degrees_new(180);
    segment_rotate_around(segment, center, angle);
    g_assert(double_equals(point_x(segment->a), 2));
    g_assert(double_equals(point_y(segment->a), 2));
    g_assert(double_equals(point_x(segment->b), 1));
    g_assert(double_equals(point_y(segment->b), 1));
    point_release(center);
    angle_release(angle);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_length_1() {
    CGPoint a = point_new(3, 0);
    CGPoint b = point_new(0, 4);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_length(segment), 5));
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_length_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 0);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_length(segment), 0));
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_triangle_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(triangle != NULL);
    g_assert(a != triangle->a);
    g_assert(b != triangle->b);
    g_assert(c != triangle->c);
    g_assert(point_equals(a, triangle->a));
    g_assert(point_equals(b, triangle->b));
    g_assert(point_equals(c, triangle->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_new_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(triangle != NULL);
    g_assert(a != triangle->a);
    g_assert(b != triangle->b);
    g_assert(c != triangle->c);
    g_assert(point_equals(a, triangle->a));
    g_assert(point_equals(b, triangle->b));
    g_assert(point_equals(c, triangle->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_new_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 0);
    CGPoint c = point_new(0, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(triangle != NULL);
    g_assert(a != triangle->a);
    g_assert(b != triangle->b);
    g_assert(c != triangle->c);
    g_assert(point_equals(a, triangle->a));
    g_assert(point_equals(b, triangle->b));
    g_assert(point_equals(c, triangle->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_release_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_equals_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGTriangle triangle2 = triangle_new(a, b, d);
    g_assert_cmpint(triangle_equals(triangle1, triangle2), ==, 0);
    triangle_release(triangle1);
    triangle_release(triangle2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_triangle_equals_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGTriangle triangle2 = triangle_new(a, c, b);
    CGTriangle triangle3 = triangle_new(b, a, c);
    CGTriangle triangle4 = triangle_new(b, c, a);
    CGTriangle triangle5 = triangle_new(c, a, b);
    CGTriangle triangle6 = triangle_new(c, b, a);
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
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_dup_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGTriangle dup = triangle_dup(triangle);
    g_assert(dup != NULL);
    g_assert(dup != triangle);
    g_assert(dup->a != triangle->a);
    g_assert(dup->b != triangle->b);
    g_assert(dup->c != triangle->c);
    g_assert(point_equals(dup->a, triangle->a));
    g_assert(point_equals(dup->b, triangle->b));
    g_assert(point_equals(dup->c, triangle->c));
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    triangle_release(dup);
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

static void test_triangle_a_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint a_copy = triangle_a(triangle);
    g_assert(a_copy != a);
    g_assert(point_equals(a_copy, a));
    point_release(a_copy);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_b_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint b_copy = triangle_b(triangle);
    g_assert(b_copy != b);
    g_assert(point_equals(b_copy, b));
    point_release(b_copy);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_c_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint c_copy = triangle_c(triangle);
    g_assert(c_copy != c);
    g_assert(point_equals(c_copy, c));
    point_release(c_copy);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_translate_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector vector = vector_new(1, 2);
    triangle_translate(triangle, vector);
    g_assert(double_equals(point_x(a) + 1, point_x(triangle->a)));
    g_assert(double_equals(point_y(a) + 2, point_y(triangle->a)));
    g_assert(double_equals(point_x(b) + 1, point_x(triangle->b)));
    g_assert(double_equals(point_y(b) + 2, point_y(triangle->b)));
    g_assert(double_equals(point_x(c) + 1, point_x(triangle->c)));
    g_assert(double_equals(point_y(c) + 2, point_y(triangle->c)));
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
    CGAngle angle = angle_in_degrees_new(0);
    triangle_rotate_around(triangle, center, angle);
    g_assert(double_equals(point_x(triangle->a), 0));
    g_assert(double_equals(point_y(triangle->a), 0));
    g_assert(double_equals(point_x(triangle->b), 1));
    g_assert(double_equals(point_y(triangle->b), 0));
    g_assert(double_equals(point_x(triangle->c), 0));
    g_assert(double_equals(point_y(triangle->c), 1));
    triangle_release(triangle);
    point_release(center);
    angle_release(angle);
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
    CGAngle angle = angle_in_degrees_new(90);
    triangle_rotate_around(triangle, center, angle);
    g_assert(double_equals(point_x(triangle->a), 2));
    g_assert(double_equals(point_y(triangle->a), 0));
    g_assert(double_equals(point_x(triangle->b), 2));
    g_assert(double_equals(point_y(triangle->b), 1));
    g_assert(double_equals(point_x(triangle->c), 1));
    g_assert(double_equals(point_y(triangle->c), 0));
    triangle_release(triangle);
    point_release(center);
    angle_release(angle);
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
    CGAngle angle = angle_in_degrees_new(180);
    triangle_rotate_around(triangle, center, angle);
    g_assert(double_equals(point_x(triangle->a), 2));
    g_assert(double_equals(point_y(triangle->a), 2));
    g_assert(double_equals(point_x(triangle->b), 1));
    g_assert(double_equals(point_y(triangle->b), 2));
    g_assert(double_equals(point_x(triangle->c), 2));
    g_assert(double_equals(point_y(triangle->c), 1));
    triangle_release(triangle);
    point_release(center);
    angle_release(angle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 1);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, c, b);
    g_assert_cmpint(triangle_orientation(triangle), ==, -1);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(2, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 0);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 0);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_orientation_5() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 0);
    CGPoint c = point_new(0, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert_cmpint(triangle_orientation(triangle), ==, 0);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_area_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(double_equals(triangle_area(triangle), 0.5));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_area_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(double_equals(triangle_area(triangle), 0));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_area_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 0);
    CGPoint c = point_new(0, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    g_assert(double_equals(triangle_area(triangle), 0));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_polygon_new_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(0, 1);
    ADTList points = list_new();
    list_append(points, c);
    list_append(points, b);
    list_append(points, a);
    list_append(points, d);
    CGPolygon polygon = polygon_new(points);
    g_assert(polygon != NULL);
    g_assert(polygon->vertices != NULL);
    g_assert_cmpint(list_size(polygon->vertices), ==, 4);
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 0), a));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 1), b));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 2), c));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 3), d));
    polygon_release(polygon);
    list_full_release(points, (void (*)(void *)) point_release);
}

static void test_polygon_new_2() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(2, 2));
    g_assert(polygon_new(vertices) == NULL);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_new_3() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(2, 0));
    list_append(vertices, point_new(2, 2));
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(0, 2));
    g_assert(polygon_new(vertices) == NULL);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_new_4() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(1, 0));
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(0, 1));
    g_assert(polygon_new(vertices) == NULL);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_new_5() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(1, 0));
    list_append(vertices, point_new(2, 0));
    list_append(vertices, point_new(2, 2));
    list_append(vertices, point_new(0, 2));
    g_assert(polygon_new(vertices) == NULL);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_new_triangle_1() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGPolygon polygon = polygon_new_triangle(a, b, c);
    g_assert(polygon == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_polygon_new_triangle_2() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 0);
    CGPolygon polygon = polygon_new_triangle(a, b, c);
    g_assert(polygon == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_polygon_new_triangle_3() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(0, 0);
    CGPoint c = point_new(0, 1);
    CGPolygon polygon = polygon_new_triangle(a, b, c);
    g_assert_cmpint(list_size(polygon->vertices), ==, 3);
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 0), b));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 1), a));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 2), c));
    polygon_release(polygon);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_polygon_new_rectangle_1() {
    CGPoint point = point_new(0, 0);
    g_assert(polygon_new_rectangle(point, 0, 1) == NULL);
    g_assert(polygon_new_rectangle(point, 1, 0) == NULL);
    point_release(point);
}

static void test_polygon_new_rectangle_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 2);
    CGPoint d = point_new(0, 2);
    CGPolygon polygon = polygon_new_rectangle(a, 1, 2);
    g_assert_cmpint(list_size(polygon->vertices), ==, 4);
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 0), a));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 1), b));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 2), c));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 3), d));
    polygon_release(polygon);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_polygon_new_square_1() {
    CGPoint point = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(point, 0);
    g_assert(polygon == NULL);
    point_release(point);
}

static void test_polygon_new_square_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(0, 1);
    CGPolygon polygon = polygon_new_square(a, 1);
    g_assert_cmpint(list_size(polygon->vertices), ==, 4);
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 0), a));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 1), b));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 2), c));
    g_assert(point_equals((CGPoint) list_at(polygon->vertices, 3), d));
    polygon_release(polygon);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_polygon_release_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_equals_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left, 2);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 0);
    point_release(lower_left);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_equals_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(0, 1);
    ADTList points1 = list_new();
    ADTList points2 = list_new();
    list_append(points1, c);
    list_append(points1, b);
    list_append(points1, a);
    list_append(points1, d);
    list_append(points2, a);
    list_append(points2, b);
    list_append(points2, c);
    list_append(points2, d);
    CGPolygon polygon1 = polygon_new(points1);
    CGPolygon polygon2 = polygon_new(points2);
    g_assert_cmpint(polygon_equals(polygon1, polygon2), ==, 1);
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    list_release(points1);
    list_release(points2);
}

static void test_polygon_dup_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPolygon dup = polygon_dup(polygon);
    g_assert(dup != NULL);
    g_assert(dup != polygon);
    g_assert(dup->vertices != polygon->vertices);
    g_assert(list_equals_cmp(polygon->vertices, dup->vertices,
                             (int (*)(void *, void *)) point_equals));
    point_release(lower_left);
    polygon_release(polygon);
    polygon_release(dup);
}

static void test_polygon_to_str_1() {
    char *polygon_str =
        (char *) "<< Polygon: (0.0, 0.0); (1.0, 0.0); (1.0, 1.0); (0.0, 1.0) >>";
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    char *str = polygon_to_str(polygon, 1);
    g_assert_cmpstr(str, ==, polygon_str);
    free(str);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_vertices_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    ADTList vertices = polygon_vertices(polygon);
    g_assert(vertices != NULL);
    g_assert(polygon->vertices != vertices);
    g_assert(list_equals_cmp(polygon->vertices, vertices,
                             (int (*)(void *, void *)) point_equals));
    polygon_release(polygon);
    point_release(lower_left);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_edges_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(0, 1);
    ADTList vertices = list_new();
    list_append(vertices, a);
    list_append(vertices, b);
    list_append(vertices, c);
    list_append(vertices, d);
    CGPolygon polygon = polygon_new(vertices);
    ADTList segments = list_new();
    list_append(segments, segment_new(a, b));
    list_append(segments, segment_new(b, c));
    list_append(segments, segment_new(c, d));
    list_append(segments, segment_new(d, a));
    ADTList edges = polygon_edges(polygon);
    g_assert(list_equals_cmp(segments, edges, (int (*)(void *, void *)) segment_equals));
    list_full_release(segments, (void (*)(void *)) segment_release);
    list_full_release(edges, (void (*)(void *)) segment_release);
    list_full_release(vertices, (void (*)(void *)) point_release);
    polygon_release(polygon);
}

static void test_polygon_translate_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGVector vector = vector_new(1, 1);
    polygon_translate(polygon, vector);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 0)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 0)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 1)), 2));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 2)), 2));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 2)), 2));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 3)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 3)), 2));
    vector_release(vector);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_translate_2() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGVector vector = vector_new(0, 0);
    polygon_translate(polygon, vector);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 0)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 1)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 3)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 3)), 1));
    vector_release(vector);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_rotate_around_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(1, 1);
    CGAngle angle = angle_in_degrees_new(0);
    polygon_rotate_around(polygon, center, angle);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 0)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 1)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 3)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 3)), 1));
    point_release(center);
    angle_release(angle);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_rotate_around_2() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(0.5, 0.5);
    CGAngle angle = angle_in_degrees_new(90);
    polygon_rotate_around(polygon, center, angle);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 0)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 0)), 0));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 2)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 3)), 0));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 3)), 0));
    point_release(center);
    angle_release(angle);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_rotate_around_3() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(1, 1);
    CGAngle angle = angle_in_degrees_new(180);
    polygon_rotate_around(polygon, center, angle);
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 0)), 2));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 0)), 2));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 1)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 1)), 2));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 2)), 1));
    g_assert(double_equals(point_x((CGPoint) list_at(polygon->vertices, 3)), 2));
    g_assert(double_equals(point_y((CGPoint) list_at(polygon->vertices, 3)), 1));
    point_release(center);
    angle_release(angle);
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_area_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    g_assert(double_equals(polygon_area(polygon), 1));
    polygon_release(polygon);
    point_release(lower_left);
}

static void test_polygon_area_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGPolygon polygon = polygon_new_triangle(a, b, c);
    g_assert(double_equals(polygon_area(polygon), 0.5));
    polygon_release(polygon);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_circle_new_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert(circle != NULL);
    g_assert(circle->center != NULL);
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
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    point_release(center);
    circle_release(circle);
}

static void test_circle_equals_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle1 = circle_new(center, 3);
    CGCircle circle2 = circle_new(center, 4);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    point_release(center);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_2() {
    CGPoint center1 = point_new(1, 1);
    CGPoint center2 = point_new(1, 2);
    CGCircle circle1 = circle_new(center1, 1);
    CGCircle circle2 = circle_new(center2, 1);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 0);
    point_release(center1);
    point_release(center2);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_equals_3() {
    CGPoint center1 = point_new(1, 1);
    CGPoint center2 = point_new(1, 1);
    CGCircle circle1 = circle_new(center1, 1);
    CGCircle circle2 = circle_new(center2, 1);
    g_assert_cmpint(circle_equals(circle1, circle2), ==, 1);
    point_release(center1);
    point_release(center2);
    circle_release(circle1);
    circle_release(circle2);
}

static void test_circle_dup_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle = circle_new(center, 3);
    CGCircle dup = circle_dup(circle);
    g_assert(dup != NULL);
    g_assert(dup != circle);
    g_assert(point_equals(dup->center, circle->center));
    g_assert(double_equals(dup->radius, circle->radius));
    point_release(center);
    circle_release(dup);
    circle_release(circle);
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

static void test_circle_center_1() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle = circle_new(center1, 1);
    CGPoint center2 = circle_center(circle);
    g_assert(center2 != NULL);
    g_assert(center1 != center2);
    g_assert(point_equals(center1, center2));
    point_release(center1);
    point_release(center2);
    circle_release(circle);
}

static void test_circle_center_x_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle = circle_new(center, 3);
    g_assert(double_equals(circle_center_x(circle), 1));
    point_release(center);
    circle_release(circle);
}

static void test_circle_center_y_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle = circle_new(center, 3);
    g_assert(double_equals(circle_center_y(circle), 2));
    point_release(center);
    circle_release(circle);
}

static void test_circle_radius_1() {
    CGPoint center = point_new(1, 2);
    CGCircle circle = circle_new(center, 3);
    g_assert(double_equals(circle_radius(circle), 3));
    point_release(center);
    circle_release(circle);
}

static void test_circle_area_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert(double_equals(circle_area(circle), M_PI));
    point_release(center);
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

static void test_circle_rotate_around_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGAngle angle = angle_in_radians_new(M_PI);
    circle_rotate_around(circle, center, angle);
    g_assert(double_equals(point_x(circle->center), 1));
    g_assert(double_equals(point_y(circle->center), 1));
    angle_release(angle);
    point_release(center);
    circle_release(circle);
}

static void test_circle_rotate_around_2() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGAngle angle = angle_in_radians_new(0);
    CGPoint point = point_new(2, 2);
    circle_rotate_around(circle, point, angle);
    g_assert(double_equals(point_x(circle->center), 1));
    g_assert(double_equals(point_y(circle->center), 1));
    angle_release(angle);
    point_release(center);
    point_release(point);
    circle_release(circle);
}

static void test_circle_rotate_around_3() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGAngle angle = angle_in_radians_new(M_PI / 2);
    CGPoint point = point_new(2, 2);
    circle_rotate_around(circle, point, angle);
    g_assert(double_equals(point_x(circle->center), 3));
    g_assert(double_equals(point_y(circle->center), 1));
    angle_release(angle);
    point_release(center);
    point_release(point);
    circle_release(circle);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/gc/angle_in_radians_new", test_angle_in_radians_new_1);
    g_test_add_func("/gc/angle_in_radians_new", test_angle_in_radians_new_2);
    g_test_add_func("/gc/angle_in_radians_new", test_angle_in_radians_new_3);
    g_test_add_func("/gc/angle_in_degrees_new", test_angle_in_degrees_new_1);
    g_test_add_func("/gc/angle_in_degrees_new", test_angle_in_degrees_new_2);
    g_test_add_func("/gc/angle_in_degrees_new", test_angle_in_degrees_new_3);
    g_test_add_func("/gc/angle_release", test_angle_release_1);
    g_test_add_func("/gc/angle_equals", test_angle_equals_1);
    g_test_add_func("/gc/angle_equals", test_angle_equals_2);
    g_test_add_func("/gc/angle_equals", test_angle_equals_3);
    g_test_add_func("/gc/angle_lt", test_angle_lt_1);
    g_test_add_func("/gc/angle_lt", test_angle_lt_2);
    g_test_add_func("/gc/angle_lt", test_angle_lt_3);
    g_test_add_func("/gc/angle_lte", test_angle_lte_1);
    g_test_add_func("/gc/angle_lte", test_angle_lte_2);
    g_test_add_func("/gc/angle_lte", test_angle_lte_3);
    g_test_add_func("/gc/angle_gt", test_angle_gt_1);
    g_test_add_func("/gc/angle_gt", test_angle_gt_2);
    g_test_add_func("/gc/angle_gt", test_angle_gt_3);
    g_test_add_func("/gc/angle_gte", test_angle_gte_1);
    g_test_add_func("/gc/angle_gte", test_angle_gte_2);
    g_test_add_func("/gc/angle_gte", test_angle_gte_3);
    g_test_add_func("/gc/angle_dup", test_angle_dup_1);
    g_test_add_func("/gc/angle_to_str", test_angle_to_str_1);
    g_test_add_func("/gc/angle_sum", test_angle_sum_1);
    g_test_add_func("/gc/angle_sum", test_angle_sum_2);
    g_test_add_func("/gc/angle_subtract", test_angle_subtract_1);
    g_test_add_func("/gc/angle_subtract", test_angle_subtract_2);
    g_test_add_func("/gc/angle_in_radians", test_angle_in_radians_1);
    g_test_add_func("/gc/angle_in_degrees", test_angle_in_degrees_1);
    g_test_add_func("/gc/vector_new", test_vector_new_1);
    g_test_add_func("/gc/vector_from_point_to_point", test_vector_from_point_to_point_1);
    g_test_add_func("/gc/vector_release", test_vector_release_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_1);
    g_test_add_func("/gc/vector_equals", test_vector_equals_2);
    g_test_add_func("/gc/vector_equals", test_vector_equals_3);
    g_test_add_func("/gc/vector_equals", test_vector_equals_4);
    g_test_add_func("/gc/vector_dup", test_vector_dup_1);
    g_test_add_func("/gc/vector_to_str", test_vector_to_str_1);
    g_test_add_func("/gc/vector_x", test_vector_x_1);
    g_test_add_func("/gc/vector_y", test_vector_y_1);
    g_test_add_func("/gc/vector_right_perpendicular_axis",
                    test_vector_right_perpendicular_axis_1);
    g_test_add_func("/gc/vector_right_perpendicular_axis",
                    test_vector_right_perpendicular_axis_2);
    g_test_add_func("/gc/vector_left_perpendicular_axis",
                    test_vector_left_perpendicular_axis_1);
    g_test_add_func("/gc/vector_left_perpendicular_axis",
                    test_vector_left_perpendicular_axis_2);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_1);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_2);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_3);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_4);
    g_test_add_func("/gc/vector_normalize", test_vector_normalize_5);
    g_test_add_func("/gc/vector_reverse", test_vector_reverse_1);
    g_test_add_func("/gc/vector_sum", test_vector_sum_1);
    g_test_add_func("/gc/vector_sum", test_vector_sum_2);
    g_test_add_func("/gc/vector_subtract", test_vector_subtract_1);
    g_test_add_func("/gc/vector_subtract", test_vector_subtract_2);
    g_test_add_func("/gc/vector_multiply", test_vector_multiply_1);
    g_test_add_func("/gc/vector_multiply", test_vector_multiply_2);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_1);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_2);
    g_test_add_func("/gc/vector_magnitude", test_vector_magnitude_3);
    g_test_add_func("/gc/vector_dot", test_vector_dot_1);
    g_test_add_func("/gc/vector_dot", test_vector_dot_2);
    g_test_add_func("/gc/vector_dot", test_vector_dot_3);
    g_test_add_func("/gc/vector_dot", test_vector_dot_4);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_1);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_2);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_3);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_4);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_5);
    g_test_add_func("/gc/vector_angle_to", test_vector_angle_to_6);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_1);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_2);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_3);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_4);
    g_test_add_func("/gc/vector_rotate", test_vector_rotate_5);
    g_test_add_func("/gc/point_new", test_point_new_1);
    g_test_add_func("/gc/midpoint_between", test_midpoint_between_1);
    g_test_add_func("/gc/point_release", test_point_release_1);
    g_test_add_func("/gc/point_equals", test_point_equals_1);
    g_test_add_func("/gc/point_equals", test_point_equals_2);
    g_test_add_func("/gc/point_equals", test_point_equals_3);
    g_test_add_func("/gc/point_equals", test_point_equals_4);
    g_test_add_func("/gc/point_equals", test_point_equals_5);
    g_test_add_func("/gc/point_dup", test_point_dup_1);
    g_test_add_func("/gc/point_to_str", test_point_to_str_1);
    g_test_add_func("/gc/point_x", test_point_x_1);
    g_test_add_func("/gc/point_x", test_point_x_2);
    g_test_add_func("/gc/point_y", test_point_y_1);
    g_test_add_func("/gc/point_y", test_point_y_2);
    g_test_add_func("/gc/point_vector_from_origin", test_point_vector_from_origin_1);
    g_test_add_func("/gc/point_vector_from_origin", test_point_vector_from_origin_2);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_1);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_2);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_3);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_4);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_5);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_6);
    g_test_add_func("/gc/point_projection_on_axis", test_point_projection_on_axis_7);
    g_test_add_func("/gc/point_translate", test_point_translate_1);
    g_test_add_func("/gc/point_translate", test_point_translate_2);
    g_test_add_func("/gc/point_translate", test_point_translate_3);
    g_test_add_func("/gc/point_translate", test_point_translate_4);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_1);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_2);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_3);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_4);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_5);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_6);
    g_test_add_func("/gc/point_rotate_around", test_point_rotate_around_7);
    g_test_add_func("/gc/point_normalize", test_point_normalize_1);
    g_test_add_func("/gc/point_distance_to_point", test_point_distance_to_point_1);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_1);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_2);
    g_test_add_func("/gc/point_distance_to_line", test_point_distance_to_line_3);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_1);
    g_test_add_func("/gc/point_is_in_line", test_point_is_in_line_2);
    g_test_add_func("/gc/point_is_in_segment", test_point_is_in_segment_1);
    g_test_add_func("/gc/point_is_in_segment", test_point_is_in_segment_2);
    g_test_add_func("/gc/point_is_in_segment", test_point_is_in_segment_3);
    g_test_add_func("/gc/point_is_in_segment", test_point_is_in_segment_4);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_1);
    g_test_add_func("/gc/point_is_in_triangle", test_point_is_in_triangle_2);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_1);
    g_test_add_func("/gc/point_is_in_polygon", test_point_is_in_polygon_2);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_1);
    g_test_add_func("/gc/point_is_in_circle", test_point_is_in_circle_2);
    g_test_add_func("/gc/point_intersection_of_lines", test_point_intersection_of_lines_1);
    g_test_add_func("/gc/point_intersection_of_lines", test_point_intersection_of_lines_2);
    g_test_add_func("/gc/point_intersection_of_lines", test_point_intersection_of_lines_3);
    g_test_add_func("/gc/point_intersection_of_segments",
                    test_point_intersection_of_segments_1);
    g_test_add_func("/gc/point_intersection_of_segments",
                    test_point_intersection_of_segments_2);
    g_test_add_func("/gc/point_intersection_of_segments",
                    test_point_intersection_of_segments_3);
    g_test_add_func("/gc/point_intersection_of_segments",
                    test_point_intersection_of_segments_4);
    g_test_add_func("/gc/point_intersection_of_segments",
                    test_point_intersection_of_segments_5);
    g_test_add_func("/gc/line_new", test_line_new_1);
    g_test_add_func("/gc/line_new", test_line_new_2);
    g_test_add_func("/gc/line_new", test_line_new_3);
    g_test_add_func("/gc/line_new", test_line_new_4);
    g_test_add_func("/gc/line_release", test_line_release_1);
    g_test_add_func("/gc/line_equals", test_line_equals_1);
    g_test_add_func("/gc/line_equals", test_line_equals_2);
    g_test_add_func("/gc/line_dup", test_line_dup_1);
    g_test_add_func("/gc/line_to_str", test_line_to_str_1);
    g_test_add_func("/gc/line_perpendicular", test_line_perpendicular_1);
    g_test_add_func("/gc/line_normalize", test_line_normalize_1);
    g_test_add_func("/gc/segment_new", test_segment_new_1);
    g_test_add_func("/gc/segment_new", test_segment_new_2);
    g_test_add_func("/gc/segment_release", test_segment_release_1);
    g_test_add_func("/gc/segment_equals", test_segment_equals_1);
    g_test_add_func("/gc/segment_dup", test_segment_dup_1);
    g_test_add_func("/gc/segment_to_str", test_segment_to_str_1);
    g_test_add_func("/gc/segment_a", test_segment_a_1);
    g_test_add_func("/gc/segment_b", test_segment_b_1);
    g_test_add_func("/gc/segment_line", test_segment_line_1);
    g_test_add_func("/gc/segment_line", test_segment_line_2);
    g_test_add_func("/gc/segment_translate", test_segment_translate_1);
    g_test_add_func("/gc/segment_translate", test_segment_translate_2);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_1);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_2);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_3);
    g_test_add_func("/gc/segment_rotate_around", test_segment_rotate_around_4);
    g_test_add_func("/gc/segment_length", test_segment_length_1);
    g_test_add_func("/gc/segment_length", test_segment_length_2);
    g_test_add_func("/gc/triangle_new", test_triangle_new_1);
    g_test_add_func("/gc/triangle_new", test_triangle_new_2);
    g_test_add_func("/gc/triangle_new", test_triangle_new_3);
    g_test_add_func("/gc/triangle_release", test_triangle_release_1);
    g_test_add_func("/gc/triangle_equals", test_triangle_equals_1);
    g_test_add_func("/gc/triangle_equals", test_triangle_equals_2);
    g_test_add_func("/gc/triangle_dup", test_triangle_dup_1);
    g_test_add_func("/gc/triangle_to_str", test_triangle_to_str_1);
    g_test_add_func("/gc/triangle_a", test_triangle_a_1);
    g_test_add_func("/gc/triangle_b", test_triangle_b_1);
    g_test_add_func("/gc/triangle_c", test_triangle_c_1);
    g_test_add_func("/gc/triangle_translate", test_triangle_translate_1);
    g_test_add_func("/gc/triangle_translate", test_triangle_translate_2);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_1);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_2);
    g_test_add_func("/gc/triangle_rotate_around", test_triangle_rotate_around_3);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_1);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_2);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_3);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_4);
    g_test_add_func("/gc/triangle_orientation", test_triangle_orientation_5);
    g_test_add_func("/gc/triangle_area", test_triangle_area_1);
    g_test_add_func("/gc/triangle_area", test_triangle_area_2);
    g_test_add_func("/gc/triangle_area", test_triangle_area_3);
    g_test_add_func("/gc/polygon_new", test_polygon_new_1);
    g_test_add_func("/gc/polygon_new", test_polygon_new_2);
    g_test_add_func("/gc/polygon_new", test_polygon_new_3);
    g_test_add_func("/gc/polygon_new", test_polygon_new_4);
    g_test_add_func("/gc/polygon_new", test_polygon_new_5);
    g_test_add_func("/gc/polygon_new_triangle", test_polygon_new_triangle_1);
    g_test_add_func("/gc/polygon_new_triangle", test_polygon_new_triangle_2);
    g_test_add_func("/gc/polygon_new_triangle", test_polygon_new_triangle_3);
    g_test_add_func("/gc/polygon_new_rectangle", test_polygon_new_rectangle_1);
    g_test_add_func("/gc/polygon_new_rectangle", test_polygon_new_rectangle_2);
    g_test_add_func("/gc/polygon_new_square", test_polygon_new_square_1);
    g_test_add_func("/gc/polygon_new_square", test_polygon_new_square_2);
    g_test_add_func("/gc/polygon_release", test_polygon_release_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_1);
    g_test_add_func("/gc/polygon_equals", test_polygon_equals_2);
    g_test_add_func("/gc/polygon_dup", test_polygon_dup_1);
    g_test_add_func("/gc/polygon_to_str", test_polygon_to_str_1);
    g_test_add_func("/gc/polygon_vertices", test_polygon_vertices_1);
    g_test_add_func("/gc/polygon_edges", test_polygon_edges_1);
    g_test_add_func("/gc/polygon_translate", test_polygon_translate_1);
    g_test_add_func("/gc/polygon_translate", test_polygon_translate_2);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_1);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_2);
    g_test_add_func("/gc/polygon_rotate_around", test_polygon_rotate_around_3);
    g_test_add_func("/gc/polygon_area", test_polygon_area_1);
    g_test_add_func("/gc/polygon_area", test_polygon_area_2);
    g_test_add_func("/gc/circle_new", test_circle_new_1);
    g_test_add_func("/gc/circle_new", test_circle_new_2);
    g_test_add_func("/gc/circle_release", test_circle_release_1);
    g_test_add_func("/gc/circle_equals", test_circle_equals_1);
    g_test_add_func("/gc/circle_equals", test_circle_equals_2);
    g_test_add_func("/gc/circle_equals", test_circle_equals_3);
    g_test_add_func("/gc/circle_dup", test_circle_dup_1);
    g_test_add_func("/gc/circle_to_str", test_circle_to_str_1);
    g_test_add_func("/gc/circle_center", test_circle_center_1);
    g_test_add_func("/gc/circle_center_x", test_circle_center_x_1);
    g_test_add_func("/gc/circle_center_y", test_circle_center_y_1);
    g_test_add_func("/gc/circle_radius", test_circle_radius_1);
    g_test_add_func("/gc/circle_area", test_circle_area_1);
    g_test_add_func("/gc/circle_translate", test_circle_translate_1);
    g_test_add_func("/gc/circle_translate", test_circle_translate_2);
    g_test_add_func("/gc/circle_rotate_around", test_circle_rotate_around_1);
    g_test_add_func("/gc/circle_rotate_around", test_circle_rotate_around_2);
    g_test_add_func("/gc/circle_rotate_around", test_circle_rotate_around_3);
    return g_test_run();
}

