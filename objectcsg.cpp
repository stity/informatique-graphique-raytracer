#include "objectcsg.h"
#include "vector.h"
#include "ray.h"

ObjectCSG::ObjectCSG()
{
    this->material = Material();

}

bool ObjectCSG::intersect(const Ray &r, Vector &P, double &t, Vector &N, Material& M) const {
    std::vector<IntersectionPointCSG* > LI;
    this->intersect(r, LI);
    double minT = 9E5;
    for (unsigned int i = 0; i < LI.size(); ++i) {
        IntersectionPointCSG* IP = LI[i];
        double T = (IP->P-r.C).dot(r.u);
        if (T > 0 && T < minT) {
            minT = T;
            P = IP->P;
            N = IP->N;
            M = IP->M;
        }
    }
    t = minT;
    for (unsigned int i = 0; i < LI.size(); ++i) {
        IntersectionPointCSG* IP = LI[i];
        delete IP;
    }
    return minT < 9E5;

}
