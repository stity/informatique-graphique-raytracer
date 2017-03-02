#include "material.h"

Material::Material(Vector color, Vector caracteristics, double diffusionCoefficient, double emissivity)
{
    this->color = color;
    this->caracteristics = caracteristics;
    this->diffusionCoefficient = diffusionCoefficient;
    this->emissivity = emissivity;
}

Material::Material(Material& m)
{
    this->color = Vector(m.color);
    this->caracteristics = Vector(m.caracteristics);
    this->diffusionCoefficient = m.diffusionCoefficient;
    this->emissivity = m.emissivity;
}
Material::Material(const Material& m)
{
    this->color = Vector(m.color);
    this->caracteristics = Vector(m.caracteristics);
    this->diffusionCoefficient = m.diffusionCoefficient;
    this->emissivity = m.emissivity;
}

bool Material::isDiffuse() {
    return this->caracteristics[0];
}

bool Material::isSpecular() {
    return this->caracteristics[1];
}

bool Material::isTransparent() {
    return this->caracteristics[2];
}
