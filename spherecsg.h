#ifndef SPHERECSG_H
#define SPHERECSG_H
#include "objectcsg.h"
#include "vector.h"
#include "material.h"

class SphereCSG : public ObjectCSG
{
public:
    SphereCSG(Vector C, double R, Material M);
    bool isInside(const Vector & P) const {return (P-C).squaredNorm()<(R*R);}
    void intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const;
    Vector C;
    double R;
    Material material;
};

#endif // SPHERECSG_H
