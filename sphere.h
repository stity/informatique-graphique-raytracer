#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "helpers.h"
#include "geometry.h"

class Sphere : public Object {
public:
    Sphere(Vector O, double R, Vector color, Vector opticProperty, double diffusionCoeff=1, double emissivity=0);

    bool intersect(const Ray& r, Vector& P, double& t, Vector& N, Material& M) const;
    bool isInside(const Vector& p) const { return (p-O).squaredNorm()<(R*R);}

    Vector O;
    double R;

};

#endif // SPHERE_H
