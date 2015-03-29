#ifndef __D2W__
#define __D2W__

#include <map>
#include <set>
#include <string>

#include "cgpp/cgpp.h"

using namespace CG;

namespace D2W {

class Body;
class World;

class Body {
    friend class World;

    private:
        World *_world;
        Point *_center;
        Angle *_rotation;
        bool _dynamic;
        std::map<std::string, Polygon> _polygons;
        std::set<std::string> _tags;

        // Constructor and destructor.
        Body() {}
        ~Body();

        // Delete copy constructor and assignment operator.
        Body(const Body& other) = delete;
        Body& operator=(const Body& other) = delete;

    public:
        // Body translation operator.
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);

        // Body rotation around its center.
        void operator%=(const Angle& angle);

        // Set body center.
        void setCenter(const Point& center);

        // Return body center.
        Point center() const;

        // Return body center on world window coordinates system.
        Point centerOnWindowCoordinates() const;

        // Set body rotation.
        void setRotation(const Angle& rotation);

        // Return body rotation.
        Angle rotation() const;

        // Return body rotation on world window coordinates system.
        Angle rotationOnWindowCoordinates() const;

        // Set body dynamic mode.
        void setIsDynamic(const bool isDynamic);

        // Return body dynamic mode.
        bool isDynamic() const;

        // Add or replace polygon identified by a string to body.
        void addPolygon(const std::string& polygonId, const Polygon& polygon);

        // Remove the specified polygon from body or raise an exception if id is invalid.
        void removePolygon(const std::string& polygonId);

        // Remove all polygons from body.
        void clearPolygons();

        // Return the specified polygon of this body or raise an exception if id is invalid.
        Polygon polygon(const std::string& polygonId) const;

        // Return the specified polygon of this body on world window coordinates system or raise an exception if id is invalid.
        Polygon polygonOnWindowCoordinates(const std::string& polygonId) const;

        // Return body polygons.
        std::set<Polygon> polygons() const;

        // Return body polygons on world window coordinates system.
        std::set<Polygon> polygonsOnWindowCoordinates() const;

        // Add tag to body.
        void addTag(const std::string& tag);

        // Remove tag from body or raise an exception if tag is invalid.
        void removeTag(const std::string& tag);

        // Remove all tags from body.
        void clearTags();

        // Return true if body has the specified tag. false, otherwise.
        bool hasTag(const std::string& tag) const;

        // Return the index quadrants in which the polygons of this body are on.
        std::set<std::pair<int, int>> indexQuadrants() const;

        // Return bodies near this body using index quadrants.
        std::set<Body*> neighbourBodies() const;

        // Return dynamic bodies near this body using index quadrants.
        std::set<Body*> neighbourDynamicBodies() const;

        // Return tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourTaggedBodies(const std::string& tag) const;

        // Return dynamic tagged bodies near this body using index quadrants.
        std::set<Body*> neighbourDynamicTaggedBodies(const std::string& tag) const;

        // Return true if this body is colliding with another body. false, otherwise.
        bool isCollidingWith(const Body& other) const;

        // Return true if the specified polygon of this body is colliding with another body or raise an exception if id is invalid.
        // false, otherwise.
        bool isCollidingWith(const std::string& polygonId, const Body& other) const;

        // Return dynamic bodies colliding with this body.
        std::set<Body*> collidingDynamicBodies() const;

        // Return dynamic bodies colliding with the specified polygon of this body or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicBodies(const std::string& polygonId) const;

        // Return dynamic tagged bodies colliding with this body.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& tag) const;

        // Return dynamic tagged bodies colliding with the specified polygon of this body or raise an exception if id is invalid.
        std::set<Body*> collidingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag) const;

        // Return a set of pairs of ids of polygons of this and another colliding body.
        std::set<std::pair<std::string, std::string>> collisionWith(const Body& other) const;

        // Return a set of ids of polygons of another body colliding with the specified polygon of this body or raise an exception if
        // if is invalid.
        std::set<std::string> collisionWith(const std::string& polygonId, const Body& other) const;

        // Return true if this body is in contact with another body. false, otherwise.
        bool isInContactWith(const Body& other);

        // Return true if the specified polygon of this body is in contact with another body or raise an exception if id is invalid.
        // false, otherwise.
        bool isInContactWith(const std::string& polygonId, const Body& other) const;

        // Return dynamic bodies in contact with this body.
        //std::set<Body*> contactingDynamicBodies() const;

        // Return dynamic bodies in contact with the specified polygon of this body or raise an exception if id is invalid.
        //std::set<Body*> contactingDynamicBodies(const std::string& polygonId) const;

        // Return dynamic tagged bodies in contact with this body.
        //std::set<Body*> contactingDynamicTaggedBodies(const std::string& tag) const;

        // Return dynamic tagged bodies in contact with the specified polygon of this body or raise an exception if id is invalid.
        //std::set<Body*> contactingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag) const;

        // Return a set of pairs of ids of polygons of this and another contacting body.
        //std::set<std::pair<std::string, std::string>> contactWith(const Body& other);

        // Return a set of ids of polygons of another body in contact with the specified polygon of this body.
        //std::set<std::string> contactWith(const std::string& polygonId, const Body& other);
};

class World {
    friend class Body;

    private:
        static World *_instance;
        Point *_windowCenter;
        Angle *_windowRotation;
        double _windowWidth;
        double _windowHeight;
        std::map<std::pair<int, int>, std::set<Body*>> _bodyIndex;
        int _bodyIndexRange;

        // Constructor.
        World() {}
        
        // Remove body from index.
        void removeBodyFromIndex(Body& body);

        // Add body to index.
        void addBodyToIndex(Body& body);

        // Delete copy constructor and assignment operator.
        World(const World& other) = delete;
        World& operator=(const World& other) = delete;

    public:
        // Singleton factory.
        static World* getInstance();
        static World* getInstance(const Point& winCenter, const Angle& winRotation, double winWidth, double winHeight, int bodyIndex);

        // Destructor.
        ~World();

        // Window translation operator.
        void operator+=(const Vector& vector);
        void operator-=(const Vector& vector);

        // Window rotation around its center operator.
        void operator%=(const Angle& angle);

        // Set window center.
        void setWindowCenter(const Point& windowCenter);

        // Return window center.
        Point windowCenter() const;

        // Set window rotation.
        void setWindowRotation(const Angle& windowRotation);

        // Return window rotation.
        Angle windowRotation() const;

        // Set window width.
        void setWindowWidth(double windowWidth);

        // Return window width.
        double windowWidth() const;

        // Set window height.
        void setWindowHeight(double windowHeight);

        // Return window height.
        double windowHeight() const;

        // Return a pointer to a new body.
        Body* createBody(const Point& center, const Angle& rotation, const bool isDynamic);

        // Destroy body.
        void removeBody(Body& body);

        // Destroy tagged bodies.
        void removeTaggedBodies(const std::string& tag);

        // Destroy all bodies.
        void clearBodies();

        // Return all bodies.
        std::set<Body*> bodies() const;

        // Return bodies on window.
        std::set<Body*> bodiesOnWindow() const;

        // Return tagged bodies.
        std::set<Body*> taggedBodies(const std::string& tag) const;

        // Return tagged bodies on window.
        std::set<Body*> taggedBodiesOnWindow(const std::string& tag) const;

        // Set body index range.
        void setBodyIndexRange(int bodyIndexRange);

        // Return body index range.
        int bodyIndexRange() const;
};

}

#endif

