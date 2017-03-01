#include "spherecsg.h"

SphereCSG::SphereCSG(Vector C, double R, Material M)
{
    this->C = C;
    this->R = R;
    this->material = M;
}

void SphereCSG::intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const {
    Vector P;
    double t;
    Vector N;
    double a =1;
    double b = 2.*r.u.dot(r.C-C);
    double c = (r.C-C).squaredNorm() - R*R;
    double delta = b*b - 4*a*c;
    if (delta>=0) {

        double t1 = (-b-sqrt(delta))/(2*a);
        double t2 = (-b+sqrt(delta))/(2*a);

        if (t1 > 0) {
            P = r.C+ t1*r.u;
            t = t1;
            N = P-C;
            N.normalize();
            IntersectionPointCSG* IP = new IntersectionPointCSG(P, N, this->material);
            LI.push_back(IP);
        }
        else if (t2 > 0) {
            P = r.C+ t2*r.u;
            t = t2;
            N = P-C;
            N.normalize();
            IntersectionPointCSG* IP = new IntersectionPointCSG(P, N, this->material);
            LI.push_back(IP);
        }
    }
}

