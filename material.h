#ifndef MATERIAL_H
#define MATERIAL_H

#include "vector.h"

class Material
{
public:
    Material(Vector color = Vector(1.,1.,1.), Vector caracteristics = Vector(true, false, false), double diffusionCoefficient = 1, double emissivity=0);
    Material(Material &m);
    Material(const Material &m);
    bool isDiffuse();
    bool isSpecular();
    bool isTransparent();

    Vector color;
    double emissivity;
    // Vecteur sous la forme [isDiffuse ; isSpecular ; isTransparent]
    Vector caracteristics;
    double diffusionCoefficient;
};

#endif // MATERIAL_H
