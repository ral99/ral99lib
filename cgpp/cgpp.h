#ifndef __CGPP__
#define __CGPP__

#include <vector>

#include "cg/cg.h"
#include "cg/collision/collision.h"

///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// DESIGN NOTES ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
//
// => Angle:
//    Represents angle values. Positive angles represent left angles, negative angles represent
//    right angles.
//
// => Vector:
//    Represents vectors in a two-dimensional space.
//
// => Point:
//    Represents points in a two-dimensional space.
//
// => Segment:
//    Represents a line segment in a two-dimensional space. A Segment is defined by any two
//    points.
//
// => Triangle:
//    Represents a triangle in a two-dimensional space. A Triangle is defined by any three
//    points.
//
// => Shape:
//    An abstract class that represents a shape in a two-dimensional space. Its subclasses
//    are Polygon and Circle.
//
// => Polygon:
//    Represents a convex polygon in a two-dimensional space. A Polygon does not have three
//    collinear points or any two coincident points.
//
// => Circle:
//    Represents a circle in a two-dimensional space. A Circle is defined by a center point
//    and a positive radius.
//
// => Collision:
//    Represents a collision between two shapes in a two-dimensional space. Collision objects
//    have a minimum translation vector (a vector to be applied on to one of the shapes to
//    separate them) and a point of collision.
//
///////////////////////////////////////////////////////////////////////////////////////////////

namespace CG {

class Angle;
class Vector;
class Point;
class Segment;
class Triangle;
class Shape;
class Polygon;
class Circle;
class Collision;

class Angle {
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Circle;
    friend class Collision;

    private:
        CGAngle _angle;
        Angle();

    public:
        // Constructor and destructor.
        Angle(const Angle& other);
        Angle(const CGAngle cgangle);
        static Angle radians(double rad);
        static Angle degrees(double deg);
        ~Angle();

        // Angle assignment operator.
        Angle& operator=(const Angle& other);

        // Angle comparison operators.
        bool operator==(const Angle& other) const;
        bool operator<(const Angle& other) const;
        bool operator<=(const Angle& other) const;
        bool operator>(const Angle& other) const;
        bool operator>=(const Angle& other) const;

        // Angle arithmetic operators.
        Angle operator+() const;
        Angle operator-() const;
        Angle operator+(const Angle& other) const;
        Angle operator-(const Angle& other) const;
        void operator+=(const Angle& other);
        void operator-=(const Angle& other);

        // Return angle in radians.
        double radians() const;

        // Return angle in degrees.
        double degrees() const;
};

class Vector {
    friend class Angle;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Circle;
    friend class Collision;

    private:
        CGVector _vector;
        Vector();

    public:
        // Constructor and destructor.
        Vector(double x, double y);
        Vector(const Point& a, const Point& b);
        Vector(const Vector& other);
        Vector(const CGVector cgvector);
        ~Vector();

        // Vector assignment operator.
        Vector& operator=(const Vector& other);

        // Vector comparison operator.
        bool operator==(const Vector& other) const;
        
        // Vector arithmetic operators.
        Vector operator+() const;
        Vector operator-() const;
        Vector operator+(const Vector& other) const;
        Vector operator-(const Vector& other) const;
        Vector operator*(double k) const;
        void operator+=(const Vector& other);
        void operator-=(const Vector& other);
        void operator*=(double k);

        // Vector rotation in counter-clockwise direction operator.
        void operator%=(const Angle& angle);

        // Normalize vector.
        void normalize();

        // Return vector x component.
        double x() const;

        // Return vector y component.
        double y() const;

        // Return a normalized perpendicular vector using the right hand rule or raise an
        // exception if it is a null vector.
        Vector rightPerpendicularAxis() const;

        // Return a normalized perpendicular vector using the left hand rule or raise an
        // exception if it is a null vector.
        Vector leftPerpendicularAxis() const;

        // Return vector magnitude.
        double magnitude() const;

        // Return the dot product between this and another vector.
        double dot(const Vector& other) const;

        // Return angle from this to another vector in counter-clockwise direction or raise an
        // exception if one or both vectors are null vectors.
        Angle angleTo(const Vector& other) const;
};

class Point {
    friend class Angle;
    friend class Vector;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Circle;
    friend class Collision;

    private:
        CGPoint _point;
        Point();

    public:
        // Constructor and destructor.
        Point(double x, double y);
        Point(const Point& other);
        Point(const CGPoint cgpoint);
        static Point midpointBetween(const Point& a, const Point& b);
        ~Point();

        // Point assignment operator.
        Point& operator=(const Point& other);

        // Point comparison operator.
        bool operator==(const Point& other) const;

        // Point translation operators.
        Point operator+(const Vector& vector) const;
        Point operator-(const Vector& vector) const;
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);

        // Point rotation around origin in counter-clockwise direction operator.
        void operator%=(const Angle& angle);

        // Return point x component.
        double x() const;

        // Return point y component.
        double y() const;

        // Return vector from origin to point.
        Vector vectorFromOrigin() const;

        // Rotate point around a center point in counter-clockwise direction.
        void rotateAround(const Point& center, const Angle& angle);

        // Return distance from this to another point.
        double distanceTo(const Point& other) const;

        // Return distance from this to a segment.
        double distanceTo(const Segment& other) const;

        // Return distance from this to a triangle.
        double distanceTo(const Triangle& other) const;

        // Return distance from this to a polygon.
        double distanceTo(const Polygon& other) const;

        // Return distance from this to a circle.
        double distanceTo(const Circle& other) const;

        // Return true if point is in segment. false, otherwise.
        bool isIn(const Segment& segment) const;

        // Return true if point is in triangle. false, otherwise.
        bool isIn(const Triangle& triangle) const;

        // Return true if point is in polygon. false, otherwise.
        bool isIn(const Polygon& polygon) const;

        // Return true if point is in circle. false, otherwise.
        bool isIn(const Circle& circle) const;
};

class Segment {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Circle;
    friend class Collision;

    private:
        CGSegment _segment;
        Segment();

    public:
        // Constructor and destructor.
        Segment(const Point& a, const Point& b);
        Segment(const Segment& other);
        Segment(const CGSegment cgsegment);
        ~Segment();

        // Segment assignment operator.
        Segment& operator=(const Segment& other);

        // Segment comparison operator.
        bool operator==(const Segment& other) const;

        // Segment translation operator.
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);

        // Segment rotation around origin in counter-clockwise direction operator.
        void operator%=(const Angle& angle);

        // Rotate segment around a center point in counter-clockwise direction.
        void rotateAround(const Point& center, const Angle& angle);

        // Return segment first point.
        Point a() const;

        // Return segment second point.
        Point b() const;

        // Return segment length.
        double length() const;
};

class Triangle {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Shape;
    friend class Polygon;
    friend class Circle;
    friend class Collision;

    private:
        CGTriangle _triangle;
        Triangle();

    public:
        // Constructor and destructor.
        Triangle(const Point& a, const Point& b, const Point& c);
        Triangle(const Triangle& other);
        Triangle(const CGTriangle cgtriangle);
        ~Triangle();

        // Triangle assignment operator.
        Triangle& operator=(const Triangle& other);

        // Triangle comparison operator.
        bool operator==(const Triangle& other) const;

        // Triangle translation operator.
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);

        // Triangle rotation around origin in counter-clockwise direction operator.
        void operator%=(const Angle& angle);

        // Rotate triangle around a center point in counter-clockwise direction.
        void rotateAround(const Point& center, const Angle& angle);

        // Return triangle first vertex.
        Point a() const;

        // Return triangle second vertex.
        Point b() const;

        // Return triangle third vertex.
        Point c() const;

        // Return 1 if triangle is in counter-clockwise orientation. -1, if in clockwise
        // orientation. 0, if vertices are collinear.
        int orientation() const;

        // Return triangle area.
        double area() const;
};

class Shape {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Polygon;
    friend class Circle;
    
    private:
        Shape& operator=(const Shape& other) = delete;

    protected:
        // Constructor.
        Shape() {}
        Shape(const Shape& other) {}

    public:
        // Destructor.
        virtual ~Shape() {}

        // Return a heap allocated shape copy.
        virtual Shape* copy() const = 0;

        // Shape translation operator.
        virtual void operator+=(const Vector& vector) = 0;
        virtual void operator-=(const Vector& vector) = 0;

        // Shape rotation around origin in counter-clockwise direction operator.
        virtual void operator%=(const Angle& angle) = 0;

        // Rotate shape around a center point in counter-clockwise direction.
        virtual void rotateAround(const Point& center, const Angle& angle) = 0;

        // Return shape rectangle hull.
        virtual Polygon rectangleHull() const = 0;

        // Return true if shape is in contact with another shape. false, otherwise.
        bool isInContactWithShape(const Shape& other) const;

        // Return true if shape is in contact with a polygon. false, otherwise.
        virtual bool isInContactWith(const Polygon& other) const = 0;

        // Return true if shape is in contact with a circle. false, otherwise.
        virtual bool isInContactWith(const Circle& other) const = 0;

        // Return true if shape is colliding with another shape. false, otherwise.
        bool isCollidingWithShape(const Shape& other) const;

        // Return true if shape is colliding with a polygon. false, otherwise.
        virtual bool isCollidingWith(const Polygon& other) const = 0;

        // Return true if shape is colliding with a circle. false, otherwise.
        virtual bool isCollidingWith(const Circle& other) const = 0;

        // Return a collision with another shape or NULL.
        Collision* collisionWithShape(const Shape& other) const;

        // Return a collision with a polygon.
        virtual Collision* collisionWith(const Polygon& other) const = 0;

        // Return a collision with a circle.
        virtual Collision* collisionWith(const Circle& other) const = 0;
};

class Polygon : public Shape {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Circle;
    friend class Collision;

    private:
        CGPolygon _polygon;
        Polygon();

    public:
        // Constructor and destructor.
        Polygon(const std::vector<Point>& vertices);
        Polygon(const Polygon& other);
        Polygon(const CGPolygon cgpolygon);
        static Polygon triangle(const Point& a, const Point& b, const Point& c);
        static Polygon rectangle(const Point& lowerLeft, double width, double height);
        static Polygon square(const Point& lowerLeft, double side);
        ~Polygon();
 
        // Polygon assignment operator.
        Polygon& operator=(const Polygon& other);

        // Polygon comparison operator.
        bool operator==(const Polygon& other) const;

        // Shape interface.
        Shape* copy() const;
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);
        void operator%=(const Angle& angle);
        void rotateAround(const Point& center, const Angle& angle);
        Polygon rectangleHull() const;
        bool isInContactWith(const Polygon& other) const;
        bool isInContactWith(const Circle& other) const;
        bool isCollidingWith(const Polygon& other) const;
        bool isCollidingWith(const Circle& other) const;
        Collision* collisionWith(const Polygon& other) const;
        Collision* collisionWith(const Circle& other) const;

        // Return polygon vertices.
        std::vector<Point> vertices() const;

        // Return polygon edges.
        std::vector<Segment> edges() const;

        // Return polygon area.
        double area() const;
};

class Circle : public Shape {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Collision;

    private:
        CGCircle _circle;
        Circle();

    public:
        // Constructor and destructor.
        Circle(const Point& center, double radius);
        Circle(const Circle& other);
        Circle(const CGCircle cgcircle);
        ~Circle();

        // Circle assignment operator.
        Circle& operator=(const Circle& other);

        // Circle comparison operator.
        bool operator==(const Circle& other) const;

        // Shape interface.
        Shape* copy() const;
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);
        void operator%=(const Angle& angle);
        void rotateAround(const Point& center, const Angle& angle);
        Polygon rectangleHull() const;
        bool isInContactWith(const Polygon& other) const;
        bool isInContactWith(const Circle& other) const;
        bool isCollidingWith(const Polygon& other) const;
        bool isCollidingWith(const Circle& other) const;
        Collision* collisionWith(const Polygon& other) const;
        Collision* collisionWith(const Circle& other) const;

        // Return circle center.
        Point center() const;

        // Return circle radius.
        double radius() const;

        // Return circle area.
        double area() const;
};

class Collision {
    friend class Angle;
    friend class Vector;
    friend class Point;
    friend class Segment;
    friend class Triangle;
    friend class Shape;
    friend class Polygon;
    friend class Circle;

    private:
        CGCollision _collision;
        Collision();

    public:
        // Constructor and destructor.
        Collision(const Collision& other);
        Collision(const CGCollision cgcollision);
        ~Collision();

        // Collision assignment operator.
        Collision& operator=(const Collision& other);

        // Collision comparison operator.
        bool operator==(const Collision& other) const;

        // Return collision minimum translation vector.
        Vector minimumTranslationVector() const;

        // Return collision point.
        Point point() const;
};

}

#endif

