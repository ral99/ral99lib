#include <math.h>

#include "cgpp/cgpp.h"
#include "gtest/gtest.h"

using namespace CG;

// ::: Angle :::

TEST(Angle, CopyConstructor) {
    EXPECT_EQ(Angle::radians(M_PI), Angle(Angle::radians(M_PI)));
}

TEST(Angle, CopyStructConstructor) {
    CGAngle cgangle = angle_in_radians_new(M_PI);
    EXPECT_EQ(Angle::radians(M_PI), Angle(cgangle));
    angle_release(cgangle);
}

TEST(Angle, RadiansConstructor) {
    EXPECT_DOUBLE_EQ(3 * M_PI / 2, Angle::radians(-M_PI / 2).radians());
    EXPECT_DOUBLE_EQ(0, Angle::radians(0).radians());
    EXPECT_DOUBLE_EQ(M_PI, Angle::radians(M_PI).radians());
    EXPECT_DOUBLE_EQ(0, Angle::radians(2 * M_PI).radians());
    EXPECT_DOUBLE_EQ(M_PI, Angle::radians(3 * M_PI).radians());
}

TEST(Angle, DegreesConstructor) {
    EXPECT_DOUBLE_EQ(270, Angle::degrees(-90).degrees());
    EXPECT_DOUBLE_EQ(0, Angle::degrees(0).degrees());
    EXPECT_DOUBLE_EQ(180, Angle::degrees(180).degrees());
    EXPECT_DOUBLE_EQ(0, Angle::degrees(360).degrees());
    EXPECT_DOUBLE_EQ(180, Angle::degrees(540).degrees());
}

TEST(Angle, Destructor) {
    delete (new Angle(Angle::radians(M_PI)));
}

TEST(Angle, AssignmentOperator) {
    Angle angle = Angle::radians(M_PI);
    EXPECT_EQ(Angle::radians(M_PI), angle);
}

TEST(Angle, ComparisonOperator) {
    EXPECT_EQ(Angle::radians(M_PI), Angle::radians(M_PI));
    EXPECT_EQ(Angle::radians(M_PI), Angle::radians(3 * M_PI));
    EXPECT_EQ(Angle::radians(M_PI), Angle::degrees(180));
    EXPECT_EQ(Angle::radians(M_PI), Angle::degrees(540));
    EXPECT_FALSE(Angle::radians(M_PI) == Angle::radians(0));
}

TEST(Angle, LowerThanOperator) {
    EXPECT_FALSE(Angle::radians(M_PI / 2) < Angle::radians(M_PI / 4));
    EXPECT_FALSE(Angle::radians(M_PI / 2) < Angle::radians(M_PI / 2));
    EXPECT_TRUE(Angle::radians(M_PI / 2) < Angle::radians(M_PI));
}

TEST(Angle, LowerThanOrEqualOperator) {
    EXPECT_FALSE(Angle::radians(M_PI / 2) <= Angle::radians(M_PI / 4));
    EXPECT_TRUE(Angle::radians(M_PI / 2) <= Angle::radians(M_PI / 2));
    EXPECT_TRUE(Angle::radians(M_PI / 2) <= Angle::radians(M_PI));
}

TEST(Angle, GreaterThanOperator) {
    EXPECT_TRUE(Angle::radians(M_PI / 2) > Angle::radians(M_PI / 4));
    EXPECT_FALSE(Angle::radians(M_PI / 2) > Angle::radians(M_PI / 2));
    EXPECT_FALSE(Angle::radians(M_PI / 2) > Angle::radians(M_PI));
}

TEST(Angle, GreaterThanOrEqualOperator) {
    EXPECT_TRUE(Angle::radians(M_PI / 2) >= Angle::radians(M_PI / 4));
    EXPECT_TRUE(Angle::radians(M_PI / 2) >= Angle::radians(M_PI / 2));
    EXPECT_FALSE(Angle::radians(M_PI / 2) >= Angle::radians(M_PI));
}

TEST(Angle, UnaryPositiveOperator) {
    Angle angle = +Angle::radians(M_PI);
    EXPECT_EQ(Angle::radians(M_PI), angle);
}

TEST(Angle, UnaryNegativeOperator) {
    Angle angle = -Angle::radians(M_PI / 2);
    EXPECT_EQ(Angle::radians(3 * M_PI / 2), angle);
}

TEST(Angle, BinarySumOperator) {
    Angle angle = Angle::radians(M_PI) + Angle::radians(M_PI / 2);
    EXPECT_EQ(Angle::radians(3 * M_PI / 2), angle);
}

TEST(Angle, BinarySubtractOperator) {
    Angle angle = Angle::radians(M_PI) - Angle::radians(M_PI / 4);
    EXPECT_EQ(Angle::radians(3 * M_PI / 4), angle);
}

TEST(Angle, UnarySumOperator) {
    Angle angle = Angle::radians(M_PI);
    angle += Angle::radians(M_PI / 2);
    EXPECT_EQ(Angle::radians(3 * M_PI / 2), angle);
}

TEST(Angle, UnarySubtractOperator) {
    Angle angle = Angle::radians(M_PI);
    angle -= Angle::radians(M_PI / 4);
    EXPECT_EQ(Angle::radians(3 * M_PI / 4), angle);
}

TEST(Angle, Radians) {
    EXPECT_DOUBLE_EQ(M_PI, Angle::radians(M_PI).radians());
    EXPECT_DOUBLE_EQ(M_PI, Angle::degrees(180).radians());
}

TEST(Angle, Degrees) {
    EXPECT_DOUBLE_EQ(180, Angle::degrees(180).degrees());
    EXPECT_DOUBLE_EQ(180, Angle::radians(M_PI).degrees());
}

// ::: Vector :::

TEST(Vector, PairOfDoublesConstructor) {
    Vector vector(1, 2);
    EXPECT_DOUBLE_EQ(1, vector.x());
    EXPECT_DOUBLE_EQ(2, vector.y());
}

TEST(Vector, PairOfPointsConstructor) {
    EXPECT_EQ(Vector(1, 2), Vector(Point(0, 0), Point(1, 2)));
    EXPECT_EQ(Vector(-1, -2), Vector(Point(1, 2), Point(0, 0)));
}

TEST(Vector, CopyConstructor) {
    EXPECT_EQ(Vector(1, 2), Vector(Vector(1, 2)));
}

TEST(Vector, CopyStructConstructor) {
    CGVector cgvector = vector_new(1, 2);
    EXPECT_EQ(Vector(1, 2), Vector(cgvector));
    vector_release(cgvector);
}

TEST(Vector, Destructor) {
    delete (new Vector(1, 2));
}

TEST(Vector, AssignmentOperator) {
    Vector vector = Vector(1, 2);
    EXPECT_EQ(Vector(1, 2), vector);
}

TEST(Vector, ComparisonOperator) {
    EXPECT_EQ(Vector(1, 2), Vector(1, 2));
    EXPECT_FALSE(Vector(1, 2) == Vector(1, 3));
    EXPECT_FALSE(Vector(1, 2) == Vector(3, 2));
}

TEST(Vector, UnaryPositiveOperator) {
    Vector vector = +Vector(1, 2);
    EXPECT_EQ(Vector(1, 2), vector);
}

TEST(Vector, UnaryNegativeOperator) {
    Vector vector = -Vector(1, 2);
    EXPECT_EQ(Vector(-1, -2), vector);
}

TEST(Vector, BinarySumOperator) {
    Vector vector = Vector(1, 2) + Vector(3, 4);
    EXPECT_EQ(Vector(4, 6), vector);
}

TEST(Vector, BinarySubtractOperator) {
    Vector vector = Vector(3, 5) - Vector(1, 2);
    EXPECT_EQ(Vector(2, 3), vector);
}

TEST(Vector, BinaryMultiplyOperator) {
    Vector vector = Vector(1, 2) * 2;
    EXPECT_EQ(Vector(2, 4), vector);
}

TEST(Vector, UnarySumOperator) {
    Vector vector(1, 2);
    vector += Vector(3, 4);
    EXPECT_EQ(Vector(4, 6), vector);
}

TEST(Vector, UnarySubtractOperator) {
    Vector vector(3, 5);
    vector -= Vector(1, 2);
    EXPECT_EQ(Vector(2, 3), vector);
}

TEST(Vector, UnaryMultiplyOperator) {
    Vector vector(1, 2);
    vector *= 2;
    EXPECT_EQ(Vector(2, 4), vector);
}

TEST(Vector, BinaryRotationOperator) {
    EXPECT_EQ(Vector(0, 1), Vector(1, 0) % Angle::radians(M_PI / 2));
    EXPECT_EQ(Vector(-1, 0), Vector(1, 0) % Angle::radians(M_PI));
    EXPECT_EQ(Vector(0, -1), Vector(1, 0) % Angle::radians(3 * M_PI / 2));
    EXPECT_EQ(Vector(1, 0), Vector(1, 0) % Angle::radians(2 * M_PI));
}

TEST(Vector, UnaryRotationOperator) {
    Vector vector(1, 0);

    vector %= Angle::radians(0);
    EXPECT_EQ(Vector(1, 0), vector);

    vector %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Vector(0, 1), vector);

    vector %= Angle::radians(M_PI);
    EXPECT_EQ(Vector(0, -1), vector);

    vector %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Vector(1, 0), vector);

    vector %= Angle::radians(M_PI / 4);
    EXPECT_EQ(Vector(sqrt(2) / 2, sqrt(2) / 2), vector);
}

TEST(Vector, Normalize) {
    Vector vector1(1, 0);
    vector1.normalize();
    EXPECT_EQ(Vector(1, 0), vector1);

    Vector vector2(5, 0);
    vector2.normalize();
    EXPECT_EQ(Vector(1, 0), vector2);

    Vector vector3(0, 1);
    vector3.normalize();
    EXPECT_EQ(Vector(0, 1), vector3);

    Vector vector4(0, 5);
    vector4.normalize();
    EXPECT_EQ(Vector(0, 1), vector4);

    Vector vector5(1, 1);
    vector5.normalize();
    EXPECT_EQ(Vector(sqrt(2) / 2, sqrt(2) / 2), vector5);
}

TEST(Vector, Normalized) {
    EXPECT_EQ(Vector(1, 0), Vector(1, 0).normalized());
    EXPECT_EQ(Vector(1, 0), Vector(5, 0).normalized());
    EXPECT_EQ(Vector(0, 1), Vector(0, 1).normalized());
    EXPECT_EQ(Vector(0, 1), Vector(0, 5).normalized());
    EXPECT_EQ(Vector(sqrt(2) / 2, sqrt(2) / 2), Vector(1, 1).normalized());
}

TEST(Vector, X) {
    EXPECT_DOUBLE_EQ(1, Vector(1, 2).x());
}

TEST(Vector, Y) {
    EXPECT_DOUBLE_EQ(2, Vector(1, 2).y());
}

TEST(Vector, RightPerpendicularAxis) {
    EXPECT_EQ(Vector(0, -1), Vector(1, 0).rightPerpendicularAxis());
    EXPECT_EQ(Vector(1, 0), Vector(0, 1).rightPerpendicularAxis());
    EXPECT_EQ(Vector(4 / 5.0, -3 / 5.0), Vector(3, 4).rightPerpendicularAxis());

    EXPECT_ANY_THROW(Vector(0, 0).rightPerpendicularAxis());
}

TEST(Vector, LeftPerpendicularAxis) {
    EXPECT_EQ(Vector(0, 1), Vector(1, 0).leftPerpendicularAxis());
    EXPECT_EQ(Vector(-1, 0), Vector(0, 1).leftPerpendicularAxis());
    EXPECT_EQ(Vector(-4 / 5.0, 3 / 5.0), Vector(3, 4).leftPerpendicularAxis());

    EXPECT_ANY_THROW(Vector(0, 0).leftPerpendicularAxis());
}

TEST(Vector, Magnitude) {
    EXPECT_DOUBLE_EQ(5, Vector(3, 4).magnitude());
    EXPECT_DOUBLE_EQ(5, Vector(-3, 4).magnitude());
    EXPECT_DOUBLE_EQ(5, Vector(3, -4).magnitude());
    EXPECT_DOUBLE_EQ(5, Vector(-3, -4).magnitude());
}

TEST(Vector, Dot) {
    EXPECT_DOUBLE_EQ(0, Vector(0, 0).dot(Vector(0, 0)));
    EXPECT_DOUBLE_EQ(0, Vector(0, 1).dot(Vector(1, 0)));
    EXPECT_DOUBLE_EQ(0, Vector(1, 0).dot(Vector(0, 1)));
    EXPECT_DOUBLE_EQ(0, Vector(1, -1).dot(Vector(1, 1)));
    EXPECT_DOUBLE_EQ(1, Vector(1, 0).dot(Vector(1, 0)));
    EXPECT_DOUBLE_EQ(1, Vector(0, 1).dot(Vector(0, 1)));
    EXPECT_DOUBLE_EQ(2, Vector(1, 1).dot(Vector(1, 1)));
    EXPECT_DOUBLE_EQ(2, Vector(-1, -1).dot(Vector(-1, -1)));
    EXPECT_DOUBLE_EQ(11, Vector(1, 2).dot(Vector(3, 4)));
}

TEST(Vector, AngleTo) {
    EXPECT_DOUBLE_EQ(M_PI / 2, Vector(1, 0).angleTo(Vector(0, 1)).radians());
    EXPECT_DOUBLE_EQ(M_PI, Vector(1, 0).angleTo(Vector(-1, 0)).radians());
    EXPECT_DOUBLE_EQ(3 * M_PI / 2, Vector(1, 0).angleTo(Vector(0, -1)).radians());
    EXPECT_DOUBLE_EQ(0, Vector(1, 0).angleTo(Vector(1, 0)).radians());
    EXPECT_DOUBLE_EQ(M_PI / 4, Vector(1, 0).angleTo(Vector(1, 1)).radians());

    EXPECT_ANY_THROW(Vector(0, 0).angleTo(Vector(1, 1)));
    EXPECT_ANY_THROW(Vector(1, 1).angleTo(Vector(0, 0)));
}

// ::: Point :::

TEST(Point, PairOfDoublesConstructor) {
    Point point(1, 2);
    EXPECT_DOUBLE_EQ(1, point.x());
    EXPECT_DOUBLE_EQ(2, point.y());
}

TEST(Point, CopyConstructor) {
    EXPECT_EQ(Point(1, 2), Point(Point(1, 2)));
}

TEST(Point, CopyStructConstructor) {
    CGPoint cgpoint = point_new(1, 2);
    EXPECT_EQ(Point(1, 2), Point(cgpoint));
    point_release(cgpoint);
}

TEST(Point, MidpointBetweenConstructor) {
    EXPECT_EQ(Point(0, 0), Point::midpointBetween(Point(0, 0), Point(0, 0)));
    EXPECT_EQ(Point(0.5, 0.5), Point::midpointBetween(Point(0, 0), Point(1, 1)));
    EXPECT_EQ(Point(0.5, 0.5), Point::midpointBetween(Point(1, 1), Point(0, 0)));
}

TEST(Point, Destructor) {
    delete (new Point(1, 2));
}

TEST(Point, AssignmentOperator) {
    Point point = Point(1, 2);
    EXPECT_EQ(Point(1, 2), point);
}

TEST(Point, EqualsComparisonOperator) {
    EXPECT_EQ(Point(1, 2), Point(1, 2));
    EXPECT_FALSE(Point(1, 2) == Point(1, 3));
    EXPECT_FALSE(Point(1, 2) == Point(3, 2));
}

TEST(Point, LowerThanComparisonOperator) {
    EXPECT_TRUE(Point(0, 0) < Point(1, 1));
    EXPECT_TRUE(Point(0, 0) < Point(1, 0));
    EXPECT_TRUE(Point(0, 0) < Point(0, 1));
    EXPECT_FALSE(Point(1, 1) < Point(0, 0));
    EXPECT_FALSE(Point(1, 0) < Point(0, 0));
    EXPECT_FALSE(Point(0, 1) < Point(0, 0));
    EXPECT_FALSE(Point(0, 0) < Point(0, 0));
}

TEST(Point, BinaryVectorSumOperator) {
    Point point = Point(1, 2) + Vector(1, 1);
    EXPECT_EQ(Point(2, 3), point);
}

TEST(Point, BinaryVectorSubtractOperator) {
    Point point = Point(1, 2) - Vector(1, 1);
    EXPECT_EQ(Point(0, 1), point);
}

TEST(Point, UnaryVectorSumOperator) {
    Point point(1, 2);
    point += Vector(1, 2);
    EXPECT_EQ(Point(2, 4), point);
}

TEST(Point, UnaryVectorSubtractOperator) {
    Point point(1, 2);
    point -= Vector(1, 2);
    EXPECT_EQ(Point(0, 0), point);
}

TEST(Point, RotationOperator) {
    Point point(1, 0);

    point %= Angle::radians(0);
    EXPECT_EQ(Point(1, 0), point);

    point %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Point(0, 1), point);

    point %= Angle::radians(M_PI);
    EXPECT_EQ(Point(0, -1), point);

    point %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Point(1, 0), point);

    point %= Angle::radians(M_PI / 4);
    EXPECT_EQ(Point(sqrt(2) / 2, sqrt(2) / 2), point);
}

TEST(Point, X) {
    EXPECT_DOUBLE_EQ(1, Point(1, 2).x());
}

TEST(Point, Y) {
    EXPECT_DOUBLE_EQ(2, Point(1, 2).y());
}

TEST(Point, VectorFromOrigin) {
    EXPECT_EQ(Vector(1, 2), Point(1, 2).vectorFromOrigin());
}

TEST(Point, RotateAround) {
    Point point1(2, 2);
    point1.rotateAround(Point(1, 1), Angle::radians(0));
    EXPECT_EQ(Point(2, 2), point1);

    Point point2(2, 2);
    point2.rotateAround(Point(1, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Point(0, 2), point2);

    Point point3(2, 2);
    point3.rotateAround(Point(1, 1), Angle::radians(2 * M_PI));
    EXPECT_EQ(Point(2, 2), point3);

    Point point4(sqrt(2) / 2, sqrt(2) / 2);
    point4.rotateAround(Point(0, 0), Angle::radians(M_PI / 4));
    EXPECT_EQ(Point(0, 1), point4);
}

TEST(Point, DistanceToPoint) {
    EXPECT_DOUBLE_EQ(0, Point(0, 0).distanceTo(Point(0, 0)));
    EXPECT_DOUBLE_EQ(5, Point(0, 0).distanceTo(Point(3, 4)));
    EXPECT_DOUBLE_EQ(5, Point(0, 0).distanceTo(Point(-3, -4)));
}

TEST(Point, DistanceToSegment) {
    EXPECT_DOUBLE_EQ(0, Point(1, 1).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(0, Point(2, 2).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(0, Point(3, 3).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(1, Point(1, 0).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(1, Point(0, 1).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(0, 0).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(4, 4).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(2, 0).distanceTo(Segment(Point(1, 1), Point(3, 3))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(0, 2).distanceTo(Segment(Point(1, 1), Point(3, 3))));

    EXPECT_DOUBLE_EQ(0, Point(1, 1).distanceTo(Segment(Point(1, 1), Point(1, 3))));
    EXPECT_DOUBLE_EQ(0, Point(1, 2).distanceTo(Segment(Point(1, 1), Point(1, 3))));
    EXPECT_DOUBLE_EQ(0, Point(1, 3).distanceTo(Segment(Point(1, 1), Point(1, 3))));
    EXPECT_DOUBLE_EQ(1, Point(1, 0).distanceTo(Segment(Point(1, 1), Point(1, 3))));
    EXPECT_DOUBLE_EQ(1, Point(1, 4).distanceTo(Segment(Point(1, 1), Point(1, 3))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(0, 0).distanceTo(Segment(Point(1, 1), Point(1, 3))));

    EXPECT_DOUBLE_EQ(0, Point(1, 1).distanceTo(Segment(Point(1, 1), Point(3, 1))));
    EXPECT_DOUBLE_EQ(0, Point(2, 1).distanceTo(Segment(Point(1, 1), Point(3, 1))));
    EXPECT_DOUBLE_EQ(0, Point(3, 1).distanceTo(Segment(Point(1, 1), Point(3, 1))));
    EXPECT_DOUBLE_EQ(1, Point(0, 1).distanceTo(Segment(Point(1, 1), Point(3, 1))));
    EXPECT_DOUBLE_EQ(1, Point(4, 1).distanceTo(Segment(Point(1, 1), Point(3, 1))));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(0, 0).distanceTo(Segment(Point(1, 1), Point(3, 1))));

    EXPECT_DOUBLE_EQ(0, Point(0, 0).distanceTo(Segment(Point(0, 0), Point(0, 0))));
    EXPECT_DOUBLE_EQ(1, Point(0, 1).distanceTo(Segment(Point(0, 0), Point(0, 0))));
    EXPECT_DOUBLE_EQ(1, Point(1, 0).distanceTo(Segment(Point(0, 0), Point(0, 0))));
    EXPECT_DOUBLE_EQ(1, Point(-1, 0).distanceTo(Segment(Point(0, 0), Point(0, 0))));
    EXPECT_DOUBLE_EQ(1, Point(0, -1).distanceTo(Segment(Point(0, 0), Point(0, 0))));
}

TEST(Point, DistanceToTriangle) {
    EXPECT_DOUBLE_EQ(
        0, Point(1, 1).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(3, 1).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(1, 3).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(1, 2).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(2, 1).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(2, 2).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(0, 1).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(1, 0).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(0, 2).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(2, 0).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        sqrt(2), Point(0, 0).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );
    EXPECT_DOUBLE_EQ(
        -0.5, Point(1.5, 1.5).distanceTo(Triangle(Point(1, 1), Point(3, 1), Point(1, 3)))
    );

    EXPECT_DOUBLE_EQ(
        0, Point(1, 1).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        0, Point(1, 2).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(2, 1).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(0, 1).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(1, 0).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(1, 3).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );
    EXPECT_DOUBLE_EQ(
        sqrt(2), Point(0, 0).distanceTo(Triangle(Point(1, 1), Point(1, 2), Point(1, 2)))
    );

    EXPECT_DOUBLE_EQ(
        0, Point(1, 1).distanceTo(Triangle(Point(1, 1), Point(1, 1), Point(1, 1)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(1, 2).distanceTo(Triangle(Point(1, 1), Point(1, 1), Point(1, 1)))
    );
    EXPECT_DOUBLE_EQ(
        1, Point(2, 1).distanceTo(Triangle(Point(1, 1), Point(1, 1), Point(1, 1)))
    );
    EXPECT_DOUBLE_EQ(
        sqrt(2), Point(0, 0).distanceTo(Triangle(Point(1, 1), Point(1, 1), Point(1, 1)))
    );
}

TEST(Point, DistanceToPolygon) {
    EXPECT_DOUBLE_EQ(0, Point(1, 1).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(3, 1).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(3, 3).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(1, 3).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(1, 2).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(2, 1).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(3, 2).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(0, Point(2, 3).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(-1, Point(2, 2).distanceTo(Polygon::square(Point(1, 1), 2)));
    EXPECT_DOUBLE_EQ(sqrt(2), Point(0, 0).distanceTo(Polygon::square(Point(1, 1), 2)));
}

TEST(Point, DistanceToCircle) {
    EXPECT_DOUBLE_EQ(-1, Point(1, 1).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(0, Point(0, 1).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(0, Point(2, 1).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(0, Point(1, 0).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(0, Point(1, 2).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(sqrt(2) - 1, Point(0, 0).distanceTo(Circle(Point(1, 1), 1)));
    EXPECT_DOUBLE_EQ(sqrt(2) - 1, Point(2, 2).distanceTo(Circle(Point(1, 1), 1)));
}

TEST(Point, IsInSegment) {
    EXPECT_TRUE(Point(1, 1).isIn(Segment(Point(0, 0), Point(1, 1))));
    EXPECT_TRUE(Point(1, 1).isIn(Segment(Point(1, 1), Point(0, 0))));
    EXPECT_TRUE(Point(1, 1).isIn(Segment(Point(0, 0), Point(2, 2))));
    EXPECT_TRUE(Point(1, 1).isIn(Segment(Point(1, 1), Point(1, 1))));
    EXPECT_FALSE(Point(1, 1).isIn(Segment(Point(1, 2), Point(1, 3))));
    EXPECT_FALSE(Point(1, 1).isIn(Segment(Point(2, 1), Point(3, 1))));
}

TEST(Point, IsInTriangle) {
    EXPECT_FALSE(Point(1, 1).isIn(Triangle(Point(0, 0), Point(0, 1), Point(1, 0))));
    EXPECT_FALSE(Point(0, 2).isIn(Triangle(Point(0, 0), Point(0, 1), Point(1, 0))));
    EXPECT_FALSE(Point(2, 0).isIn(Triangle(Point(0, 0), Point(0, 1), Point(1, 0))));
    EXPECT_TRUE(Point(1, 1).isIn(Triangle(Point(0, 0), Point(0, 1), Point(1, 1))));
    EXPECT_TRUE(Point(1, 1).isIn(Triangle(Point(0, 0), Point(0, 2), Point(2, 2))));
    EXPECT_TRUE(Point(1, 1).isIn(Triangle(Point(0, 0), Point(1, 2), Point(2, 0))));
    EXPECT_TRUE(Point(1, 1).isIn(Triangle(Point(0, 0), Point(1, 1), Point(1, 1))));
    EXPECT_TRUE(Point(1, 1).isIn(Triangle(Point(1, 1), Point(1, 1), Point(1, 1))));
}

TEST(Point, IsInPolygon) {
    EXPECT_FALSE(Point(1, 1).isIn(Polygon::rectangle(Point(0, 0), 1, 0.9)));
    EXPECT_FALSE(Point(1, 1).isIn(Polygon::rectangle(Point(0, 0), 0.9, 1)));
    EXPECT_FALSE(Point(1, 1).isIn(Polygon::square(Point(0, 0), 0.9)));
    EXPECT_TRUE(Point(1, 1).isIn(Polygon::square(Point(0, 0), 1)));
    EXPECT_TRUE(Point(1, 1).isIn(Polygon::square(Point(0, 0), 2)));
    EXPECT_TRUE(Point(1, 1).isIn(Polygon::rectangle(Point(0, 0), 2, 1)));
}

TEST(Point, IsInCircle) {
    EXPECT_FALSE(Point(1, 1).isIn(Circle(Point(0, 0), 1)));
    EXPECT_FALSE(Point(2, 1).isIn(Circle(Point(0, 1), 1)));
    EXPECT_FALSE(Point(1, 2).isIn(Circle(Point(1, 0), 1)));
    EXPECT_TRUE(Point(1, 1).isIn(Circle(Point(0, 1), 1)));
    EXPECT_TRUE(Point(1, 1).isIn(Circle(Point(1, 1), 1)));
}

// ::: Segment :::

TEST(Segment, PairOfPointsConstructor) {
    Segment segment(Point(0, 1), Point(2, 3));
    EXPECT_EQ(Point(0, 1), segment.a());
    EXPECT_EQ(Point(2, 3), segment.b());
}

TEST(Segment, PairOfCoincidentPointsConstructor) {
    Segment segment(Point(1, 1), Point(1, 1));
    EXPECT_EQ(Point(1, 1), segment.a());
    EXPECT_EQ(Point(1, 1), segment.b());
}

TEST(Segment, CopyConstructor) {
    EXPECT_EQ(Segment(Point(0, 1), Point(2, 3)), Segment(Segment(Point(0, 1), Point(2, 3))));
}

TEST(Segment, CopyStructConstructor) {
    CGPoint cga = point_new(0, 1);
    CGPoint cgb = point_new(2, 3);
    CGSegment cgsegment = segment_new(cga, cgb);
    EXPECT_EQ(Segment(Point(0, 1), Point(2, 3)), Segment(cgsegment));
    point_release(cga);
    point_release(cgb);
    segment_release(cgsegment);
}

TEST(Segment, Destructor) {
    delete (new Segment(Point(0, 1), Point(2, 3)));
}

TEST(Segment, AssignmentOperator) {
    Segment segment = Segment(Point(0, 1), Point(2, 3));
    EXPECT_EQ(Segment(Point(0, 1), Point(2, 3)), segment);
}

TEST(Segment, EqualsComparisonOperator) {
    EXPECT_EQ(Segment(Point(1, 1), Point(3, 3)), Segment(Point(1, 1), Point(3, 3)));
    EXPECT_EQ(Segment(Point(1, 1), Point(3, 3)), Segment(Point(3, 3), Point(1, 1)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(0, 0), Point(1, 1)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(3, 3), Point(4, 4)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(1, 1), Point(2, 2)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(2, 2), Point(3, 3)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(0, 0), Point(3, 3)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(1, 1), Point(4, 4)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(3, 3)) == Segment(Point(0, 0), Point(4, 4)));
}

TEST(Segment, LowerThanComparisonOperator) {
    EXPECT_TRUE(Segment(Point(0, 0), Point(1, 1)) < Segment(Point(0, 1), Point(1, 1)));
    EXPECT_TRUE(Segment(Point(0, 0), Point(1, 1)) < Segment(Point(1, 1), Point(0, 1)));
    EXPECT_TRUE(Segment(Point(1, 1), Point(0, 0)) < Segment(Point(0, 1), Point(1, 1)));
    EXPECT_TRUE(Segment(Point(1, 1), Point(0, 0)) < Segment(Point(1, 1), Point(0, 1)));
    EXPECT_FALSE(Segment(Point(0, 1), Point(1, 1)) < Segment(Point(0, 0), Point(1, 1)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(0, 1)) < Segment(Point(0, 0), Point(1, 1)));
    EXPECT_FALSE(Segment(Point(0, 1), Point(1, 1)) < Segment(Point(1, 1), Point(0, 0)));
    EXPECT_FALSE(Segment(Point(1, 1), Point(0, 1)) < Segment(Point(1, 1), Point(0, 0)));
    EXPECT_FALSE(Segment(Point(0, 0), Point(1, 1)) < Segment(Point(0, 0), Point(1, 1)));
}

TEST(Segment, VectorSumOperator) {
    Segment segment(Point(0, 0), Point(1, 1));
    segment += Vector(1, 2);
    EXPECT_EQ(Segment(Point(1, 2), Point(2, 3)), segment);
}

TEST(Segment, VectorSubtractOperator) {
    Segment segment(Point(1, 1), Point(2, 2));
    segment -= Vector(1, 1);
    EXPECT_EQ(Segment(Point(0, 0), Point(1, 1)), segment);
}

TEST(Segment, RotationOperator) {
    Segment segment(Point(0, 0), Point(1, 1));

    segment %= Angle::radians(0);
    EXPECT_EQ(Segment(Point(0, 0), Point(1, 1)), segment);

    segment %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Segment(Point(0, 0), Point(-1, 1)), segment);
    
    segment %= Angle::radians(M_PI);
    EXPECT_EQ(Segment(Point(0, 0), Point(1, -1)), segment);

    segment %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Segment(Point(0, 0), Point(1, 1)), segment);

    segment %= Angle::radians(M_PI / 4);
    EXPECT_EQ(Segment(Point(0, 0), Point(0, sqrt(2))), segment);
}

TEST(Segment, RotateAround) {
    Segment segment(Point(0, 0), Point(1, 1));

    segment.rotateAround(Point(2, 2), Angle::radians(0));
    EXPECT_EQ(Segment(Point(0, 0), Point(1, 1)), segment);

    segment.rotateAround(Point(2, 2), Angle::radians(M_PI / 2));
    EXPECT_EQ(Segment(Point(4, 0), Point(3, 1)), segment);

    segment.rotateAround(Point(2, 2), Angle::radians(M_PI));
    EXPECT_EQ(Segment(Point(0, 4), Point(1, 3)), segment);

    segment.rotateAround(Point(2, 2), Angle::radians(M_PI / 2));
    EXPECT_EQ(Segment(Point(0, 0), Point(1, 1)), segment);
}

TEST(Segment, A) {
    EXPECT_EQ(Point(0, 0), Segment(Point(0, 0), Point(1, 1)).a());
}

TEST(Segment, B) {
    EXPECT_EQ(Point(1, 1), Segment(Point(0, 0), Point(1, 1)).b());
}

TEST(Segment, Length) {
    EXPECT_DOUBLE_EQ(5, Segment(Point(0, 0), Point(3, 4)).length());
    EXPECT_DOUBLE_EQ(5, Segment(Point(0, 0), Point(-3, 4)).length());
    EXPECT_DOUBLE_EQ(5, Segment(Point(0, 0), Point(3, -4)).length());
    EXPECT_DOUBLE_EQ(5, Segment(Point(0, 0), Point(-3, -4)).length());
}

// ::: Triangle :::

TEST(Triangle, TripleOfPointsConstructor) {
    Triangle triangle(Point(0, 0), Point(1, 0), Point(0, 1));
    EXPECT_EQ(Point(0, 0), triangle.a());
    EXPECT_EQ(Point(1, 0), triangle.b());
    EXPECT_EQ(Point(0, 1), triangle.c());
}

TEST(Triangle, TripleOfCoincidentPointsConstructor) {
    Triangle triangle(Point(1, 1), Point(1, 1), Point(1, 1));
    EXPECT_EQ(Point(1, 1), triangle.a());
    EXPECT_EQ(Point(1, 1), triangle.b());
    EXPECT_EQ(Point(1, 1), triangle.c());
}

TEST(Triangle, CopyConstructor) {
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Triangle(Point(0, 0), Point(1, 0), Point(0, 1))));
}

TEST(Triangle, CopyStructConstructor) {
    CGPoint cga = point_new(0, 0);
    CGPoint cgb = point_new(1, 0);
    CGPoint cgc = point_new(0, 1);
    CGTriangle cgtriangle = triangle_new(cga, cgb, cgc);
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)), Triangle(cgtriangle));
    point_release(cga);
    point_release(cgb);
    point_release(cgc);
    triangle_release(cgtriangle);
}

TEST(Triangle, Destruct) {
    delete (new Triangle(Point(0, 0), Point(1, 0), Point(0, 1)));
}

TEST(Triangle, AssignmentOperator) {
    Triangle triangle = Triangle(Point(0, 0), Point(1, 0), Point(0, 1));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)), triangle);
}

TEST(Triangle, ComparisonOperator) { 
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(0, 0), Point(1, 0), Point(0, 1)));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(0, 0), Point(0, 1), Point(1, 0)));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(0, 1), Point(0, 0), Point(1, 0)));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(0, 1), Point(1, 0), Point(0, 0)));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(1, 0), Point(0, 0), Point(0, 1)));
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)),
              Triangle(Point(1, 0), Point(0, 1), Point(0, 0)));
    EXPECT_FALSE(Triangle(Point(0, 0), Point(1, 0), Point(0, 1)) ==
                 Triangle(Point(1, 1), Point(0, 1), Point(0, 0)));
}

TEST(Triangle, VectorSumOperator) {
    Triangle triangle(Point(0, 0), Point(1, 0), Point(0, 1));
    triangle += Vector(1, 2);
    EXPECT_EQ(Triangle(Point(1, 2), Point(2, 2), Point(1, 3)), triangle);
}

TEST(Triangle, VectorSubtractOperator) {
    Triangle triangle(Point(2, 2), Point(3, 2), Point(2, 3));
    triangle -= Vector(1, 2);
    EXPECT_EQ(Triangle(Point(1, 0), Point(2, 0), Point(1, 1)), triangle);
}

TEST(Triangle, RotationOperator) {
    Triangle triangle(Point(0, 0), Point(0, 1), Point(1, 0));

    triangle %= Angle::radians(0);
    EXPECT_EQ(Triangle(Point(0, 0), Point(0, 1), Point(1, 0)), triangle);

    triangle %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Triangle(Point(0, 0), Point(-1, 0), Point(0, 1)), triangle);

    triangle %= Angle::radians(M_PI);
    EXPECT_EQ(Triangle(Point(0, 0), Point(1, 0), Point(0, -1)), triangle);

    triangle %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Triangle(Point(0, 0), Point(0, 1), Point(1, 0)), triangle);

    triangle %= Angle::radians(M_PI / 4);
    EXPECT_EQ(Triangle(Point(0, 0), Point(-sqrt(2) / 2, sqrt(2) / 2),
              Point(sqrt(2) / 2, sqrt(2) / 2)), triangle);
}

TEST(Triangle, RotateAround) {
    Triangle triangle(Point(0, 0), Point(0, 1), Point(1, 0));

    triangle.rotateAround(Point(0, 1), Angle::radians(0));
    EXPECT_EQ(Triangle(Point(0, 0), Point(0, 1), Point(1, 0)), triangle);

    triangle.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Triangle(Point(1, 1), Point(0, 1), Point(1, 2)), triangle);

    triangle.rotateAround(Point(0, 1), Angle::radians(M_PI));
    EXPECT_EQ(Triangle(Point(-1, 1), Point(0, 1), Point(-1, 0)), triangle);

    triangle.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Triangle(Point(0, 0), Point(0, 1), Point(1, 0)), triangle);
}

TEST(Triangle, A) {
    EXPECT_EQ(Point(0, 0), Triangle(Point(0, 0), Point(0, 1), Point(1, 0)).a());
}

TEST(Triangle, B) {
    EXPECT_EQ(Point(0, 1), Triangle(Point(0, 0), Point(0, 1), Point(1, 0)).b());
}

TEST(Triangle, C) {
    EXPECT_EQ(Point(1, 0), Triangle(Point(0, 0), Point(0, 1), Point(1, 0)).c());
}

TEST(Triangle, Orientation) {
    EXPECT_EQ(-1, Triangle(Point(0, 0), Point(0, 1), Point(1, 0)).orientation());
    EXPECT_EQ(0, Triangle(Point(0, 0), Point(1, 1), Point(2, 2)).orientation());
    EXPECT_EQ(0, Triangle(Point(0, 0), Point(1, 1), Point(1, 1)).orientation());
    EXPECT_EQ(0, Triangle(Point(1, 1), Point(1, 1), Point(1, 1)).orientation());
    EXPECT_EQ(1, Triangle(Point(0, 0), Point(1, 0), Point(0, 1)).orientation());
}

TEST(Triangle, Area) {
    EXPECT_EQ(0, Triangle(Point(0, 0), Point(1, 1), Point(2, 2)).area());
    EXPECT_EQ(0, Triangle(Point(0, 0), Point(1, 1), Point(1, 1)).area());
    EXPECT_EQ(0, Triangle(Point(1, 1), Point(1, 1), Point(1, 1)).area());
    EXPECT_EQ(0.5, Triangle(Point(0, 0), Point(0, 1), Point(1, 0)).area());
    EXPECT_EQ(1, Triangle(Point(0, 0), Point(1, 1), Point(2, 0)).area());
}

// ::: Polygon :::

TEST(Polygon, SetOfVerticesConstructor) {
    std::set<Point> vertexSet;
    vertexSet.insert(Point(0, 1));
    vertexSet.insert(Point(1, 1));
    vertexSet.insert(Point(1, 0));
    vertexSet.insert(Point(0, 0));
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 0));
    vertices.push_back(Point(1, 0));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(0, 1));
    Polygon polygon(vertexSet);
    EXPECT_EQ(vertices, polygon.vertices());

    EXPECT_ANY_THROW(Polygon(std::set<Point>()));
}

TEST(Polygon, CopyConstructor) {
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), Polygon(Polygon::square(Point(0, 0), 1)));
}

TEST(Polygon, CopyStructConstructor) {
    CGPoint cglowerleft = point_new(0, 0);
    CGPolygon cgpolygon = polygon_new_square(cglowerleft, 1);
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), Polygon(cgpolygon));
    point_release(cglowerleft);
    polygon_release(cgpolygon);
}

TEST(Polygon, TriangleConstructor) {
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 0));
    vertices.push_back(Point(1, 0));
    vertices.push_back(Point(0, 1));
    Polygon polygon = Polygon::triangle(Point(0, 0), Point(0, 1), Point(1, 0));
    EXPECT_EQ(vertices, polygon.vertices());

    EXPECT_ANY_THROW(Polygon::triangle(Point(0, 0), Point(1, 0), Point(2, 0)));
    EXPECT_ANY_THROW(Polygon::triangle(Point(0, 0), Point(1, 0), Point(1, 0)));
    EXPECT_ANY_THROW(Polygon::triangle(Point(0, 0), Point(0, 0), Point(0, 0)));
}

TEST(Polygon, RectangleConstructor) {
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 0));
    vertices.push_back(Point(2, 0));
    vertices.push_back(Point(2, 1));
    vertices.push_back(Point(0, 1));
    Polygon polygon = Polygon::rectangle(Point(0, 0), 2, 1);
    EXPECT_EQ(vertices, polygon.vertices());

    EXPECT_ANY_THROW(Polygon::rectangle(Point(0, 0), 0, 1));
    EXPECT_ANY_THROW(Polygon::rectangle(Point(0, 0), 1, 0));
}

TEST(Polygon, SquareConstructor) {
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 0));
    vertices.push_back(Point(1, 0));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(0, 1));
    Polygon polygon = Polygon::square(Point(0, 0), 1);
    EXPECT_EQ(vertices, polygon.vertices());

    EXPECT_ANY_THROW(Polygon::square(Point(0, 0), 0));
}

TEST(Polygon, CircleConstructor) {
    std::vector<Point> vertices;
    vertices.push_back(Point(1, 0));
    vertices.push_back(Point(2, 1));
    vertices.push_back(Point(1, 2));
    vertices.push_back(Point(0, 1));
    Polygon polygon = Polygon::circle(Point(1, 1), 1, 4);
    EXPECT_EQ(vertices, polygon.vertices());

    EXPECT_ANY_THROW(Polygon::circle(Point(1, 1), -1, 4));
    EXPECT_ANY_THROW(Polygon::circle(Point(1, 1), 0, 4));
    EXPECT_ANY_THROW(Polygon::circle(Point(1, 1), 1, 3));
}

TEST(Polygon, Destructor) {
    delete (new Polygon(Polygon::square(Point(0, 0), 1)));
}

TEST(Polygon, AssignmentOperator) {
    Polygon polygon = Polygon::square(Point(0, 0), 1);
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);
}

TEST(Polygon, EqualsComparisonOperator) {
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), Polygon::square(Point(0, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(0, 0), 1) == Polygon::square(Point(0, 0), 2));
    EXPECT_FALSE(Polygon::square(Point(0, 0), 1) == Polygon::square(Point(0, 1), 1));
    EXPECT_FALSE(Polygon::square(Point(0, 0), 1) == Polygon::square(Point(1, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(0, 0), 1) == Polygon::square(Point(1, 1), 1));
}

TEST(Polygon, LowerThanComparisonOperator) {
    EXPECT_FALSE(Polygon::square(Point(0, 0), 1) < Polygon::square(Point(0, 0), 1));
    EXPECT_TRUE(Polygon::square(Point(0, 0), 1) < Polygon::square(Point(0, 1), 1));
    EXPECT_TRUE(Polygon::square(Point(0, 0), 1) < Polygon::square(Point(1, 0), 1));
    EXPECT_TRUE(Polygon::square(Point(0, 0), 1) < Polygon::square(Point(1, 1), 1));

    EXPECT_FALSE(Polygon::square(Point(0, 1), 1) < Polygon::square(Point(0, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(0, 1), 1) < Polygon::square(Point(0, 1), 1));
    EXPECT_TRUE(Polygon::square(Point(0, 1), 1) < Polygon::square(Point(1, 0), 1));
    EXPECT_TRUE(Polygon::square(Point(0, 1), 1) < Polygon::square(Point(1, 1), 1));

    EXPECT_FALSE(Polygon::square(Point(1, 0), 1) < Polygon::square(Point(0, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(1, 0), 1) < Polygon::square(Point(0, 1), 1));
    EXPECT_FALSE(Polygon::square(Point(1, 0), 1) < Polygon::square(Point(1, 0), 1));
    EXPECT_TRUE(Polygon::square(Point(1, 0), 1) < Polygon::square(Point(1, 1), 1));

    EXPECT_FALSE(Polygon::square(Point(1, 1), 1) < Polygon::square(Point(0, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(1, 1), 1) < Polygon::square(Point(0, 1), 1));
    EXPECT_FALSE(Polygon::square(Point(1, 1), 1) < Polygon::square(Point(1, 0), 1));
    EXPECT_FALSE(Polygon::square(Point(1, 1), 1) < Polygon::square(Point(1, 1), 1));
}

TEST(Polygon, VectorSumOperator) {
    Polygon polygon = Polygon::square(Point(0, 0), 1);
    polygon += Vector(1, 2);
    EXPECT_EQ(Polygon::square(Point(1, 2), 1), polygon);
}

TEST(Polygon, VectorSubtractOperator) {
    Polygon polygon = Polygon::square(Point(1, 2), 1);
    polygon -= Vector(1, 2);
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);
}

TEST(Polygon, RotationOperator) {
    Polygon polygon = Polygon::square(Point(0, 0), 1);

    polygon %= Angle::radians(0);
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);

    polygon %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Polygon::square(Point(-1, 0), 1), polygon);

    polygon %= Angle::radians(M_PI);
    EXPECT_EQ(Polygon::square(Point(0, -1), 1), polygon);

    polygon %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);
}

TEST(Polygon, RotateAround) {
    Polygon polygon = Polygon::square(Point(0, 0), 1);

    polygon.rotateAround(Point(0, 1), Angle::radians(0));
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);

    polygon.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Polygon::square(Point(0, 1), 1), polygon);

    polygon.rotateAround(Point(0, 1), Angle::radians(M_PI));
    EXPECT_EQ(Polygon::square(Point(-1, 0), 1), polygon);

    polygon.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), polygon);
}

TEST(Polygon, IsInContactWithPolygon) {
    EXPECT_FALSE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(0, 0), 2))
    );
    EXPECT_FALSE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(1, 0), 2))
    );
    EXPECT_FALSE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(3, 0), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(2, 0), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(2, 2), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(0, 2), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(-2, 2), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(-2, 0), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(-2, -2), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(0, -2), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isInContactWith(Polygon::square(Point(2, -2), 2))
    );
}

TEST(Polygon, PointOfContactWithPolygon) {
    Point *poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(2, 0), 1));
    EXPECT_EQ(NULL, poc);

    poc =Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(0.5, 0), 1));
    EXPECT_EQ(NULL, poc);

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(1, 0), 1));
    EXPECT_EQ(Point(1, 0.5), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(1, 1), 1));
    EXPECT_EQ(Point(1, 1), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(0, 1), 1));
    EXPECT_EQ(Point(0.5, 1), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(-1, 1), 1));
    EXPECT_EQ(Point(0, 1), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(-1, 0), 1));
    EXPECT_EQ(Point(0, 0.5), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(0, -1), 1));
    EXPECT_EQ(Point(0.5, 0), *poc);
    delete poc;

    poc = Polygon::square(Point(0, 0), 1).pointOfContactWith(Polygon::square(Point(1, -1), 1));
    EXPECT_EQ(Point(1, 0), *poc);
    delete poc;
}

TEST(Polygon, IsCollidingWithPolygon) {
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isCollidingWith(Polygon::square(Point(0, 0), 2))
    );
    EXPECT_TRUE(
        Polygon::square(Point(0, 0), 2).isCollidingWith(Polygon::square(Point(1, 0), 2))
    );
    EXPECT_FALSE(
        Polygon::square(Point(0, 0), 2).isCollidingWith(Polygon::square(Point(2, 0), 2))
    );
    EXPECT_FALSE(
        Polygon::square(Point(0, 0), 2).isCollidingWith(Polygon::square(Point(3, 0), 2))
    );
}

TEST(Polygon, MinimumTranslationVectorFromPolygon) {
    Polygon poly0 = Polygon::square(Point(0, 0), 2);
    Polygon poly1 = Polygon::square(Point(1, 0), 2);
    Polygon poly2 = Polygon::square(Point(2, 0), 2);
    Polygon poly3 = Polygon::square(Point(3, 0), 2);

    EXPECT_ANY_THROW(poly0.minimumTranslationVectorFrom(poly1, Vector(0, 0)));

    EXPECT_EQ(Vector(5, 0), poly0.minimumTranslationVectorFrom(poly3, Vector(1, 0)));
    EXPECT_EQ(Vector(0, 0), poly0.minimumTranslationVectorFrom(poly3, Vector(-1, 0)));
    EXPECT_EQ(Vector(0, 0), poly0.minimumTranslationVectorFrom(poly3, Vector(0, 1)));
    EXPECT_EQ(Vector(0, 0), poly0.minimumTranslationVectorFrom(poly3, Vector(0, -1)));

    EXPECT_EQ(Vector(4, 0), poly0.minimumTranslationVectorFrom(poly2, Vector(1, 0)));
    EXPECT_EQ(Vector(0, 0), poly0.minimumTranslationVectorFrom(poly2, Vector(-1, 0)));
    EXPECT_EQ(Vector(0, 2), poly0.minimumTranslationVectorFrom(poly2, Vector(0, 1)));
    EXPECT_EQ(Vector(0, -2), poly0.minimumTranslationVectorFrom(poly2, Vector(0, -1)));

    EXPECT_EQ(Vector(3, 0), poly0.minimumTranslationVectorFrom(poly1, Vector(1, 0)));
    EXPECT_EQ(Vector(-1, 0), poly0.minimumTranslationVectorFrom(poly1, Vector(-1, 0)));
    EXPECT_EQ(Vector(0, 2), poly0.minimumTranslationVectorFrom(poly1, Vector(0, 1)));
    EXPECT_EQ(Vector(0, -2), poly0.minimumTranslationVectorFrom(poly1, Vector(0, -1)));
}

TEST(Polygon, Vertices) {
    std::vector<Point> vertices;
    vertices.push_back(Point(0, 0));
    vertices.push_back(Point(1, 0));
    vertices.push_back(Point(1, 1));
    vertices.push_back(Point(0, 1));
    EXPECT_EQ(vertices, Polygon::square(Point(0, 0), 1).vertices());
}

TEST(Polygon, Edges) {
    std::set<Segment> edges;
    edges.insert(Segment(Point(0, 0), Point(1, 0)));
    edges.insert(Segment(Point(1, 0), Point(1, 1)));
    edges.insert(Segment(Point(1, 1), Point(0, 1)));
    edges.insert(Segment(Point(0, 1), Point(0, 0)));
    EXPECT_EQ(edges, Polygon::square(Point(0, 0), 1).edges());
}

TEST(Polygon, Area) {
    EXPECT_DOUBLE_EQ(3, Polygon::triangle(Point(0, 0), Point(2, 0), Point(2, 3)).area());
    EXPECT_DOUBLE_EQ(6, Polygon::rectangle(Point(0, 0), 2, 3).area());
    EXPECT_DOUBLE_EQ(1, Polygon::square(Point(0, 0), 1).area());
}

// ::: Circle :::

TEST(Circle, CenterAndRadiusConstructor) {
    Circle circle(Point(1, 2), 3);
    EXPECT_EQ(Point(1, 2), circle.center());
    EXPECT_DOUBLE_EQ(3, circle.radius());

    EXPECT_ANY_THROW(Circle(Point(1, 1), 0));
    EXPECT_ANY_THROW(Circle(Point(1, 1), -1));
}

TEST(Circle, CopyConstructor) {
    EXPECT_EQ(Circle(Point(1, 2), 3), Circle(Circle(Point(1, 2), 3)));
}

TEST(Circle, CopyStructConstructor) {
    CGPoint cgcenter = point_new(1, 2);
    CGCircle cgcircle = circle_new(cgcenter, 3);
    EXPECT_EQ(Circle(Point(1, 2), 3), Circle(cgcircle));
    point_release(cgcenter);
    circle_release(cgcircle);
}

TEST(Circle, Destructor) {
    delete (new Circle(Point(1, 2), 3));
}

TEST(Circle, AssignmentOperator) {
    Circle circle = Circle(Point(1, 2), 3);
    EXPECT_EQ(Circle(Point(1, 2), 3), circle);
}

TEST(Circle, ComparisonOperator) {
    EXPECT_EQ(Circle(Point(1, 1), 1), Circle(Point(1, 1), 1));
    EXPECT_FALSE(Circle(Point(1, 1), 1) == Circle(Point(1, 0), 1));
    EXPECT_FALSE(Circle(Point(1, 1), 1) == Circle(Point(0, 1), 1));
    EXPECT_FALSE(Circle(Point(1, 1), 1) == Circle(Point(1, 1), 2));
}

TEST(Circle, VectorSumOperator) {
    Circle circle(Point(1, 2), 3);
    circle += Vector(1, 2);
    EXPECT_EQ(Circle(Point(2, 4), 3), circle);
}

TEST(Circle, VectorSubtractOperator) {
    Circle circle(Point(1, 2), 3);
    circle -= Vector(1, 2);
    EXPECT_EQ(Circle(Point(0, 0), 3), circle);
}

TEST(Circle, RotationOperator) {
    Circle circle(Point(1, 1), 1);

    circle %= Angle::radians(0);
    EXPECT_EQ(Circle(Point(1, 1), 1), circle);

    circle %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Circle(Point(-1, 1), 1), circle);

    circle %= Angle::radians(M_PI);
    EXPECT_EQ(Circle(Point(1, -1), 1), circle);

    circle %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Circle(Point(1, 1), 1), circle);
}

TEST(Circle, RotateAround) {
    Circle circle(Point(1, 1), 1);

    circle.rotateAround(Point(0, 1), Angle::radians(0));
    EXPECT_EQ(Circle(Point(1, 1), 1), circle);

    circle.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Circle(Point(0, 2), 1), circle);

    circle.rotateAround(Point(0, 1), Angle::radians(M_PI));
    EXPECT_EQ(Circle(Point(0, 0), 1), circle);

    circle.rotateAround(Point(0, 1), Angle::radians(M_PI / 2));
    EXPECT_EQ(Circle(Point(1, 1), 1), circle);
}

TEST(Circle, Center) {
    EXPECT_EQ(Point(1, 2), Circle(Point(1, 2), 3).center());
}

TEST(Circle, Radius) {
    EXPECT_DOUBLE_EQ(3, Circle(Point(1, 2), 3).radius());
}

TEST(Circle, Area) {
    EXPECT_DOUBLE_EQ(M_PI, Circle(Point(1, 1), 1).area());
    EXPECT_DOUBLE_EQ(M_PI, Circle(Point(-1, 1), 1).area());
    EXPECT_DOUBLE_EQ(M_PI, Circle(Point(1, -1), 1).area());
    EXPECT_DOUBLE_EQ(M_PI, Circle(Point(-1, -1), 1).area());
    EXPECT_DOUBLE_EQ(M_PI * 4, Circle(Point(1, 1), 2).area());
    EXPECT_DOUBLE_EQ(M_PI * 4, Circle(Point(-1, 1), 2).area());
    EXPECT_DOUBLE_EQ(M_PI * 4, Circle(Point(1, -1), 2).area());
    EXPECT_DOUBLE_EQ(M_PI * 4, Circle(Point(-1, -1), 2).area());
}

