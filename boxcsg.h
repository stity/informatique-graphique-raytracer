#ifndef BOXCSG_H
#define BOXCSG_H

#include "objectcsg.h"

class BoxCSG : public ObjectCSG
{
public:
    BoxCSG(Vector C, Vector T1, Vector T2, Vector Size);
    Vector C;
    Vector T1;
    Vector T2;
    Vector T3;
    Vector size;
    bool isInside(const Vector &P) const;
    bool isAlmostInside(const Vector& P, bool localSystem) const;
    void intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const;
    void addIntersectionPoint(double t, Vector& E, Vector& D, std::vector<IntersectionPointCSG *> & LI) const;
};

#endif // BOXCSG_H
