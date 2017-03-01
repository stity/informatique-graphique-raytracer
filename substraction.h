#ifndef SUBSTRACTION_H
#define SUBSTRACTION_H

#include "objectcsg.h"

class Substraction : public ObjectCSG
{
public:
    Substraction(ObjectCSG* a, ObjectCSG* b);
    ObjectCSG* a;
    ObjectCSG* b;

    bool isInside(const Vector & P) const {return this->a->isInside(P) && !this->b->isInside(P);}
    void intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const;
};

#endif // SUBSTRACTION_H
