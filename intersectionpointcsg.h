#ifndef INTERSECTIONPOINTCSG_H
#define INTERSECTIONPOINTCSG_H
#include "vector.h"
#include "material.h"

class IntersectionPointCSG
{
public:
    IntersectionPointCSG(Vector& P, Vector& N, Material& M);
    Vector P;
    Vector N;
    Material M;

};

#endif // INTERSECTIONPOINTCSG_H
