#ifndef __CG__COLLISION__
#define __CG__COLLISION__

#include "cg/cg.h"

typedef struct _CGCollision *CGCollision;
struct _CGCollision {
    CGVector mtv;
    CGPoint point;
};

/* Return minimum projection of segment on axis. */
double segment_min_projection_on_axis(CGSegment segment, CGVector axis);

/* Return maximum projection of segment on axis. */
double segment_max_projection_on_axis(CGSegment segment, CGVector axis);

/* Return minimum projection of triangle on axis. */
double triangle_min_projection_on_axis(CGTriangle triangle, CGVector axis);

/* Return maximum projection of triangle on axis. */
double triangle_max_projection_on_axis(CGTriangle triangle, CGVector axis);

/* Return minimum projection of polygon on axis. */
double polygon_min_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return maximum projection of polygon on axis. */
double polygon_max_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return minimum projection of circle on axis. */
double circle_min_projection_on_axis(CGCircle circle, CGVector axis);

/* Return maximum projection of circle on axis. */
double circle_max_projection_on_axis(CGCircle circle, CGVector axis);

/* Return a list of axes perpendicular to segment. */
ADTList segment_perpendicular_axes(CGSegment segment);

/* Return a list of axes perpendicular to triangle edges. */
ADTList triangle_perpendicular_axes(CGTriangle triangle);

/* Return a list of axes perpendicular to polygon edges. */
ADTList polygon_perpendicular_axes(CGPolygon polygon);

/* Return a new collision. */
CGCollision collision_new(CGVector mtv, CGPoint point);

/* Return a collision between a segment and a segment or NULL. */
CGCollision segment_and_segment_collision(CGSegment segment1, CGSegment segment2);

/* Return a collision between a segment and a triangle or NULL. */
CGCollision segment_and_triangle_collision(CGSegment segment, CGTriangle triangle);

/* Return a collision between a segment and a polygon or NULL. */
CGCollision segment_and_polygon_collision(CGSegment segment, CGPolygon polygon);

/* Return a collision between a segment and a circle or NULL. */
CGCollision segment_and_circle_collision(CGSegment segment, CGCircle circle);

/* Return a collision between a triangle and a segment or NULL. */
CGCollision triangle_and_segment_collision(CGTriangle triangle, CGSegment segment);

/* Return a collision between a triangle and a triangle or NULL. */
CGCollision triangle_and_triangle_collision(CGTriangle triangle1, CGTriangle triangle2);

/* Return a collision between a triangle and a polygon or NULL. */
CGCollision triangle_and_polygon_collision(CGTriangle triangle, CGPolygon polygon);

/* Return a collision between a triangle and a circle or NULL. */
CGCollision triangle_and_circle_collision(CGTriangle triangle, CGCircle circle);

/* Return a collision between a polygon and a segment or NULL. */
CGCollision polygon_and_segment_collision(CGPolygon polygon, CGSegment segment);

/* Return a collision between a polygon and a triangle or NULL. */
CGCollision polygon_and_triangle_collision(CGPolygon polygon, CGTriangle triangle);

/* Return a collision between a polygon and a polygon or NULL. */
CGCollision polygon_and_polygon_collision(CGPolygon polygon1, CGPolygon polygon2);

/* Return a collision between a polygon and a circle or NULL. */
CGCollision polygon_and_circle_collision(CGPolygon polygon, CGCircle circle);

/* Return a collision between a circle and a segment or NULL. */
CGCollision circle_and_segment_collision(CGCircle circle, CGSegment segment);

/* Return a collision between a circle and a triangle or NULL. */
CGCollision circle_and_triangle_collision(CGCircle circle, CGTriangle triangle);

/* Return a collision between a circle and a polygon or NULL. */
CGCollision circle_and_polygon_collision(CGCircle circle, CGPolygon polygon);

/* Return a collision between a circle and a circle or NULL. */
CGCollision circle_and_circle_collision(CGCircle circle1, CGCircle circle2);

/* Free the memory used by collision. */
void collision_release(CGCollision collision);

/* Return 1 if collision1 is equal to collision2. 0, otherwise. */
int collision_equals(CGCollision collision1, CGCollision collision2);

/* Return a copy of collision. */
CGCollision collision_dup(CGCollision collision);

/* Return collision minimum translation vector. */
CGVector collision_minimum_translation_vector(CGCollision);

/* Return collision point. */
CGPoint collision_point(CGCollision);

#endif

