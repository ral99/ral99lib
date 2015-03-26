#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cg/cg.h"
#include "adt/adt.h"
#include "mem/mem.h"
#include "num/num.h"
#include "str/str.h"

/**********************************************************************************************
 ******************************************* CGAngle ******************************************
 *********************************************************************************************/

CGAngle angle_in_radians_new(double rad) {
    CGAngle angle = (CGAngle) memalloc(sizeof(*angle));
    while (double_lt(rad, 0))
        rad += 2 * M_PI;
    angle->rad = rad - ((int) (rad / (2 * M_PI))) * (2 * M_PI);
    return angle;
}

CGAngle angle_in_degrees_new(double deg) {
    return angle_in_radians_new((M_PI * deg) / 180);
}

void angle_release(CGAngle angle) {
    free(angle);
}

int angle_equals(CGAngle angle1, CGAngle angle2) {
    return double_equals(angle1->rad, angle2->rad);
}

int angle_lt(CGAngle angle1, CGAngle angle2) {
    return double_lt(angle1->rad, angle2->rad);
}

int angle_lte(CGAngle angle1, CGAngle angle2) {
    return double_lte(angle1->rad, angle2->rad);
}

int angle_gt(CGAngle angle1, CGAngle angle2) {
    return double_gt(angle1->rad, angle2->rad);
}

int angle_gte(CGAngle angle1, CGAngle angle2) {
    return double_gte(angle1->rad, angle2->rad);
}

CGAngle angle_dup(CGAngle angle) {
    CGAngle dup = (CGAngle) memalloc(sizeof(*dup));
    dup->rad = angle->rad;
    return dup;
}

char *angle_to_str(CGAngle angle, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Angle: "));
    list_append(str_list, double_to_str(angle->rad, decimal_positions));
    list_append(str_list, str_dup((char *) " >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

double angle_in_radians(CGAngle angle) {
    return angle->rad;
}

double angle_in_degrees(CGAngle angle) {
    return (180 * angle->rad) / M_PI;
}

void angle_sum(CGAngle angle1, CGAngle angle2) {
    angle1->rad += angle2->rad;
    angle1->rad -= ((int) (angle1->rad / (2 * M_PI))) * (2 * M_PI);
}

void angle_subtract(CGAngle angle1, CGAngle angle2) {
    angle1->rad -= angle2->rad;
    while (double_lt(angle1->rad, 0))
        angle1->rad += 2 * M_PI;
}

/**********************************************************************************************
 ****************************************** CGVector ******************************************
 *********************************************************************************************/

CGVector vector_new(double x, double y) {
    CGVector vector = (CGVector) memalloc(sizeof(*vector));
    vector->x = x;
    vector->y = y;
    return vector;
}

CGVector vector_from_point_to_point(CGPoint a, CGPoint b) {
    double x = point_x(b) - point_x(a);
    double y = point_y(b) - point_y(a);
    return vector_new(x, y);
}

CGVector vector_from_origin_to_point(CGPoint point) {
    return vector_new(point_x(point), point_y(point));
}

void vector_release(CGVector vector) {
    free(vector);
}

int vector_equals(CGVector vector1, CGVector vector2) {
    return (double_equals(vector1->x, vector2->x) && double_equals(vector1->y, vector2->y));
}

CGVector vector_dup(CGVector vector) {
    CGVector dup = (CGVector) memalloc(sizeof(*dup));
    dup->x = vector->x;
    dup->y = vector->y;
    return dup;
}

char *vector_to_str(CGVector vector, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Vector: ("));
    list_append(str_list, double_to_str(vector->x, decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(vector->y, decimal_positions));
    list_append(str_list, str_dup((char *) ") >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

double vector_x(CGVector vector) {
    return vector->x;
}

double vector_y(CGVector vector) {
    return vector->y;
}

CGVector vector_right_perpendicular_axis(CGVector vector) {
    CGVector axis = NULL;
    if (double_gt(vector_magnitude(vector), 0)) {
        axis = vector_new(vector->y, -vector->x);
        vector_normalize(axis);
    }
    return axis;
}

CGVector vector_left_perpendicular_axis(CGVector vector) {
    CGVector axis = NULL;
    if (double_gt(vector_magnitude(vector), 0)) {
        axis = vector_new(-vector->y, vector->x);
        vector_normalize(axis);
    }
    return axis;
}

void vector_normalize(CGVector vector) {
    double magnitude = vector_magnitude(vector);
    if (double_gt(magnitude, 0)) {
        vector->x /= magnitude;
        vector->y /= magnitude;
    }
}

void vector_reverse(CGVector vector) {
    vector->x = -vector->x;
    vector->y = -vector->y;
}

void vector_sum(CGVector vector1, CGVector vector2) {
    vector1->x += vector2->x;
    vector1->y += vector2->y;
}

void vector_subtract(CGVector vector1, CGVector vector2) {
    vector1->x -= vector2->x;
    vector1->y -= vector2->y;
}

void vector_multiply(CGVector vector, double k) {
    vector->x *= k;
    vector->y *= k;
}

double vector_magnitude(CGVector vector) {
    return sqrt(vector->x * vector->x + vector->y * vector->y);
}

double vector_dot(CGVector vector1, CGVector vector2) {
    return vector1->x * vector2->x + vector1->y * vector2->y;
}

CGAngle vector_angle_to(CGVector vector1, CGVector vector2) {
    double dot = vector_dot(vector1, vector2);
    double magnitude1 = vector_magnitude(vector1);
    double magnitude2 = vector_magnitude(vector2);
    if (double_equals(magnitude1 * magnitude2, 0))
        return NULL;
    CGAngle angle_between = angle_in_radians_new(acos(dot / (magnitude1 * magnitude2)));
    CGAngle replementary_angle = angle_in_radians_new(2 * M_PI - angle_between->rad);
    CGVector vector1_dup = vector_dup(vector1);
    CGVector vector2_dup = vector_dup(vector2);
    vector_normalize(vector1_dup);
    vector_normalize(vector2_dup);
    vector_rotate(vector1_dup, angle_between);
    CGAngle angle = (vector_equals(vector1_dup, vector2_dup))
                    ? angle_dup(angle_between) : angle_dup(replementary_angle);
    angle_release(angle_between);
    angle_release(replementary_angle);
    vector_release(vector1_dup);
    vector_release(vector2_dup);
    return angle;
}

void vector_rotate(CGVector vector, CGAngle angle) {
    double vector_x = vector->x;
    double vector_y = vector->y;
    vector->x = vector_x * cos(angle->rad) - vector_y * sin(angle->rad);
    vector->y = vector_x * sin(angle->rad) + vector_y * cos(angle->rad);
}

/**********************************************************************************************
 ******************************************* CGPoint ******************************************
 *********************************************************************************************/

CGPoint point_new(double x, double y) {
    CGPoint point = (CGPoint) memalloc(sizeof(*point));
    point->w = 1;
    point->x = x;
    point->y = y;
    return point;
}

CGPoint midpoint_between(CGPoint point1, CGPoint point2) {
    CGPoint midpoint = (CGPoint) memalloc(sizeof(*midpoint));
    midpoint->w = 2 * point1->w * point2->w;
    midpoint->x = point1->x * point2->w + point2->x * point1->w;
    midpoint->y = point1->y * point2->w + point2->y * point1->w;
    return midpoint;
}

void point_release(CGPoint point) {
    free(point);
}

int point_equals(CGPoint point1, CGPoint point2) {
    return (double_equals(point1->x * point2->w, point2->x * point1->w) &&
            double_equals(point1->y * point2->w, point2->y * point1->w));
}

int point_lt(CGPoint point1, CGPoint point2) {
    return (double_lt(point_x(point1), point_x(point2)) ||
            (double_equals(point_x(point1), point_x(point2)) &&
             double_lt(point_y(point1), point_y(point2)))) ? 1 : 0;
}

CGPoint point_dup(CGPoint point) {
    CGPoint dup = (CGPoint) memalloc(sizeof(*dup));
    dup->w = point->w;
    dup->x = point->x;
    dup->y = point->y;
    return dup;
}

char *point_to_str(CGPoint point, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Point: ("));
    list_append(str_list, double_to_str(point_x(point), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(point), decimal_positions));
    list_append(str_list, str_dup((char *) ") >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

double point_x(CGPoint point) {
    return point->x / point->w;
}

double point_y(CGPoint point) {
    return point->y / point->w;
}

void point_translate(CGPoint point, CGVector vector) {
    point->x += point->w * vector->x;
    point->y += point->w * vector->y;
}

void point_rotate_around(CGPoint point, CGPoint center, CGAngle angle) {
    CGVector center_vector = vector_from_origin_to_point(center);
    vector_reverse(center_vector);
    point_translate(point, center_vector);
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x * cos(angle->rad) - point_y * sin(angle->rad);
    point->y = point_x * sin(angle->rad) + point_y * cos(angle->rad);
    vector_reverse(center_vector);
    point_translate(point, center_vector);
    vector_release(center_vector);
}

double point_distance_to_point(CGPoint point1, CGPoint point2) {
    double x_dist = point_x(point1) - point_x(point2);
    double y_dist = point_y(point1) - point_y(point2);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

double point_distance_to_line(CGPoint point, CGLine line) {
    CGPoint normalized_point = point_dup(point);
    normalized_point->x /= point->w;
    normalized_point->y /= point->w;
    normalized_point->w = 1;
    CGLine normalized_line = line_dup(line);
    double normalized_line_divisor = sqrt(line->x * line->x + line->y * line->y);
    normalized_line->w /= normalized_line_divisor;
    normalized_line->x /= normalized_line_divisor;
    normalized_line->y /= normalized_line_divisor;
    double dist = fabs(normalized_point->w * normalized_line->w +
                       normalized_point->x * normalized_line->x +
                       normalized_point->y * normalized_line->y);
    line_release(normalized_line);
    point_release(normalized_point);
    return dist;
}

double point_distance_to_segment(CGPoint point, CGSegment segment) {
    double dist = double_min(point_distance_to_point(point, segment->a),
                             point_distance_to_point(point, segment->b));
    if (!point_equals(segment->a, segment->b)) {
        CGLine segment_line = line_new(segment->a, segment->b);
        CGLine perpendicular_segment_line = line_perpendicular(segment_line, point);
        CGPoint closest_point = line_intersection(segment_line, perpendicular_segment_line);
        if (point_is_in_segment(closest_point, segment))
            dist = double_min(dist, point_distance_to_point(point, closest_point));
        line_release(segment_line);
        line_release(perpendicular_segment_line);
        point_release(closest_point);
    }
    return dist;
}

double point_distance_to_triangle(CGPoint point, CGTriangle triangle) {
    CGSegment segment1 = segment_new(triangle->a, triangle->b);
    CGSegment segment2 = segment_new(triangle->b, triangle->c);
    CGSegment segment3 = segment_new(triangle->c, triangle->a);
    double dist = double_min(point_distance_to_segment(point, segment1),
                             double_min(point_distance_to_segment(point, segment2),
                                        point_distance_to_segment(point, segment3)));
    return (!point_is_in_triangle(point, triangle)) ? dist : -dist;
}

double point_distance_to_polygon(CGPoint point, CGPolygon polygon) {
    double dist;
    ADTList edges = polygon_edges(polygon);
    for (ADTListItem it = list_head(edges); it; it = list_next(it)) {
        CGSegment edge = (CGSegment) list_value(it);
        if (it == list_head(edges))
            dist = point_distance_to_segment(point, edge);
        else
            dist = double_min(dist, point_distance_to_segment(point, edge));
    }
    list_full_release(edges, (void (*)(void *)) segment_release);
    return (!point_is_in_polygon(point, polygon)) ? dist : -dist;
}

double point_distance_to_circle(CGPoint point, CGCircle circle) {
    return point_distance_to_point(point, circle->center) - circle->radius;
}

int point_is_in_line(CGPoint point, CGLine line) {
    return double_equals(line->w * point->w + line->x * point->x + line->y * point->y, 0);
}

int point_is_in_segment(CGPoint point, CGSegment segment) {
    int is_in = 0;
    double min_x = (double_lt(point_x(segment->a), point_x(segment->b)))
                   ? point_x(segment->a) : point_x(segment->b);
    double max_x = (double_gt(point_x(segment->a), point_x(segment->b)))
                   ? point_x(segment->a) : point_x(segment->b);
    double min_y = (double_lt(point_y(segment->a), point_y(segment->b)))
                   ? point_y(segment->a) : point_y(segment->b);
    double max_y = (double_gt(point_y(segment->a), point_y(segment->b)))
                   ? point_y(segment->a) : point_y(segment->b);
    CGLine line = line_new(segment->a, segment->b);
    if (line != NULL) {
        if (point_is_in_line(point, line) && double_gte(point_x(point), min_x) &&
            double_lte(point_x(point), max_x) && double_gte(point_y(point), min_y) &&
            double_lte(point_y(point), max_y))
            is_in = 1;
        line_release(line);
    }
    else if (point_equals(point, segment->a))
            is_in = 1;
    return is_in;
}

int point_is_in_triangle(CGPoint point, CGTriangle triangle) {
    int is_in = 0;
    CGTriangle triangle1 = triangle_new(triangle->a, point, triangle->b);
    CGTriangle triangle2 = triangle_new(triangle->b, point, triangle->c);
    CGTriangle triangle3 = triangle_new(triangle->c, point, triangle->a);
    CGSegment segment1 = segment_new(triangle->a, triangle->b);
    CGSegment segment2 = segment_new(triangle->b, triangle->c);
    CGSegment segment3 = segment_new(triangle->c, triangle->a);
    if ((triangle_orientation(triangle1) == 1 &&
         triangle_orientation(triangle2) == 1 &&
         triangle_orientation(triangle3) == 1) ||
        (triangle_orientation(triangle1) == -1 &&
         triangle_orientation(triangle2) == -1 &&
         triangle_orientation(triangle3) == -1) ||
        (point_is_in_segment(point, segment1) ||
         point_is_in_segment(point, segment2) ||
         point_is_in_segment(point, segment3)))
        is_in = 1;
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    segment_release(segment1);
    segment_release(segment2);
    segment_release(segment3);
    return is_in;
}

int point_is_in_polygon(CGPoint point, CGPolygon polygon) {
    int is_in = 1;
    int n_vertices = list_size(polygon->vertices);
    int orientation;
    for (int i = 0; i < n_vertices && is_in; i++) {
        CGPoint vertex1 = (CGPoint) list_at(polygon->vertices, i);
        CGPoint vertex2 = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        CGTriangle triangle = triangle_new(vertex1, point, vertex2);
        orientation = (i == 0) ? triangle_orientation(triangle) : orientation;
        if (orientation != triangle_orientation(triangle))
            is_in = 0;
        triangle_release(triangle);
    }
    for (int i = 0; i < n_vertices && !is_in; i++) {
        CGPoint vertex1 = (CGPoint) list_at(polygon->vertices, i);
        CGPoint vertex2 = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        CGSegment segment = segment_new(vertex1, vertex2);
        if (point_is_in_segment(point, segment))
            is_in = 1;
        segment_release(segment);
    }
    return is_in;
}

int point_is_in_circle(CGPoint point, CGCircle circle) {
    return (double_lte(point_distance_to_point(point, circle->center), circle->radius));
}

/**********************************************************************************************
 ******************************************* CGLine *******************************************
 *********************************************************************************************/

CGLine line_new(CGPoint a, CGPoint b) {
    if (point_equals(a, b))
        return NULL;
    CGLine line = (CGLine) memalloc(sizeof(*line));
    line->w = a->x * b->y - b->x * a->y;
    line->x = b->w * a->y - a->w * b->y;
    line->y = a->w * b->x - b->w * a->x;
    return line;
}

void line_release(CGLine line) {
    free(line);
}

int line_equals(CGLine line1, CGLine line2) {
    return (double_equals(line1->x / line1->w, line2->x / line2->w) &&
            double_equals(line1->y / line1->w, line2->y / line2->w));
}

CGLine line_dup(CGLine line) {
    CGLine dup = (CGLine) memalloc(sizeof(*dup));
    dup->w = line->w;
    dup->x = line->x;
    dup->y = line->y;
    return dup;
}

char *line_to_str(CGLine line, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Line: ("));
    list_append(str_list, double_to_str(line->w, decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(line->x, decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(line->y, decimal_positions));
    list_append(str_list, str_dup((char *) ") >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

CGLine line_perpendicular(CGLine line, CGPoint point) {
    CGLine perpendicular = (CGLine) memalloc(sizeof(*perpendicular));
    perpendicular->w = (line->y * point->x - line->x * point->y) / point->w;
    perpendicular->x = -line->y;
    perpendicular->y = line->x;
    return perpendicular;
}

CGPoint line_intersection(CGLine line1, CGLine line2) {
    CGPoint intersection = (CGPoint) memalloc(sizeof(*intersection));
    intersection->w = line1->x * line2->y - line1->y * line2->x;
    intersection->x = line1->y * line2->w - line1->w * line2->y;
    intersection->y = line1->w * line2->x - line1->x * line2->w;
    if (double_equals(intersection->w, 0)) {
        point_release(intersection);
        intersection = NULL;
    }
    return intersection;
}

/**********************************************************************************************
 ****************************************** CGSegment *****************************************
 *********************************************************************************************/

CGSegment segment_new(CGPoint a, CGPoint b) {
    CGSegment segment = (CGSegment) memalloc(sizeof(*segment));
    segment->a = point_dup(a);
    segment->b = point_dup(b);
    return segment;
}

void segment_release(CGSegment segment) {
    point_release(segment->a);
    point_release(segment->b);
    free(segment);
}

int segment_equals(CGSegment segment1, CGSegment segment2) {
    return ((point_equals(segment1->a, segment2->a) &&
             point_equals(segment1->b, segment2->b)) ||
            (point_equals(segment1->a, segment2->b) &&
             point_equals(segment1->b, segment2->a))) ? 1 : 0;
}

int segment_lt(CGSegment segment1, CGSegment segment2) {
    CGPoint minPoint1 = point_lt(segment1->a, segment1->b) ? segment1->a : segment1->b;
    CGPoint maxPoint1 = point_lt(segment1->a, segment1->b) ? segment1->b : segment1->a;
    CGPoint minPoint2 = point_lt(segment2->a, segment2->b) ? segment2->a : segment2->b;
    CGPoint maxPoint2 = point_lt(segment2->a, segment2->b) ? segment2->b : segment2->a;
    return (point_lt(minPoint1, minPoint2) ||
            (point_equals(minPoint1, minPoint2) && point_lt(maxPoint1, maxPoint2))) ? 1 : 0;
}

CGSegment segment_dup(CGSegment segment) {
    return segment_new(segment->a, segment->b);
}

char *segment_to_str(CGSegment segment, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Segment: ("));
    list_append(str_list, double_to_str(point_x(segment->a), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(segment->a), decimal_positions));
    list_append(str_list, str_dup((char *) "); ("));
    list_append(str_list, double_to_str(point_x(segment->b), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(segment->b), decimal_positions));
    list_append(str_list, str_dup((char *) ") >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

CGPoint segment_a(CGSegment segment) {
    return point_dup(segment->a);
}

CGPoint segment_b(CGSegment segment) {
    return point_dup(segment->b);
}

void segment_translate(CGSegment segment, CGVector vector) {
    point_translate(segment->a, vector);
    point_translate(segment->b, vector);
}

void segment_rotate_around(CGSegment segment, CGPoint center, CGAngle angle) {
    point_rotate_around(segment->a, center, angle);
    point_rotate_around(segment->b, center, angle);
}

double segment_length(CGSegment segment) {
    double x_dist = point_x(segment->a) - point_x(segment->b);
    double y_dist = point_y(segment->a) - point_y(segment->b);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

/**********************************************************************************************
 ***************************************** CGTriangle *****************************************
 *********************************************************************************************/

CGTriangle triangle_new(CGPoint a, CGPoint b, CGPoint c) {
    CGTriangle triangle = (CGTriangle) memalloc(sizeof(*triangle));
    triangle->a = point_dup(a);
    triangle->b = point_dup(b);
    triangle->c = point_dup(c);
    return triangle;
}

void triangle_release(CGTriangle triangle) {
    point_release(triangle->a);
    point_release(triangle->b);
    point_release(triangle->c);
    free(triangle);
}

int triangle_equals(CGTriangle triangle1, CGTriangle triangle2) {
    if ((point_equals(triangle1->a, triangle2->a) &&
         point_equals(triangle1->b, triangle2->b) &&
         point_equals(triangle1->c, triangle2->c)) ||
        (point_equals(triangle1->a, triangle2->a) &&
         point_equals(triangle1->b, triangle2->c) &&
         point_equals(triangle1->c, triangle2->b)) ||
        (point_equals(triangle1->a, triangle2->b) &&
         point_equals(triangle1->b, triangle2->a) &&
         point_equals(triangle1->c, triangle2->c)) ||
        (point_equals(triangle1->a, triangle2->b) &&
         point_equals(triangle1->b, triangle2->c) &&
         point_equals(triangle1->c, triangle2->a)) ||
        (point_equals(triangle1->a, triangle2->c) &&
         point_equals(triangle1->b, triangle2->a) &&
         point_equals(triangle1->c, triangle2->b)) ||
        (point_equals(triangle1->a, triangle2->c) &&
         point_equals(triangle1->b, triangle2->b) &&
         point_equals(triangle1->c, triangle2->a)))
        return 1;
    return 0;
}

CGTriangle triangle_dup(CGTriangle triangle) {
    return triangle_new(triangle->a, triangle->b, triangle->c);
}

char *triangle_to_str(CGTriangle triangle, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Triangle: ("));
    list_append(str_list, double_to_str(point_x(triangle->a), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(triangle->a), decimal_positions));
    list_append(str_list, str_dup((char *) "); ("));
    list_append(str_list, double_to_str(point_x(triangle->b), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(triangle->b), decimal_positions));
    list_append(str_list, str_dup((char *) "); ("));
    list_append(str_list, double_to_str(point_x(triangle->c), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(triangle->c), decimal_positions));
    list_append(str_list, str_dup((char *) ") >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

CGPoint triangle_a(CGTriangle triangle) {
    return point_dup(triangle->a);
}

CGPoint triangle_b(CGTriangle triangle) {
    return point_dup(triangle->b);
}

CGPoint triangle_c(CGTriangle triangle) {
    return point_dup(triangle->c);
}

void triangle_translate(CGTriangle triangle, CGVector vector) {
    point_translate(triangle->a, vector);
    point_translate(triangle->b, vector);
    point_translate(triangle->c, vector);
}

void triangle_rotate_around(CGTriangle triangle, CGPoint center, CGAngle angle) {
    point_rotate_around(triangle->a, center, angle);
    point_rotate_around(triangle->b, center, angle);
    point_rotate_around(triangle->c, center, angle);
}

int triangle_orientation(CGTriangle triangle) {
    double value = triangle->a->w * triangle->b->x * triangle->c->y +
                   triangle->a->x * triangle->b->y * triangle->c->w +
                   triangle->a->y * triangle->b->w * triangle->c->x -
                   triangle->a->y * triangle->b->x * triangle->c->w -
                   triangle->a->w * triangle->b->y * triangle->c->x -
                   triangle->a->x * triangle->b->w * triangle->c->y;
    return double_equals(value, 0) ? 0 : double_gt(value, 0) ? 1 : -1;
}

double triangle_area(CGTriangle triangle) {
    return fabs(triangle->a->w * triangle->b->x * triangle->c->y +
                triangle->a->x * triangle->b->y * triangle->c->w +
                triangle->a->y * triangle->b->w * triangle->c->x -
                triangle->a->y * triangle->b->x * triangle->c->w -
                triangle->a->w * triangle->b->y * triangle->c->x -
                triangle->a->x * triangle->b->w * triangle->c->y) / 2;
}

/**********************************************************************************************
 ****************************************** CGPolygon *****************************************
 *********************************************************************************************/

CGPolygon polygon_new(ADTList vertices) {
    int n_vertices = list_size(vertices);
    if (n_vertices < 3)
        return NULL;
    CGPolygon polygon = (CGPolygon) memalloc(sizeof(*polygon));
    polygon->vertices = list_new();
    vertices = list_dup(vertices);
    CGPoint base_vertex = NULL;
    for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        if (!base_vertex || double_lt(point_y(vertex), point_y(base_vertex)) ||
            (double_equals(point_y(vertex), point_y(base_vertex)) &&
             double_lt(point_x(vertex), point_x(base_vertex))))
            base_vertex = vertex;
    }
    list_append(polygon->vertices, point_dup(base_vertex));
    list_remove(vertices, base_vertex);
    CGVector base_vector = vector_new(1, 0);
    while (list_size(vertices) > 0) {
        CGPoint next_vertex = NULL;
        CGAngle next_angle = NULL;
        for (ADTListItem it = list_head(vertices); it; it = list_next(it)) {
            CGPoint vertex = (CGPoint) list_value(it);
            CGVector vector = vector_from_point_to_point(base_vertex, vertex);
            CGAngle angle = vector_angle_to(base_vector, vector);
            if (angle == NULL)
                angle = angle_in_radians_new(0);
            if (!next_vertex || angle_lt(angle, next_angle)) {
                if (next_angle != NULL)
                    angle_release(next_angle);
                next_angle = angle_dup(angle);
                next_vertex = vertex;
            }
            angle_release(angle);
            vector_release(vector);
        }
        angle_release(next_angle);
        list_append(polygon->vertices, point_dup(next_vertex));
        list_remove(vertices, next_vertex);
    }
    vector_release(base_vector);
    list_release(vertices);
    for (int i = 0; i < n_vertices && polygon != NULL; i++) {
        CGPoint a = (CGPoint) list_at(polygon->vertices, i);
        CGPoint b = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        CGPoint c = (CGPoint) list_at(polygon->vertices, (i + 2) % n_vertices);
        CGTriangle triangle = triangle_new(a, b, c);
        if (triangle_orientation(triangle) != 1) {
            polygon_release(polygon);
            polygon = NULL;
        }
        triangle_release(triangle);
    }
    return polygon;
}

CGPolygon polygon_new_triangle(CGPoint a, CGPoint b, CGPoint c) {
    ADTList vertices = list_new();
    list_append(vertices, a);
    list_append(vertices, b);
    list_append(vertices, c);
    CGPolygon polygon = polygon_new(vertices);
    list_release(vertices);
    return polygon;
}

CGPolygon polygon_new_rectangle(CGPoint lower_left, double width, double height) {
    ADTList vertices = list_new();
    double x0 = point_x(lower_left);
    double y0 = point_y(lower_left);
    list_append(vertices, point_new(x0, y0));
    list_append(vertices, point_new(x0 + width, y0));
    list_append(vertices, point_new(x0 + width, y0 + height));
    list_append(vertices, point_new(x0, y0 + height));
    CGPolygon polygon = polygon_new(vertices);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return polygon;
}

CGPolygon polygon_new_square(CGPoint lower_left, double side) {
    ADTList vertices = list_new();
    double x0 = point_x(lower_left);
    double y0 = point_y(lower_left);
    list_append(vertices, point_new(x0, y0));
    list_append(vertices, point_new(x0 + side, y0));
    list_append(vertices, point_new(x0 + side, y0 + side));
    list_append(vertices, point_new(x0, y0 + side));
    CGPolygon polygon = polygon_new(vertices);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return polygon;
}

CGPolygon polygon_new_circle(CGPoint center, double radius, int n_vertices) {
    if (double_lte(radius, 0) || n_vertices < 4)
        return NULL;
    ADTList vertices = list_new();
    CGAngle angle = angle_in_radians_new((2 * M_PI) / n_vertices);
    CGVector vector = vector_new(radius, 0);
    for (int i = 0; i < n_vertices; i++) {
        CGPoint vertex = point_dup(center);
        point_translate(vertex, vector);
        list_append(vertices, vertex);
        vector_rotate(vector, angle);
    }
    CGPolygon polygon = polygon_new(vertices);
    angle_release(angle);
    vector_release(vector);
    list_full_release(vertices, (void (*)(void *)) point_release);
    return polygon;
}

void polygon_release(CGPolygon polygon) {
    list_full_release(polygon->vertices, (void (*)(void *)) point_release);
    free(polygon);
}

int polygon_equals(CGPolygon polygon1, CGPolygon polygon2) {
    if (list_size(polygon1->vertices) != list_size(polygon2->vertices))
        return 0;
    for (ADTListItem it = list_head(polygon1->vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        if (!list_find_cmp(polygon2->vertices, (int (*)(void *, void *)) point_equals, vertex))
            return 0;
    }
    return 1;
}

CGPolygon polygon_dup(CGPolygon polygon) {
    CGPolygon dup = (CGPolygon) memalloc(sizeof(*dup));
    dup->vertices = list_new();
    for (ADTListItem it = list_head(polygon->vertices); it; it = list_next(it))
        list_append(dup->vertices, point_dup((CGPoint) list_value(it)));
    return dup;
}

char *polygon_to_str(CGPolygon polygon, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Polygon: ("));
    for (ADTListItem it = list_head(polygon->vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        list_append(str_list, double_to_str(point_x(vertex), decimal_positions));
        list_append(str_list, str_dup((char *) ", "));
        list_append(str_list, double_to_str(point_y(vertex), decimal_positions));
        if (list_next(it))
            list_append(str_list, str_dup((char *) "); ("));
        else
            list_append(str_list, str_dup((char *) ") >>"));
    }
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

ADTList polygon_vertices(CGPolygon polygon) {
    ADTList vertices = list_new();
    for (ADTListItem it = list_head(polygon->vertices); it; it = list_next(it))
        list_append(vertices, point_dup((CGPoint) list_value(it)));
    return vertices;
}

ADTList polygon_edges(CGPolygon polygon) {
    ADTList edges = list_new();
    int n_vertices = list_size(polygon->vertices);
    for (int i = 0; i < n_vertices; i++) {
        CGPoint vertex1 = (CGPoint) list_at(polygon->vertices, i);
        CGPoint vertex2 = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        list_append(edges, segment_new(vertex1, vertex2));
    }
    return edges;
}

void polygon_translate(CGPolygon polygon, CGVector vector) {
    for (ADTListItem it = list_head(polygon->vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        point_translate(vertex, vector);
    }
}

void polygon_rotate_around(CGPolygon polygon, CGPoint center, CGAngle angle) {
    for (ADTListItem it = list_head(polygon->vertices); it; it = list_next(it)) {
        CGPoint vertex = (CGPoint) list_value(it);
        point_rotate_around(vertex, center, angle);
    }
}

double polygon_area(CGPolygon polygon) {
    double area = 0;
    int n_vertices = list_size(polygon->vertices);
    for (int i = 0; i < n_vertices; i++) {
        CGPoint vertex1 = (CGPoint) list_at(polygon->vertices, i);
        CGPoint vertex2 = (CGPoint) list_at(polygon->vertices, (i + 1) % n_vertices);
        area += point_x(vertex1) * point_y(vertex2) - point_x(vertex2) * point_y(vertex1);
    }
    return fabs(area) / 2;
}

/**********************************************************************************************
 ****************************************** CGCircle ******************************************
 *********************************************************************************************/

CGCircle circle_new(CGPoint center, double radius) {
    if (double_lte(radius, 0))
        return NULL;
    CGCircle circle = (CGCircle) memalloc(sizeof(*circle));
    circle->center = point_dup(center);
    circle->radius = radius;
    return circle;
}

void circle_release(CGCircle circle) {
    point_release(circle->center);
    free(circle);
}

int circle_equals(CGCircle circle1, CGCircle circle2) {
    if (point_equals(circle1->center, circle2->center) &&
        double_equals(circle1->radius, circle2->radius))
        return 1;
    return 0;
}

CGCircle circle_dup(CGCircle circle) {
    CGCircle dup = (CGCircle) memalloc(sizeof(*dup));
    dup->center = point_dup(circle->center);
    dup->radius = circle->radius;
    return dup;
}

char *circle_to_str(CGCircle circle, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Circle: ("));
    list_append(str_list, double_to_str(point_x(circle->center), decimal_positions));
    list_append(str_list, str_dup((char *) ", "));
    list_append(str_list, double_to_str(point_y(circle->center), decimal_positions));
    list_append(str_list, str_dup((char *) "); "));
    list_append(str_list, double_to_str(circle->radius, decimal_positions));
    list_append(str_list, str_dup((char *) " >>"));
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

CGPoint circle_center(CGCircle circle) {
    return point_dup(circle->center);
}

double circle_center_x(CGCircle circle) {
    return point_x(circle->center);
}

double circle_center_y(CGCircle circle) {
    return point_y(circle->center);
}

double circle_radius(CGCircle circle) {
    return circle->radius;
}

void circle_translate(CGCircle circle, CGVector vector) {
    point_translate(circle->center, vector);
}

void circle_rotate_around(CGCircle circle, CGPoint center, CGAngle angle) {
    point_rotate_around(circle->center, center, angle);
}

double circle_area(CGCircle circle) {
    return (M_PI * circle->radius * circle->radius);
}
