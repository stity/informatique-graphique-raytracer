#include "vector.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>

Vector::Vector(double x, double y, double z) {
    xyz[0] = x;
    xyz[1] = y;
    xyz[2] = z;
}
Vector::Vector(const Vector& b) {
    memcpy(xyz, b.xyz, 3*sizeof(double));
}


double Vector::operator[](int i) const {
    return xyz[i];
}
double Vector::squaredNorm() {
    return xyz[0]*xyz[0]+xyz[1]*xyz[1]+xyz[2]*xyz[2];
}
void Vector::normalize() {
    double norm = sqrt(squaredNorm());
    xyz[0] = xyz[0]/norm;
    xyz[1] = xyz[1]/norm;
    xyz[2] = xyz[2]/norm;
}
double Vector::dot(Vector& b) {
    return xyz[0]*b[0]+xyz[1]*b[1]+xyz[2]*b[2];
}




