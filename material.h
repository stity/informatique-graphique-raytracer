#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

class Material
{
public:
    Material(Vector color = Vector(1.,1.,1.), Vector caracteristics = Vector(true, false, false));

    bool isDiffuse();
    bool isSpecular();
    bool isTransparent();

    Vector color;
    // Vecteur sous la forme [isDiffuse ; isSpecular ; isTransparent]
    Vector caracteristics;
};

#endif // MATERIAL_H
