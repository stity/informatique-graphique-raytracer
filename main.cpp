#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include "vector.h"
#include "ray.h"
#include "scene.h"
#include "material.h"
#include "helpers.h"

using namespace std;

int main()
{


    // Dimensions de l'image finale
    int H = 1024;
    int W = 1024;

    // Définition de l'image
    unsigned char *img = NULL;
    if (img) {
        free(img);
    }
    img = (unsigned char *)malloc(3*W*H);
    memset(img,0,sizeof(img));

    // Champ visuel en radians
    double fov = 60*3.14/180;

    // Définition du point d'observation
    Vector C(0,0,55);

    // Définition des principales couleurs
    Vector red(0,0,1.);
    Vector blue(.9, .12, .12);
    Vector green(0, 1., 0);
    Vector yellow(0,1.,1.);
    Vector white(1.,1.,1.);
    Vector black(0.,0.,0.);

    // Définition des propriétés optiques de matériaux
    Vector diffuse(true, false, false);
    Vector mirror(false, true, false);
    Vector transparent(false, false, true);
    Vector diffuseTransparent(true, false, true);

    // Définition des éléments à observer
    Sphere sphere1(Vector(0,0,10), 10, white, transparent);
    Sphere sphere2(Vector(0,0,20), 10, white, diffuse, 0.7);
    Sphere sphere3(Vector(-15,0,20), 3, white, mirror);

    // Définition des "murs"
    Sphere mur1(Vector(0,0,-1000), 940., green, diffuse);
    Sphere mur2(Vector(0,1000,0), 960., red, diffuse);
    Sphere mur3(Vector(0,0,1000), 940., yellow, diffuse);
    Sphere mur4(Vector(0,-1000,0), 990., blue, diffuse);
    Sphere mur5(Vector(-1000,0,0), 960., yellow, diffuse);
    Sphere mur6(Vector(1000,0,0), 960., yellow, diffuse);

    // Création de la scène en ajoutant les objets à afficher
    Scene scene;
    //scene.L = Vector(-10,20,40); // Lumière de la scène
    scene.L = Vector(10,10,40);
    //scene.objects.push_back(sphere1);
    scene.objects.push_back(sphere2);
    //scene.objects.push_back(sphere3);
    scene.objects.push_back(mur1);
    scene.objects.push_back(mur2);
    scene.objects.push_back(mur3);
    scene.objects.push_back(mur4);
    scene.objects.push_back(mur5);
    scene.objects.push_back(mur6);

    int sampleNumber = 100;
    int linesDone = 0;

#pragma omp parallel for
    for (int i=0; i<H; i++) {
        std::cout << "line " << linesDone++ << std::endl;
        for (int j=0; j <W; j++) {
            // Direction associée au pixel
            Vector u (j-W/2., H-i-H/2., -W/(2.*tan(fov/2.)));
            u.normalize();
            Vector sum_intensities;
            for (int k = 0; k<sampleNumber; k++) {
                // Calcul du vecteur d'intensité
                Vector intensity = scene.getColor(Ray(C, u), 3);
                sum_intensities = sum_intensities + intensity;
            }
            sum_intensities = sum_intensities*(1./sampleNumber);


            img[(i*W+j)*3]=255*std::min(pow(sum_intensities[0], 1./2.2),1.);
            img[(i*W+j)*3+1]=255*std::min(pow(sum_intensities[1], 1./2.2),1.);
            img[(i*W+j)*3+2]=255*std::min(pow(sum_intensities[2], 1./2.2),1.);
        }
    }

    // Enregistrement de l'image
    saveBMP(W, H, img);

    return 0;
}
