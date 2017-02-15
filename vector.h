#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iostream>

class Vector {
public:
    Vector(double x=0, double y=0, double z=0);
    Vector(const Vector& b);

    Vector refract(const Vector& N, double n1, double n2, bool &is_refracted) const;
    Vector reflect(const Vector& N) const;
    double dot(const Vector& a);

    double xyz[3];

    double operator[](int i) const ;
    double& operator[](int i);
    double squaredNorm();
    void normalize();
    Vector getNormalized();
    double dot(const Vector& b) const;
    void random_cos(const Vector& N);
    Vector cross(const Vector& b) const;

};


inline Vector operator+(const Vector &a, const Vector &b) {
    return Vector(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}
inline Vector operator-(const Vector& a) {
    return Vector(-a[0], -a[1], -a[2]);
}
inline Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}
inline Vector operator*(const double a, const Vector& b) {
    return Vector(a*b[0], a*b[1], a*b[2]);
}
inline Vector operator*(const Vector& a, const Vector& b) {
    return Vector(a[0]*b[0], a[1]*b[1], a[2]*b[2]);
}
inline Vector operator*(const Vector& a, const double b) {
    return Vector(a[0]*b, a[1]*b, a[2]*b);
}



#endif // VECTOR_H
