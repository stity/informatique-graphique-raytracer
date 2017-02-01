#include "scene.h"

Scene::Scene()
{
    objects =std::vector<Sphere>();
}

bool Scene::intersect(const Ray& r, Vector& P, Vector& N, int& id) {
    double mint = 1E9;
    bool result = false;
    for(int i = 0; i<objects.size(); i++) {
        double t;
        Vector N1;
        Vector P1;
        if (objects[i].intersect(r, P1, t, N1)) {
            result = true;
            if (t<mint) {
                mint = t;
                P = P1;
                N = N1;
                id = i;
            }
        }
    }
    return result;
}

Vector Scene::getColor(const Ray &ray, int recursion) {
    Vector N, P;
    int sphereId;
    Vector finalColor;

    if (intersect(ray, P, N, sphereId)) {
        if(objects[sphereId].material.isDiffuse()){
            Vector l = L-P;
            double distLight2 = l.squaredNorm();
            l.normalize();

            double shadow_coeff = 1;
            Vector Pp, Np, direction;
            int idp;
            direction = (L-P);
            direction.normalize();
            if(intersect(Ray(P+0.001*N, direction), Pp, Np, idp)){
                if((Pp-P).squaredNorm() < distLight2){
                    shadow_coeff = .6;
                }
            }

            finalColor = shadow_coeff * (1500.*dot(N,l)/distLight2)*objects[sphereId].material.color;
            if (recursion>0) {
                Vector random_direction;
                random_direction.random_cos(N);
                Vector indirect = getColor(Ray(P+0.001*N, random_direction), recursion-1);
                finalColor = finalColor + objects[sphereId].material.diffusionCoefficient*objects[sphereId].material.color*indirect;
            }
            return finalColor;
        } if(objects[sphereId].material.isSpecular()) {
            if(recursion > 0){
                Vector refl = ray.u.reflect(N);
                return getColor(Ray(P+0.01*N, refl), recursion-1)*this->objects[sphereId].material.color;
            }
        } if(objects[sphereId].material.isTransparent()) {
            if(recursion >0){
                bool is_refracted;
                double n1=1;
                double n2=1.3;
                Vector normale = N;

                if(dot(normale, ray.u)>0){
                    std::swap(n1, n2);
                    normale = -normale;
                }
                Vector refr = ray.u.refract(normale, n1, n2, is_refracted);
                if(is_refracted){
                    return getColor(Ray(P+0.001*refr, refr), recursion-1);
                }
            } else {
                return Vector(0.,0.,0.);
            }
        } else {
            if(recursion >0){
                Vector refl = ray.u-2.*dot(ray.u, N)*N;
                return getColor(Ray(P+0.001*refl, refl), recursion-1);
            } else {
                return Vector(0.,0.,0.);
            }
        }
    } else {
        return Vector(0.,0.,0.);
    }
}
