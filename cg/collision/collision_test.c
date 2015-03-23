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

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/gc/polygon_min_projection_on_axis",
                    test_polygon_min_projection_on_axis_1);
    g_test_add_func("/gc/polygon_min_projection_on_axis",
                    test_polygon_min_projection_on_axis_2);
    g_test_add_func("/gc/polygon_max_projection_on_axis",
                    test_polygon_max_projection_on_axis_1);
    g_test_add_func("/gc/polygon_max_projection_on_axis",
                    test_polygon_max_projection_on_axis_2);
    g_test_add_func("/gc/polygon_perpendicular_axes", test_polygon_perpendicular_axes_1);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_1);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_2);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_3);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_4);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_5);
    g_test_add_func("/gc/polygon_is_in_contact_with_polygon",
                    test_polygon_is_in_contact_with_polygon_6);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_1);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_2);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_3);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_4);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_5);
    g_test_add_func("/gc/polygon_is_colliding_with_polygon",
                    test_polygon_is_colliding_with_polygon_6);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_1);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_2);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_3);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_4);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_5);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_6);
    g_test_add_func("/gc/polygon_point_of_contact_with_polygon",
                    test_polygon_point_of_contact_with_polygon_7);
    return g_test_run();
}

