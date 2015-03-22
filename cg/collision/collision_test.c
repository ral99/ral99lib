#include <glib.h>
#include <math.h>
#include <stdlib.h>

#include "cg/collision/collision.h"
#include "cg/cg.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

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

static void test_polygon_is_in_contact_with_circle_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 0);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_is_in_contact_with_circle_2() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 0);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_is_in_contact_with_circle_3() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_is_in_contact_with_circle_4() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 3);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_is_in_contact_with_circle_5() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(-1, 1);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_polygon_is_in_contact_with_circle_6() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, -1);
    CGCircle circle = circle_new(center, 1);
    g_assert_cmpint(polygon_is_in_contact_with_circle(polygon, circle), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_1() {
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 0);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_2() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 0);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_3() {
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_4() {
    CGPoint center = point_new(1, 3);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_5() {
    CGPoint center = point_new(-1, 1);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

static void test_circle_is_in_contact_with_polygon_6() {
    CGPoint center = point_new(1, -1);
    CGCircle circle = circle_new(center, 1);
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    g_assert_cmpint(circle_is_in_contact_with_polygon(circle, polygon), ==, 1);
    point_release(lower_left);
    point_release(center);
    polygon_release(polygon);
    circle_release(circle);
}

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

static void test_circle_min_projection_on_axis_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(circle_min_projection_on_axis(circle, axis), 0));
    vector_release(axis);
    point_release(center);
    circle_release(circle);
}

static void test_circle_min_projection_on_axis_2() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    g_assert(double_equals(circle_min_projection_on_axis(circle, axis), sqrt(2) - 1));
    vector_release(axis);
    point_release(center);
    circle_release(circle);
}

static void test_circle_max_projection_on_axis_1() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(circle_max_projection_on_axis(circle, axis), 2));
    vector_release(axis);
    point_release(center);
    circle_release(circle);
}

static void test_circle_max_projection_on_axis_2() {
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    g_assert(double_equals(circle_max_projection_on_axis(circle, axis), sqrt(2) + 1));
    vector_release(axis);
    point_release(center);
    circle_release(circle);
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

static void test_collision_new_1() {
    CGVector mtv = vector_new(1, 2);
    CGPoint point = point_new(1, 2);
    CGCollision collision = collision_new(mtv, point);
    g_assert(collision != NULL);
    g_assert(collision->mtv != mtv);
    g_assert(vector_equals(collision->mtv, mtv));
    g_assert(collision->point != point);
    g_assert(point_equals(collision->point, point));
    vector_release(mtv);
    point_release(point);
    collision_release(collision);
}

static void test_polygon_and_polygon_collision_1() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(2, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGCollision collision = polygon_and_polygon_collision(polygon1, polygon2);
    g_assert(collision == NULL);
    point_release(lower_left1);
    polygon_release(polygon1);
    point_release(lower_left2);
    polygon_release(polygon2);
}

static void test_polygon_and_polygon_collision_2() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(1, 1);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGCollision collision = polygon_and_polygon_collision(polygon1, polygon2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(lower_left1);
    polygon_release(polygon1);
    point_release(lower_left2);
    polygon_release(polygon2);
}

static void test_polygon_and_polygon_collision_3() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(1, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGCollision collision = polygon_and_polygon_collision(polygon1, polygon2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 0.5));
    collision_release(collision);
    point_release(lower_left1);
    polygon_release(polygon1);
    point_release(lower_left2);
    polygon_release(polygon2);
}

static void test_polygon_and_polygon_collision_4() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0.9, 0);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGCollision collision = polygon_and_polygon_collision(polygon1, polygon2);
    g_assert(double_equals(vector_x(collision->mtv), 0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 0.5));
    collision_release(collision);
    point_release(lower_left1);
    polygon_release(polygon1);
    point_release(lower_left2);
    polygon_release(polygon2);
}

static void test_polygon_and_polygon_collision_5() {
    CGPoint lower_left1 = point_new(0, 0);
    CGPolygon polygon1 = polygon_new_square(lower_left1, 1);
    CGPoint lower_left2 = point_new(0, 0.9);
    CGPolygon polygon2 = polygon_new_square(lower_left2, 1);
    CGCollision collision = polygon_and_polygon_collision(polygon1, polygon2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0.1));
    g_assert(double_equals(point_x(collision->point), 0.5));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(lower_left1);
    polygon_release(polygon1);
    point_release(lower_left2);
    polygon_release(polygon2);
}

static void test_polygon_and_circle_collision_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = polygon_and_circle_collision(polygon, circle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_circle_collision_2() {
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = polygon_and_circle_collision(polygon, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_circle_collision_3() {
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = polygon_and_circle_collision(polygon, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_circle_collision_4() {
    CGPoint lower_left = point_new(1.9, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = polygon_and_circle_collision(polygon, circle);
    g_assert(double_equals(vector_x(collision->mtv), -0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 1.9));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_circle_and_polygon_collision_1() {
    CGPoint lower_left = point_new(0, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(3, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_polygon_collision(circle, polygon);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_circle_and_polygon_collision_2() {
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_polygon_collision(circle, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_circle_and_polygon_collision_3() {
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_polygon_collision(circle, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_circle_and_polygon_collision_4() {
    CGPoint lower_left = point_new(1.9, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 2);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_polygon_collision(circle, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_circle_and_circle_collision_1() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle1 = circle_new(center1, 1);
    CGPoint center2 = point_new(4, 1);
    CGCircle circle2 = circle_new(center2, 1);
    CGCollision collision = circle_and_circle_collision(circle1, circle2);
    g_assert(collision == NULL);
    point_release(center1);
    circle_release(circle1);
    point_release(center2);
    circle_release(circle2);
}

static void test_circle_and_circle_collision_2() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle1 = circle_new(center1, 1);
    CGPoint center2 = point_new(3, 1);
    CGCircle circle2 = circle_new(center2, 1);
    CGCollision collision = circle_and_circle_collision(circle1, circle2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center1);
    circle_release(circle1);
    point_release(center2);
    circle_release(circle2);
}

static void test_circle_and_circle_collision_3() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle1 = circle_new(center1, 1);
    CGPoint center2 = point_new(2.9, 1);
    CGCircle circle2 = circle_new(center2, 1);
    CGCollision collision = circle_and_circle_collision(circle1, circle2);
    g_assert(double_equals(vector_x(collision->mtv), 0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center1);
    circle_release(circle1);
    point_release(center2);
    circle_release(circle2);
}

static void test_circle_and_circle_collision_4() {
    CGPoint center1 = point_new(1, 1);
    CGCircle circle1 = circle_new(center1, 1);
    CGPoint center2 = point_new(1, 2.9);
    CGCircle circle2 = circle_new(center2, 1);
    CGCollision collision = circle_and_circle_collision(circle1, circle2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0.1));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 2));
    collision_release(collision);
    point_release(center1);
    circle_release(circle1);
    point_release(center2);
    circle_release(circle2);
}

static void test_collision_release_1() {
    CGCollision collision = memalloc(sizeof(*collision));
    collision->mtv = vector_new(1, 2);
    collision->point = point_new(1, 2);
    collision_release(collision);
}

static void test_collision_equals_1() {
    CGVector mtv1 = vector_new(1, 2);
    CGPoint point1 = point_new(3, 4);
    CGCollision collision1 = collision_new(mtv1, point1);
    CGVector mtv2 = vector_new(1, 2);
    CGPoint point2 = point_new(3, 5);
    CGCollision collision2 = collision_new(mtv2, point2);
    g_assert_cmpint(collision_equals(collision1, collision2), ==, 0);
    point_release(point1);
    point_release(point2);
    vector_release(mtv1);
    vector_release(mtv2);
    collision_release(collision1);
    collision_release(collision2);
}

static void test_collision_equals_2() {
    CGVector mtv1 = vector_new(1, 2);
    CGPoint point1 = point_new(3, 4);
    CGCollision collision1 = collision_new(mtv1, point1);
    CGVector mtv2 = vector_new(1, 5);
    CGPoint point2 = point_new(3, 4);
    CGCollision collision2 = collision_new(mtv2, point2);
    g_assert_cmpint(collision_equals(collision1, collision2), ==, 0);
    point_release(point1);
    point_release(point2);
    vector_release(mtv1);
    vector_release(mtv2);
    collision_release(collision1);
    collision_release(collision2);
}

static void test_collision_equals_3() {
    CGVector mtv1 = vector_new(1, 2);
    CGPoint point1 = point_new(3, 4);
    CGCollision collision1 = collision_new(mtv1, point1);
    CGVector mtv2 = vector_new(1, 2);
    CGPoint point2 = point_new(3, 4);
    CGCollision collision2 = collision_new(mtv2, point2);
    g_assert_cmpint(collision_equals(collision1, collision2), ==, 1);
    point_release(point1);
    point_release(point2);
    vector_release(mtv1);
    vector_release(mtv2);
    collision_release(collision1);
    collision_release(collision2);
}

static void test_collision_dup_1() {
    CGVector mtv = vector_new(1, 2);
    CGPoint point = point_new(1, 2);
    CGCollision collision = collision_new(mtv, point);
    CGCollision dup = collision_dup(collision);
    g_assert(dup != NULL);
    g_assert(dup != collision);
    g_assert(dup->mtv != collision->mtv);
    g_assert(vector_equals(dup->mtv, collision->mtv));
    g_assert(dup->point != collision->point);
    g_assert(point_equals(dup->point, collision->point));
    collision_release(dup);
    collision_release(collision);
    vector_release(mtv);
    point_release(point);
}

static void test_collision_minimum_translation_vector_1() {
    CGCollision collision = memalloc(sizeof(*collision));
    collision->mtv = vector_new(1, 2);
    collision->point = point_new(1, 2);
    CGVector mtv = collision_minimum_translation_vector(collision);
    g_assert(mtv != NULL);
    g_assert(mtv != collision->mtv);
    g_assert(vector_equals(mtv, collision->mtv));
    vector_release(mtv);
    collision_release(collision);
}

static void test_collision_point_1() {
    CGCollision collision = memalloc(sizeof(*collision));
    collision->mtv = vector_new(1, 2);
    collision->point = point_new(1, 2);
    CGPoint point = collision_point(collision);
    g_assert(point != NULL);
    g_assert(point != collision->point);
    g_assert(point_equals(point, collision->point));
    point_release(point);
    collision_release(collision);
}

int main(int argc, char *argv[]) {
    g_test_init(&argc, &argv, NULL);
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
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_1);
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_2);
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_3);
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_4);
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_5);
    g_test_add_func("/gc/polygon_is_in_contact_with_circle",
                    test_polygon_is_in_contact_with_circle_6);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_1);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_2);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_3);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_4);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_5);
    g_test_add_func("/gc/circle_is_in_contact_with_polygon",
                    test_circle_is_in_contact_with_polygon_6);
    g_test_add_func("/gc/polygon_min_projection_on_axis",
                    test_polygon_min_projection_on_axis_1);
    g_test_add_func("/gc/polygon_min_projection_on_axis",
                    test_polygon_min_projection_on_axis_2);
    g_test_add_func("/gc/polygon_max_projection_on_axis",
                    test_polygon_max_projection_on_axis_1);
    g_test_add_func("/gc/polygon_max_projection_on_axis",
                    test_polygon_max_projection_on_axis_2);
    g_test_add_func("/gc/circle_min_projection_on_axis",
                    test_circle_min_projection_on_axis_1);
    g_test_add_func("/gc/circle_min_projection_on_axis",
                    test_circle_min_projection_on_axis_2);
    g_test_add_func("/gc/circle_max_projection_on_axis",
                    test_circle_max_projection_on_axis_1);
    g_test_add_func("/gc/circle_max_projection_on_axis",
                    test_circle_max_projection_on_axis_2);
    g_test_add_func("/gc/polygon_perpendicular_axes", test_polygon_perpendicular_axes_1);
    g_test_add_func("/gc/collision_new", test_collision_new_1);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_1);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_2);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_3);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_4);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_5);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_1);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_2);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_3);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_4);
    g_test_add_func("/gc/circle_and_polygon_collision", test_circle_and_polygon_collision_1);
    g_test_add_func("/gc/circle_and_polygon_collision", test_circle_and_polygon_collision_2);
    g_test_add_func("/gc/circle_and_polygon_collision", test_circle_and_polygon_collision_3);
    g_test_add_func("/gc/circle_and_polygon_collision", test_circle_and_polygon_collision_4);
    g_test_add_func("/gc/circle_and_circle_collision", test_circle_and_circle_collision_1);
    g_test_add_func("/gc/circle_and_circle_collision", test_circle_and_circle_collision_2);
    g_test_add_func("/gc/circle_and_circle_collision", test_circle_and_circle_collision_3);
    g_test_add_func("/gc/circle_and_circle_collision", test_circle_and_circle_collision_4);
    g_test_add_func("/gc/collision_release", test_collision_release_1);
    g_test_add_func("/gc/collision_dup", test_collision_dup_1);
    g_test_add_func("/gc/collision_equals", test_collision_equals_1);
    g_test_add_func("/gc/collision_equals", test_collision_equals_2);
    g_test_add_func("/gc/collision_equals", test_collision_equals_3);
    g_test_add_func("/gc/collision_minimum_translation_vector",
                    test_collision_minimum_translation_vector_1);
    g_test_add_func("/gc/collision_point", test_collision_point_1);
    return g_test_run();
}

