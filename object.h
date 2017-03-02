#ifndef OBJECT_H
#define OBJECT_H

#include "vector"
#include "material.h"
#include "ray.h"

class Object
{
public:
    Object();

    virtual bool intersect(const Ray& r, Vector& P, double& t, Vector& N, Material& M) const = 0;

    Material material;
};

#endif // OBJECT_H
