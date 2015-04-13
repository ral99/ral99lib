#include <stdexcept>
#include <utility>
#include <vector>

#include "d2w/d2w.h"
#include "num/num.h"

using namespace D2W;
using namespace CG;

// ::: Body :::

Body::~Body() {
    delete _center;
    delete _rotation;
}

void Body::refreshIndexQuadrants() {
    _indexQuadrants.clear();
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++) {
        std::vector<Point> vertices = it->second.vertices();
        double minX, maxX, minY, maxY;
        for (std::vector<Point>::iterator jt = vertices.begin(); jt != vertices.end(); jt++) {
            if (jt == vertices.begin() || (double_lt(jt->x(), minX)))
                minX = jt->x();
            if (jt == vertices.begin() || (double_gt(jt->x(), maxX)))
                maxX = jt->x();
            if (jt == vertices.begin() || (double_lt(jt->y(), minY)))
                minY = jt->y();
            if (jt == vertices.begin() || (double_gt(jt->y(), maxY)))
                maxY = jt->y();
        } 
        for (int i = (int) (minX / _world->_bodyIndexRange); i <= (int) (maxX / _world->_bodyIndexRange); i++)
            for (int j = (int) (minY / _world->_bodyIndexRange); j <= (int) (maxY / _world->_bodyIndexRange); j++)
                _indexQuadrants.push_back(std::make_pair(i, j));
    }
}

void Body::operator+=(const Vector& vector) {  
    _world->removeBodyFromIndex(*this);
    *_center += vector;
    for (std::map<std::string, Polygon>::iterator it = _polygons.begin(); it != _polygons.end(); it++)
        it->second += vector;
    refreshIndexQuadrants();
    _world->addBodyToIndex(*this);
}

void Body::operator-=(const Vector& vector) {
    *this += -vector;
}

void Body::operator%=(const Angle& angle) { 
    _world->removeBodyFromIndex(*this);
    *_rotation += angle;
    for (std::map<std::string, Polygon>::iterator it = _polygons.begin(); it != _polygons.end(); it++)
        it->second.rotateAround(*_center, angle);
    refreshIndexQuadrants();
    _world->addBodyToIndex(*this);
}

void Body::setCenter(const Point& center) {
    *this += Vector(*_center, center);
}

Point Body::center() const {
    return *_center;
}

Point Body::centerOnWindowCoordinates() const {
    Point center = *_center;
    center -= _world->_windowCenter->vectorFromOrigin() - Vector(_world->_windowWidth / 2, _world->_windowHeight / 2);
    center.rotateAround(Point(_world->_windowWidth / 2, _world->_windowHeight / 2), -*(_world->_windowRotation));
    return center;
}

void Body::setRotation(const Angle& rotation) {
    *this %= rotation - *_rotation;
}

Angle Body::rotation() const {
    return *_rotation;
}

Angle Body::rotationOnWindowCoordinates() const {
    return *_rotation - *(_world->_windowRotation);
}

void Body::setIsDynamic(const bool isDynamic) {
    _dynamic = isDynamic;
}

bool Body::isDynamic() const {
    return _dynamic;
}

void Body::addPolygon(const std::string& polygonId, const Polygon& polygon) {  
    _world->removeBodyFromIndex(*this);
    Polygon polygonCopy(polygon);
    polygonCopy += _center->vectorFromOrigin();
    polygonCopy.rotateAround(*_center, *_rotation);
    std::map<std::string, Polygon>::iterator it = _polygons.find(polygonId);
    if (it != _polygons.end())
        _polygons.erase(it);
    _polygons.insert(std::make_pair(polygonId, polygonCopy));
    refreshIndexQuadrants();
    _world->addBodyToIndex(*this);
}

void Body::removePolygon(const std::string& polygonId) { 
    _world->removeBodyFromIndex(*this); 
    std::map<std::string, Polygon>::iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    _polygons.erase(it);
    refreshIndexQuadrants();
    _world->addBodyToIndex(*this);
}

void Body::clearPolygons() {
    _world->removeBodyFromIndex(*this);
    _polygons.clear();
    _indexQuadrants.clear();
}

Polygon Body::polygon(const std::string& polygonId) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    return it->second;
}

Polygon Body::polygonOnWindowCoordinates(const std::string& polygonId) const {
    Polygon polygon = this->polygon(polygonId);
    polygon -= _world->_windowCenter->vectorFromOrigin() - Vector(_world->_windowWidth / 2, _world->_windowHeight / 2);
    polygon.rotateAround(Point(_world->_windowWidth / 2, _world->_windowHeight / 2), -*(_world->_windowRotation));
    return polygon;
}

std::set<Polygon> Body::polygons() const { 
    std::set<Polygon> polygons;
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        polygons.insert(it->second);
    return polygons;
}

std::set<Polygon> Body::polygonsOnWindowCoordinates() const { 
    std::set<Polygon> polygons;
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++) {
        Polygon polygon = it->second;
        polygon -= _world->_windowCenter->vectorFromOrigin() - Vector(_world->_windowWidth / 2, _world->_windowHeight / 2);
        polygon.rotateAround(Point(_world->_windowWidth / 2, _world->_windowHeight / 2), -*(_world->_windowRotation));
        polygons.insert(polygon);
    }
    return polygons;
}

void Body::addTag(const std::string& tag) {
    _tags.insert(tag);
}

void Body::removeTag(const std::string& tag) {
    std::set<std::string>::iterator it = _tags.find(tag);
    if (it == _tags.end())
        throw std::invalid_argument("Body tag is invalid.");
    _tags.erase(it);
}

void Body::clearTags() {
    _tags.clear();
}

bool Body::hasTag(const std::string& tag) const {
    return _tags.find(tag) != _tags.end();
}

bool Body::isOnWindow() const {
    Polygon windowPolygon = _world->windowPolygon();
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        if (it->second.isCollidingWith(windowPolygon))
            return true;
    return false;
}

std::vector<std::pair<int, int>> Body::indexQuadrants() const { 
    return _indexQuadrants;
}

std::set<Body*> Body::neighbourBodies() const {
    std::set<Body*> neighbourBodies; 
    for (std::vector<std::pair<int, int>>::const_iterator it = _indexQuadrants.begin(); it != _indexQuadrants.end(); it++)
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                std::map<std::pair<int, int>, std::set<Body*>>::iterator bodies;
                bodies = _world->_bodyIndex.find(std::make_pair(it->first + i, it->second + j));
                if (bodies != _world->_bodyIndex.end())
                    for (std::set<Body*>::iterator jt = bodies->second.begin(); jt != bodies->second.end(); jt++)
                        if (*jt != this)
                            neighbourBodies.insert(*jt);
            }
    return neighbourBodies;
}

std::set<Body*> Body::neighbourDynamicBodies() const {
    std::set<Body*> neighbourDynamicBodies; 
    for (std::vector<std::pair<int, int>>::const_iterator it = _indexQuadrants.begin(); it != _indexQuadrants.end(); it++)
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                std::map<std::pair<int, int>, std::set<Body*>>::iterator bodies;
                bodies = _world->_bodyIndex.find(std::make_pair(it->first + i, it->second + j));
                if (bodies != _world->_bodyIndex.end())
                    for (std::set<Body*>::iterator jt = bodies->second.begin(); jt != bodies->second.end(); jt++)
                        if (*jt != this && (*jt)->isDynamic())
                            neighbourDynamicBodies.insert(*jt);
            }
    return neighbourDynamicBodies;
}

std::set<Body*> Body::neighbourTaggedBodies(const std::string& tag) const {
    std::set<Body*> neighbourTaggedBodies; 
    for (std::vector<std::pair<int, int>>::const_iterator it = _indexQuadrants.begin(); it != _indexQuadrants.end(); it++)
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                std::map<std::pair<int, int>, std::set<Body*>>::iterator bodies;
                bodies = _world->_bodyIndex.find(std::make_pair(it->first + i, it->second + j));
                if (bodies != _world->_bodyIndex.end())
                    for (std::set<Body*>::iterator jt = bodies->second.begin(); jt != bodies->second.end(); jt++)
                        if (*jt != this && (*jt)->hasTag(tag))
                            neighbourTaggedBodies.insert(*jt);
            }
    return neighbourTaggedBodies;
}

std::set<Body*> Body::neighbourDynamicTaggedBodies(const std::string& tag) const {
    std::set<Body*> neighbourDynamicTaggedBodies; 
    for (std::vector<std::pair<int, int>>::const_iterator it = _indexQuadrants.begin(); it != _indexQuadrants.end(); it++)
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++) {
                std::map<std::pair<int, int>, std::set<Body*>>::iterator bodies;
                bodies = _world->_bodyIndex.find(std::make_pair(it->first + i, it->second + j));
                if (bodies != _world->_bodyIndex.end())
                    for (std::set<Body*>::iterator jt = bodies->second.begin(); jt != bodies->second.end(); jt++)
                        if (*jt != this && (*jt)->isDynamic() && (*jt)->hasTag(tag))
                            neighbourDynamicTaggedBodies.insert(*jt);
            }
    return neighbourDynamicTaggedBodies;
}

bool Body::isCollidingWith(const Body& other) const {
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
            if (it->second.isCollidingWith(jt->second))
                return true;
    return false;
}

bool Body::isCollidingWith(const std::string& polygonId, const Body& other) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
        if (it->second.isCollidingWith(jt->second))
            return true;
    return false;
}

std::set<Body*> Body::collidingDynamicBodies() const {
    std::set<Body*> collidingDynamicBodies;
    std::set<Body*> neighbourDynamicBodies = this->neighbourDynamicBodies();
    for (std::set<Body*>::iterator it = neighbourDynamicBodies.begin(); it != neighbourDynamicBodies.end(); it++)
        if (isCollidingWith(**it))
            collidingDynamicBodies.insert(*it);
    return collidingDynamicBodies;
}

std::set<Body*> Body::collidingDynamicBodies(const std::string& polygonId) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<Body*> collidingDynamicBodies;
    std::set<Body*> neighbourDynamicBodies = this->neighbourDynamicBodies();
    for (std::set<Body*>::iterator it = neighbourDynamicBodies.begin(); it != neighbourDynamicBodies.end(); it++)
        if (isCollidingWith(polygonId, **it))
            collidingDynamicBodies.insert(*it);
    return collidingDynamicBodies;
}

std::set<Body*> Body::collidingDynamicTaggedBodies(const std::string& tag) const {
    std::set<Body*> collidingDynamicTaggedBodies;
    std::set<Body*> neighbourDynamicTaggedBodies = this->neighbourDynamicTaggedBodies(tag);
    for (std::set<Body*>::iterator it = neighbourDynamicTaggedBodies.begin(); it != neighbourDynamicTaggedBodies.end(); it++)
        if (isCollidingWith(**it))
            collidingDynamicTaggedBodies.insert(*it);
    return collidingDynamicTaggedBodies;
}

std::set<Body*> Body::collidingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<Body*> collidingDynamicTaggedBodies;
    std::set<Body*> neighbourDynamicTaggedBodies = this->neighbourDynamicTaggedBodies(tag);
    for (std::set<Body*>::iterator jt = neighbourDynamicTaggedBodies.begin(); jt != neighbourDynamicTaggedBodies.end(); jt++)
        if (isCollidingWith(polygonId, **jt))
            collidingDynamicTaggedBodies.insert(*jt);
    return collidingDynamicTaggedBodies;
}

std::set<std::pair<std::string, std::string>> Body::collisionWith(const Body& other) const {
    std::set<std::pair<std::string, std::string>> collision;
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
            if (it->second.isCollidingWith(jt->second))
                collision.insert(std::make_pair(it->first, jt->first));
    return collision;
}

std::set<std::string> Body::collisionWith(const std::string& polygonId, const Body& other) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<std::string> collision;
    for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
        if (it->second.isCollidingWith(jt->second))
            collision.insert(jt->first);
    return collision;
}

bool Body::isInContactWith(const Body& other) const {
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
            if (it->second.isInContactWith(jt->second))
                return true;
    return false;
}

bool Body::isInContactWith(const std::string& polygonId, const Body& other) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
        if (it->second.isInContactWith(jt->second))
            return true;
    return false;
}

std::set<Body*> Body::contactingDynamicBodies() const {
    std::set<Body*> contactingDynamicBodies;
    std::set<Body*> neighbourDynamicBodies = this->neighbourDynamicBodies();
    for (std::set<Body*>::iterator it = neighbourDynamicBodies.begin(); it != neighbourDynamicBodies.end(); it++)
        if (isInContactWith(**it))
            contactingDynamicBodies.insert(*it);
    return contactingDynamicBodies;
}

std::set<Body*> Body::contactingDynamicBodies(const std::string& polygonId) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<Body*> contactingDynamicBodies;
    std::set<Body*> neighbourDynamicBodies = this->neighbourDynamicBodies();
    for (std::set<Body*>::iterator it = neighbourDynamicBodies.begin(); it != neighbourDynamicBodies.end(); it++)
        if (isInContactWith(polygonId, **it))
            contactingDynamicBodies.insert(*it);
    return contactingDynamicBodies;
}

std::set<Body*> Body::contactingDynamicTaggedBodies(const std::string& tag) const {
    std::set<Body*> contactingDynamicTaggedBodies;
    std::set<Body*> neighbourDynamicTaggedBodies = this->neighbourDynamicTaggedBodies(tag);
    for (std::set<Body*>::iterator it = neighbourDynamicTaggedBodies.begin(); it != neighbourDynamicTaggedBodies.end(); it++)
        if (isInContactWith(**it))
            contactingDynamicTaggedBodies.insert(*it);
    return contactingDynamicTaggedBodies;
}

std::set<Body*> Body::contactingDynamicTaggedBodies(const std::string& polygonId, const std::string& tag) const {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<Body*> contactingDynamicTaggedBodies;
    std::set<Body*> neighbourDynamicTaggedBodies = this->neighbourDynamicTaggedBodies(tag);
    for (std::set<Body*>::iterator jt = neighbourDynamicTaggedBodies.begin(); jt != neighbourDynamicTaggedBodies.end(); jt++)
        if (isInContactWith(polygonId, **jt))
            contactingDynamicTaggedBodies.insert(*jt);
    return contactingDynamicTaggedBodies;
}

std::set<std::pair<std::string, std::string>> Body::contactWith(const Body& other) {
    std::set<std::pair<std::string, std::string>> contact;
    for (std::map<std::string, Polygon>::const_iterator it = _polygons.begin(); it != _polygons.end(); it++)
        for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
            if (it->second.isInContactWith(jt->second))
                contact.insert(std::make_pair(it->first, jt->first));
    return contact;
}

std::set<std::string> Body::contactWith(const std::string& polygonId, const Body& other) {
    std::map<std::string, Polygon>::const_iterator it = _polygons.find(polygonId);
    if (it == _polygons.end())
        throw std::invalid_argument("Polygon id is invalid.");
    std::set<std::string> contact;
    for (std::map<std::string, Polygon>::const_iterator jt = other._polygons.begin(); jt != other._polygons.end(); jt++)
        if (it->second.isInContactWith(jt->second))
            contact.insert(jt->first);
    return contact;
}

// ::: World :::

void World::removeBodyFromIndex(Body& body) {
    for (std::vector<std::pair<int, int>>::iterator it = body._indexQuadrants.begin(); it != body._indexQuadrants.end(); it++) {
        std::map<std::pair<int, int>, std::set<Body*>>::iterator jt = _bodyIndex.find(*it);
        jt->second.erase(&body);
    }
}

void World::addBodyToIndex(Body& body) {
    for (std::vector<std::pair<int, int>>::iterator it = body._indexQuadrants.begin(); it != body._indexQuadrants.end(); it++) {
        std::map<std::pair<int, int>, std::set<Body*>>::iterator jt = _bodyIndex.find(*it);
        if (jt == _bodyIndex.end()) {
            _bodyIndex.insert(std::make_pair(*it, std::set<Body*>()));
            jt = _bodyIndex.find(*it);
        }
        jt->second.insert(&body);
    }
}

World::World(const Point& winCenter, const Angle& winRotation, double winWidth, double winHeight, int bodyIndexRange) {
    _windowCenter = new Point(winCenter);
    _windowRotation = new Angle(winRotation);
    _windowWidth = winWidth;
    _windowHeight = winHeight;
    _bodyIndexRange = bodyIndexRange;
}

World::~World() {
    clearBodies();
    delete _windowCenter;
    delete _windowRotation;
}

void World::operator+=(const Vector& vector) {
    *_windowCenter += vector;
}

void World::operator-=(const Vector& vector) {
    *_windowCenter -= vector;
}

void World::operator%=(const Angle& angle) {
    *_windowRotation += angle;
}

void World::setWindowCenter(const Point& windowCenter) {
    *_windowCenter = windowCenter;
}

Point World::windowCenter() const {
    return *_windowCenter;
}

void World::setWindowRotation(const Angle& windowRotation) {
    *_windowRotation = windowRotation;
}

Angle World::windowRotation() const {
    return *_windowRotation;
}

void World::setWindowWidth(double windowWidth) {
    _windowWidth = windowWidth;
}

double World::windowWidth() const {
    return _windowWidth;
}

void World::setWindowHeight(double windowHeight) {
    _windowHeight = windowHeight;
}

double World::windowHeight() const {
    return _windowHeight;
}

Polygon World::windowPolygon() const {
    Polygon polygon = Polygon::rectangle(*_windowCenter - Vector(_windowWidth / 2, _windowHeight / 2), _windowWidth, _windowHeight);
    polygon.rotateAround(*_windowCenter, *_windowRotation);
    return polygon;
}

Body* World::createBody(const Point& center, const Angle& rotation, const bool isDynamic) {
    Body *body = new Body;
    body->_world = this;
    body->_center = new Point(center);
    body->_rotation = new Angle(rotation);
    body->_dynamic = isDynamic;
    _bodies.insert(body);
    return body;
}

void World::removeBody(Body& body) {
    removeBodyFromIndex(body);
    _bodies.erase(&body);
    delete &body;
}

void World::removeTaggedBodies(const std::string& tag) {
    std::set<Body*> taggedBodies = this->taggedBodies(tag);
    for (std::set<Body*>::iterator it = taggedBodies.begin(); it != taggedBodies.end(); it++)
        removeBody(**it);
}

void World::clearBodies() {
    for (std::set<Body*>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
        delete *it;
    _bodies.clear();
    _bodyIndex.clear();
}

std::set<Body*> World::bodies() const {
    return _bodies;
}

std::set<Body*> World::bodiesNearWindow() const {
    std::set<Body*> bodiesNearWindow;
    std::vector<Point> windowCorners;
    windowCorners.push_back(*_windowCenter + Vector(_windowWidth / 2, _windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(_windowWidth / 2, -_windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(-_windowWidth / 2, _windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(-_windowWidth / 2, -_windowHeight / 2));
    double windowMinX, windowMaxX, windowMinY, windowMaxY;
    for (std::vector<Point>::iterator it = windowCorners.begin(); it != windowCorners.end(); it++) {
        it->rotateAround(*_windowCenter, *_windowRotation);
        if (it == windowCorners.begin() || double_lt(it->x(), windowMinX))
            windowMinX = it->x();
        if (it == windowCorners.begin() || double_gt(it->x(), windowMaxX))
            windowMaxX = it->x();
        if (it == windowCorners.begin() || double_lt(it->y(), windowMinY))
            windowMinY = it->y();
        if (it == windowCorners.begin() || double_gt(it->y(), windowMaxY))
            windowMaxY = it->y();
    }
    for (int i = (int) (windowMinX / _bodyIndexRange); i <= (int) (windowMaxX / _bodyIndexRange); i++)
        for (int j = (int) (windowMinY / _bodyIndexRange); j <= (int) (windowMaxY / _bodyIndexRange); j++) {
            std::map<std::pair<int, int>, std::set<Body*>>::const_iterator jt = _bodyIndex.find(std::make_pair(i, j));
            if (jt != _bodyIndex.end())
                for (std::set<Body*>::iterator kt = jt->second.begin(); kt != jt->second.end(); kt++)
                    bodiesNearWindow.insert(*kt);
        }
    return bodiesNearWindow;
}

std::set<Body*> World::bodiesOnWindow() const {
    std::set<Body*> bodiesNearWindow = this->bodiesNearWindow();
    std::set<Body*> bodiesOnWindow;
    for (std::set<Body*>::iterator it = bodiesNearWindow.begin(); it != bodiesNearWindow.end(); it++)
        if ((*it)->isOnWindow())
            bodiesOnWindow.insert(*it);
    return bodiesOnWindow;
}

std::set<Body*> World::taggedBodies(const std::string& tag) const {
    std::set<Body*> taggedBodies;
    for (std::set<Body*>::const_iterator it = _bodies.begin(); it != _bodies.end(); it++)
        if ((*it)->hasTag(tag))
            taggedBodies.insert(*it);
    return taggedBodies;
}

std::set<Body*> World::taggedBodiesNearWindow(const std::string& tag) const {
    std::set<Body*> taggedBodiesNearWindow;
    std::vector<Point> windowCorners;
    windowCorners.push_back(*_windowCenter + Vector(_windowWidth / 2, _windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(_windowWidth / 2, -_windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(-_windowWidth / 2, _windowHeight / 2));
    windowCorners.push_back(*_windowCenter + Vector(-_windowWidth / 2, -_windowHeight / 2));
    double windowMinX, windowMaxX, windowMinY, windowMaxY;
    for (std::vector<Point>::iterator it = windowCorners.begin(); it != windowCorners.end(); it++) {
        it->rotateAround(*_windowCenter, *_windowRotation);
        if (it == windowCorners.begin() || double_lt(it->x(), windowMinX))
            windowMinX = it->x();
        if (it == windowCorners.begin() || double_gt(it->x(), windowMaxX))
            windowMaxX = it->x();
        if (it == windowCorners.begin() || double_lt(it->y(), windowMinY))
            windowMinY = it->y();
        if (it == windowCorners.begin() || double_gt(it->y(), windowMaxY))
            windowMaxY = it->y();
    }
    for (int i = (int) (windowMinX / _bodyIndexRange); i <= (int) (windowMaxX / _bodyIndexRange); i++)
        for (int j = (int) (windowMinY / _bodyIndexRange); j <= (int) (windowMaxY / _bodyIndexRange); j++) {
            std::map<std::pair<int, int>, std::set<Body*>>::const_iterator jt = _bodyIndex.find(std::make_pair(i, j));
            if (jt != _bodyIndex.end())
                for (std::set<Body*>::iterator kt = jt->second.begin(); kt != jt->second.end(); kt++)
                    if ((*kt)->hasTag(tag))
                        taggedBodiesNearWindow.insert(*kt);
        }
    return taggedBodiesNearWindow;
}

std::set<Body*> World::taggedBodiesOnWindow(const std::string& tag) const {
    std::set<Body*> taggedBodiesNearWindow = this->taggedBodiesNearWindow(tag);
    std::set<Body*> taggedBodiesOnWindow;
    for (std::set<Body*>::iterator it = taggedBodiesNearWindow.begin(); it != taggedBodiesNearWindow.end(); it++)
        if ((*it)->isOnWindow())
            taggedBodiesOnWindow.insert(*it);
    return taggedBodiesOnWindow;
}

void World::setBodyIndexRange(int bodyIndexRange) {
    _bodyIndexRange = bodyIndexRange;
}

int World::bodyIndexRange() const {
    return _bodyIndexRange;
}

