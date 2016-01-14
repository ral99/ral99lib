#include <glib.h>
#include <math.h>
#include <stdlib.h>

#include "cg/collision/collision.h"
#include "cg/cg.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

static void test_polygon_min_projection_on_axis_1() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(1, 0));
    list_append(vertices, point_new(0, 1));
    list_append(vertices, point_new(1, 1));
    CGPolygon polygon = polygon_new(vertices);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(polygon_min_projection_on_axis(polygon, axis), 0));
    vector_release(axis);
    polygon_release(polygon);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_min_projection_on_axis_2() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(2, 1));
    list_append(vertices, point_new(1, 2));
    list_append(vertices, point_new(2, 2));
    CGPolygon polygon = polygon_new(vertices);
    CGVector axis = vector_new(sqrt(2) / 2,  sqrt(2) / 2);
    g_assert(double_equals(polygon_min_projection_on_axis(polygon, axis), sqrt(2)));
    vector_release(axis);
    polygon_release(polygon);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_max_projection_on_axis_1() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(1, 0));
    list_append(vertices, point_new(0, 1));
    list_append(vertices, point_new(1, 1));
    CGPolygon polygon = polygon_new(vertices);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(polygon_max_projection_on_axis(polygon, axis), 1));
    vector_release(axis);
    polygon_release(polygon);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_max_projection_on_axis_2() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(1, 1));
    list_append(vertices, point_new(2, 1));
    list_append(vertices, point_new(1, 2));
    list_append(vertices, point_new(2, 2));
    CGPolygon polygon = polygon_new(vertices);
    CGVector axis = vector_new(sqrt(2) / 2,  sqrt(2) / 2);
    g_assert(double_equals(polygon_max_projection_on_axis(polygon, axis), 2 * sqrt(2)));
    vector_release(axis);
    polygon_release(polygon);
    list_full_release(vertices, (void (*)(void *)) point_release);
}

static void test_polygon_perpendicular_axes_1() {
    ADTList vertices = list_new();
    list_append(vertices, point_new(0, 0));
    list_append(vertices, point_new(2, 0));
    list_append(vertices, point_new(2, 3));
    list_append(vertices, point_new(0, 3));
    CGPolygon polygon = polygon_new(vertices);
    ADTList perpendicular_axes = polygon_perpendicular_axes(polygon);
    g_assert_cmpint(list_size(perpendicular_axes), ==, 4);
    CGVector axis = (CGVector) list_at(perpendicular_axes, 0);
    g_assert(double_equals(vector_x(axis), 0));
    g_assert(double_equals(vector_y(axis), -1));
    axis = (CGVector) list_at(perpendicular_axes, 1);
    g_assert(double_equals(vector_x(axis), 1));
    g_assert(double_equals(vector_y(axis), 0));
    axis = (CGVector) list_at(perpendicular_axes, 2);
    g_assert(double_equals(vector_x(axis), 0));
    g_assert(double_equals(vector_y(axis), 1));
    axis = (CGVector) list_at(perpendicular_axes, 3);
    g_assert(double_equals(vector_x(axis), -1));
    g_assert(double_equals(vector_y(axis), 0));
    polygon_release(polygon);
    list_full_release(vertices, (void (*)(void *)) point_release);
    list_full_release(perpendicular_axes, (void (*)(void *)) vector_release);
}

static void test_polygon_is_in_contact_with_polygon_1() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_2() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_3() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_4() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(-1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_5() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_6() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, -1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_in_contact_with_polygon_7() {
    CGPoint lower_left1 = point_new(0, 1);
    CGPolygon polygon1 = polygon_new_rectangle(lower_left1, 2, 1);
    CGPoint lower_left2 = point_new(5, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_in_contact_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_1() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_2() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_3() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_4() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(0, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_5() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(-1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_6() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(0, -1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_7() {
    CGPoint lower_left1 = point_new(0, 1);
    CGPolygon polygon1 = polygon_new_rectangle(lower_left1, 2, 1);
    CGPoint lower_left2 = point_new(5, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 0);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_8() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 3);
    CGPoint lower_left2 = point_new(1, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_is_colliding_with_polygon_9() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 3);
    ADTList vertices2 = list_new();
    list_append(vertices2, point_new(1, 1.5));
    list_append(vertices2, point_new(1.5, 1));
    list_append(vertices2, point_new(1.5, 2));
    list_append(vertices2, point_new(2, 1.5));
    CGPolygon polygon2 = polygon_new(vertices2);
    g_assert_cmpint(polygon_is_colliding_with_polygon(polygon1, polygon2), ==, 1);
    point_release(lower_left1);
    polygon_release(polygon1);
    polygon_release(polygon2);
    list_full_release(vertices2, (void (*)(void *)) point_release);
}

static void test_polygon_point_of_contact_with_polygon_1() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(3, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert(polygon_point_of_contact_with_polygon(polygon1, polygon2) == NULL);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_2() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    g_assert(polygon_point_of_contact_with_polygon(polygon1, polygon2) == NULL);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_3() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGPoint point_of_contact = polygon_point_of_contact_with_polygon(polygon1, polygon2);
    g_assert(double_equals(point_x(point_of_contact), 2));
    g_assert(double_equals(point_y(point_of_contact), 1));
    point_release(point_of_contact);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_4() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(0, 2);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGPoint point_of_contact = polygon_point_of_contact_with_polygon(polygon1, polygon2);
    g_assert(double_equals(point_x(point_of_contact), 1));
    g_assert(double_equals(point_y(point_of_contact), 2));
    point_release(point_of_contact);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_5() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(-2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGPoint point_of_contact = polygon_point_of_contact_with_polygon(polygon1, polygon2);
    g_assert(double_equals(point_x(point_of_contact), 0));
    g_assert(double_equals(point_y(point_of_contact), 1));
    point_release(point_of_contact);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_6() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(0, -2);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGPoint point_of_contact = polygon_point_of_contact_with_polygon(polygon1, polygon2);
    g_assert(double_equals(point_x(point_of_contact), 1));
    g_assert(double_equals(point_y(point_of_contact), 0));
    point_release(point_of_contact);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_point_of_contact_with_polygon_7() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(1, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGPoint point_of_contact = polygon_point_of_contact_with_polygon(polygon1, polygon2);
    g_assert(double_equals(point_x(point_of_contact), 1));
    g_assert(double_equals(point_y(point_of_contact), 1));
    point_release(point_of_contact);
    point_release(lower_left1);
    point_release(lower_left2);
    polygon_release(polygon1);
    polygon_release(polygon2);
}

static void test_polygon_mtv_from_polygon_1() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGVector null_vector = vector_new(0, 0);
    g_assert(polygon_mtv_from_polygon(polygon1, polygon2, null_vector) == NULL);
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(null_vector);
}

static void test_polygon_mtv_from_polygon_2() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(3, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 5));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_3() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(3, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(-1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_4() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(3, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, 1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_5() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(3, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, -1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_6() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 4));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_7() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(-1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_8() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, 1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 2));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_9() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, -1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), -2));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_10() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 3));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_11() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(-1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), -1));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_12() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, 1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), 2));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_13() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 2);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 2);
    CGVector axis = vector_new(0, -1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), -2));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_14() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 1));
    g_assert(double_equals(vector_y(mtv), 1));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_15() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGVector axis = vector_new(-sqrt(2) / 2, -sqrt(2) / 2);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), -1));
    g_assert(double_equals(vector_y(mtv), -1));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left1);
    point_release(lower_left2);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_16() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(2.1, 1);
    CGPolygon polygon1 = polygon_new_triangle(a, b, c);
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left, 1);
    CGVector axis = vector_new(1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 3));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left);
    point_release(a);
    point_release(b);
    point_release(c);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_17() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(2.1, 1);
    CGPolygon polygon1 = polygon_new_triangle(a, b, c);
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left, 1);
    CGVector axis = vector_new(-1, 0);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), -0.1));
    g_assert(double_equals(vector_y(mtv), 0));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left);
    point_release(a);
    point_release(b);
    point_release(c);
    vector_release(axis);
    vector_release(mtv);
}

static void test_polygon_mtv_from_polygon_18() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(2.1, 1);
    CGPolygon polygon1 = polygon_new_triangle(a, b, c);
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left, 1);
    CGVector axis = vector_new(0, -1);
    CGVector mtv = polygon_mtv_from_polygon(polygon1, polygon2, axis);
    g_assert(double_equals(vector_x(mtv), 0));
    g_assert(double_equals(vector_y(mtv), -1));
    polygon_release(polygon1);
    polygon_release(polygon2);
    point_release(lower_left);
    point_release(a);
    point_release(b);
    point_release(c);
    vector_release(axis);
    vector_release(mtv);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/gc/polygon_min_projection_on_axis", test_polygon_min_projection_on_axis_1);
    g_test_add_func("/gc/polygon_min_projection_on_axis", test_polygon_min_projection_on_axis_2);
    g_test_add_func("/gc/polygon_max_projection_on_axis", test_polygon_max_projection_on_axis_1);
    g_test_add_func("/gc/polygon_max_projection_on_axis", test_polygon_max_projection_on_axis_2);
    g_test_add_func("/gc/polygon_perpendicular_axes", test_polygon_perpendicular_axes_1);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_1);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_2);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_3);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_4);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_5);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_6);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon", test_polygon_is_in_contact_with_polygon_7);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_1);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_2);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_3);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_4);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_5);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_6);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_7);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_8);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon", test_polygon_is_colliding_with_polygon_9);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_1);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_2);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_3);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_4);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_5);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_6);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon", test_polygon_point_of_contact_with_polygon_7);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_1);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_2);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_3);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_4);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_5);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_6);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_7);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_8);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_9);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_10);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_11);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_12);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_13);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_14);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_15);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_16);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_17);
    g_test_add_func("/gc/polygon_mtv_from_polygon", test_polygon_mtv_from_polygon_18);
    return g_test_run();
}

