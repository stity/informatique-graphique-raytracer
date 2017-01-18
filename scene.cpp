#include "scene.h"

Scene::Scene()
{
    objects =std::vector<Sphere>();
}

bool Scene::intersect( const Ray& r, Vector& P, Vector& N, int& id) {
    double mint = 1E9;
    bool result = false;
    for(int i = 0; i<objects.size(); i++) {
        double t;
        Vector N1;
        Vector P1;
        if (objects[i].intersect(r, P1, t, N1)) {
            result = true;
            if (t<mint) {
                mint = t;
                P = P1;
                N = N1;
                id = i;
            }
        }
    }
    return result;
}
