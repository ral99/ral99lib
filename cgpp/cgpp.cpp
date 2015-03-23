#include <math.h>
#include <stdexcept>

#include "cgpp/cgpp.h"
#include "num/num.h"

using namespace CG;

// ::: Angle :::

Angle::Angle() {
    _angle = NULL;
}

Angle::Angle(const Angle& other) {
    _angle = angle_dup(other._angle);
}

Angle::Angle(const CGAngle cgangle) {
    _angle = angle_dup(cgangle);
}

Angle Angle::radians(double rad) {
    Angle angle;
    angle._angle = angle_in_radians_new(rad);
    return angle;
}

Angle Angle::degrees(double deg) {
    Angle angle;
    angle._angle = angle_in_degrees_new(deg);
    return angle;
}

Angle::~Angle() {
    if (_angle != NULL)
        angle_release(_angle);
}

Angle& Angle::operator=(const Angle& other) {
    if (this != &other) {
        if (_angle != NULL)
            angle_release(_angle);
        _angle = angle_dup(other._angle);
    }
    return *this;
}

bool Angle::operator==(const Angle& other) const {
    return (angle_equals(_angle, other._angle)) ? true : false;
}

bool Angle::operator<(const Angle& other) const {
    return (angle_lt(_angle, other._angle)) ? true : false;
}

bool Angle::operator<=(const Angle& other) const {
    return (angle_lte(_angle, other._angle)) ? true : false;
}

bool Angle::operator>(const Angle& other) const {
    return (angle_gt(_angle, other._angle)) ? true : false;
}

bool Angle::operator>=(const Angle& other) const {
    return (angle_gte(_angle, other._angle)) ? true : false;
}

Angle Angle::operator+() const {
    Angle angle(_angle);
    return angle;
}

Angle Angle::operator-() const {
    Angle angle;
    angle._angle = angle_in_radians_new(-angle_in_radians(_angle));
    return angle;
}

Angle Angle::operator+(const Angle& other) const {
    Angle angle(_angle);
    angle_sum(angle._angle, other._angle);
    return angle;
}

Angle Angle::operator-(const Angle& other) const {
    Angle angle(_angle);
    angle_subtract(angle._angle, other._angle);
    return angle;
}

void Angle::operator+=(const Angle& other) {
    angle_sum(_angle, other._angle);
}

void Angle::operator-=(const Angle& other) {
    angle_subtract(_angle, other._angle);
}

double Angle::radians() const {
    return angle_in_radians(_angle);
}

double Angle::degrees() const {
    return angle_in_degrees(_angle);
}

// ::: Vector :::

Vector::Vector() {
    _vector = NULL;
}

Vector::Vector(double x, double y) {
    _vector = vector_new(x, y);
}

Vector::Vector(const Point& a, const Point& b) {
    _vector = vector_from_point_to_point(a._point, b._point);
}

Vector::Vector(const Vector& other) {
    _vector = vector_dup(other._vector);
}

Vector::Vector(const CGVector cgvector) {
    _vector = vector_dup(cgvector);
}

Vector::~Vector() {
    if (_vector != NULL)
        vector_release(_vector);
}

Vector& Vector::operator=(const Vector& other) {
    if (this != &other) {
        if (_vector != NULL)
            vector_release(_vector);
        _vector = vector_dup(other._vector);
    }
    return *this;
}

bool Vector::operator==(const Vector& other) const {
    return (vector_equals(_vector, other._vector)) ? true : false;
}

Vector Vector::operator+() const {
    Vector vector(_vector);
    return vector;
}

Vector Vector::operator-() const {
    Vector vector(_vector);
    vector_reverse(vector._vector);
    return vector;
}

Vector Vector::operator+(const Vector& other) const {
    Vector vector(_vector);
    vector_sum(vector._vector, other._vector);
    return vector;
}

Vector Vector::operator-(const Vector& other) const {
    Vector vector(_vector);
    vector_subtract(vector._vector, other._vector);
    return vector;
}

Vector Vector::operator*(double k) const {
    Vector vector(_vector);
    vector_multiply(vector._vector, k);
    return vector;
}

void Vector::operator+=(const Vector& other) {
    vector_sum(_vector, other._vector);
}

void Vector::operator-=(const Vector& other) {
    vector_subtract(_vector, other._vector);
}

void Vector::operator*=(double k) {
    vector_multiply(_vector, k);
}

void Vector::operator%=(const Angle& angle) {
    vector_rotate(_vector, angle._angle);
}

void Vector::normalize() {
    vector_normalize(_vector);
}

double Vector::x() const {
    return vector_x(_vector);
}

double Vector::y() const {
    return vector_y(_vector);
}

Vector Vector::rightPerpendicularAxis() const {
    Vector perpendicular;
    if ((perpendicular._vector = vector_right_perpendicular_axis(_vector)) == NULL)
        throw std::invalid_argument("Invalid operation on null vector.");
    return perpendicular;
}

Vector Vector::leftPerpendicularAxis() const {
    Vector perpendicular;
    if ((perpendicular._vector = vector_left_perpendicular_axis(_vector)) == NULL)
        throw std::invalid_argument("Invalid operation on null vector.");
    return perpendicular;
}

double Vector::magnitude() const {
    return vector_magnitude(_vector);
}

double Vector::dot(const Vector& other) const {
    return vector_dot(_vector, other._vector);
}

Angle Vector::angleTo(const Vector& other) const {
    Angle angle;
    if ((angle._angle = vector_angle_to(_vector, other._vector)) == NULL)
        throw std::invalid_argument("Invalid operation on null vector.");
    return angle;
}

// ::: Point :::

Point::Point() {
    _point = NULL;
}

Point::Point(double x, double y) {
    _point = point_new(x, y);
}

Point::Point(const Point& other) {
    _point = point_dup(other._point);
}

Point::Point(const CGPoint cgpoint) {
    _point = point_dup(cgpoint);
}

Point Point::midpointBetween(const Point& a, const Point& b) {
    Point midpoint;
    midpoint._point = midpoint_between(a._point, b._point);
    return midpoint;
}

Point::~Point() {
    if (_point != NULL)
        point_release(_point);
}

Point& Point::operator=(const Point& other) {
    if (this != &other) {
        if (_point != NULL)
            point_release(_point);
        _point = point_dup(other._point);
    }
    return *this;
}

bool Point::operator==(const Point& other) const {
    return (point_equals(_point, other._point)) ? true : false;
}

Point Point::operator+(const Vector& vector) const {
    Point point(_point);
    point_translate(point._point, vector._vector);
    return point;
}

Point Point::operator-(const Vector& vector) const {
    Point point(_point);
    point_translate(point._point, (-vector)._vector);
    return point;
}

void Point::operator+=(const Vector& vector) {
    point_translate(_point, vector._vector);
}

void Point::operator-=(const Vector& vector) {
    point_translate(_point, (-vector)._vector);
}

void Point::operator%=(const Angle& angle) {
    CGPoint cgorigin = point_new(0, 0);
    point_rotate_around(_point, cgorigin, angle._angle);
    point_release(cgorigin);
}

double Point::x() const {
    return point_x(_point);
}

double Point::y() const {
    return point_y(_point);
}

Vector Point::vectorFromOrigin() const {
    Vector vector;
    vector._vector = vector_from_origin_to_point(_point);
    return vector;
}

void Point::rotateAround(const Point& center, const Angle& angle) {
    point_rotate_around(_point, center._point, angle._angle);
}

double Point::distanceTo(const Point& other) const {
    return point_distance_to_point(_point, other._point);
}

double Point::distanceTo(const Segment& other) const {
    return point_distance_to_segment(_point, other._segment);
}

double Point::distanceTo(const Triangle& other) const {
    return point_distance_to_triangle(_point, other._triangle);
}

double Point::distanceTo(const Polygon& other) const {
    return point_distance_to_polygon(_point, other._polygon);
}

double Point::distanceTo(const Circle& other) const {
    return point_distance_to_circle(_point, other._circle);
}

bool Point::isIn(const Segment& segment) const {
    return (point_is_in_segment(_point, segment._segment) == 1) ? true : false;
}

bool Point::isIn(const Triangle& triangle) const {
    return (point_is_in_triangle(_point, triangle._triangle) == 1) ? true : false;
}

bool Point::isIn(const Polygon& polygon) const {
    return (point_is_in_polygon(_point, polygon._polygon) == 1) ? true : false;
}

bool Point::isIn(const Circle& circle) const {
    return (point_is_in_circle(_point, circle._circle) == 1) ? true : false;
}

// ::: Segment :::

Segment::Segment() {
    _segment = NULL;
}

Segment::Segment(const Point& a, const Point& b) {
    _segment = segment_new(a._point, b._point);
}

Segment::Segment(const Segment& other) {
    _segment = segment_dup(other._segment);
}

Segment::Segment(const CGSegment cgsegment) {
    _segment = segment_dup(cgsegment);
}

Segment::~Segment() {
    if (_segment != NULL)
        segment_release(_segment);
}

Segment& Segment::operator=(const Segment& other) {
    if (this != &other) {
        if (_segment != NULL)
            segment_release(_segment);
        _segment = segment_dup(other._segment);
    }
    return *this;
}

bool Segment::operator==(const Segment& other) const {
    return (segment_equals(_segment, other._segment)) ? true : false;
}

void Segment::operator+=(const Vector& vector) {
    segment_translate(_segment, vector._vector);
}

void Segment::operator-=(const Vector& vector) {
    segment_translate(_segment, (-vector)._vector);
}

void Segment::operator%=(const Angle& angle) {
    CGPoint cgorigin = point_new(0, 0);
    segment_rotate_around(_segment, cgorigin, angle._angle);
    point_release(cgorigin);
}

void Segment::rotateAround(const Point& center, const Angle& angle) {
    segment_rotate_around(_segment, center._point, angle._angle);
}

Point Segment::a() const {
    Point a;
    a._point = segment_a(_segment);
    return a;
}

Point Segment::b() const {
    Point b;
    b._point = segment_b(_segment);
    return b;
}

double Segment::length() const {
    return segment_length(_segment);
}

// ::: Triangle :::

Triangle::Triangle() {
    _triangle = NULL;
}

Triangle::Triangle(const Point& a, const Point& b, const Point& c) {
    _triangle = triangle_new(a._point, b._point, c._point);
}

Triangle::Triangle(const Triangle& other) {
    _triangle = triangle_dup(other._triangle);
}

Triangle::Triangle(const CGTriangle cgtriangle) {
    _triangle = triangle_dup(cgtriangle);
}

Triangle::~Triangle() {
    if (_triangle != NULL)
        triangle_release(_triangle);
}

Triangle& Triangle::operator=(const Triangle& other) {
    if (this != &other) {
        if (_triangle != NULL)
            triangle_release(_triangle);
        _triangle = triangle_dup(other._triangle);
    }
    return *this;
}

bool Triangle::operator==(const Triangle& other) const {
    return (triangle_equals(_triangle, other._triangle)) ? true : false;
}

void Triangle::operator+=(const Vector& vector) {
    triangle_translate(_triangle, vector._vector);
}

void Triangle::operator-=(const Vector& vector) {
    triangle_translate(_triangle, (-vector)._vector);
}

void Triangle::operator%=(const Angle& angle) {
    CGPoint cgorigin = point_new(0, 0);
    triangle_rotate_around(_triangle, cgorigin, angle._angle);
    point_release(cgorigin);
}

void Triangle::rotateAround(const Point& center, const Angle& angle) {
    triangle_rotate_around(_triangle, center._point, angle._angle);
}

Point Triangle::a() const {
    Point a;
    a._point = triangle_a(_triangle);
    return a;
}

Point Triangle::b() const {
    Point b;
    b._point = triangle_b(_triangle);
    return b;
}

Point Triangle::c() const {
    Point c;
    c._point = triangle_c(_triangle);
    return c;
}

int Triangle::orientation() const {
    return triangle_orientation(_triangle);
}

double Triangle::area() const {
    return triangle_area(_triangle);
}

// ::: Shape :::

bool Shape::isInContactWithShape(const Shape& other) const {
    if (const Polygon *polygon = dynamic_cast<const Polygon*>(&other))
        return isInContactWith(*polygon);
    const Circle *circle = dynamic_cast<const Circle*>(&other);
    return isInContactWith(*circle);
}

bool Shape::isCollidingWithShape(const Shape& other) const {
    if (const Polygon *polygon = dynamic_cast<const Polygon*>(&other))
        return isCollidingWith(*polygon);
    const Circle *circle = dynamic_cast<const Circle*>(&other);
    return isCollidingWith(*circle);
}

Collision* Shape::collisionWithShape(const Shape& other) const {
    if (const Polygon *polygon = dynamic_cast<const Polygon*>(&other))
        return collisionWith(*polygon);
    const Circle *circle = dynamic_cast<const Circle*>(&other);
    return collisionWith(*circle);
}

// ::: Polygon :::

Polygon::Polygon() {
    _polygon = NULL;
}

Polygon::Polygon(const std::vector<Point>& vertices) {
    ADTList cgvertices = list_new();
    for (std::vector<const Point>::iterator it = vertices.begin(); it != vertices.end(); it++)
        list_append(cgvertices, it->_point);
    _polygon = polygon_new(cgvertices);
    list_release(cgvertices);
    if (_polygon == NULL)
        throw std::invalid_argument("Invalid vertices.");
}

Polygon::Polygon(const Polygon& other) {
    _polygon = polygon_dup(other._polygon);
}

Polygon::Polygon(const CGPolygon cgpolygon) {
    _polygon = polygon_dup(cgpolygon);
}

Polygon Polygon::triangle(const Point& a, const Point& b, const Point& c) {
    Polygon polygon;
    if ((polygon._polygon = polygon_new_triangle(a._point, b._point, c._point)) == NULL)
        throw std::invalid_argument("Invalid vertices.");
    return polygon;
}

Polygon Polygon::rectangle(const Point& lowerLeft, double width, double height) {
    Polygon polygon;
    if ((polygon._polygon = polygon_new_rectangle(lowerLeft._point, width, height)) == NULL)
        throw std::invalid_argument("Invalid vertices");
    return polygon;
}

Polygon Polygon::square(const Point& lowerLeft, double side) {
    Polygon polygon;
    if ((polygon._polygon = polygon_new_square(lowerLeft._point, side)) == NULL)
        throw std::invalid_argument("Invalid vertices.");
    return polygon;
}

Polygon Polygon::circle(const Point& center, double radius, int nVertices) {
    Polygon polygon;
    if ((polygon._polygon = polygon_new_circle(center._point, radius, nVertices)) == NULL)
        throw std::invalid_argument("Invalid arguments.");
    return polygon;
}

Polygon::~Polygon() {
    if (_polygon != NULL)
        polygon_release(_polygon);
}

Polygon& Polygon::operator=(const Polygon& other) {
    if (this != &other) {
        if (_polygon != NULL)
            polygon_release(_polygon);
        _polygon = polygon_dup(other._polygon);
    }
    return *this;
}

bool Polygon::operator==(const Polygon& other) const {
    return (polygon_equals(_polygon, other._polygon)) ? true : false;
}

Shape* Polygon::copy() const {
    return new Polygon(*this);
}

void Polygon::operator+=(const Vector& vector) {
    polygon_translate(_polygon, vector._vector);
}

void Polygon::operator-=(const Vector& vector) {
    polygon_translate(_polygon, (-vector)._vector);
}

void Polygon::operator%=(const Angle& angle) {
    CGPoint cgorigin = point_new(0, 0);
    polygon_rotate_around(_polygon, cgorigin, angle._angle);
    point_release(cgorigin);
}

void Polygon::rotateAround(const Point& center, const Angle& angle) {
    polygon_rotate_around(_polygon, center._point, angle._angle);
}

Polygon Polygon::rectangleHull() const {
    double minX, maxX, minY, maxY;
    std::vector<Point> vertices = this->vertices();
    for (std::vector<Point>::iterator it = vertices.begin(); it != vertices.end(); it++) {
        if (it == vertices.begin()) {
            minX = maxX = it->x();
            minY = maxY = it->y();
        }
        else {
            minX = double_min(minX, it->x());
            maxX = double_max(maxX, it->x());
            minY = double_min(minY, it->y());
            maxY = double_max(maxY, it->y());
        }
    }
    return Polygon::rectangle(Point(minX, minY), maxX - minX, maxY - minY);
}

bool Polygon::isInContactWith(const Polygon& other) const {
    return polygon_is_in_contact_with_polygon(_polygon, other._polygon);
}

bool Polygon::isInContactWith(const Circle& other) const {
    return polygon_is_in_contact_with_circle(_polygon, other._circle);
}

bool Polygon::isCollidingWith(const Polygon& other) const {
    return polygon_is_colliding_with_polygon(_polygon, other._polygon);
}

bool Polygon::isCollidingWith(const Circle& other) const {
    return polygon_is_colliding_with_circle(_polygon, other._circle);
}

Collision* Polygon::collisionWith(const Polygon& other) const {
    Collision *collision = NULL;
    CGCollision cgcollision = polygon_and_polygon_collision(_polygon, other._polygon);
    if (cgcollision != NULL) {
        collision = new Collision(cgcollision);
        collision_release(cgcollision);
    }
    return collision;
}

Collision* Polygon::collisionWith(const Circle& other) const {
    Collision *collision = NULL;
    CGCollision cgcollision = polygon_and_circle_collision(_polygon, other._circle);
    if (cgcollision != NULL) {
        collision = new Collision(cgcollision);
        collision_release(cgcollision);
    }
    return collision;
}

std::vector<Point> Polygon::vertices() const {
    std::vector<Point> vertices;
    ADTList cgvertices = polygon_vertices(_polygon);
    for (ADTListItem it = list_head(cgvertices); it; it = list_next(it)) {
        Point vertex;
        vertex._point = (CGPoint) list_value(it);
        vertices.push_back(vertex);
    }
    list_release(cgvertices);
    return vertices;
}

std::vector<Segment> Polygon::edges() const {
    std::vector<Segment> edges;
    ADTList cgedges = polygon_edges(_polygon);
    for (ADTListItem it = list_head(cgedges); it; it = list_next(it)) {
        Segment edge;
        edge._segment = (CGSegment) list_value(it);
        edges.push_back(edge);
    }
    list_release(cgedges);
    return edges;
}

double Polygon::area() const {
    return polygon_area(_polygon);
}

// ::: Circle :::

Circle::Circle() {
    _circle = NULL;
}

Circle::Circle(const Point& center, double radius) {
    if ((_circle = circle_new(center._point, radius)) == NULL)
        throw std::invalid_argument("Invalid radius.");
}

Circle::Circle(const Circle& other) {
    _circle = circle_dup(other._circle);
}

Circle::Circle(const CGCircle cgcircle) {
    _circle = circle_dup(cgcircle);
}

Circle::~Circle() {
    if (_circle != NULL)
        circle_release(_circle);
}

Circle& Circle::operator=(const Circle& other) {
    if (this != &other) {
        if (_circle != NULL)
            circle_release(_circle);
        _circle = circle_dup(other._circle);
    }
    return *this;
}

bool Circle::operator==(const Circle& other) const {
    return (circle_equals(_circle, other._circle) == 1) ? true : false;
}

Shape* Circle::copy() const {
    return new Circle(*this);
}

void Circle::operator+=(const Vector& vector) {
    circle_translate(_circle, vector._vector);
}

void Circle::operator-=(const Vector& vector) {
    circle_translate(_circle, (-vector)._vector);
}

void Circle::operator%=(const Angle& angle) {
    CGPoint cgorigin = point_new(0, 0);
    circle_rotate_around(_circle, cgorigin, angle._angle);
    point_release(cgorigin);
}

void Circle::rotateAround(const Point& center, const Angle& angle) {
    circle_rotate_around(_circle, center._point, angle._angle);
}

Polygon Circle::rectangleHull() const {
    double minX = center().x() - radius();
    double maxX = center().x() + radius();
    double minY = center().y() - radius();
    double maxY = center().y() + radius();
    return Polygon::rectangle(Point(minX, minY), maxX - minX, maxY - minY);
}

bool Circle::isInContactWith(const Polygon& other) const {
    return circle_is_in_contact_with_polygon(_circle, other._polygon);
}

bool Circle::isInContactWith(const Circle& other) const {
    return circle_is_in_contact_with_circle(_circle, other._circle);
}

bool Circle::isCollidingWith(const Polygon& other) const {
    return circle_is_colliding_with_polygon(_circle, other._polygon);
}

bool Circle::isCollidingWith(const Circle& other) const {
    return circle_is_colliding_with_circle(_circle, other._circle);
}

Collision* Circle::collisionWith(const Polygon& other) const {
    Collision *collision = NULL;
    CGCollision cgcollision = circle_and_polygon_collision(_circle, other._polygon);
    if (cgcollision != NULL) {
        collision = new Collision(cgcollision);
        collision_release(cgcollision);
    }
    return collision;
}

Collision* Circle::collisionWith(const Circle& other) const {
    Collision *collision = NULL;
    CGCollision cgcollision = circle_and_circle_collision(_circle, other._circle);
    if (cgcollision != NULL) {
        collision = new Collision(cgcollision);
        collision_release(cgcollision);
    }
    return collision;
}

Point Circle::center() const {
    Point center;
    center._point = circle_center(_circle);
    return center;
}

double Circle::radius() const {
    return circle_radius(_circle);
}

double Circle::area() const {
    return circle_area(_circle);
}

// ::: Collision :::

Collision::Collision() {
    _collision = NULL;
}

Collision::Collision(const Collision& other) {
    _collision = collision_dup(other._collision);
}

Collision::Collision(const CGCollision cgcollision) {
    _collision = collision_dup(cgcollision);
}

Collision::~Collision() {
    if (_collision != NULL)
        collision_release(_collision);
}

Collision& Collision::operator=(const Collision& other) {
    if (this != &other) {
        if (_collision != NULL)
            collision_release(_collision);
        _collision = collision_dup(other._collision);
    }
    return *this;
}

bool Collision::operator==(const Collision& other) const {
    return (collision_equals(_collision, other._collision)) ? true : false;
}

Vector Collision::minimumTranslationVector() const {
    Vector mtv;
    mtv._vector = collision_minimum_translation_vector(_collision);
    return mtv;
}

Point Collision::point() const {
    Point point;
    point._point = collision_point(_collision);
    return point;
}

