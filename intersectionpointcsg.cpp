#include "intersectionpointcsg.h"

IntersectionPointCSG::IntersectionPointCSG(Vector &P, Vector &N, Material &M)
{
    this->P = P;
    this->N = N;
    this->M = M;
}
