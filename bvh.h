#ifndef BVH_H
#define BVH_H

#include "boundingbox.h"

class BVH
{
public:
    BVH();
    BoundingBox bbox;
    BVH *left;
    BVH *right;
    int i0;
    int i1;

};

#endif // BVH_H
