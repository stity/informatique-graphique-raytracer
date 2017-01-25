#ifndef SCENE_H
#define SCENE_H
#include "sphere.h"
#include "helpers.h"
#include <vector>
#include <cmath>

class Scene {
public:
    Scene();

    bool intersect(const Ray& r, Vector& P, Vector& N, int& id);
    Vector getColor(const Ray &ray, int recursion);

    std::vector<Sphere> objects;
    Vector L;
};


#endif // SCENE_H
