#include <glib.h>
#include <math.h>
#include <stdlib.h>

#include "cg/collision/collision.h"
#include "cg/cg.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

static void test_segment_min_projection_on_axis_1() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(5, 9);
    CGVector axis = vector_new(1, 0);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_min_projection_on_axis(segment, axis), 2));
    point_release(a);
    point_release(b);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_min_projection_on_axis_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_min_projection_on_axis(segment, axis), 0));
    point_release(a);
    point_release(b);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_max_projection_on_axis_1() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(5, 9);
    CGVector axis = vector_new(1, 0);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_max_projection_on_axis(segment, axis), 5));
    point_release(a);
    point_release(b);
    segment_release(segment);
    vector_release(axis);
}

static void test_segment_max_projection_on_axis_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    CGSegment segment = segment_new(a, b);
    g_assert(double_equals(segment_max_projection_on_axis(segment, axis), sqrt(2)));
    point_release(a);
    point_release(b);
    segment_release(segment);
    vector_release(axis);
}

static void test_triangle_min_projection_on_axis_1() {
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(2, 1);
    CGPoint c = point_new(1, 2);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(triangle_min_projection_on_axis(triangle, axis), 1));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_min_projection_on_axis_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    g_assert(double_equals(triangle_min_projection_on_axis(triangle, axis), 0));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_max_projection_on_axis_1() {
    CGPoint a = point_new(1, 1);
    CGPoint b = point_new(2, 1);
    CGPoint c = point_new(1, 2);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector axis = vector_new(1, 0);
    g_assert(double_equals(triangle_max_projection_on_axis(triangle, axis), 2));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
}

static void test_triangle_max_projection_on_axis_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGVector axis = vector_new(sqrt(2) / 2, sqrt(2) / 2);
    g_assert(double_equals(triangle_max_projection_on_axis(triangle, axis), sqrt(2) / 2));
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
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

static void test_segment_perpendicular_axes_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(5, 0);
    CGSegment segment = segment_new(a, b);
    ADTList perpendicular_axes = segment_perpendicular_axes(segment);
    g_assert_cmpint(list_size(perpendicular_axes), ==, 1);
    CGVector axis = (CGVector) list_at(perpendicular_axes, 0);
    g_assert(double_equals(vector_x(axis), 0));
    g_assert(double_equals(vector_y(axis), -1));
    list_full_release(perpendicular_axes, (void (*)(void *)) vector_release);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_segment_perpendicular_axes_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 5);
    CGSegment segment = segment_new(a, b);
    ADTList perpendicular_axes = segment_perpendicular_axes(segment);
    g_assert_cmpint(list_size(perpendicular_axes), ==, 1);
    CGVector axis = (CGVector) list_at(perpendicular_axes, 0);
    g_assert(double_equals(vector_x(axis), 1));
    g_assert(double_equals(vector_y(axis), 0));
    list_full_release(perpendicular_axes, (void (*)(void *)) vector_release);
    segment_release(segment);
    point_release(a);
    point_release(b);
}

static void test_triangle_perpendicular_axes_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(5, 0);
    CGPoint c = point_new(0, 5);
    CGTriangle triangle = triangle_new(a, b, c);
    ADTList perpendicular_axes = triangle_perpendicular_axes(triangle);
    g_assert_cmpint(list_size(perpendicular_axes), ==, 3);
    CGVector axis = (CGVector) list_at(perpendicular_axes, 0);
    g_assert(double_equals(vector_x(axis), 0));
    g_assert(double_equals(vector_y(axis), -1));
    axis = (CGVector) list_at(perpendicular_axes, 1);
    g_assert(double_equals(vector_x(axis), sqrt(2) / 2));
    g_assert(double_equals(vector_y(axis), sqrt(2) / 2));
    axis = (CGVector) list_at(perpendicular_axes, 2);
    g_assert(double_equals(vector_x(axis), -1));
    g_assert(double_equals(vector_y(axis), 0));
    list_full_release(perpendicular_axes, (void (*)(void *)) vector_release);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
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

static void test_segment_and_segment_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(1, 0);
    CGPoint d = point_new(1, 1);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGCollision collision = segment_and_segment_collision(segment1, segment2);
    g_assert(collision == NULL);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_segment_and_segment_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGPoint c = point_new(0, 1);
    CGPoint d = point_new(1, 1);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGCollision collision = segment_and_segment_collision(segment1, segment2);
    g_assert(collision == NULL);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_segment_and_segment_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(2, 0);
    CGPoint c = point_new(1, 0);
    CGPoint d = point_new(3, 0);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGCollision collision = segment_and_segment_collision(segment1, segment2);
    g_assert(collision == NULL);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_segment_and_segment_collision_4() {
    CGPoint a = point_new(0, 2);
    CGPoint b = point_new(3, 2);
    CGPoint c = point_new(1, 0);
    CGPoint d = point_new(1, 4);
    CGSegment segment1 = segment_new(a, b);
    CGSegment segment2 = segment_new(c, d);
    CGCollision collision1 = segment_and_segment_collision(segment1, segment2);
    g_assert(double_equals(vector_x(collision1->mtv), -1));
    g_assert(double_equals(vector_y(collision1->mtv), 0));
    g_assert(double_equals(point_x(collision1->point), 0));
    g_assert(double_equals(point_y(collision1->point), 2));
    CGCollision collision2 = segment_and_segment_collision(segment2, segment1);
    g_assert(double_equals(vector_x(collision2->mtv), 1));
    g_assert(double_equals(vector_y(collision2->mtv), 0));
    g_assert(double_equals(point_x(collision2->point), 1));
    g_assert(double_equals(point_y(collision2->point), 2));
    collision_release(collision1);
    collision_release(collision2);
    segment_release(segment1);
    segment_release(segment2);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
}

static void test_segment_and_triangle_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = segment_and_triangle_collision(segment, triangle);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_segment_and_triangle_collision_2() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = segment_and_triangle_collision(segment, triangle);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_segment_and_triangle_collision_3() {
    CGPoint a = point_new(0, 1);
    CGPoint b = point_new(3, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = segment_and_triangle_collision(segment, triangle);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_segment_and_triangle_collision_4() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 4);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = segment_and_triangle_collision(segment, triangle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 1));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 2));
    collision_release(collision);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_segment_and_polygon_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = segment_and_polygon_collision(segment, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_segment_and_polygon_collision_2() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = segment_and_polygon_collision(segment, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_segment_and_polygon_collision_3() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 6);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = segment_and_polygon_collision(segment, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_segment_and_polygon_collision_4() {
    CGPoint a = point_new(1, 3);
    CGPoint b = point_new(6, 3);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = segment_and_polygon_collision(segment, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 1));
    g_assert(double_equals(point_x(collision->point), 3.5));
    g_assert(double_equals(point_y(collision->point), 3));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_segment_and_polygon_collision_5() {
    CGPoint a = point_new(3, 2);
    CGPoint b = point_new(3, 5);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = segment_and_polygon_collision(segment, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 3));
    g_assert(double_equals(point_y(collision->point), 3.5));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_segment_and_circle_collision_1() {
    CGPoint a = point_new(3, 0);
    CGPoint b = point_new(3, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_segment_and_circle_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_segment_and_circle_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_segment_and_circle_collision_4() {
    CGPoint a = point_new(0.5, 0);
    CGPoint b = point_new(0.5, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0.5));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 0.5));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_segment_and_circle_collision_5() {
    CGPoint a = point_new(0, 0.5);
    CGPoint b = point_new(2, 0.5);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0.5));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 0.5));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_segment_and_circle_collision_6() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(0, 1.95);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = segment_and_circle_collision(segment, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0.05));
    g_assert(double_equals(point_x(collision->point), 0));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_triangle_and_segment_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = triangle_and_segment_collision(triangle, segment);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_triangle_and_segment_collision_2() {
    CGPoint a = point_new(1, 0);
    CGPoint b = point_new(1, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = triangle_and_segment_collision(triangle, segment);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_triangle_and_segment_collision_3() {
    CGPoint a = point_new(0, 1);
    CGPoint b = point_new(3, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 2);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = triangle_and_segment_collision(triangle, segment);
    g_assert(collision == NULL);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_triangle_and_segment_collision_4() {
    CGPoint a = point_new(1, 2);
    CGPoint b = point_new(3, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint c = point_new(1, 1);
    CGPoint d = point_new(2, 4);
    CGPoint e = point_new(3, 1);
    CGTriangle triangle = triangle_new(c, d, e);
    CGCollision collision = triangle_and_segment_collision(triangle, segment);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), -1));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    segment_release(segment);
    triangle_release(triangle);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
}

static void test_triangle_and_triangle_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGPoint d = point_new(1, 1);
    CGPoint e = point_new(2, 1);
    CGPoint f = point_new(1, 2);
    CGTriangle triangle2 = triangle_new(d, e, f);
    CGCollision collision = triangle_and_triangle_collision(triangle1, triangle2);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_and_triangle_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGPoint d = point_new(1, 0);
    CGPoint f = point_new(2, 0);
    CGPoint e = point_new(1, 1);
    CGTriangle triangle2 = triangle_new(d, e, f);
    CGCollision collision = triangle_and_triangle_collision(triangle1, triangle2);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_and_triangle_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGPoint d = point_new(1, 0);
    CGPoint f = point_new(1, 1);
    CGPoint e = point_new(0, 1);
    CGTriangle triangle2 = triangle_new(d, e, f);
    CGCollision collision = triangle_and_triangle_collision(triangle1, triangle2);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_and_triangle_collision_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 4);
    CGPoint c = point_new(2, 0);
    CGTriangle triangle1 = triangle_new(a, b, c);
    CGPoint d = point_new(0, 3);
    CGPoint f = point_new(1, 7);
    CGPoint e = point_new(2, 3);
    CGTriangle triangle2 = triangle_new(d, e, f);
    CGCollision collision = triangle_and_triangle_collision(triangle1, triangle2);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 1));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 4));
    collision_release(collision);
    point_release(a);
    point_release(b);
    point_release(c);
    point_release(d);
    point_release(e);
    point_release(f);
    triangle_release(triangle1);
    triangle_release(triangle2);
}

static void test_triangle_and_polygon_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = triangle_and_polygon_collision(triangle, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_triangle_and_polygon_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(1, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = triangle_and_polygon_collision(triangle, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_triangle_and_polygon_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(1, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = triangle_and_polygon_collision(triangle, polygon);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_triangle_and_polygon_collision_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(4, 0);
    CGPoint c = point_new(4, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(3.9, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = triangle_and_polygon_collision(triangle, polygon);
    g_assert(double_equals(vector_x(collision->mtv), 0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 4));
    g_assert(double_equals(point_y(collision->point), 0.5));
    collision_release(collision);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_triangle_and_circle_collision_1() {
    CGPoint a = point_new(3, 0);
    CGPoint b = point_new(3, 1);
    CGPoint c = point_new(4, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = triangle_and_circle_collision(triangle, circle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_and_circle_collision_2() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 1);
    CGPoint c = point_new(3, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = triangle_and_circle_collision(triangle, circle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_and_circle_collision_3() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 2);
    CGPoint c = point_new(3, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = triangle_and_circle_collision(triangle, circle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_triangle_and_circle_collision_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(1, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1.95);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = triangle_and_circle_collision(triangle, circle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), 0.05));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_polygon_and_segment_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = polygon_and_segment_collision(polygon, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_segment_collision_2() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = polygon_and_segment_collision(polygon, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_segment_collision_3() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 6);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = polygon_and_segment_collision(polygon, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_segment_collision_4() {
    CGPoint a = point_new(1, 3);
    CGPoint b = point_new(6, 3);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = polygon_and_segment_collision(polygon, segment);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), -1));
    g_assert(double_equals(point_x(collision->point), 3.5));
    g_assert(double_equals(point_y(collision->point), 2));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_segment_collision_5() {
    CGPoint a = point_new(3, 2);
    CGPoint b = point_new(3, 5);
    CGSegment segment = segment_new(a, b);
    CGPoint lower_left = point_new(2, 2);
    CGPolygon polygon = polygon_new_square(lower_left, 3);
    CGCollision collision = polygon_and_segment_collision(polygon, segment);
    g_assert(double_equals(vector_x(collision->mtv), -1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 2));
    g_assert(double_equals(point_y(collision->point), 3.5));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_triangle_collision_1() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(2, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = polygon_and_triangle_collision(polygon, triangle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_triangle_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(0, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(1, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = polygon_and_triangle_collision(polygon, triangle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_triangle_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 0);
    CGPoint c = point_new(1, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(1, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = polygon_and_triangle_collision(polygon, triangle);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
}

static void test_polygon_and_triangle_collision_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(4, 0);
    CGPoint c = point_new(4, 1);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint lower_left = point_new(3.9, 0);
    CGPolygon polygon = polygon_new_square(lower_left, 1);
    CGCollision collision = polygon_and_triangle_collision(polygon, triangle);
    g_assert(double_equals(vector_x(collision->mtv), -0.1));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 3.9));
    g_assert(double_equals(point_y(collision->point), 0.5));
    collision_release(collision);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
    point_release(lower_left);
    polygon_release(polygon);
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
    g_assert(collision == NULL);
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
    g_assert(collision == NULL);
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
    g_assert(collision == NULL);
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
    g_assert(collision == NULL);
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

static void test_circle_and_segment_collision_1() {
    CGPoint a = point_new(3, 0);
    CGPoint b = point_new(3, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_segment_collision_2() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_segment_collision_3() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(collision == NULL);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_segment_collision_4() {
    CGPoint a = point_new(0.5, 0);
    CGPoint b = point_new(0.5, 2);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(double_equals(vector_x(collision->mtv), -0.5));
    g_assert(double_equals(vector_y(collision->mtv), 0));
    g_assert(double_equals(point_x(collision->point), 0));
    g_assert(double_equals(point_y(collision->point), 1));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_segment_collision_5() {
    CGPoint a = point_new(0, 0.5);
    CGPoint b = point_new(2, 0.5);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), -0.5));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 0));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_segment_collision_6() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(0, 1);
    CGSegment segment = segment_new(a, b);
    CGPoint center = point_new(0, 1.95);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_segment_collision(circle, segment);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), -0.05));
    g_assert(double_equals(point_x(collision->point), 0));
    g_assert(double_equals(point_y(collision->point), 0.95));
    collision_release(collision);
    point_release(a);
    point_release(b);
    segment_release(segment);
    point_release(center);
    circle_release(circle);
}

static void test_circle_and_triangle_collision_1() {
    CGPoint a = point_new(3, 0);
    CGPoint b = point_new(3, 1);
    CGPoint c = point_new(4, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_triangle_collision(circle, triangle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_circle_and_triangle_collision_2() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 1);
    CGPoint c = point_new(3, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_triangle_collision(circle, triangle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_circle_and_triangle_collision_3() {
    CGPoint a = point_new(2, 0);
    CGPoint b = point_new(2, 2);
    CGPoint c = point_new(3, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_triangle_collision(circle, triangle);
    g_assert(collision == NULL);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
}

static void test_circle_and_triangle_collision_4() {
    CGPoint a = point_new(0, 0);
    CGPoint b = point_new(1, 1);
    CGPoint c = point_new(1, 0);
    CGTriangle triangle = triangle_new(a, b, c);
    CGPoint center = point_new(1, 1.95);
    CGCircle circle = circle_new(center, 1);
    CGCollision collision = circle_and_triangle_collision(circle, triangle);
    g_assert(double_equals(vector_x(collision->mtv), 0));
    g_assert(double_equals(vector_y(collision->mtv), -0.05));
    g_assert(double_equals(point_x(collision->point), 1));
    g_assert(double_equals(point_y(collision->point), 0.95));
    collision_release(collision);
    point_release(center);
    circle_release(circle);
    point_release(a);
    point_release(b);
    point_release(c);
    triangle_release(triangle);
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
    g_assert(collision == NULL);
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
    g_assert(collision == NULL);
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
    g_assert(collision == NULL);
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
    g_test_add_func("/gc/segment_min_projection_on_axis",
                    test_segment_min_projection_on_axis_1);
    g_test_add_func("/gc/segment_min_projection_on_axis",
                    test_segment_min_projection_on_axis_2);
    g_test_add_func("/gc/segment_max_projection_on_axis",
                    test_segment_max_projection_on_axis_1);
    g_test_add_func("/gc/segment_max_projection_on_axis",
                    test_segment_max_projection_on_axis_2);
    g_test_add_func("/gc/triangle_min_projection_on_axis",
                    test_triangle_min_projection_on_axis_1);
    g_test_add_func("/gc/triangle_min_projection_on_axis",
                    test_triangle_min_projection_on_axis_2);
    g_test_add_func("/gc/triangle_max_projection_on_axis",
                    test_triangle_max_projection_on_axis_1);
    g_test_add_func("/gc/triangle_max_projection_on_axis",
                    test_triangle_max_projection_on_axis_2);
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
    g_test_add_func("/gc/segment_perpendicular_axes", test_segment_perpendicular_axes_1);
    g_test_add_func("/gc/segment_perpendicular_axes", test_segment_perpendicular_axes_2);
    g_test_add_func("/gc/triangle_perpendicular_axes", test_triangle_perpendicular_axes_1);
    g_test_add_func("/gc/polygon_perpendicular_axes", test_polygon_perpendicular_axes_1);
    g_test_add_func("/gc/collision_new", test_collision_new_1);
    g_test_add_func("/gc/segment_and_segment_collision", test_segment_and_segment_collision_1);
    g_test_add_func("/gc/segment_and_segment_collision", test_segment_and_segment_collision_2);
    g_test_add_func("/gc/segment_and_segment_collision", test_segment_and_segment_collision_3);
    g_test_add_func("/gc/segment_and_segment_collision", test_segment_and_segment_collision_4);
    g_test_add_func("/gc/segment_and_triangle_collision",
                    test_segment_and_triangle_collision_1);
    g_test_add_func("/gc/segment_and_triangle_collision",
                    test_segment_and_triangle_collision_2);
    g_test_add_func("/gc/segment_and_triangle_collision",
                    test_segment_and_triangle_collision_3);
    g_test_add_func("/gc/segment_and_triangle_collision",
                    test_segment_and_triangle_collision_4);
    g_test_add_func("/gc/segment_and_polygon_collision", test_segment_and_polygon_collision_1);
    g_test_add_func("/gc/segment_and_polygon_collision", test_segment_and_polygon_collision_2);
    g_test_add_func("/gc/segment_and_polygon_collision", test_segment_and_polygon_collision_3);
    g_test_add_func("/gc/segment_and_polygon_collision", test_segment_and_polygon_collision_4);
    g_test_add_func("/gc/segment_and_polygon_collision", test_segment_and_polygon_collision_5);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_1);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_2);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_3);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_4);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_5);
    g_test_add_func("/gc/segment_and_circle_collision", test_segment_and_circle_collision_6);
    g_test_add_func("/gc/triangle_and_segment_collision",
                    test_triangle_and_segment_collision_1);
    g_test_add_func("/gc/triangle_and_segment_collision",
                    test_triangle_and_segment_collision_2);
    g_test_add_func("/gc/triangle_and_segment_collision",
                    test_triangle_and_segment_collision_3);
    g_test_add_func("/gc/triangle_and_segment_collision",
                    test_triangle_and_segment_collision_4);
    g_test_add_func("/gc/triangle_and_triangle_collision",
                    test_triangle_and_triangle_collision_1);
    g_test_add_func("/gc/triangle_and_triangle_collision",
                    test_triangle_and_triangle_collision_2);
    g_test_add_func("/gc/triangle_and_triangle_collision",
                    test_triangle_and_triangle_collision_3);
    g_test_add_func("/gc/triangle_and_triangle_collision",
                    test_triangle_and_triangle_collision_4);
    g_test_add_func("/gc/triangle_and_polygon_collision",
                    test_triangle_and_polygon_collision_1);
    g_test_add_func("/gc/triangle_and_polygon_collision",
                    test_triangle_and_polygon_collision_2);
    g_test_add_func("/gc/triangle_and_polygon_collision",
                    test_triangle_and_polygon_collision_3);
    g_test_add_func("/gc/triangle_and_polygon_collision",
                    test_triangle_and_polygon_collision_4);
    g_test_add_func("/gc/triangle_and_circle_collision", test_triangle_and_circle_collision_1);
    g_test_add_func("/gc/triangle_and_circle_collision", test_triangle_and_circle_collision_2);
    g_test_add_func("/gc/triangle_and_circle_collision", test_triangle_and_circle_collision_3);
    g_test_add_func("/gc/triangle_and_circle_collision", test_triangle_and_circle_collision_4);
    g_test_add_func("/gc/polygon_and_segment_collision", test_polygon_and_segment_collision_1);
    g_test_add_func("/gc/polygon_and_segment_collision", test_polygon_and_segment_collision_2);
    g_test_add_func("/gc/polygon_and_segment_collision", test_polygon_and_segment_collision_3);
    g_test_add_func("/gc/polygon_and_segment_collision", test_polygon_and_segment_collision_4);
    g_test_add_func("/gc/polygon_and_segment_collision", test_polygon_and_segment_collision_5);
    g_test_add_func("/gc/polygon_and_triangle_collision",
                    test_polygon_and_triangle_collision_1);
    g_test_add_func("/gc/polygon_and_triangle_collision",
                    test_polygon_and_triangle_collision_2);
    g_test_add_func("/gc/polygon_and_triangle_collision",
                    test_polygon_and_triangle_collision_3);
    g_test_add_func("/gc/polygon_and_triangle_collision",
                    test_polygon_and_triangle_collision_4);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_1);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_2);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_3);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_4);
    g_test_add_func("/gc/polygon_and_polygon_collision", test_polygon_and_polygon_collision_5);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_1);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_2);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_3);
    g_test_add_func("/gc/polygon_and_circle_collision", test_polygon_and_circle_collision_4);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_1);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_2);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_3);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_4);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_5);
    g_test_add_func("/gc/circle_and_segment_collision", test_circle_and_segment_collision_6);
    g_test_add_func("/gc/circle_and_triangle_collision", test_circle_and_triangle_collision_1);
    g_test_add_func("/gc/circle_and_triangle_collision", test_circle_and_triangle_collision_2);
    g_test_add_func("/gc/circle_and_triangle_collision", test_circle_and_triangle_collision_3);
    g_test_add_func("/gc/circle_and_triangle_collision", test_circle_and_triangle_collision_4);
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

