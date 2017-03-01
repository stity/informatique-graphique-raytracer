#ifndef CYLINDERCSG_H
#define CYLINDERCSG_H
#include "objectcsg.h"
#include "vector.h"

class CylinderCSG : public ObjectCSG
{
public:
    CylinderCSG(Vector A, Vector B, double R, Material M);
    Vector A;
    Vector B;
    double R;
    Material material;
    bool isInside(const Vector & P) const {
        Vector u = (B-A).getNormalized();
        return ((P-A-(P-A).dot(u)*u).squaredNorm()<(R*R)) && ((P-A).dot(u)>0) && ((P-B).dot(u) < 0);
    }
    void intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const;
};

#endif // CYLINDERCSG_H
