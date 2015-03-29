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
    int is_in_contact = 1;
    for (ADTListItem it = list_head(axes); it && is_in_contact; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        if (double_lt(polygon_max_projection_on_axis(polygon1, axis) -
                      polygon_min_projection_on_axis(polygon2, axis), 0))
            is_in_contact = 0;
        if (double_gt(polygon_min_projection_on_axis(polygon1, axis) -
                      polygon_max_projection_on_axis(polygon2, axis), 0))
            is_in_contact = 0;
        if (double_equals(polygon_max_projection_on_axis(polygon1, axis),
                          polygon_min_projection_on_axis(polygon2, axis)) ||
            double_equals(polygon_min_projection_on_axis(polygon1, axis),
                          polygon_max_projection_on_axis(polygon2, axis)))
            is_in_contact = 2;
    }
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return (is_in_contact == 2) ? 1 : 0;
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

CGVector polygon_mtv_from_polygon(CGPolygon polygon1, CGPolygon polygon2, CGVector axis) {
    if (double_equals(vector_x(axis), 0) && double_equals(vector_y(axis), 0))
        return NULL;
    ADTList vertices1 = polygon_vertices(polygon1);
    ADTList vertices2 = polygon_vertices(polygon2);
    ADTList edges1 = polygon_edges(polygon1);
    ADTList edges2 = polygon_edges(polygon2);
    CGVector mtv = vector_new(0, 0);
    for (ADTListItem it = list_head(vertices1); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        CGPoint aux_point = point_dup(vertex);
        point_translate(aux_point, axis);
        CGLine vertex_line = line_new(vertex, aux_point);
        for (ADTListItem jt = list_head(edges2); jt; jt = list_next(jt)) {
            CGSegment edge = (CGSegment) list_value(jt);
            CGLine edge_line = line_new(edge->a, edge->b);
            CGPoint intersection = line_intersection(vertex_line, edge_line);
            if (intersection == NULL && point_is_in_line(edge->a, vertex_line)) {
                CGVector tv1 = vector_from_point_to_point(vertex, edge->a);
                CGAngle angle1 = vector_angle_to(axis, tv1);
                CGVector tv2 = vector_from_point_to_point(vertex, edge->b);
                CGAngle angle2 = vector_angle_to(axis, tv2);
                if (angle1 != NULL) {
                    if (double_equals(angle_in_radians(angle1), 0) &&
                        double_gt(vector_magnitude(tv1), vector_magnitude(mtv))) {
                        vector_release(mtv);
                        mtv = vector_dup(tv1);
                    }
                    angle_release(angle1);
                }
                if (angle2 != NULL) {
                    if (double_equals(angle_in_radians(angle2), 0) &&
                        double_gt(vector_magnitude(tv2), vector_magnitude(mtv))) {
                        vector_release(mtv);
                        mtv = vector_dup(tv2);
                    }
                    angle_release(angle2);
                }
                vector_release(tv1);
                vector_release(tv2);
            }
            else if (intersection != NULL) {
                if (point_is_in_segment(intersection, edge)) {
                    CGVector tv = vector_from_point_to_point(vertex, intersection);
                    CGAngle angle = vector_angle_to(axis, tv);
                    if (angle != NULL && double_equals(angle_in_radians(angle), 0) &&
                        double_gt(vector_magnitude(tv), vector_magnitude(mtv))) {
                        vector_release(mtv);
                        mtv = vector_dup(tv);
                        angle_release(angle);
                    }
                    vector_release(tv);
                }
                point_release(intersection);
            }
            line_release(edge_line);
        }
        point_release(aux_point);
        line_release(vertex_line);
    }
    for (ADTListItem it = list_head(vertices2); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        CGPoint aux_point = point_dup(vertex);
        point_translate(aux_point, axis);
        CGLine vertex_line = line_new(vertex, aux_point);
        for (ADTListItem jt = list_head(edges1); jt; jt = list_next(jt)) {
            CGSegment edge = (CGSegment) list_value(jt);
            CGLine edge_line = line_new(edge->a, edge->b);
            CGPoint intersection = line_intersection(vertex_line, edge_line);
            if (intersection == NULL && point_is_in_line(edge->a, vertex_line)) {
                CGVector tv1 = vector_from_point_to_point(vertex, edge->a);
                CGAngle angle1 = vector_angle_to(axis, tv1);
                CGVector tv2 = vector_from_point_to_point(vertex, edge->b);
                CGAngle angle2 = vector_angle_to(axis, tv2);
                if (angle1 != NULL && double_equals(angle_in_radians(angle1), M_PI) &&
                    double_gt(vector_magnitude(tv1), vector_magnitude(mtv))) {
                    vector_release(mtv);
                    mtv = vector_dup(tv1);
                    angle_release(angle1);
                }
                if (angle2 != NULL && double_equals(angle_in_radians(angle2), M_PI) &&
                    double_gt(vector_magnitude(tv2), vector_magnitude(mtv))) {
                    vector_release(mtv);
                    mtv = vector_dup(tv2);
                    angle_release(angle2);
                }
                vector_release(tv1);
                vector_release(tv2);
            }
            else if (intersection != NULL) {
                if (point_is_in_segment(intersection, edge)) {
                    CGVector tv = vector_from_point_to_point(vertex, intersection);
                    CGAngle angle = vector_angle_to(axis, tv);
                    if (angle != NULL && double_equals(angle_in_radians(angle), M_PI) &&
                        double_gt(vector_magnitude(tv), vector_magnitude(mtv))) {
                        vector_release(mtv);
                        mtv = vector_dup(tv);
                        angle_release(angle);
                    }
                    vector_release(tv);
                }
                point_release(intersection);
            }
            line_release(edge_line);
        }
        point_release(aux_point);
        line_release(vertex_line);
    }
    list_full_release(vertices1, (void (*)(void *)) point_release);
    list_full_release(vertices2, (void (*)(void *)) point_release);
    list_full_release(edges1, (void (*)(void *)) segment_release);
    list_full_release(edges2, (void (*)(void *)) segment_release);
    return mtv;
}

