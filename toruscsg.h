#ifndef TORUSCSG_H
#define TORUSCSG_H
#include "objectcsg.h"

class TorusCSG : public ObjectCSG
{
public:
    TorusCSG(Vector C, Vector u, double R, double r, Material m);
    bool isInside(const Vector &P) const {
        Vector deltaP = P-C;
        Vector projection = C+(deltaP-deltaP.dot(u)*u).getNormalized()*R;
        double distToCircle2 = (P-projection).squaredNorm();
        return distToCircle2 < r*r;
    }
    void intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const;
    Vector C;
    Vector u;
    double R;
    double r;
};

#endif // TORUSCSG_H
