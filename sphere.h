#ifndef SPHERE_H
#define SPHERE_H
#include "vector.h"
#include "ray.h"

class Sphere {
public:
    Sphere(Vector O, double R, Vector color = Vector(1.,1.,1.), bool isDiffuse = true, bool isSpecular = false, bool isTransparent = false);

    bool intersect(const Ray& r, Vector& P, double& t, Vector& N);

    Vector O;
    double R;
    Vector color;
    Vector L;
    bool isDiffuse;
    bool isSpecular;
    bool isTransparent;

};

#endif // SPHERE_H
