#ifndef __CG__COLLISION__
#define __CG__COLLISION__

#include "cg/cg.h"

typedef struct _CGCollision *CGCollision;
struct _CGCollision {
    CGVector mtv;
    CGPoint point;
};

/* Return 1 if polygon is in contact with another polygon. 0, otherwise. */
int polygon_is_in_contact_with_polygon(CGPolygon polygon1, CGPolygon polygon2);

/* Return 1 if polygon is in contact with a circle. 0, otherwise. */
int polygon_is_in_contact_with_circle(CGPolygon polygon, CGCircle circle);

/* Return minimum projection of polygon on axis. */
double polygon_min_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return maximum projection of polygon on axis. */
double polygon_max_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return minimum projection of circle on axis. */
double circle_min_projection_on_axis(CGCircle circle, CGVector axis);

/* Return maximum projection of circle on axis. */
double circle_max_projection_on_axis(CGCircle circle, CGVector axis);

/* Return a list of axes perpendicular to polygon edges. */
ADTList polygon_perpendicular_axes(CGPolygon polygon);

/* Return a new collision. */
CGCollision collision_new(CGVector mtv, CGPoint point);

/* Return a collision between a polygon and a polygon or NULL. */
CGCollision polygon_and_polygon_collision(CGPolygon polygon1, CGPolygon polygon2);

/* Return a collision between a polygon and a circle or NULL. */
CGCollision polygon_and_circle_collision(CGPolygon polygon, CGCircle circle);

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

