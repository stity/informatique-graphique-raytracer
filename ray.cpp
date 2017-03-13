#include "ray.h"

Ray::Ray(Vector C, Vector u) {
    this->C = C;
    this->u = u;
    this->uInv = Vector(1/u[0], 1/u[1], 1/u[2]);
}
