#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "cg/cg.h"
#include "adt/adt.h"
#include "num/num.h"
#include "mem/mem.h"
#include "str/str.h"

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

CGAngle angle_from_str(char *str) {
    char *str_rad = str_substr(str, 10, strlen(str) - 13);
    CGAngle angle = angle_in_radians_new(atof(str_rad));
    free(str_rad);
    return angle;
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

double angle_in_radians(CGAngle angle) {
    return angle->rad;
}

double angle_in_degrees(CGAngle angle) {
    return (180 * angle->rad) / M_PI;
}

CGAngle angle_complementary(CGAngle angle) {
    return angle_in_radians_new(M_PI / 2 - angle->rad);
}

CGAngle angle_supplementary(CGAngle angle) {
    return angle_in_radians_new(M_PI - angle->rad);
}

CGAngle angle_replementary(CGAngle angle) {
    return angle_in_radians_new(2 * M_PI - angle->rad);
}

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

CGVector vector_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) ", ");
    char *str_x = str_substr((char *) list_at(str_list, 0), 12,
                             strlen((char *) list_at(str_list, 0)) - 12);
    char *str_y = str_substr((char *) list_at(str_list, 1), 0,
                             strlen((char *) list_at(str_list, 1)) - 4);
    CGVector vector = vector_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return vector;
}

double vector_x(CGVector vector) {
    return vector->x;
}

double vector_y(CGVector vector) {
    return vector->y;
}

CGVector vector_right_perpendicular(CGVector vector) {
    return vector_new(vector->y, -vector->x);
}

CGVector vector_left_perpendicular(CGVector vector) {
    return vector_new(-vector->y, vector->x);
}

void vector_normalize(CGVector vector) {
    double magnitude = vector_magnitude(vector);
    vector->x /= magnitude;
    vector->y /= magnitude;
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

CGAngle angle_between_vectors(CGVector vector1, CGVector vector2) {
    double dot = vector_dot(vector1, vector2);
    double magnitude1 = vector_magnitude(vector1);
    double magnitude2 = vector_magnitude(vector2);
    return angle_in_radians_new(acos(dot / (magnitude1 * magnitude2)));
}

CGAngle angle_from_vector_to_vector(CGVector vector1, CGVector vector2) {
    CGVector vector1_dup = vector_dup(vector1);
    CGVector vector2_dup = vector_dup(vector2);
    vector_normalize(vector1_dup);
    vector_normalize(vector2_dup);
    CGAngle angle_between = angle_between_vectors(vector1_dup, vector2_dup);
    vector_rotate(vector1_dup, angle_between);
    CGAngle angle_from_to = (vector_equals(vector1_dup, vector2_dup))
                            ? angle_dup(angle_between) : angle_replementary(angle_between);
    angle_release(angle_between);
    vector_release(vector1_dup);
    vector_release(vector2_dup);
    return angle_from_to;
}

void vector_rotate(CGVector vector, CGAngle angle) {
    double vector_x = vector->x;
    double vector_y = vector->y;
    vector->x = vector_x * cos(angle->rad) - vector_y * sin(angle->rad);
    vector->y = vector_x * sin(angle->rad) + vector_y * cos(angle->rad);
}

CGPoint point_new(double x, double y) {
    CGPoint point = (CGPoint) memalloc(sizeof(*point));
    point->w = 1;
    point->x = x;
    point->y = y;
    return point;
}

void point_release(CGPoint point) {
    free(point);
}

int point_equals(CGPoint point1, CGPoint point2) {
    return (double_equals(point1->x * point2->w, point2->x * point1->w) &&
            double_equals(point1->y * point2->w, point2->y * point1->w));
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

CGPoint point_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) ", ");
    char *str_x = str_substr((char *) list_at(str_list, 0), 11,
                             strlen((char *) list_at(str_list, 0)) - 11);
    char *str_y = str_substr((char *) list_at(str_list, 1), 0,
                             strlen((char *) list_at(str_list, 1)) - 4);
    CGPoint point = point_new(atof(str_x), atof(str_y));
    list_full_release(str_list, free);
    free(str_x);
    free(str_y);
    return point;
}

double point_x(CGPoint point) {
    return point->x / point->w;
}

double point_y(CGPoint point) {
    return point->y / point->w;
}

CGVector point_vector_from_origin(CGPoint point) {
    return vector_new(point_x(point), point_y(point));
}

double point_projection_magnitude_on_axis(CGPoint point, CGVector axis) {
    CGVector projection = vector_dup(axis);
    CGVector vector = point_vector_from_origin(point);
    double projection_magnitude = vector_dot(vector, projection);
    vector_release(vector);
    vector_release(projection);
    return projection_magnitude;
}

CGVector point_projection_on_axis(CGPoint point, CGVector axis) {
    CGVector projection = vector_dup(axis);
    CGVector vector = point_vector_from_origin(point);
    double projection_magnitude = vector_dot(vector, projection);
    vector_multiply(projection, projection_magnitude);
    vector_release(vector);
    return projection;
}

void point_translate(CGPoint point, CGVector vector) {
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x + point->w * vector->x;
    point->y = point_y + point->w * vector->y;
}

void point_rotate_around(CGPoint point, CGPoint center, CGAngle angle) {
    CGVector vector1 = vector_new(-point_x(center), -point_y(center));
    CGVector vector2 = vector_new(point_x(center), point_y(center));
    point_translate(point, vector1);
    double point_x = point->x;
    double point_y = point->y;
    point->x = point_x * cos(angle->rad) - point_y * sin(angle->rad);
    point->y = point_x * sin(angle->rad) + point_y * cos(angle->rad);
    point_translate(point, vector2);
    vector_release(vector1);
    vector_release(vector2);
}

CGPoint midpoint_between_points(CGPoint point1, CGPoint point2) {
    CGPoint midpoint = (CGPoint) memalloc(sizeof(*midpoint));
    midpoint->w = 2 * point1->w * point2->w;
    midpoint->x = point1->x * point2->w + point2->x * point1->w;
    midpoint->y = point1->y * point2->w + point2->y * point1->w;
    return midpoint;
}

void point_normalize(CGPoint point) {
    point->x /= point->w;
    point->y /= point->w;
    point->w = 1;
}

double point_distance_to_line(CGPoint point, CGLine line) {
    CGPoint normalized_point = point_dup(point);
    CGLine normalized_line = line_dup(line);
    point_normalize(normalized_point);
    line_normalize(normalized_line);
    double dist = fabs(normalized_point->w * normalized_line->w +
                       normalized_point->x * normalized_line->x +
                       normalized_point->y * normalized_line->y);
    line_release(normalized_line);
    point_release(normalized_point);
    return dist;
}

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

CGLine line_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) ", ");
    char *str_w = str_substr((char *) list_at(str_list, 0), 10,
                             strlen((char *) list_at(str_list, 0)) - 10);
    char *str_x = str_dup((char *) list_at(str_list, 1));
    char *str_y = str_substr((char *) list_at(str_list, 2), 0,
                             strlen((char *) list_at(str_list, 2)) - 4);
    CGLine line = (CGLine) memalloc(sizeof(*line));
    line->w = atof(str_w);
    line->x = atof(str_x);
    line->y = atof(str_y);
    list_full_release(str_list, free);
    free(str_w);
    free(str_x);
    free(str_y);
    return line;
}

CGLine line_perpendicular(CGLine line, CGPoint point) {
    CGLine perpendicular = (CGLine) memalloc(sizeof(*perpendicular));
    perpendicular->w = (line->y * point->x - line->x * point->y) / point->w;
    perpendicular->x = -line->y;
    perpendicular->y = line->x;
    return perpendicular;
}

CGPoint point_intersection_of_lines(CGLine line1, CGLine line2) {
    CGPoint point = (CGPoint) memalloc(sizeof(*point));
    point->w = line1->x * line2->y - line1->y * line2->x;
    point->x = line1->y * line2->w - line1->w * line2->y;
    point->y = line1->w * line2->x - line1->x * line2->w;
    if (double_equals(point->w, 0)) {
        point_release(point);
        point = NULL;
    }
    return point;
}

void line_normalize(CGLine line) {
    double div = sqrt(line->x * line->x + line->y * line->y);
    line->w /= div;
    line->x /= div;
    line->y /= div;
}

int point_is_in_line(CGPoint point, CGLine line) {
    return double_equals(line->w * point->w + line->x * point->x + line->y * point->y, 0);
}

double point_distance_to_point(CGPoint point1, CGPoint point2) {
    double x_dist = point_x(point1) - point_x(point2);
    double y_dist = point_y(point1) - point_y(point2);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

CGAngle angle_between_lines(CGLine line1, CGLine line2) {
    CGLine normalized_line1 = line_dup(line1);
    CGLine normalized_line2 = line_dup(line2);
    line_normalize(normalized_line1);
    line_normalize(normalized_line2);
    double cos = normalized_line1->x * normalized_line2->x +
                 normalized_line1->y * normalized_line2->y;
    double rad = acos(cos);
    line_release(normalized_line1);
    line_release(normalized_line2);
    return angle_in_radians_new(double_gt(rad, M_PI / 2) ? M_PI - rad : rad);
}

CGSegment segment_new(CGPoint a, CGPoint b) {
    if (point_equals(a, b))
        return NULL;
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
    return (point_equals(segment1->a, segment2->a) && point_equals(segment1->b, segment2->b))
           ? 1 : 0;
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

CGSegment segment_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) "; ");
    char *point_a = str_substr((char *) list_at(str_list, 0), 12,
                               strlen((char *) list_at(str_list, 0)) - 12);
    char *point_b = str_substr((char *) list_at(str_list, 1), 0,
                               strlen((char *) list_at(str_list, 1)) - 3);
    ADTList a_list = str_split(point_a, (char *) ", ");
    ADTList b_list = str_split(point_b, (char *) ", ");
    char *a_x = str_substr((char *) list_at(a_list, 0), 1,
                           strlen((char *) list_at(a_list, 0)) - 1);
    char *a_y = str_substr((char *) list_at(a_list, 1), 0,
                           strlen((char *) list_at(a_list, 1)) - 1);
    char *b_x = str_substr((char *) list_at(b_list, 0), 1,
                           strlen((char *) list_at(b_list, 0)) - 1);
    char *b_y = str_substr((char *) list_at(b_list, 1), 0,
                           strlen((char *) list_at(b_list, 1)) - 1);
    CGPoint a = point_new(atof(a_x), atof(a_y));
    CGPoint b = point_new(atof(b_x), atof(b_y));
    CGSegment segment = segment_new(a, b);
    point_release(a);
    point_release(b);
    list_full_release(str_list, free);
    free(point_a);
    free(point_b);
    list_full_release(a_list, free);
    list_full_release(b_list, free);
    free(a_x);
    free(a_y);
    free(b_x);
    free(b_y);
    return segment;
}

ADTList segment_points(CGSegment segment) {
    ADTList points = list_new();
    list_append(points, point_dup(segment->a));
    list_append(points, point_dup(segment->b));
    return points;
}

CGVector segment_vector(CGSegment segment) {
    return vector_from_point_to_point(segment->a, segment->b);
}

CGLine segment_line(CGSegment segment) {
    return line_new(segment->a, segment->b);
}

double segment_length(CGSegment segment) {
    double x_dist = point_x(segment->a) - point_x(segment->b);
    double y_dist = point_y(segment->a) - point_y(segment->b);
    return sqrt(x_dist * x_dist + y_dist * y_dist);
}

CGShapeProjectionOnAxis segment_projection_on_axis(CGSegment segment, CGVector axis) {
    double magnitude1 = point_projection_magnitude_on_axis(segment->a, axis);
    double magnitude2 = point_projection_magnitude_on_axis(segment->b, axis);
    double min = (double_lte(magnitude1, magnitude2)) ? magnitude1 : magnitude2;
    double max = (double_gte(magnitude1, magnitude2)) ? magnitude1 : magnitude2;
    return shape_projection_on_axis_new(min, max);
}

ADTList segment_collision_axes(CGSegment segment) {
    ADTList collision_axes = list_new();
    CGVector seg_vec = segment_vector(segment);
    CGVector axis = vector_right_perpendicular(seg_vec);
    vector_normalize(axis);
    list_append(collision_axes, axis);
    vector_release(seg_vec);
    return collision_axes;
}

void segment_translate(CGSegment segment, CGVector vector) {
    point_translate(segment->a, vector);
    point_translate(segment->b, vector);
}

void segment_rotate_around(CGSegment segment, CGPoint center, CGAngle angle) {
    point_rotate_around(segment->a, center, angle);
    point_rotate_around(segment->b, center, angle);
}

CGPoint point_intersection_of_segments(CGSegment segment1, CGSegment segment2) {
    double segment1_min_x = (double_lt(point_x(segment1->a), point_x(segment1->b)))
                            ? point_x(segment1->a) : point_x(segment1->b);
    double segment1_max_x = (double_gt(point_x(segment1->a), point_x(segment1->b)))
                            ? point_x(segment1->a) : point_x(segment1->b);
    double segment1_min_y = (double_lt(point_y(segment1->a), point_y(segment1->b)))
                            ? point_y(segment1->a) : point_y(segment1->b);
    double segment1_max_y = (double_gt(point_y(segment1->a), point_y(segment1->b)))
                            ? point_y(segment1->a) : point_y(segment1->b);
    double segment2_min_x = (double_lt(point_x(segment2->a), point_x(segment2->b)))
                            ? point_x(segment2->a) : point_x(segment2->b);
    double segment2_max_x = (double_gt(point_x(segment2->a), point_x(segment2->b)))
                            ? point_x(segment2->a) : point_x(segment2->b);
    double segment2_min_y = (double_lt(point_y(segment2->a), point_y(segment2->b)))
                            ? point_y(segment2->a) : point_y(segment2->b);
    double segment2_max_y = (double_gt(point_y(segment2->a), point_y(segment2->b)))
                            ? point_y(segment2->a) : point_y(segment2->b);
    CGLine line1 = segment_line(segment1);
    CGLine line2 = segment_line(segment2);
    CGPoint intersection = point_intersection_of_lines(line1, line2);
    if (intersection != NULL &&
        (double_lt(point_x(intersection), segment1_min_x) ||
         double_gt(point_x(intersection), segment1_max_x) ||
         double_lt(point_y(intersection), segment1_min_y) ||
         double_gt(point_y(intersection), segment1_max_y) ||
         double_lt(point_x(intersection), segment2_min_x) ||
         double_gt(point_x(intersection), segment2_max_x) ||
         double_lt(point_y(intersection), segment2_min_y) ||
         double_gt(point_y(intersection), segment2_max_y))) {
        point_release(intersection);
        intersection = NULL;
    }
    line_release(line1);
    line_release(line2);
    return intersection;
}

int point_is_in_segment(CGPoint point, CGSegment segment) {
    int is_in = 0;
    CGLine line = line_new(segment->a, segment->b);
    double min_x = (double_lt(point_x(segment->a), point_x(segment->b)))
                   ? point_x(segment->a) : point_x(segment->b);
    double max_x = (double_gt(point_x(segment->a), point_x(segment->b)))
                   ? point_x(segment->a) : point_x(segment->b);
    if (point_is_in_line(point, line) && double_gte(point_x(point), min_x) &&
        double_lte(point_x(point), max_x))
        is_in = 1;
    line_release(line);
    return is_in;
}

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

CGCircle circle_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) "; ");
    char *str_center = str_substr((char *) list_at(str_list, 0), 11,
                                  strlen((char *) list_at(str_list, 0)) - 11);
    char *str_radius = str_substr((char *) list_at(str_list, 1), 0,
                                  strlen((char *) list_at(str_list, 1)) - 3);
    ADTList center_list = str_split(str_center, (char *) ", ");
    char *str_x = str_substr((char *) list_at(center_list, 0), 1,
                             strlen((char *) list_at(center_list, 0)) - 1);
    char *str_y = str_substr((char *) list_at(center_list, 1), 0,
                             strlen((char *) list_at(center_list, 1)) - 1);
    CGPoint center = point_new(atof(str_x), atof(str_y));
    CGCircle circle = circle_new(center, atof(str_radius));
    point_release(center);
    free(str_x);
    free(str_y);
    free(str_center);
    free(str_radius);
    list_full_release(center_list, free);
    list_full_release(str_list, free);
    return circle;
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

double circle_area(CGCircle circle) {
    return M_PI * circle->radius * circle->radius;
}

ADTList circle_points(CGCircle circle, int n_points) {
    ADTList points = list_new();
    for (int i = 0; i < n_points; i++) {
        CGPoint point = point_dup(circle->center);
        CGVector vector = vector_new(circle->radius, 0);
        CGAngle angle = angle_in_degrees_new((360 * i) / n_points);
        vector_rotate(vector, angle);
        point_translate(point, vector);
        list_append(points, point);
        angle_release(angle);
        vector_release(vector);
    }
    return points;
}

void circle_translate(CGCircle circle, CGVector vector) {
    point_translate(circle->center, vector);
}

CGShapeProjectionOnAxis circle_projection_on_axis(CGCircle circle, CGVector axis) {
    double magnitude = point_projection_magnitude_on_axis(circle->center, axis);
    return shape_projection_on_axis_new(magnitude - circle->radius,
                                        magnitude + circle->radius);
}

ADTList circle_collision_axes(CGCircle circle, ADTList points) {
    ADTList collision_axes = list_new();
    for (ADTListItem it = list_head(points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        CGVector axis = vector_from_point_to_point(circle->center, point);
        vector_normalize(axis);
        list_append(collision_axes, axis);
    }
    return collision_axes;
}

int point_is_in_circle(CGPoint point, CGCircle circle) {
    double circle_center_x = point_x(circle->center);
    double circle_center_y = point_y(circle->center);
    double point_x = point->x / point->w;
    double point_y = point->y / point->w;
    double squared_dist = (point_x - circle_center_x) * (point_x - circle_center_x) +
                          (point_y - circle_center_y) * (point_y - circle_center_y);
    return (double_lt(squared_dist, circle->radius * circle->radius)) ? 1 : 0;
}

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

CGTriangle triangle_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) "; ");
    char *str_a = str_substr((char *) list_at(str_list, 0), 14,
                             strlen((char *) list_at(str_list, 0)) - 15);
    ADTList str_a_list = str_split(str_a, (char *) ", ");
    CGPoint a = point_new(atof((char *) list_at(str_a_list, 0)),
                          atof((char *) list_at(str_a_list, 1)));
    char *str_b = str_substr((char *) list_at(str_list, 1), 1,
                             strlen((char *) list_at(str_list, 1)) - 2);
    ADTList str_b_list = str_split(str_b, (char *) ", ");
    CGPoint b = point_new(atof((char *) list_at(str_b_list, 0)),
                          atof((char *) list_at(str_b_list, 1)));
    char *str_c = str_substr((char *) list_at(str_list, 2), 1,
                             strlen((char *) list_at(str_list, 2)) - 5);
    ADTList str_c_list = str_split(str_c, (char *) ", ");
    CGPoint c = point_new(atof((char *) list_at(str_c_list, 0)),
                          atof((char *) list_at(str_c_list, 1)));
    CGTriangle triangle = triangle_new(a, b, c);
    point_release(a);
    point_release(b);
    point_release(c);
    free(str_a);
    free(str_b);
    free(str_c);
    list_full_release(str_list, free);
    list_full_release(str_a_list, free);
    list_full_release(str_b_list, free);
    list_full_release(str_c_list, free);
    return triangle;
}

ADTList triangle_points(CGTriangle triangle) {
    ADTList points = list_new();
    list_append(points, point_dup(triangle->a));
    list_append(points, point_dup(triangle->b));
    list_append(points, point_dup(triangle->c));
    return points;
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

CGShapeProjectionOnAxis triangle_projection_on_axis(CGTriangle triangle, CGVector axis) {
    double min, max;
    ADTList points = triangle_points(triangle);
    for (ADTListItem it = list_head(points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        double magnitude = point_projection_magnitude_on_axis(point, axis);
        min = (it == list_head(points) || double_lt(magnitude, min)) ? magnitude : min;
        max = (it == list_head(points) || double_gt(magnitude, max)) ? magnitude : max;
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return shape_projection_on_axis_new(min, max);
}

ADTList triangle_collision_axes(CGTriangle triangle) {
    ADTList collision_axes = list_new();
    ADTList points = triangle_points(triangle);
    for (int i = 0; i < 3; i++) {
        CGPoint point1 = (CGPoint) list_at(points, i);
        CGPoint point2 = (CGPoint) list_at(points, (i + 1) % 3);
        CGVector vector = vector_from_point_to_point(point1, point2);
        CGVector axis = vector_right_perpendicular(vector);
        vector_normalize(axis);
        list_append(collision_axes, axis);
        vector_release(vector);
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return collision_axes;
}

int point_is_in_triangle(CGPoint point, CGTriangle triangle) {
    int is_in = 0;
    CGTriangle triangle1 = triangle_new(triangle->a, point, triangle->b);
    CGTriangle triangle2 = triangle_new(triangle->b, point, triangle->c);
    CGTriangle triangle3 = triangle_new(triangle->c, point, triangle->a);
    if ((triangle_orientation(triangle1) == 1 &&
         triangle_orientation(triangle2) == 1 &&
         triangle_orientation(triangle3) == 1) ||
        (triangle_orientation(triangle1) == -1 &&
         triangle_orientation(triangle2) == -1 &&
         triangle_orientation(triangle3) == -1))
        is_in = 1;
    triangle_release(triangle1);
    triangle_release(triangle2);
    triangle_release(triangle3);
    return is_in;
}

CGPolygon polygon_new(ADTList points) {
    int n = list_size(points);
    if (n < 3)
        return NULL;
    CGPolygon polygon = (CGPolygon) memalloc(sizeof(*polygon));
    polygon->points = list_new();
    points = list_dup(points);
    CGPoint base_point = NULL;
    for (ADTListItem it = list_head(points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        if (!base_point ||
            double_lt(point_y(point), point_y(base_point)) ||
            (double_equals(point_y(point), point_y(base_point)) &&
             double_lt(point_x(point), point_x(base_point))))
            base_point = point;
    }
    list_append(polygon->points, point_dup(base_point));
    list_remove(points, base_point);
    CGVector base_vector = vector_new(1, 0);
    while (list_size(points)) {
        CGPoint next_point = NULL;
        double next_angle;
        for (ADTListItem it = list_head(points); it; it = list_next(it)) {
            CGPoint point = (CGPoint) list_value(it);
            CGVector vector = vector_new(point_x(point) - point_x(base_point),
                                         point_y(point) - point_y(base_point));
            CGAngle angle = angle_between_vectors(base_vector, vector);
            if (!next_point || double_lt(angle_in_radians(angle), next_angle)) {
                next_angle = angle_in_radians(angle);
                next_point = point;
            }
            vector_release(vector);
        }
        list_append(polygon->points, point_dup(next_point));
        list_remove(points, next_point);
    }
    vector_release(base_vector);
    list_release(points);
    double value = 0;
    for (int i = 0; i < n; i++) {
        CGPoint point1 = (CGPoint) list_at(polygon->points, i);
        CGPoint point2 = (CGPoint) list_at(polygon->points, (i + 1) % n);
        value += point_x(point1) * point_y(point2) - point_x(point2) * point_y(point1);
    }
    if (double_equals(value, 0)) {
        polygon_release(polygon);
        return NULL;
    }
    return polygon;
}

CGPolygon polygon_new_triangle(CGPoint a, CGPoint b, CGPoint c) {
    ADTList points = list_new();
    list_append(points, a);
    list_append(points, b);
    list_append(points, c);
    CGPolygon polygon = polygon_new(points);
    list_release(points);
    return polygon;
}

CGPolygon polygon_new_rectangle(CGPoint lower_left, double width, double height) {
    ADTList points = list_new();
    list_append(points, point_dup(lower_left));
    list_append(points, point_new(point_x(lower_left) + width, point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + width, point_y(lower_left) + height));
    list_append(points, point_new(point_x(lower_left), point_y(lower_left) + height));
    CGPolygon polygon = polygon_new(points);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

CGPolygon polygon_new_square(CGPoint lower_left, double side) {
    ADTList points = list_new();
    list_append(points, point_dup(lower_left));
    list_append(points, point_new(point_x(lower_left) + side, point_y(lower_left)));
    list_append(points, point_new(point_x(lower_left) + side, point_y(lower_left) + side));
    list_append(points, point_new(point_x(lower_left), point_y(lower_left) + side));
    CGPolygon polygon = polygon_new(points);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

void polygon_release(CGPolygon polygon) {
    list_full_release(polygon->points, (void (*)(void *)) point_release);
    free(polygon);
}

int polygon_equals(CGPolygon polygon1, CGPolygon polygon2) {
    if (list_size(polygon1->points) != list_size(polygon2->points))
        return 0;
    for (ADTListItem it = list_head(polygon1->points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        if (!list_find_cmp(polygon2->points, (int (*)(void *, void *)) point_equals, point))
            return 0;
    }
    return 1;
}

CGPolygon polygon_dup(CGPolygon polygon) {
    CGPolygon dup = (CGPolygon) memalloc(sizeof(*dup));
    dup->points = list_new();
    for (ADTListItem it = list_head(polygon->points); it; it = list_next(it))
        list_append(dup->points, point_dup((CGPoint) list_value(it)));
    return dup;
}

char *polygon_to_str(CGPolygon polygon, int decimal_positions) {
    ADTList str_list = list_new();
    list_append(str_list, str_dup((char *) "<< Polygon: ("));
    for (ADTListItem it = list_head(polygon->points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        list_append(str_list, double_to_str(point_x(point), decimal_positions));
        list_append(str_list, str_dup((char *) ", "));
        list_append(str_list, double_to_str(point_y(point), decimal_positions));
        if (list_next(it))
            list_append(str_list, str_dup((char *) "); ("));
        else
            list_append(str_list, str_dup((char *) ") >>"));
    }
    char *str = str_join(str_list, (char *) "");
    list_full_release(str_list, free);
    return str;
}

CGPolygon polygon_from_str(char *str) {
    ADTList str_list = str_split(str, (char *) "; ");
    ADTList points = list_new();
    int n_points = list_size(str_list);
    for (int i = 1; i < n_points - 1; i++) {
        ADTList point_list = str_split((char *) list_at(str_list, i), (char *) ", ");
        char *point_x = str_substr((char *) list_at(point_list, 0), 1,
                                   strlen((char *) list_at(point_list, 0)) - 1);
        char *point_y = str_substr((char *) list_at(point_list, 1), 0,
                                   strlen((char *) list_at(point_list, 1)) - 1);
        list_append(points, point_new(atof(point_x), atof(point_y)));
        list_full_release(point_list, free);
        free(point_x);
        free(point_y);
    }
    ADTList point_0_list = str_split((char *) list_at(str_list, 0), (char *) ", ");
    ADTList point_n_list = str_split((char *) list_at(str_list, n_points - 1), (char *) ", ");
    char *point_0_x = str_substr((char *) list_at(point_0_list, 0), 13,
                                 strlen((char *) list_at(point_0_list, 0)) - 13);
    char *point_0_y = str_substr((char *) list_at(point_0_list, 1), 0,
                                 strlen((char *) list_at(point_0_list, 1)) - 1);
    char *point_n_x = str_substr((char *) list_at(point_n_list, 0), 1,
                                 strlen((char *) list_at(point_n_list, 0)) - 1);
    char *point_n_y = str_substr((char *) list_at(point_n_list, 1), 0,
                                 strlen((char *) list_at(point_n_list, 1)) - 4);
    list_append(points, point_new(atof(point_0_x), atof(point_0_y)));
    list_append(points, point_new(atof(point_n_x), atof(point_n_y)));
    CGPolygon polygon = polygon_new(points);
    list_full_release(str_list, free);
    list_full_release(point_0_list, free);
    list_full_release(point_n_list, free);
    free(point_0_x);
    free(point_0_y);
    free(point_n_x);
    free(point_n_y);
    list_full_release(points, (void (*)(void *)) point_release);
    return polygon;
}

ADTList polygon_points(CGPolygon polygon) {
    ADTList points = list_new();
    for (ADTListItem it = list_head(polygon->points); it; it = list_next(it))
        list_append(points, point_dup((CGPoint) list_value(it)));
    return points;
}

void polygon_translate(CGPolygon polygon, CGVector vector) {
    for (ADTListItem it = list_head(polygon->points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        point_translate(point, vector);
    }
}

void polygon_rotate_around(CGPolygon polygon, CGPoint center, CGAngle angle) {
    for (ADTListItem it = list_head(polygon->points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        point_rotate_around(point, center, angle);
    }
}

double polygon_area(CGPolygon polygon) {
    double double_area = 0;
    int n = list_size(polygon->points);
    for (int i = 0; i < n; i++) {
        CGPoint point1 = (CGPoint) list_at(polygon->points, i);
        CGPoint point2 = (CGPoint) list_at(polygon->points, (i + 1) % n);
        double_area += point_x(point1) * point_y(point2) - point_x(point2) * point_y(point1);
    }
    return fabs(double_area) / 2;
}

CGShapeProjectionOnAxis polygon_projection_on_axis(CGPolygon polygon, CGVector axis) {
    double min, max;
    ADTList points = polygon_points(polygon);
    for (ADTListItem it = list_head(points); it; it = list_next(it)) {
        CGPoint point = (CGPoint) list_value(it);
        double magnitude = point_projection_magnitude_on_axis(point, axis);
        min = (it == list_head(points) || double_lt(magnitude, min)) ? magnitude : min;
        max = (it == list_head(points) || double_gt(magnitude, max)) ? magnitude : max;
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return shape_projection_on_axis_new(min, max);
}

ADTList polygon_collision_axes(CGPolygon polygon) {
    ADTList collision_axes = list_new();
    ADTList points = polygon_points(polygon);
    int n_points = list_size(points);
    for (int i = 0; i < n_points; i++) {
        CGPoint point1 = (CGPoint) list_at(points, i);
        CGPoint point2 = (CGPoint) list_at(points, (i + 1) % n_points);
        CGVector side_vec = vector_from_point_to_point(point1, point2);
        CGVector axis = vector_right_perpendicular(side_vec);
        vector_normalize(axis);
        list_append(collision_axes, axis);
        vector_release(side_vec);
    }
    list_full_release(points, (void (*)(void *)) point_release);
    return collision_axes;
}

int point_is_in_polygon(CGPoint point, CGPolygon polygon) {
    int point_is_in = 1;
    int n = list_size(polygon->points);
    int orientation;
    for (int i = 0; i < n && point_is_in; i++) {
        CGPoint point1 = (CGPoint) list_at(polygon->points, i);
        CGPoint point2 = (CGPoint) list_at(polygon->points, (i + 1) % n);
        CGTriangle triangle = triangle_new(point1, point, point2);
        if (i == 0)
            orientation = triangle_orientation(triangle);
        else if (orientation != triangle_orientation(triangle))
            point_is_in = 0;
        triangle_release(triangle);
    }
    return point_is_in;
}

CGShapeProjectionOnAxis shape_projection_on_axis_new(double min, double max) {
    CGShapeProjectionOnAxis spoa = (CGShapeProjectionOnAxis) memalloc(sizeof(*spoa));
    spoa->min = min;
    spoa->max = max;
    return spoa;
}

void shape_projection_on_axis_release(CGShapeProjectionOnAxis spoa) {
    free(spoa);
}

int shape_projection_on_axis_equals(CGShapeProjectionOnAxis spoa1,
                                    CGShapeProjectionOnAxis spoa2) {
    return (double_equals(spoa1->min, spoa2->min) && double_equals(spoa1->max, spoa2->max))
           ? 1 : 0;
}

CGShapeProjectionOnAxis shape_projection_on_axis_dup(CGShapeProjectionOnAxis spoa) {
    return shape_projection_on_axis_new(spoa->min, spoa->max);
}

double shape_projection_on_axis_min(CGShapeProjectionOnAxis spoa) {
    return spoa->min;
}

double shape_projection_on_axis_max(CGShapeProjectionOnAxis spoa) {
    return spoa->max;
}

double shape_projection_on_axis_tv(CGShapeProjectionOnAxis spoa1,
                                   CGShapeProjectionOnAxis spoa2) {
    if (double_gte(spoa1->min, spoa2->max) || double_gte(spoa2->min, spoa1->max))
        return 0;
    if (double_lte(spoa1->max - spoa2->min, spoa2->max - spoa1->min))
        return spoa1->max - spoa2->min;
    return spoa1->min - spoa2->max;
}

CGVector segment_segment_collision_mtv(CGSegment segment1, CGSegment segment2) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = segment_collision_axes(segment1);
    ADTList axes2 = segment_collision_axes(segment2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment1, axis);
        CGShapeProjectionOnAxis spoa2 = segment_projection_on_axis(segment2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector segment_triangle_collision_mtv(CGSegment segment, CGTriangle triangle) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = segment_collision_axes(segment);
    ADTList axes2 = triangle_collision_axes(triangle);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        CGShapeProjectionOnAxis spoa2 = triangle_projection_on_axis(triangle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector segment_polygon_collision_mtv(CGSegment segment, CGPolygon polygon) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = segment_collision_axes(segment);
    ADTList axes2 = polygon_collision_axes(polygon);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        CGShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector segment_circle_collision_mtv(CGSegment segment, CGCircle circle) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList seg_points = segment_points(segment);
    ADTList axes = list_new();
    ADTList axes1 = segment_collision_axes(segment);
    ADTList axes2 = circle_collision_axes(circle, seg_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = segment_projection_on_axis(segment, axis);
        CGShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_full_release(seg_points, (void (*)(void *)) point_release);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector triangle_segment_collision_mtv(CGTriangle triangle, CGSegment segment) {
    CGVector mtv = segment_triangle_collision_mtv(segment, triangle);
    vector_reverse(mtv);
    return mtv;
}

CGVector triangle_triangle_collision_mtv(CGTriangle triangle1, CGTriangle triangle2) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = triangle_collision_axes(triangle1);
    ADTList axes2 = triangle_collision_axes(triangle2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle1, axis);
        CGShapeProjectionOnAxis spoa2 = triangle_projection_on_axis(triangle2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector triangle_polygon_collision_mtv(CGTriangle triangle, CGPolygon polygon) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = triangle_collision_axes(triangle);
    ADTList axes2 = polygon_collision_axes(polygon);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle, axis);
        CGShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector triangle_circle_collision_mtv(CGTriangle triangle, CGCircle circle) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList tri_points = triangle_points(triangle);
    ADTList axes = list_new();
    ADTList axes1 = triangle_collision_axes(triangle);
    ADTList axes2 = circle_collision_axes(circle, tri_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = triangle_projection_on_axis(triangle, axis);
        CGShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_full_release(tri_points, (void (*)(void *)) point_release);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector polygon_segment_collision_mtv(CGPolygon polygon, CGSegment segment) {
    CGVector mtv = segment_polygon_collision_mtv(segment, polygon);
    vector_reverse(mtv);
    return mtv;
}

CGVector polygon_triangle_collision_mtv(CGPolygon polygon, CGTriangle triangle) {
    CGVector mtv = triangle_polygon_collision_mtv(triangle, polygon);
    vector_reverse(mtv);
    return mtv;
}

CGVector polygon_polygon_collision_mtv(CGPolygon polygon1, CGPolygon polygon2) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList axes = list_new();
    ADTList axes1 = polygon_collision_axes(polygon1);
    ADTList axes2 = polygon_collision_axes(polygon2);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = polygon_projection_on_axis(polygon1, axis);
        CGShapeProjectionOnAxis spoa2 = polygon_projection_on_axis(polygon2, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    return mtv;
}

CGVector polygon_circle_collision_mtv(CGPolygon polygon, CGCircle circle) {
    CGVector mtv;
    double mtv_magnitude;
    ADTList poly_points = polygon_points(polygon);
    ADTList axes = list_new();
    ADTList axes1 = polygon_collision_axes(polygon);
    ADTList axes2 = circle_collision_axes(circle, poly_points);
    list_extend(axes, axes1);
    list_extend(axes, axes2);
    for (ADTListItem it = list_head(axes); it; it = list_next(it)) {
        CGVector axis = (CGVector) list_value(it);
        CGShapeProjectionOnAxis spoa1 = polygon_projection_on_axis(polygon, axis);
        CGShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle, axis);
        double tv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
        if (it == list_head(axes) || double_lt(fabs(tv_magnitude), fabs(mtv_magnitude))) {
            mtv_magnitude = tv_magnitude;
            mtv = axis;
        }
        shape_projection_on_axis_release(spoa1);
        shape_projection_on_axis_release(spoa2);
    }
    mtv = vector_dup(mtv);
    vector_multiply(mtv, mtv_magnitude);
    list_release(axes);
    list_full_release(axes1, (void (*)(void *)) vector_release);
    list_full_release(axes2, (void (*)(void *)) vector_release);
    list_full_release(poly_points, (void (*)(void *)) point_release);
    return mtv;
}

CGVector circle_segment_collision_mtv(CGCircle circle, CGSegment segment) {
    CGVector mtv = segment_circle_collision_mtv(segment, circle);
    vector_reverse(mtv);
    return mtv;
}

CGVector circle_triangle_collision_mtv(CGCircle circle, CGTriangle triangle) {
    CGVector mtv = triangle_circle_collision_mtv(triangle, circle);
    vector_reverse(mtv);
    return mtv;
}

CGVector circle_polygon_collision_mtv(CGCircle circle, CGPolygon polygon) {
    CGVector mtv = polygon_circle_collision_mtv(polygon, circle);
    vector_reverse(mtv);
    return mtv;
}

CGVector circle_circle_collision_mtv(CGCircle circle1, CGCircle circle2) {
    CGVector axis = vector_from_point_to_point(circle1->center, circle2->center);
    vector_normalize(axis);
    CGShapeProjectionOnAxis spoa1 = circle_projection_on_axis(circle1, axis);
    CGShapeProjectionOnAxis spoa2 = circle_projection_on_axis(circle2, axis);
    double mtv_magnitude = shape_projection_on_axis_tv(spoa1, spoa2);
    vector_multiply(axis, mtv_magnitude);
    shape_projection_on_axis_release(spoa1);
    shape_projection_on_axis_release(spoa2);
    return axis;
}

