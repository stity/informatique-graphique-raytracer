#ifndef SCENE_H
#define SCENE_H
#include "sphere.h"
#include "helpers.h"
#include "object.h"
#include <vector>
#include <cmath>

class Scene {
public:
    Scene();

    bool intersect(const Ray& r, Vector& P, Vector& N, int& id, Material &M) const;
    Vector getColor(const Ray &ray, int recursion, int recursionMax) const;

    std::vector<Object*> objects;
    Vector L;
};


#endif // SCENE_H
