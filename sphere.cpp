#include "sphere.h"
#include <cmath>
#include "helpers.h"

Sphere::Sphere(Vector O, double R, Vector color) {
    this->O = O;
    this->R = R;
    this->color = color;
}

bool Sphere::intersect(const Ray& r, Vector& P, double& t, Vector& N) {
    double a =1;
    double b = 2.*dot(r.u,r.C-O);
    double c = (r.C-O).squaredNorm() - R*R;
    double delta = b*b - 4*a*c;
    if (delta>=0) {

        double t1 = (-b-sqrt(delta))/(2*a);
        double t2 = (-b+sqrt(delta))/(2*a);

        if (t1 > 0) {
            P = r.C+ t1*r.u;
            t = t1;
            N = P-O;
            N.normalize();
            return true;
        }
        else if (t2 > 0) {
            P = r.C+ t2*r.u;
            t = t2;
            N = P-O;
            N.normalize();
            return true;
        }
    }
    return false;
}
