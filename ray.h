#ifndef RAY_H
#define RAY_H
#include "vector.h"

class Ray {
public:
    Ray(Vector C, Vector u);
    Vector C;
    Vector u;
    Vector uInv;
};

#endif // RAY_H
