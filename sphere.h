#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"
#include "ray.h"
#include "material.h"
#include "sphere.h"
#include "helpers.h"

class Sphere {
public:
    Sphere(Vector O, double R, Vector color, Vector opticProperty, double diffusionCoeff=1, double emissivity=0);

    bool intersect(const Ray& r, Vector& P, double& t, Vector& N);

    Vector O;
    double R;
    Vector L;
    Material material;
};

#endif // SPHERE_H
