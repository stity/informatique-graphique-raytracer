#ifndef SCENE_H
#define SCENE_H
#include "sphere.h"
#include <vector>


class Scene {
public:
    Scene();

    bool intersect( const Ray& r, Vector& P, Vector& N, int& id);

    std::vector<Sphere> objects;
};


#endif // SCENE_H
