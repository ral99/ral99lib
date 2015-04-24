#ifndef __D2W__
#define __D2W__

#include <map>
#include <set>
#include <string>

#include "cgpp/cgpp.h"

namespace D2W {

class Body;
class World;

class Body {
    friend class World;

    private:
        World *_world;
        CG::Point *_center;
        CG::Angle *_rotation;
        bool _dynamic;
        std::map<std::string, CG::Polygon> _polygons;
        std::set<std::string> _tags;
        std::set<std::pair<int, int>> _indexQuadrants;

        // Constructor.
        Body() {}

        // Delete copy constructor and assignment operator.
        Body(const Body& other) = delete;
        Body& operator=(const Body& other) = delete;

        // Refresh body index quadrants.
        void refreshIndexQuadrants();

    public:
        // Destructor.
        ~Body();

        // Body translation operator.
        void operator+=(const CG::Vector& vector);
        void operator-=(const CG::Vector& vector);

        // Body rotation around its center.
        void operator%=(const CG::Angle& angle);

        // Set body center.
        void setCenter(const CG::Point& center);

        // Return body center.
        CG::Point center() const;

        // Return body center on world window coordinates system.
        CG::Point centerOnWindowCoordinates() const;

        // Set body rotation.
        void setRotation(const CG::Angle& rotation);

        // Return body rotation.
        CG::Angle rotation() const;

        // Return body rotation on world window coordinates system.
        CG::Angle rotationOnWindowCoordinates() const;

        // Set body dynamic mode.
        void setIsDynamic(const bool isDynamic);

        // Return body dynamic mode.
        bool isDynamic() const;

        // Add or replace polygon identified by a string to body.
        void addPolygon(const std::string& polygonId, const CG::Polygon& polygon);

        // Remove the specified polygon from body or raise an exception if id is invalid.
        void removePolygon(const std::string& polygonId);

        // Remove all polygons from body.
        void clearPolygons();

        // Return the specified polygon of this body or raise an exception if id is invalid.
        CG::Polygon polygon(const std::string& polygonId) const;

        // Return the specified polygon of this body on world window coordinates system or raise an exception if id is invalid.
        CG::Polygon polygonOnWindowCoordinates(const std::string& polygonId) const;

        // Return body polygons.
        std::set<CG::Polygon> polygons() const;

        // Return body polygons on world window coordinates system.
        std::set<CG::Polygon> polygonsOnWindowCoordinates() const;

        // Add tag to body.
        void addTag(const std::string& tag);

        // Remove tag from body or raise an exception if tag is invalid.
        void removeTag(const std::string& tag);

        // Remove all tags from body.
        void clearTags();

        // Return true if body has the specified tag. false, otherwise.
        bool hasTag(const std::string& tag) const;

        // Return true if body is on window. false, otherwise.
        bool isOnWindow() const;

        // Return the index quadrants in which the polygons of this body are on.
        std::set<std::pair<int, int>> indexQuadrants() const;

        // Return the distace between the center of the bodies.
        double distanceTo(const Body& other) const;

        // Return bodies near this body using index quadrants.
        std::set<Body*> neighbourBodies() const;

        // Return dynamic bodies near this body using index quadrants.
        std::set<Body*> neighbourDynamicBodies() const;

        // Return tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourTaggedBodies(const std::string& tag) const;

        // Return tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourTaggedBodies(const std::set<std::string>& tags) const;

        // Return dynamic tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourDynamicTaggedBodies(const std::string& tag) const;

        // Return dynamic tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourDynamicTaggedBodies(const std::set<std::string>& tags) const;

        // Return true if this body is colliding with another body. false, otherwise.
        bool isCollidingWith(const Body& other) const;

        // Return true if this body is colliding with another body. false, otherwise or if the distance between the centers of
        // the bodies is greater than maxDistance.
        bool isCollidingWith(const Body& other, float maxDistance) const;

        // Return true if the specified polygon of this body is colliding with another body or raise an exception if id is
        // invalid. false, otherwise.
        bool isCollidingWith(const std::string& polygonId, const Body& other) const;

        // Return true if the specified polygon of this body is colliding with another body or raise an exception if id is
        // invalid. false, otherwise or if the distance between the centers of the bodies is greater than maxDistance.
        bool isCollidingWith(const std::string& polygonId, const Body& other, float maxDistance) const;

        // Return dynamic bodies colliding with this body.
        std::set<Body*> collidingDynamicBodies() const;

        // Return dynamic bodies colliding with this body which the distance between their centers is lower than maxDistance.
        std::set<Body*> collidingDynamicBodies(float maxDistance) const;

        // Return dynamic bodies colliding with the specified polygon of this body or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicBodies(const std::string& polygonId) const;

        // Return dynamic bodies colliding with the specified polygon of this body which the distance between their centers is
        // lower than maxDistance or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicBodies(const std::string& polygonId, float maxDistance) const;

        // Return dynamic tagged bodies colliding with this body.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& tag) const;

        // Return dynamic tagged bodies colliding with this body which the distance between their centers is lower than
        // maxDistance.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& tag, float maxDistance) const;

        // Return dynamic tagged bodies colliding with this body.
        std::set<Body*> collidingDynamicTaggedBodies(const std::set<std::string>& tags) const;

        // Return dynamic tagged bodies colliding with this body which the distance between their centers is lower than
        // maxDistance.
        std::set<Body*> collidingDynamicTaggedBodies(const std::set<std::string>& tags, float maxDistance) const;

        // Return dynamic tagged bodies colliding with the specified polygon of this body or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag) const;

        // Return dynamic tagged bodies colliding with the specified polygon of this body which the distance between their
        // centers is lower than maxDistance or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag,
                                                     float maxDistance) const;

        // Return dynamic tagged bodies colliding with the specified polygon of this body or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& polygonId, const std::set<std::string>& tags) const;

        // Return dynamic tagged bodies colliding with the specified polygon of this body which the distance between their
        // centers is lower than maxDistance or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& polygonId, const std::set<std::string>& tags,
                                                     float maxDistance) const;

        // Return a set of pairs of ids of polygons of this and another colliding body.
        std::set<std::pair<std::string, std::string>> collisionWith(const Body& other) const;

        // Return a set of ids of polygons of another body colliding with the specified polygon of this body or raise an
        // exception if if is invalid.
        std::set<std::string> collisionWith(const std::string& polygonId, const Body& other) const;
};

class World {
    friend class Body;

    private:
        CG::Point *_windowCenter;
        CG::Angle *_windowRotation;
        double _windowWidth;
        double _windowHeight;
        std::set<Body*> _bodies;
        std::map<std::pair<int, int>, std::set<Body*>> _bodyIndex;
        int _bodyIndexRange;

        // Default constructor
        World() {}
  
        // Remove body from index.
        void removeBodyFromIndex(Body& body);

        // Add body to index.
        void addBodyToIndex(Body& body);

        // Remove body from world.
        void removeBody(Body &body);

        // Delete copy constructor and assignment operator.
        World(const World& other) = delete;
        World& operator=(const World& other) = delete;

    public:
        // Constructor and destructor.
        World(const CG::Point& winCenter, const CG::Angle& winRotation, double winWidth, double winHeight, int bodyIndexRange);
        ~World();

        // Window translation operator.
        void operator+=(const CG::Vector& vector);
        void operator-=(const CG::Vector& vector);

        // Window rotation around its center operator.
        void operator%=(const CG::Angle& angle);

        // Set window center.
        void setWindowCenter(const CG::Point& windowCenter);

        // Return window center.
        CG::Point windowCenter() const;

        // Set window rotation.
        void setWindowRotation(const CG::Angle& windowRotation);

        // Return window rotation.
        CG::Angle windowRotation() const;

        // Set window width.
        void setWindowWidth(double windowWidth);

        // Return window width.
        double windowWidth() const;

        // Set window height.
        void setWindowHeight(double windowHeight);

        // Return window height.
        double windowHeight() const;

        // Return window polygon.
        CG::Polygon windowPolygon() const;

        // Return a pointer to a new body.
        Body* createBody(const CG::Point& center, const CG::Angle& rotation, const bool isDynamic);

        // Destroy tagged bodies.
        void removeTaggedBodies(const std::string& tag);

        // Destroy tagged bodies.
        void removeTaggedBodies(const std::set<std::string>& tags);

        // Destroy all bodies.
        void clearBodies();

        // Return all bodies.
        std::set<Body*> bodies() const;

        // Return bodies near window.
        std::set<Body*> bodiesNearWindow() const;

        // Return bodies on window.
        std::set<Body*> bodiesOnWindow() const;

        // Return tagged bodies.
        std::set<Body*> taggedBodies(const std::string& tag) const;

        // Return tagged bodies.
        std::set<Body*> taggedBodies(const std::set<std::string>& tags) const;

        // Return tagged bodies near window.
        std::set<Body*> taggedBodiesNearWindow(const std::string& tag) const;

        // Return tagged bodies near window.
        std::set<Body*> taggedBodiesNearWindow(const std::set<std::string>& tags) const;

        // Return tagged bodies on window.
        std::set<Body*> taggedBodiesOnWindow(const std::string& tag) const;

        // Return tagged bodies on window.
        std::set<Body*> taggedBodiesOnWindow(const std::set<std::string>& tags) const;

        // Set body index range.
        void setBodyIndexRange(int bodyIndexRange);

        // Return body index range.
        int bodyIndexRange() const;
};

}

#endif

