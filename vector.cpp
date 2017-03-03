#include "vector.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <random>
#include <thread>
#include "helpers.h"
#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


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

double& Vector::operator [](int i) {
    return xyz[i];
}

double Vector::squaredNorm() const {
    return xyz[0]*xyz[0]+xyz[1]*xyz[1]+xyz[2]*xyz[2];
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
    double u = doubleRand();
    double v = doubleRand();
    double x = cos(2*M_PI*u)*sqrt(1-v);
    double y = sin(2*M_PI*u)*sqrt(1-v);
    double z = sqrt(v);

    Vector tangent1;
    Vector tangent2;
    N.orthogonalSystem(tangent1, tangent2);
    Vector result;
    result = x*tangent1+y*tangent2+z*N;
    this->xyz[0] = result[0];
    this->xyz[1] = result[1];
    this->xyz[2] = result[2];
}

void Vector::orthogonalSystem(Vector &tangent1, Vector &tangent2) const {
    double abs0 = abs(xyz[0]);
    double abs1 = abs(xyz[1]);
    double abs2 = abs(xyz[2]);
    double minComp = std::min(abs0,abs1);
    minComp = std::min(minComp, abs2);
    if (xyz[0] <= minComp) {
        tangent1 = Vector(0,xyz[2],-xyz[1]);
    }
    else if (xyz[1] <= minComp) {
        tangent1 = Vector(xyz[2],0,-xyz[0]);
    }
    else {
        tangent1 = Vector(xyz[1],-xyz[0],0);
    }
    tangent1.normalize();
    tangent2 = this->cross(tangent1);
}

Vector Vector::cross(const Vector& b) const {
    Vector result;
    result.xyz[0] = this->xyz[1]*b[2] - this->xyz[2]*b[1];
    result.xyz[1] = this->xyz[2]*b[0] - this->xyz[0]*b[2];
    result.xyz[2] = this->xyz[0]*b[1] - this->xyz[1]*b[0];
    return result;
}


double Vector::infiniteNorm() const{
    double n = abs(xyz[0]);
    n = std::max(n, (double) abs((double) xyz[1]));
    n = std::max(n, (double) abs(xyz[2]));
    return n;

}
