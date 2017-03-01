#ifndef UNION_H
#define UNION_H
#include "objectcsg.h"
class Union:public ObjectCSG
{
public:
    Union(ObjectCSG* a, ObjectCSG* b);
    ObjectCSG* a;
    ObjectCSG* b;
    bool isInside (const Vector & P) const {return a->isInside(P) || b->isInside(P);}
    void intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const;
};

#endif // UNION_H
