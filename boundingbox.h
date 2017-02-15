#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H
#include "ray.h"
#include "vector.h"

class BoundingBox
{
public:
    BoundingBox();
    Vector bmin, bmax;

    bool intersect(const Ray& r) const;
};

#endif // BOUNDINGBOX_H
