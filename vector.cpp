#include "vector.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <random>
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif
std::default_random_engine engine;
std::uniform_real_distribution<double> distrib(0,1);


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
Vector Vector::getNormalized() {
    double norm = sqrt(squaredNorm());
    Vector result(xyz[0]/norm, xyz[1]/norm, xyz[2]/norm );
    return result;
}

double Vector::dot(const Vector& b) const {
    return xyz[0]*b[0]+xyz[1]*b[1]+xyz[2]*b[2];
}

void Vector::random_cos(const Vector& N) {
    double u = distrib(engine);
    double v = distrib(engine);
    double x = cos(2*M_PI*u)*sqrt(1-v);
    double y = sin(2*M_PI*u)*sqrt(1-v);
    double z = sqrt(v);

    Vector tangent1;
    double abs0 = abs((double) N[0]);
    double abs1 = abs((double) N[1]);
    double abs2 = abs((double) N[20]);
    double minComp = std::min(abs0,abs1);
    minComp = std::min(minComp, abs2);
    if (N[0] <= minComp) {
        tangent1 = Vector(0,N[2],-N[1]);
    }
    else if (N[1] <= minComp) {
        tangent1 = Vector(N[2],0,-N[0]);
    }
    else {
        tangent1 = Vector(N[1],-N[0],0);
    }
    tangent1.normalize();
    Vector tangent2 = N.cross(tangent1);
    Vector result;
    result = x*tangent1+y*tangent2+z*N;
    this->xyz[0] = result[0];
    this->xyz[1] = result[1];
    this->xyz[2] = result[2];
}

Vector Vector::cross(const Vector& b) const {
    Vector result;
    result.xyz[0] = this->xyz[1]*b[2] - this->xyz[2]*b[1];
    result.xyz[1] = this->xyz[2]*b[0] - this->xyz[0]*b[2];
    result.xyz[2] = this->xyz[0]*b[1] - this->xyz[1]*b[0];
    return result;
}
