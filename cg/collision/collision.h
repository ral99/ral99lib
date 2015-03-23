#ifndef __CG__COLLISION__
#define __CG__COLLISION__

#include "cg/cg.h"

/* Return minimum projection of polygon on axis. */
double polygon_min_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return maximum projection of polygon on axis. */
double polygon_max_projection_on_axis(CGPolygon polygon, CGVector axis);

/* Return a list of axes perpendicular to polygon edges. */
ADTList polygon_perpendicular_axes(CGPolygon polygon);

/* Return 1 if polygon is in contact with another polygon. 0, otherwise. */
int polygon_is_in_contact_with_polygon(CGPolygon polygon1, CGPolygon polygon2);

/* Return 1 if polygon is colliding with another polygon. 0, otherwise. */
int polygon_is_colliding_with_polygon(CGPolygon polygon1, CGPolygon polygon2);

/* Return the point of contact between two polygons, or NULL if they are not in contact. */
CGPoint polygon_point_of_contact_with_polygon(CGPolygon polygon1, CGPolygon polygon2);

#endif

