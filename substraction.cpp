#include "substraction.h"

Substraction::Substraction(ObjectCSG *a, ObjectCSG *b)
{
    this->a = a;
    this->b = b;
}

void Substraction::intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const {
    std::vector<IntersectionPointCSG *> LIa;
    std::vector<IntersectionPointCSG *> LIb;

    this->a->intersect(r, LIa);
    this->b->intersect(r, LIb);
    for (unsigned int i = 0; i < LIa.size(); ++i) {
        if (!this->b->isInside(LIa[i]->P)) {
            LI.push_back(LIa[i]);
        }
    }
    for (unsigned int i = 0; i < LIb.size(); ++i) {
        if (this->a->isInside(LIb[i]->P)) {
            Vector inverseNormale = -LIb[i]->N;
            LIb[i]->N = inverseNormale;
            LI.push_back(LIb[i]);
        }
    }
}
