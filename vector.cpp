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

double Vector::dot(const Vector& a) {
    return a[0]*xyz[0]+a[1]*xyz[1]+a[2]*xyz[2];
}

Vector Vector::reflect(const Vector& N) const {
    return *this-2.*dot(N)*N;
}

Vector Vector::refract(const Vector& N, double n1, double n2, bool &is_refracted) const {
    double cosThetai = dot(N);
    //double D = 1-sqrt(n1/n2)*(1-sqrt(cosThetai));
    double D = 1-pow((n1/n2),2)*(1-pow(cosThetai,2));
    Vector Rt =((*this)-cosThetai*N)*(n1/n2);

    if(D<0){
        is_refracted = false;
        return Vector(0.,0.,0.);
    } else {
        Vector Rn = -sqrt(D)*N;
        is_refracted = true;
        return Rn+Rt;
    }
}

void Vector::normalize() {
    double norm = sqrt(squaredNorm());
    xyz[0] = xyz[0]/norm;
    xyz[1] = xyz[1]/norm;
    xyz[2] = xyz[2]/norm;
}

double Vector::dot(const Vector& b) const {
    return xyz[0]*b[0]+xyz[1]*b[1]+xyz[2]*b[2];
}
