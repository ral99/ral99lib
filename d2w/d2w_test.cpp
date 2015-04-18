#include <math.h>
#include <utility>

#include "d2w/d2w.h"
#include "gtest/gtest.h"

using namespace D2W;
using namespace CG;

class D2WTest : public ::testing::Test {
    protected:
        World *world;

        virtual void SetUp() {
            world = new World(Point(0, 0), Angle::radians(0), 0, 0, 1);
        }

        virtual void TearDown() {
            delete world;
        }
};

// ::: Body :::

TEST_F(D2WTest, BodyDestructor) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    delete body;
}

TEST_F(D2WTest, BodyUnarySumOperator) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    *body += Vector(1, 2);
    EXPECT_EQ(Point(1, 2), body->center());
    EXPECT_EQ(Polygon::square(Point(1, 2), 1), body->polygon("square"));
}

TEST_F(D2WTest, BodyUnarySubtractOperator) {
    Body *body = world->createBody(Point(1, 2), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    *body -= Vector(1, 2);
    EXPECT_EQ(Point(0, 0), body->center());
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), body->polygon("square"));
}

TEST_F(D2WTest, BodyUnaryRotationOperator) {
    Body *body = world->createBody(Point(1, 1), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(-1, -1), 1));

    *body %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Angle::radians(M_PI / 2), body->rotation());
    EXPECT_EQ(Point(1, 1), body->center());
    EXPECT_EQ(Polygon::square(Point(1, 0), 1), body->polygon("square"));

    *body %= Angle::radians(M_PI / 2);
    EXPECT_EQ(Angle::radians(M_PI), body->rotation());
    EXPECT_EQ(Point(1, 1), body->center());
    EXPECT_EQ(Polygon::square(Point(1, 1), 1), body->polygon("square"));
}

TEST_F(D2WTest, BodySetCenter) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body->setCenter(Point(1, 2));
    EXPECT_EQ(Point(1, 2), body->center());
    EXPECT_EQ(Polygon::square(Point(1, 2), 1), body->polygon("square"));
}

TEST_F(D2WTest, BodyCenter) {
    Body *body = world->createBody(Point(1, 2), Angle::radians(0), true);
    EXPECT_EQ(Point(1, 2), body->center());
}

TEST_F(D2WTest, BodyCenterOnWindowCoordinates) {
    world->setWindowCenter(Point(2, 1));
    world->setWindowWidth(2);
    world->setWindowHeight(4);
    world->setWindowRotation(Angle::radians(M_PI / 2));
    Body *body = world->createBody(Point(1, 2), Angle::radians(0), true);
    EXPECT_EQ(Point(2, 3), body->centerOnWindowCoordinates());
}

TEST_F(D2WTest, BodySetRotation) {
    Body *body = world->createBody(Point(1, 1), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(-1, -1), 1));
    body->setRotation(Angle::radians(M_PI / 2));
    EXPECT_EQ(Angle::radians(M_PI / 2), body->rotation());
    EXPECT_EQ(Polygon::square(Point(1, 0), 1), body->polygon("square"));
}

TEST_F(D2WTest, BodyRotation) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(M_PI), true);
    EXPECT_EQ(Angle::radians(M_PI), body->rotation());
}

TEST_F(D2WTest, BodyRotationOnWindowCoordinates) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(M_PI / 4), true);
    world->setWindowRotation(Angle::radians(M_PI));
    EXPECT_EQ(Angle::radians(-3 * M_PI / 4), body->rotationOnWindowCoordinates());
}

TEST_F(D2WTest, BodySetIsDynamic) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->setIsDynamic(false);
    EXPECT_FALSE(body->isDynamic());
    body->setIsDynamic(true);
    EXPECT_TRUE(body->isDynamic());
}

TEST_F(D2WTest, BodyIsDynamic) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->setIsDynamic(false);
    EXPECT_FALSE(body->isDynamic());
    body->setIsDynamic(true);
    EXPECT_TRUE(body->isDynamic());
}

TEST_F(D2WTest, BodyAddPolygon) {
    Body *body = world->createBody(Point(1, 2), Angle::radians(M_PI / 2), true);

    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    EXPECT_EQ(Polygon::square(Point(0, 2), 1), body->polygon("square"));

    body->addPolygon("square", Polygon::square(Point(0, 0), 2));
    EXPECT_EQ(Polygon::square(Point(-1, 2), 2), body->polygon("square"));
}

TEST_F(D2WTest, BodyRemovePolygon) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));

    body->removePolygon("rectangle");
    EXPECT_EQ(1, body->polygons().size());

    body->removePolygon("square");
    EXPECT_EQ(0, body->polygons().size());

    EXPECT_ANY_THROW(body->removePolygon("rectangle"));
    EXPECT_ANY_THROW(body->removePolygon("square"));
}

TEST_F(D2WTest, BodyClearPolygons) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body->clearPolygons();
    EXPECT_EQ(0, body->polygons().size());
}

TEST_F(D2WTest, BodyPolygon) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    EXPECT_EQ(Polygon::rectangle(Point(0, 0), 2, 1), body->polygon("rectangle"));
    EXPECT_EQ(Polygon::square(Point(0, 0), 1), body->polygon("square"));
    EXPECT_ANY_THROW(body->polygon("triangle"));
}

TEST_F(D2WTest, BodyPolygonOnWindowCoordinates) {
    world->setWindowCenter(Point(2, 1));
    world->setWindowWidth(4);
    world->setWindowHeight(2);
    world->setWindowRotation(Angle::radians(M_PI));
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(2, 0), 1));
    EXPECT_EQ(Polygon::rectangle(Point(2, 1), 2, 1), body->polygonOnWindowCoordinates("rectangle"));
    EXPECT_EQ(Polygon::square(Point(1, 1), 1), body->polygonOnWindowCoordinates("square"));
    EXPECT_ANY_THROW(body->polygonOnWindowCoordinates("triangle"));
}

TEST_F(D2WTest, BodyPolygons) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(2, 0), 1));
    std::set<Polygon> polygons = body->polygons();
    EXPECT_EQ(2, polygons.size());
    EXPECT_NE(polygons.end(), polygons.find(Polygon::rectangle(Point(0, 0), 2, 1)));
    EXPECT_NE(polygons.end(), polygons.find(Polygon::square(Point(2, 0), 1)));
}

TEST_F(D2WTest, BodyPolygonsOnWindowCoordinates) {
    world->setWindowWidth(2);
    world->setWindowHeight(4);
    world->setWindowCenter(Point(2, 1));
    world->setWindowRotation(Angle::radians(M_PI / 2));
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    body->addPolygon("square", Polygon::square(Point(2, 0), 1));
    std::set<Polygon> polygons = body->polygonsOnWindowCoordinates();
    EXPECT_EQ(2, polygons.size());
    EXPECT_NE(polygons.end(), polygons.find(Polygon::rectangle(Point(0, 2), 1, 2)));
    EXPECT_NE(polygons.end(), polygons.find(Polygon::square(Point(0, 1), 1)));
}

TEST_F(D2WTest, BodyAddTag) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addTag("tag");
    EXPECT_TRUE(body->hasTag("tag"));
}

TEST_F(D2WTest, BodyRemoveTag) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addTag("tag");
    body->removeTag("tag");
    EXPECT_FALSE(body->hasTag("tag"));
    EXPECT_ANY_THROW(body->removeTag("tag"));
}

TEST_F(D2WTest, BodyClearTags) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addTag("tag");
    body->clearTags();
    EXPECT_FALSE(body->hasTag("tag"));
}

TEST_F(D2WTest, BodyHasTag) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addTag("tag");
    EXPECT_TRUE(body->hasTag("tag"));
    EXPECT_FALSE(body->hasTag("gat"));
}

TEST_F(D2WTest, BodyIsOnWindow) {
    world->setWindowCenter(Point(sqrt(2) / 2, sqrt(2) / 2));
    world->setWindowRotation(Angle::radians(M_PI / 4));
    world->setWindowWidth(1);
    world->setWindowHeight(1);
    world->setBodyIndexRange(1);

    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 0.1));
    EXPECT_FALSE(body1->isOnWindow());

    Body *body2 = world->createBody(Point(sqrt(2) - 0.1, 0), Angle::radians(0), true);
    body2->addPolygon("square", Polygon::square(Point(0, 0), 0.1));
    EXPECT_FALSE(body2->isOnWindow());

    Body *body3 = world->createBody(Point(0, sqrt(2) - 0.1), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 0.1));
    EXPECT_FALSE(body3->isOnWindow());

    Body *body4 = world->createBody(Point(sqrt(2) - 0.1, sqrt(2) - 0.1), Angle::radians(0), true);
    body4->addPolygon("square", Polygon::square(Point(0, 0), 0.1));
    EXPECT_FALSE(body4->isOnWindow());

    Body *body5 = world->createBody(Point(sqrt(2) / 2, sqrt(2) / 2), Angle::radians(0), true);
    body5->addPolygon("square", Polygon::square(Point(0, 0), 0.1));
    EXPECT_TRUE(body5->isOnWindow());
}

TEST_F(D2WTest, BodyIndexQuadrants) {
    world->setBodyIndexRange(1);

    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body->addPolygon("rectangle", Polygon::rectangle(Point(4, 0), 2, 1));
    std::vector<std::pair<int, int>> indexQuadrants = body->indexQuadrants();
    EXPECT_EQ(10, indexQuadrants.size());
    EXPECT_EQ(std::make_pair(4, 0), indexQuadrants[0]);
    EXPECT_EQ(std::make_pair(4, 1), indexQuadrants[1]);
    EXPECT_EQ(std::make_pair(5, 0), indexQuadrants[2]);
    EXPECT_EQ(std::make_pair(5, 1), indexQuadrants[3]);
    EXPECT_EQ(std::make_pair(6, 0), indexQuadrants[4]);
    EXPECT_EQ(std::make_pair(6, 1), indexQuadrants[5]);
    EXPECT_EQ(std::make_pair(0, 0), indexQuadrants[6]);
    EXPECT_EQ(std::make_pair(0, 1), indexQuadrants[7]);
    EXPECT_EQ(std::make_pair(1, 0), indexQuadrants[8]);
    EXPECT_EQ(std::make_pair(1, 1), indexQuadrants[9]);

    Body *emptyBody = world->createBody(Point(0, 0), Angle::radians(0), true);
    EXPECT_EQ(0, emptyBody->indexQuadrants().size());
}

TEST_F(D2WTest, BodyDistanceTo) {
    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("circle", Polygon::square(Point(0, 0), 1));
    Body *body2 = world->createBody(Point(1, 0), Angle::radians(0), true);
    body2->addPolygon("circle", Polygon::square(Point(0, 0), 1));
    Body *body3 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body3->addPolygon("circle", Polygon::square(Point(0, 0), 1));
    EXPECT_EQ(0, body1->distanceTo(*body1));
    EXPECT_EQ(1, body1->distanceTo(*body2));
    EXPECT_EQ(sqrt(2), body1->distanceTo(*body3));
    EXPECT_EQ(1, body2->distanceTo(*body1));
    EXPECT_EQ(0, body2->distanceTo(*body2));
    EXPECT_EQ(1, body2->distanceTo(*body3));
    EXPECT_EQ(sqrt(2), body3->distanceTo(*body1));
    EXPECT_EQ(1, body3->distanceTo(*body2));
    EXPECT_EQ(0, body3->distanceTo(*body3));
}

TEST_F(D2WTest, BodyNeighbourBodies) {
    Body *bodyGrid[6][6];
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            bodyGrid[i][j] = world->createBody(Point(i, j), Angle::radians(0), true);
            bodyGrid[i][j]->addPolygon("square", Polygon::square(Point(0, 0), 1));
        }
        bodyGrid[0][i]->setIsDynamic(false);
        bodyGrid[0][i]->addTag("firstColumn");
    }
    bodyGrid[0][0]->addTag("zero");

    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<Body*> bodies = body1->neighbourBodies();
    EXPECT_EQ(9, bodies.size());
    for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
            EXPECT_NE(bodies.end(), bodies.find(bodyGrid[i][j]));
    delete body1;

    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodies = body2->neighbourBodies();
    EXPECT_EQ(20, bodies.size());
    for (int i = 0; i <= 3; i++)
        for (int j = 0; j <= 4; j++)
            EXPECT_NE(bodies.end(), bodies.find(bodyGrid[i][j]));
    delete body2;
}

TEST_F(D2WTest, BodyNeighbourDynamicBodies) {
    Body *bodyGrid[6][6];
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            bodyGrid[i][j] = world->createBody(Point(i, j), Angle::radians(0), true);
            bodyGrid[i][j]->addPolygon("square", Polygon::square(Point(0, 0), 1));
        }
        bodyGrid[0][i]->setIsDynamic(false);
        bodyGrid[0][i]->addTag("firstColumn");
    }
    bodyGrid[0][0]->addTag("zero");

    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<Body*> bodies = body1->neighbourDynamicBodies();
    EXPECT_EQ(6, bodies.size());
    for (int i = 1; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
            EXPECT_NE(bodies.end(), bodies.find(bodyGrid[i][j]));
    delete body1;

    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodies = body2->neighbourDynamicBodies();
    EXPECT_EQ(15, bodies.size());
    for (int i = 1; i <= 3; i++)
        for (int j = 0; j <= 4; j++)
            EXPECT_NE(bodies.end(), bodies.find(bodyGrid[i][j]));
    delete body2;
}

TEST_F(D2WTest, BodyNeighbourTaggedBodies) {
    Body *bodyGrid[6][6];
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            bodyGrid[i][j] = world->createBody(Point(i, j), Angle::radians(0), true);
            bodyGrid[i][j]->addPolygon("square", Polygon::square(Point(0, 0), 1));
        }
        bodyGrid[0][i]->setIsDynamic(false);
        bodyGrid[0][i]->addTag("firstColumn");
    }
    bodyGrid[0][0]->addTag("zero");

    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<Body*> bodies = body1->neighbourTaggedBodies("firstColumn"); 
    EXPECT_EQ(3, bodies.size());
    for (int i = 0; i <= 2; i++)
        EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][i]));
    delete body1;

    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodies = body2->neighbourTaggedBodies("firstColumn");
    EXPECT_EQ(5, bodies.size());
    for (int i = 0; i <= 4; i++)
        EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][i]));
    delete body2;

    Body *body3 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<std::string> tags;
    tags.insert("firstColumn");
    tags.insert("zero");
    bodies = body3->neighbourTaggedBodies(tags);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][0]));
    delete body3;
}

TEST_F(D2WTest, BodyNeighbourDynamicTaggedBodies) {
    Body *bodyGrid[6][6];
    for (int i = 0; i <= 5; i++) {
        for (int j = 0; j <= 5; j++) {
            bodyGrid[i][j] = world->createBody(Point(i, j), Angle::radians(0), false);
            bodyGrid[i][j]->addPolygon("square", Polygon::square(Point(0, 0), 1));
        }
        bodyGrid[0][i]->setIsDynamic(true);
        bodyGrid[0][i]->addTag("firstColumn");
    }
    bodyGrid[0][0]->addTag("zero");

    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<Body*> bodies = body1->neighbourDynamicTaggedBodies("zero");
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][0]));
    delete body1;

    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodies = body2->neighbourDynamicTaggedBodies("zero");
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][0]));
    delete body2;

    Body *body3 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    std::set<std::string> tags;
    tags.insert("firstColumn");
    tags.insert("zero");
    bodies = body3->neighbourDynamicTaggedBodies(tags);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyGrid[0][0]));
    delete body3;
}

TEST_F(D2WTest, BodyIsCollidingWithBody) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));

    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    EXPECT_TRUE(body->isCollidingWith(*bodyA));
    EXPECT_TRUE(body->isCollidingWith(*bodyA, 0));
    EXPECT_TRUE(body->isCollidingWith(*bodyA, 1));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyA));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyA, 0));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyA, 1));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyA));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyA, 0));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyA, 1));
    EXPECT_ANY_THROW(body->isCollidingWith("triangle", *bodyA));

    Body *bodyB = world->createBody(Point(0, 1), Angle::radians(0), false);
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    EXPECT_TRUE(body->isCollidingWith(*bodyB));
    EXPECT_FALSE(body->isCollidingWith(*bodyB, 0));
    EXPECT_TRUE(body->isCollidingWith(*bodyB, 1));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyB));
    EXPECT_FALSE(body->isCollidingWith("rectangle", *bodyB, 0));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyB, 1));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyB));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyB, 0));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyB, 1));
    EXPECT_ANY_THROW(body->isCollidingWith("triangle", *bodyB));

    Body *bodyC = world->createBody(Point(1, 0), Angle::radians(0), true);
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    EXPECT_FALSE(body->isCollidingWith(*bodyC));
    EXPECT_FALSE(body->isCollidingWith(*bodyC, 0));
    EXPECT_FALSE(body->isCollidingWith(*bodyC, 1));
    EXPECT_FALSE(body->isCollidingWith("rectangle", *bodyC));
    EXPECT_FALSE(body->isCollidingWith("rectangle", *bodyC, 0));
    EXPECT_FALSE(body->isCollidingWith("rectangle", *bodyC, 1));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyC));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyC, 0));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyC, 1));
    EXPECT_ANY_THROW(body->isCollidingWith("triangle", *bodyC));

    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), false);
    bodyD->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    EXPECT_TRUE(body->isCollidingWith(*bodyD));
    EXPECT_TRUE(body->isCollidingWith("rectangle", *bodyD));
    EXPECT_FALSE(body->isCollidingWith("square", *bodyD));
    EXPECT_ANY_THROW(body->isCollidingWith("triangle", *bodyD));

    Body *bodyE = world->createBody(Point(0, 0), Angle::radians(0), false);
    bodyE->addPolygon("rectangle", Polygon::rectangle(Point(5, 0), 2, 1));
    EXPECT_TRUE(body->isCollidingWith(*bodyE));
    EXPECT_FALSE(body->isCollidingWith("rectangle", *bodyE));
    EXPECT_TRUE(body->isCollidingWith("square", *bodyE));
    EXPECT_ANY_THROW(body->isCollidingWith("triangle", *bodyE));
}

TEST_F(D2WTest, BodyCollidingDynamicBodies) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));
    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), false);
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(0, 1), 1, 2));
    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyD->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    Body *bodyE = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyE->addPolygon("rectangle", Polygon::rectangle(Point(5, 0), 1, 2));
    Body *bodyF = world->createBody(Point(0, 1), Angle::radians(0), true);
    bodyF->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));

    std::set<Body*> bodies = body->collidingDynamicBodies();
    EXPECT_EQ(4, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyE));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicBodies(0);
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyE));

    bodies = body->collidingDynamicBodies("rectangle");
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicBodies("rectangle", 0);
    EXPECT_EQ(2, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));

    bodies = body->collidingDynamicBodies("square");
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyE));

    EXPECT_ANY_THROW(body->collidingDynamicBodies("triangle"));
    EXPECT_ANY_THROW(body->collidingDynamicBodies("triangle", 0));
}

TEST_F(D2WTest, BodyCollidingDynamicTaggedBodies) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));
    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), false);
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodyA->addTag("vowel");
    bodyA->addTag("a");
    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(0, 1), 1, 2));
    bodyB->addTag("consonant");
    bodyB->addTag("b");
    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    bodyC->addTag("consonant");
    bodyC->addTag("c");
    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyD->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    bodyD->addTag("consonant");
    bodyD->addTag("d");
    Body *bodyE = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyE->addPolygon("rectangle", Polygon::rectangle(Point(5, 0), 1, 2));
    bodyE->addTag("vowel");
    bodyE->addTag("e");
    Body *bodyF = world->createBody(Point(0, 1), Angle::radians(0), true);
    bodyF->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    bodyF->addTag("consonant");
    bodyF->addTag("f");

    std::set<std::string> tags;
    tags.insert("consonant");
    tags.insert("vowel");

    std::set<std::string> consonantF;
    consonantF.insert("consonant");
    consonantF.insert("f");

    std::set<Body*> bodies = body->collidingDynamicTaggedBodies("consonant");
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("consonant", 0);
    EXPECT_EQ(2, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));

    bodies = body->collidingDynamicTaggedBodies("consonant", 1);
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("vowel");
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyE));

    bodies = body->collidingDynamicTaggedBodies(tags);
    EXPECT_EQ(0, bodies.size());

    bodies = body->collidingDynamicTaggedBodies(consonantF);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies(consonantF, 0);
    EXPECT_EQ(0, bodies.size());

    bodies = body->collidingDynamicTaggedBodies(consonantF, 1);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("rectangle", "consonant");
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("rectangle", "consonant", 0);
    EXPECT_EQ(2, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));

    bodies = body->collidingDynamicTaggedBodies("rectangle", "consonant", 1);
    EXPECT_EQ(3, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyD));
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("rectangle", "vowel");
    EXPECT_EQ(0, bodies.size());

    bodies = body->collidingDynamicTaggedBodies("square", "consonant");
    EXPECT_EQ(0, bodies.size());

    bodies = body->collidingDynamicTaggedBodies("square", "vowel");
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyE));

    bodies = body->collidingDynamicTaggedBodies("rectangle", tags);
    EXPECT_EQ(0, bodies.size());

    bodies = body->collidingDynamicTaggedBodies("rectangle", consonantF);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("rectangle", consonantF, 0);
    EXPECT_EQ(0, bodies.size());
    
    bodies = body->collidingDynamicTaggedBodies("rectangle", consonantF, 1);
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyF));

    bodies = body->collidingDynamicTaggedBodies("square", tags);
    EXPECT_EQ(0, bodies.size());

    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", "vowel"));
    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", "vowel", 0));
    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", "consonant"));
    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", "consonant", 0));
    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", tags));
    EXPECT_ANY_THROW(body->collidingDynamicTaggedBodies("triangle", tags, 0));
}

TEST_F(D2WTest, BodyCollisionWithBody) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));

    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("triangle", Polygon::triangle(Point(0, 1), Point(1, 0), Point(0, 0)));
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    std::set<std::pair<std::string, std::string>> collision = body->collisionWith(*bodyA);
    EXPECT_EQ(1, collision.size());
    EXPECT_NE(collision.end(), collision.find(std::make_pair("rectangle", "triangle")));
    std::set<std::string> polygonCollision = body->collisionWith("rectangle", *bodyA);
    EXPECT_EQ(1, polygonCollision.size());
    EXPECT_NE(polygonCollision.end(), polygonCollision.find("triangle"));
    polygonCollision = body->collisionWith("square", *bodyA);
    EXPECT_EQ(0, polygonCollision.size());
    EXPECT_ANY_THROW(body->collisionWith("triangle", *bodyA));

    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("triangle", Polygon::triangle(Point(5, 0), Point(5, 1), Point(6, 0)));
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    collision = body->collisionWith(*bodyB);
    EXPECT_EQ(1, collision.size());
    EXPECT_NE(collision.end(), collision.find(std::make_pair("square", "triangle")));
    polygonCollision = body->collisionWith("rectangle", *bodyB);
    EXPECT_EQ(0, polygonCollision.size());
    polygonCollision = body->collisionWith("square", *bodyB);
    EXPECT_EQ(1, polygonCollision.size());
    EXPECT_NE(polygonCollision.end(), polygonCollision.find("triangle"));
    EXPECT_ANY_THROW(body->collisionWith("triangle", *bodyB));

    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("triangle", Polygon::triangle(Point(4, 0), Point(4, 1), Point(5, 0)));
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    collision = body->collisionWith(*bodyC);
    EXPECT_EQ(0, collision.size());
    polygonCollision = body->collisionWith("rectangle", *bodyC);
    EXPECT_EQ(0, polygonCollision.size());
    polygonCollision = body->collisionWith("square", *bodyC);
    EXPECT_EQ(0, polygonCollision.size());
    EXPECT_ANY_THROW(body->collisionWith("triangle", *bodyC));

    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyD->addPolygon("triangle", Polygon::triangle(Point(5, 0), Point(5, 1), Point(6, 0)));
    bodyD->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 2, 1));
    collision = body->collisionWith(*bodyD);
    EXPECT_EQ(2, collision.size());
    EXPECT_NE(collision.end(), collision.find(std::make_pair("rectangle", "rectangle")));
    EXPECT_NE(collision.end(), collision.find(std::make_pair("square", "triangle")));
    polygonCollision = body->collisionWith("rectangle", *bodyD);
    EXPECT_EQ(1, polygonCollision.size());
    EXPECT_NE(polygonCollision.end(), polygonCollision.find("rectangle"));
    polygonCollision = body->collisionWith("square", *bodyD);
    EXPECT_EQ(1, polygonCollision.size());
    EXPECT_NE(polygonCollision.end(), polygonCollision.find("triangle"));
    EXPECT_ANY_THROW(body->collisionWith("triangle", *bodyD));
}

TEST_F(D2WTest, BodyIsInContactWithPolygon) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));

    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    EXPECT_FALSE(body->isInContactWith(*bodyA));
    EXPECT_FALSE(body->isInContactWith("rectangle", *bodyA));
    EXPECT_FALSE(body->isInContactWith("square", *bodyA));
    EXPECT_ANY_THROW(body->isInContactWith("triangle", *bodyA));

    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(2, 0), 2, 1));
    EXPECT_FALSE(body->isInContactWith(*bodyB));
    EXPECT_FALSE(body->isInContactWith("rectangle", *bodyB));
    EXPECT_FALSE(body->isInContactWith("square", *bodyB));
    EXPECT_ANY_THROW(body->isInContactWith("triangle", *bodyB));

    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 4, 1));
    EXPECT_TRUE(body->isInContactWith(*bodyC));
    EXPECT_TRUE(body->isInContactWith("rectangle", *bodyC));
    EXPECT_TRUE(body->isInContactWith("square", *bodyC));
    EXPECT_ANY_THROW(body->isInContactWith("triangle", *bodyC));

    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyD->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 5, 1));
    EXPECT_TRUE(body->isInContactWith(*bodyD));
    EXPECT_FALSE(body->isInContactWith("rectangle", *bodyD));
    EXPECT_TRUE(body->isInContactWith("square", *bodyD));
    EXPECT_ANY_THROW(body->isInContactWith("triangle", *bodyD));
}

TEST_F(D2WTest, BodyContactWithBody) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("rectangle", Polygon::rectangle(Point(0, 0), 1, 2));
    body->addPolygon("square", Polygon::square(Point(5, 0), 1));

    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("triangle", Polygon::triangle(Point(0, 1), Point(1, 0), Point(0, 0)));
    bodyA->addPolygon("rectangle", Polygon::rectangle(Point(1, 0), 1, 2));
    std::set<std::pair<std::string, std::string>> contact = body->contactWith(*bodyA);
    EXPECT_EQ(1, contact.size());
    EXPECT_NE(contact.end(), contact.find(std::make_pair("rectangle", "rectangle")));
    std::set<std::string> polygonContact = body->contactWith("rectangle", *bodyA);
    EXPECT_EQ(1, polygonContact.size());
    EXPECT_NE(polygonContact.end(), polygonContact.find("rectangle"));
    polygonContact = body->contactWith("square", *bodyA);
    EXPECT_EQ(0, polygonContact.size());
    EXPECT_ANY_THROW(body->contactWith("triangle", *bodyA));

    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("triangle", Polygon::triangle(Point(1, 0), Point(2, 0), Point(1, 1)));
    bodyB->addPolygon("rectangle", Polygon::rectangle(Point(3, 0), 2, 1));
    contact = body->contactWith(*bodyB);
    EXPECT_EQ(2, contact.size());
    EXPECT_NE(contact.end(), contact.find(std::make_pair("rectangle", "triangle")));
    EXPECT_NE(contact.end(), contact.find(std::make_pair("square", "rectangle")));
    polygonContact = body->contactWith("rectangle", *bodyB);
    EXPECT_EQ(1, polygonContact.size());
    EXPECT_NE(polygonContact.end(), polygonContact.find("triangle"));
    polygonContact = body->contactWith("square", *bodyB);
    EXPECT_EQ(1, polygonContact.size());
    EXPECT_NE(polygonContact.end(), polygonContact.find("rectangle"));
    EXPECT_ANY_THROW(body->contactWith("triangle", *bodyB));

    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("triangle", Polygon::triangle(Point(2, 0), Point(3, 0), Point(2, 1)));
    bodyC->addPolygon("rectangle", Polygon::rectangle(Point(3, 0), 1, 2));
    contact = body->contactWith(*bodyC);
    EXPECT_EQ(0, contact.size());
    polygonContact = body->contactWith("rectangle", *bodyC);
    EXPECT_EQ(0, polygonContact.size());
    polygonContact = body->contactWith("square", *bodyC);
    EXPECT_EQ(0, polygonContact.size());
    EXPECT_ANY_THROW(body->contactWith("triangle", *bodyC));
}

// ::: World :::

TEST(World, Destructor) {
    World *world = new World(Point(0, 0), Angle::radians(0), 1024, 768, 64);
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    delete world;
}

TEST_F(D2WTest, WorldUnarySumOperator) {
    world->setWindowCenter(Point(0, 0));
    world->operator+=(Vector(1, 2));
    EXPECT_EQ(Point(1, 2), world->windowCenter());
}

TEST_F(D2WTest, WorldUnarySubtractOperator) {
    world->setWindowCenter(Point(1, 2));
    world->operator-=(Vector(1, 2));
    EXPECT_EQ(Point(0, 0), world->windowCenter());
}

TEST_F(D2WTest, WorldUnaryRotationOperator) {
    world->setWindowRotation(Angle::radians(0));
    world->operator%=(Angle::radians(M_PI / 2));
    EXPECT_EQ(Angle::radians(M_PI / 2), world->windowRotation());
    world->operator%=(Angle::radians(M_PI / 2));
    EXPECT_EQ(Angle::radians(M_PI), world->windowRotation());
    world->operator%=(Angle::radians(M_PI / 2));
    EXPECT_EQ(Angle::radians(3 * M_PI / 2), world->windowRotation());
    world->operator%=(Angle::radians(M_PI / 2));
    EXPECT_EQ(Angle::radians(0), world->windowRotation());
}

TEST_F(D2WTest, WorldSetWindowCenter) {
    world->setWindowCenter(Point(1, 2));
    EXPECT_EQ(Point(1, 2), world->windowCenter());
}

TEST_F(D2WTest, WorldWindowCenter) {
    world->setWindowCenter(Point(1, 2));
    EXPECT_EQ(Point(1, 2), world->windowCenter());
}

TEST_F(D2WTest, WorldSetWindowRotation) {
    world->setWindowRotation(Angle::radians(M_PI / 4));
    EXPECT_EQ(Angle::radians(M_PI / 4), world->windowRotation());
}

TEST_F(D2WTest, WorldWindowRotation) {
    world->setWindowRotation(Angle::radians(M_PI / 4));
    EXPECT_EQ(Angle::radians(M_PI / 4), world->windowRotation());
}

TEST_F(D2WTest, WorldSetWindowWidth) {
    world->setWindowWidth(800);
    EXPECT_EQ(800, world->windowWidth());
}

TEST_F(D2WTest, WorldWindowWidth) {
    world->setWindowWidth(800);
    EXPECT_EQ(800, world->windowWidth());
}

TEST_F(D2WTest, WorldSetWindowHeight) {
    world->setWindowHeight(600);
    EXPECT_EQ(600, world->windowHeight());
}

TEST_F(D2WTest, WorldWindowHeight) {
    world->setWindowHeight(600);
    EXPECT_EQ(600, world->windowHeight());
}

TEST_F(D2WTest, WorldWindowPolygon) {
    world->setWindowCenter(Point(sqrt(2) / 2, sqrt(2) / 2));
    world->setWindowRotation(Angle::radians(M_PI / 4));
    world->setWindowWidth(1);
    world->setWindowHeight(1);
    std::set<Point> rhombusVertices;
    rhombusVertices.insert(Point(0, sqrt(2) / 2));
    rhombusVertices.insert(Point(sqrt(2) / 2, 0));
    rhombusVertices.insert(Point(sqrt(2) / 2, sqrt(2)));
    rhombusVertices.insert(Point(sqrt(2), sqrt(2) / 2));
    EXPECT_EQ(Polygon(rhombusVertices), world->windowPolygon());
}

TEST_F(D2WTest, WorldCreateBody) {
    Body *emptyBody = world->createBody(Point(0, 0), Angle::radians(0), true);
    EXPECT_EQ(Point(0, 0), emptyBody->center());
    EXPECT_EQ(Angle::radians(0), emptyBody->rotation());
    EXPECT_TRUE(emptyBody->isDynamic());
    std::set<Body*> bodies = world->bodies();
    EXPECT_EQ(1, bodies.size());

    Body *body = world->createBody(Point(1, 1), Angle::radians(M_PI), false);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));
    EXPECT_EQ(Point(1, 1), body->center());
    EXPECT_EQ(Angle::radians(M_PI), body->rotation());
    EXPECT_FALSE(body->isDynamic());
    bodies = world->bodies();
    EXPECT_EQ(2, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(body));
}

TEST_F(D2WTest, WorldRemoveTaggedBodies) {
    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("square", Polygon::square(Point(0, 0), 1));
    bodyA->addTag("vowel");
    bodyA->addTag("a");
    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("square", Polygon::square(Point(0, 0), 1));
    bodyB->addTag("consonant");
    bodyB->addTag("b");
    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("square", Polygon::square(Point(0, 0), 1));
    bodyC->addTag("consonant");
    bodyC->addTag("c");
    Body *bodyD = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyD->addPolygon("square", Polygon::square(Point(0, 0), 1));
    bodyD->addTag("consonant");
    bodyD->addTag("d");
    Body *bodyE = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyE->addPolygon("square", Polygon::square(Point(0, 0), 1));
    bodyE->addTag("vowel");
    bodyE->addTag("e");

    world->removeTaggedBodies("consonant");
    std::set<Body*> bodies = world->bodies();
    EXPECT_EQ(2, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyA));
    EXPECT_NE(bodies.end(), bodies.find(bodyE));
    
    std::set<std::string> tags;
    tags.insert("vowel");
    tags.insert("e");
    world->removeTaggedBodies(tags);
    bodies = world->bodies();
    EXPECT_EQ(1, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyA));
}

TEST_F(D2WTest, WorldClearBodies) {
    world->createBody(Point(0, 0), Angle::radians(0), true);
    world->createBody(Point(0, 0), Angle::radians(0), true);
    world->createBody(Point(0, 0), Angle::radians(0), true);
    world->clearBodies();
    EXPECT_EQ(0, world->bodies().size());
}

TEST_F(D2WTest, WorldBodies) {
    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *emptyBody = world->createBody(Point(0, 0), Angle::radians(0), true);
    std::set<Body*> bodies = world->bodies();
    EXPECT_EQ(4, bodies.size());
    EXPECT_NE(bodies.end(), bodies.find(bodyA));
    EXPECT_NE(bodies.end(), bodies.find(bodyB));
    EXPECT_NE(bodies.end(), bodies.find(bodyC));
    EXPECT_NE(bodies.end(), bodies.find(emptyBody));
}

TEST_F(D2WTest, WorldBodiesNearWindow) {
    world->setWindowCenter(Point(1, 1));
    world->setWindowRotation(Angle::radians(0));
    world->setWindowWidth(2);
    world->setWindowHeight(2);
    world->setBodyIndexRange(1);
    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body3 = world->createBody(Point(2, 2), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body4 = world->createBody(Point(3, 3), Angle::radians(0), true);
    body4->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body5 = world->createBody(Point(4, 4), Angle::radians(0), true);
    body5->addPolygon("square", Polygon::square(Point(0, 0), 1));
    world->createBody(Point(1, 1), Angle::radians(0), true);
    std::set<Body*> bodiesNearWindow = world->bodiesNearWindow();
    EXPECT_EQ(3, bodiesNearWindow.size());
    EXPECT_NE(bodiesNearWindow.end(), bodiesNearWindow.find(body1));
    EXPECT_NE(bodiesNearWindow.end(), bodiesNearWindow.find(body2));
    EXPECT_NE(bodiesNearWindow.end(), bodiesNearWindow.find(body3));
}

TEST_F(D2WTest, WorldBodiesOnWindow) {
    world->setWindowCenter(Point(1, 1));
    world->setWindowRotation(Angle::radians(0));
    world->setWindowWidth(2);
    world->setWindowHeight(2);
    world->setBodyIndexRange(1);
    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body3 = world->createBody(Point(2, 2), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body4 = world->createBody(Point(3, 3), Angle::radians(0), true);
    body4->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *body5 = world->createBody(Point(4, 4), Angle::radians(0), true);
    body5->addPolygon("square", Polygon::square(Point(0, 0), 1));
    world->createBody(Point(1, 1), Angle::radians(0), true);
    std::set<Body*> bodiesOnWindow = world->bodiesOnWindow();
    EXPECT_EQ(2, bodiesOnWindow.size());
    EXPECT_NE(bodiesOnWindow.end(), bodiesOnWindow.find(body1));
    EXPECT_NE(bodiesOnWindow.end(), bodiesOnWindow.find(body2));
}

TEST_F(D2WTest, WorldTaggedBodies) {
    Body *bodyA = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyA->addTag("vowel");
    bodyA->addTag("a");
    bodyA->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *bodyB = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyB->addTag("consonant");
    bodyB->addTag("b");
    bodyB->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *bodyC = world->createBody(Point(0, 0), Angle::radians(0), true);
    bodyC->addTag("consonant");
    bodyC->addTag("c");
    bodyC->addPolygon("square", Polygon::square(Point(0, 0), 1));
    Body *emptyBody = world->createBody(Point(0, 0), Angle::radians(0), true);
    emptyBody->addTag("empty");
 
    std::set<Body*> taggedBodies = world->taggedBodies("consonant");
    EXPECT_EQ(2, taggedBodies.size());
    EXPECT_NE(taggedBodies.end(), taggedBodies.find(bodyB));
    EXPECT_NE(taggedBodies.end(), taggedBodies.find(bodyC));

    taggedBodies = world->taggedBodies("empty");
    EXPECT_EQ(1, taggedBodies.size());
    EXPECT_NE(taggedBodies.end(), taggedBodies.find(emptyBody));

    std::set<std::string> tags;
    tags.insert("consonant");
    tags.insert("c");
    taggedBodies = world->taggedBodies(tags);
    EXPECT_EQ(1, taggedBodies.size());
    EXPECT_NE(taggedBodies.end(), taggedBodies.find(bodyC));
}

TEST_F(D2WTest, WorldTaggedBodiesNearWindow) {
    world->setWindowCenter(Point(1, 1));
    world->setWindowRotation(Angle::radians(0));
    world->setWindowWidth(2);
    world->setWindowHeight(2);
    world->setBodyIndexRange(1);
    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body1->addTag("odd");
    body1->addTag("1");
    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body2->addTag("even");
    body2->addTag("2");
    Body *body3 = world->createBody(Point(2, 2), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body3->addTag("odd");
    body3->addTag("3");
    Body *body4 = world->createBody(Point(3, 3), Angle::radians(0), true);
    body4->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body4->addTag("even");
    body4->addTag("4");
    Body *body5 = world->createBody(Point(4, 4), Angle::radians(0), true);
    body5->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body5->addTag("odd");
    body5->addTag("5");

    std::set<Body*> taggedBodiesNearWindow = world->taggedBodiesNearWindow("odd");
    EXPECT_EQ(2, taggedBodiesNearWindow.size());
    EXPECT_NE(taggedBodiesNearWindow.end(), taggedBodiesNearWindow.find(body1));
    EXPECT_NE(taggedBodiesNearWindow.end(), taggedBodiesNearWindow.find(body3));

    std::set<std::string> tags;
    tags.insert("odd");
    tags.insert("3");
    taggedBodiesNearWindow = world->taggedBodiesNearWindow(tags);
    EXPECT_EQ(1, taggedBodiesNearWindow.size());
    EXPECT_NE(taggedBodiesNearWindow.end(), taggedBodiesNearWindow.find(body3));
}

TEST_F(D2WTest, WorldTaggedBodiesOnWindow) {
    world->setWindowCenter(Point(1, 1));
    world->setWindowRotation(Angle::radians(0));
    world->setWindowWidth(2);
    world->setWindowHeight(2);
    world->setBodyIndexRange(1);
    Body *body1 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body1->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body1->addTag("odd");
    body1->addTag("1");
    Body *body2 = world->createBody(Point(1, 1), Angle::radians(0), true);
    body2->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body2->addTag("even");
    body2->addTag("2");
    Body *body3 = world->createBody(Point(2, 2), Angle::radians(0), true);
    body3->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body3->addTag("odd");
    body3->addTag("3");
    Body *body4 = world->createBody(Point(3, 3), Angle::radians(0), true);
    body4->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body4->addTag("even");
    body4->addTag("4");
    Body *body5 = world->createBody(Point(4, 4), Angle::radians(0), true);
    body5->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body5->addTag("odd");
    body5->addTag("5");
    Body *body6 = world->createBody(Point(0, 0), Angle::radians(0), true);
    body6->addPolygon("square", Polygon::square(Point(0, 0), 1));
    body6->addTag("even");
    body6->addTag("6");

    std::set<Body*> taggedBodiesOnWindow = world->taggedBodiesOnWindow("even");
    EXPECT_EQ(2, taggedBodiesOnWindow.size());
    EXPECT_NE(taggedBodiesOnWindow.end(), taggedBodiesOnWindow.find(body2));
    EXPECT_NE(taggedBodiesOnWindow.end(), taggedBodiesOnWindow.find(body6));

    std::set<std::string> tags;
    tags.insert("even");
    tags.insert("6");
    taggedBodiesOnWindow = world->taggedBodiesOnWindow(tags);
    EXPECT_EQ(1, taggedBodiesOnWindow.size());
    EXPECT_NE(taggedBodiesOnWindow.end(), taggedBodiesOnWindow.find(body6));
}

TEST_F(D2WTest, WorldSetBodyIndexRange) {
    Body *body = world->createBody(Point(0, 0), Angle::radians(0), true);
    body->addPolygon("square", Polygon::square(Point(0, 0), 1));

    world->setBodyIndexRange(1);
    std::vector<std::pair<int, int>> indexQuadrants = body->indexQuadrants();
    EXPECT_EQ(4, indexQuadrants.size());
    EXPECT_EQ(std::make_pair(0, 0), indexQuadrants[0]);
    EXPECT_EQ(std::make_pair(0, 1), indexQuadrants[1]);
    EXPECT_EQ(std::make_pair(1, 0), indexQuadrants[2]);
    EXPECT_EQ(std::make_pair(1, 1), indexQuadrants[3]);

    world->setBodyIndexRange(2);
    indexQuadrants = body->indexQuadrants();
    EXPECT_EQ(1, indexQuadrants.size());
    EXPECT_EQ(std::make_pair(0, 0), indexQuadrants[0]);
}

TEST_F(D2WTest, WorldBodyIndexRange) {
    world->setBodyIndexRange(128);
    EXPECT_EQ(128, world->bodyIndexRange());
}

