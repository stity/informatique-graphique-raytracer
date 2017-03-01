#ifndef OBJECTCSG_H
#define OBJECTCSG_H

#include "vector.h"
#include "ray.h"
#include <vector>
#include "intersectionpointcsg.h"

class ObjectCSG
{
public:
    ObjectCSG();
    virtual bool isInside(const Vector&) const=0;
    virtual void intersect(const Ray&, std::vector<IntersectionPointCSG*>&) const = 0;
};

#endif // OBJECTCSG_H
