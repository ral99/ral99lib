#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cg/collision/collision.h"
#include "cg/cg.h"
#include "adt/adt.h"
#include "num/num.h"
#include "mem/mem.h"
#include "str/str.h"

double polygon_min_projection_on_axis(CGPolygon polygon, CGVector axis) {
    double min;
    ADTList vertices = polygon_vertices(polygon);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        CGVector vector = vector_from_origin_to_point(point);
        double projection = vector_dot(vector, axis);
        min = (it == list_head(vertices) || double_lt(projection, min)) ? projection : min;
        vector_release(vector);
    }
    list_full_release(vertices, (void (*)(void *)) point_release);
    return min;
}

double polygon_max_projection_on_axis(CGPolygon polygon, CGVector axis) {
    double max;
    ADTList vertices = polygon_vertices(polygon);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        CGVector vector = vector_from_origin_to_point(point);
        double projection = vector_dot(vector, axis);
        max = (it == list_head(vertices) || double_gt(projection, max)) ? projection : max;
        vector_release(vector);
    }
    list_full_release(vertices, (void (*)(void *)) point_release);
    return max;
}

ADTList polygon_perpendicular_axes(CGPolygon polygon) {
    ADTList perpendicular_axes = list_new();
    int n_vertices = list_size(polygon->vertices);
    for (int i = 0; i < n_vertices; i++) {
        CGPoint vertex1 = (CGPoint) list_at(polygon->vertices, i);
        CGPoint vertex2 = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        CGVector vector = vector_from_point_to_point(vertex1, vertex2);
        list_append(perpendicular_axes, vector_right_perpendicular_axis(vector));
        vector_release(vector);
    }
    return perpendicular_axes;
}

int polygon_is_in_contact_with_polygon(CGPolygon polygon1, CGPolygon polygon2) {
    ADTList axes = list_new();
    ADTList axes1 = polygon_perpendicular_axes(polygon1);
    ADTList axes2 = polygon_perpendicular_axes(polygon2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    int is_in_contact = 0;
    for (ADTListItem it = list_head(axes); it && !is_in_contact; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        if (double_equals(polygon_max_projection_on_axis(polygon1, axis),
                          polygon_min_projection_on_axis(polygon2, axis)) ||
            double_equals(polygon_min_projection_on_axis(polygon1, axis),
                          polygon_max_projection_on_axis(polygon2, axis)))
            is_in_contact = 1;
    }
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return is_in_contact;
}

int polygon_is_colliding_with_polygon(CGPolygon polygon1, CGPolygon polygon2) {
    ADTList axes = list_new();
    ADTList axes1 = polygon_perpendicular_axes(polygon1);
    ADTList axes2 = polygon_perpendicular_axes(polygon2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    int is_colliding = 1;
    for (ADTListItem it = list_head(axes); it && is_colliding; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        if (double_lte(polygon_max_projection_on_axis(polygon1, axis) -
                       polygon_min_projection_on_axis(polygon2, axis), 0))
            is_colliding = 0;
        if (double_gte(polygon_min_projection_on_axis(polygon1, axis) -
                       polygon_max_projection_on_axis(polygon2, axis), 0))
            is_colliding = 0;
    }
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return is_colliding;
}

CGPoint polygon_point_of_contact_with_polygon(CGPolygon polygon1, CGPolygon polygon2) {
    if (!polygon_is_in_contact_with_polygon(polygon1, polygon2))
        return NULL;
    ADTList vertices = list_new();
    ADTList vertices1 = polygon_vertices(polygon1);
    ADTList vertices2 = polygon_vertices(polygon2);
    list_extend(vertices, vertices1);
    list_extend(vertices, vertices2);
    CGPoint point1 = NULL;
    CGPoint point2 = NULL;
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        if (point_is_in_polygon(vertex, polygon1) && point_is_in_polygon(vertex, polygon2)) {
            point1 = (point1 == NULL) ? vertex : point1;
            point2 = (point2 == NULL || point_equals(point1, point2)) ? vertex : point2;
        }
    }
    CGPoint point_of_contact = midpoint_between(point1, point2);
    list_full_release(vertices1, (void (*)(void *)) point_release);
    list_full_release(vertices2, (void (*)(void *)) point_release);
    list_release(vertices);
    return point_of_contact;
}
