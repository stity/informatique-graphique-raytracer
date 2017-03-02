#ifndef OBJECTCSG_H
#define OBJECTCSG_H

#include "vector.h"
#include "ray.h"
#include <vector>
#include "intersectionpointcsg.h"
#include "object.h"

class ObjectCSG : public Object
{
public:
    ObjectCSG();
    virtual bool isInside(const Vector&) const=0;
    virtual void intersect(const Ray&, std::vector<IntersectionPointCSG*>&) const = 0;
    bool intersect(const Ray& r, Vector& P, double& t, Vector& N, Material &M) const;
};

#endif // OBJECTCSG_H
