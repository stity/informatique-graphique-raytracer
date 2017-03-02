#include "union.h"

Union::Union(ObjectCSG *a, ObjectCSG *b)
{
    this->a = a;
    this->b = b;
}

void Union::intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const {
    std::vector<IntersectionPointCSG *> LIa;
    std::vector<IntersectionPointCSG *> LIb;

    this->a->intersect(r, LIa);
    this->b->intersect(r, LIb);
    for (int i = 0; i < LIa.size(); ++i) {
        if (!this->b->isInside(LIa[i]->P)) {
            LI.push_back(LIa[i]);
        }
        else {
            delete LIa[i];
        }
    }
    for (int i = 0; i < LIb.size(); ++i) {
        if (!this->a->isInside(LIb[i]->P)) {
            LI.push_back(LIb[i]);
        }
        else {
            delete LIb[i];
        }
    }
}
