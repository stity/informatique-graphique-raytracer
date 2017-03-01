#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "objectcsg.h"

class Intersection : public ObjectCSG
{
public:
    Intersection(ObjectCSG* a, ObjectCSG* b);
    ObjectCSG* a;
    ObjectCSG* b;
    bool isInside(const Vector &P) const {return this->a->isInside(P) && this->b->isInside(P);}
    void intersect(const Ray & r , std::vector<IntersectionPointCSG *> & LI) const;

};

#endif // INTERSECTION_H
