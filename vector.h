#ifndef VECTOR_H
#define VECTOR_H


class Vector {
public:
    Vector(double x=0, double y=0, double z=0);
    Vector(const Vector& b);

    double xyz[3];

    double operator[](int i) const ;
    double squaredNorm();
    void normalize();
    double dot(Vector& b);

};


inline Vector operator+(const Vector &a, const Vector &b) {
    return Vector(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}
inline Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}
inline Vector operator*(const double a, const Vector& b) {
    return Vector(a*b[0], a*b[1], a*b[2]);
}
inline Vector operator*(const Vector& a, const double b) {
    return Vector(a[0]*b, a[1]*b, a[2]*b);
}



#endif // VECTOR_H
