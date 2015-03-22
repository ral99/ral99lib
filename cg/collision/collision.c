#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cg/collision/collision.h"
#include "cg/cg.h"
#include "adt/adt.h"
#include "num/num.h"
#include "mem/mem.h"
#include "str/str.h"

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

int polygon_is_in_contact_with_circle(CGPolygon polygon, CGCircle circle) {
    ADTList axes = polygon_perpendicular_axes(polygon);
    ADTList vertices = polygon_vertices(polygon);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        CGVector axis = vector_from_point_to_point(circle->center, vertex);
        vector_normalize(axis);
        list_append(axes, axis);
    }
    int is_in_contact = 0;
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        if (double_equals(polygon_max_projection_on_axis(polygon, axis),
                          circle_min_projection_on_axis(circle, axis)) ||
            double_equals(polygon_min_projection_on_axis(polygon, axis),
                          circle_max_projection_on_axis(circle, axis)))
            is_in_contact = 1;
    }
    list_full_release(axes, (void (*)(void *)) vector_release);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return is_in_contact;
}

int circle_is_in_contact_with_polygon(CGCircle circle, CGPolygon polygon) {
    return polygon_is_in_contact_with_circle(polygon, circle);
}

int circle_is_in_contact_with_circle(CGCircle circle1, CGCircle circle2) {
    return double_equals(point_distance_to_point(circle1->center, circle2->center),
                         circle1->radius + circle2->radius);
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

int polygon_is_colliding_with_circle(CGPolygon polygon, CGCircle circle) {
    ADTList axes = polygon_perpendicular_axes(polygon);
    ADTList vertices = polygon_vertices(polygon);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        CGVector axis = vector_from_point_to_point(circle->center, vertex);
        vector_normalize(axis);
        list_append(axes, axis);
    }
    int is_colliding = 1;
    for (ADTListItem it = list_head(axes); it && is_colliding; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        if (double_lte(polygon_max_projection_on_axis(polygon, axis) -
                       circle_min_projection_on_axis(circle, axis), 0))
            is_colliding = 0;
        if (double_gte(polygon_min_projection_on_axis(polygon, axis) -
                       circle_max_projection_on_axis(circle, axis), 0))
            is_colliding = 0;
    }
    list_full_release(axes, (void (*)(void *)) vector_release);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return is_colliding;
}

int circle_is_colliding_with_polygon(CGCircle circle, CGPolygon polygon) {
    return polygon_is_colliding_with_circle(polygon, circle);
}

int circle_is_colliding_with_circle(CGCircle circle1, CGCircle circle2) {
    return (double_lt(point_distance_to_point(circle1->center, circle2->center),
                      circle1->radius + circle2->radius));
}

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

double circle_min_projection_on_axis(CGCircle circle, CGVector axis) {
    CGVector vector = vector_from_origin_to_point(circle->center);
    double projection = vector_dot(vector, axis);
    vector_release(vector);
    return projection - circle->radius;
}

double circle_max_projection_on_axis(CGCircle circle, CGVector axis) {
    CGVector vector = vector_from_origin_to_point(circle->center);
    double projection = vector_dot(vector, axis);
    vector_release(vector);
    return projection + circle->radius;
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

CGCollision collision_new(CGVector mtv, CGPoint point) {
    CGCollision collision = (CGCollision) memalloc(sizeof(*collision));
    collision->mtv = vector_dup(mtv);
    collision->point = point_dup(point);
    return collision;
}

CGCollision polygon_and_polygon_collision(CGPolygon polygon1, CGPolygon polygon2) {
    CGCollision collision = NULL;
    ADTList axes = list_new();
    ADTList axes1 = polygon_perpendicular_axes(polygon1);
    ADTList axes2 = polygon_perpendicular_axes(polygon2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    CGVector mtv;
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        double mult1 = double_max(polygon_max_projection_on_axis(polygon1, axis) -
                                  polygon_min_projection_on_axis(polygon2, axis), 0);
        double mult2 = double_min(polygon_min_projection_on_axis(polygon1, axis) -
                                  polygon_max_projection_on_axis(polygon2, axis), 0);
        double mult = double_lt(mult1, -mult2) ? mult1 : mult2;
        if (it == list_head(axes) || double_lt(fabs(mult), vector_magnitude(mtv))) {
            vector_multiply(axis, mult);
            mtv = axis;
        }
    }
    CGPoint point1 = NULL;
    CGPoint point2 = NULL;
    CGPolygon dup = polygon_dup(polygon2);
    polygon_translate(dup, mtv);
    ADTList vertices = list_new();
    ADTList vertices1 = polygon_vertices(polygon1);
    ADTList vertices2 = polygon_vertices(dup);
    list_extend(vertices, vertices1);
    list_extend(vertices, vertices2);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        if (point_is_in_polygon(vertex, polygon1) && point_is_in_polygon(vertex, dup)) {
            if (point1 == NULL)
                point1 = vertex;
            if (point2 == NULL || point_equals(point1, point2))
                point2 = vertex;
        }
    }
    if (point1 != NULL && point2 != NULL) {
        CGPoint point = midpoint_between(point1, point2);
        collision = collision_new(mtv, point);
        point_release(point);
    }
    polygon_release(dup);
    list_release(vertices);
    list_full_release(vertices1, (void (*)(void *)) point_release);
    list_full_release(vertices2, (void (*)(void *)) point_release);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return collision;
}

CGCollision polygon_and_circle_collision(CGPolygon polygon, CGCircle circle) {
    CGCollision collision = NULL;
    ADTList axes = polygon_perpendicular_axes(polygon);
    ADTList vertices = polygon_vertices(polygon);
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        CGVector axis = vector_from_point_to_point(circle->center, vertex);
        vector_normalize(axis);
        list_append(axes, axis);
    }
    CGVector mtv;
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        double mult1 = double_max(polygon_max_projection_on_axis(polygon, axis) -
                                  circle_min_projection_on_axis(circle, axis), 0);
        double mult2 = double_min(polygon_min_projection_on_axis(polygon, axis) -
                                  circle_max_projection_on_axis(circle, axis), 0);
        double mult = double_lt(mult1, -mult2) ? mult1 : mult2;
        if (it == list_head(axes) || double_lt(fabs(mult), vector_magnitude(mtv))) {
            vector_multiply(axis, mult);
            mtv = axis;
        }
    }
    CGPoint coll_point = NULL;
    CGCircle dup = circle_dup(circle);
    circle_translate(dup, mtv);
    for (ADTListItem it = list_head(vertices); it && !coll_point; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        if (point_is_in_circle(vertex, dup))
            coll_point = point_dup(vertex);
    }
    if (coll_point == NULL) {
        ADTList edges = polygon_edges(polygon);
        for (ADTListItem it = list_head(edges); it && !coll_point; it = list_next(it)) {
            CGSegment segment = (CGSegment) list_value(it);
            CGLine line = line_new(segment->a, segment->b);
            CGLine perpendicular_line = line_perpendicular(line, dup->center);
            CGPoint point = line_intersection(line, perpendicular_line);
            if (point_is_in_circle(point, dup) && point_is_in_polygon(point, polygon))
                coll_point = point_dup(point);
            line_release(line);
            line_release(perpendicular_line);
            point_release(point);
        }
        list_full_release(edges, (void (*)(void *)) segment_release);
    }
    if (coll_point != NULL) {
        collision = collision_new(mtv, coll_point);
        point_release(coll_point);
    }
    circle_release(dup);
    list_full_release(axes, (void (*)(void *)) vector_release);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return collision;
}

CGCollision circle_and_polygon_collision(CGCircle circle, CGPolygon polygon) {
    CGCollision collision = polygon_and_circle_collision(polygon, circle);
    if (collision != NULL) {
        vector_reverse(collision->mtv);
        point_translate(collision->point, collision->mtv);
    }
    return collision;
}

CGCollision circle_and_circle_collision(CGCircle circle1, CGCircle circle2) {
    CGCollision collision = NULL;
    if (double_lte(point_distance_to_point(circle1->center, circle2->center),
                   circle1->radius + circle2->radius)) {
        CGVector mtv = vector_from_point_to_point(circle1->center, circle2->center);
        vector_normalize(mtv);
        double mult1 = double_max(circle_max_projection_on_axis(circle1, mtv) -
                                  circle_min_projection_on_axis(circle2, mtv), 0);
        double mult2 = double_min(circle_min_projection_on_axis(circle1, mtv) -
                                  circle_max_projection_on_axis(circle2, mtv), 0);
        vector_multiply(mtv, double_lt(mult1, -mult2) ? mult1 : mult2);
        CGCircle dup = circle_dup(circle2);
        circle_translate(dup, mtv);
        CGPoint point = midpoint_between(circle1->center, dup->center);
        collision = collision_new(mtv, point);
        vector_release(mtv);
        point_release(point);
        circle_release(dup);
    }
    return collision;
}

void collision_release(CGCollision collision) {
    vector_release(collision->mtv);
    point_release(collision->point);
    free(collision);
}

int collision_equals(CGCollision collision1, CGCollision collision2) {
    return (vector_equals(collision1->mtv, collision2->mtv) &&
            point_equals(collision1->point, collision2->point)) ? 1 : 0;
}

CGCollision collision_dup(CGCollision collision) {
    CGCollision dup = (CGCollision) memalloc(sizeof(*dup));
    dup->mtv = vector_dup(collision->mtv);
    dup->point = point_dup(collision->point);
    return dup;
}

CGVector collision_minimum_translation_vector(CGCollision collision) {
    return vector_dup(collision->mtv);
}

CGPoint collision_point(CGCollision collision) {
    return point_dup(collision->point);
}

