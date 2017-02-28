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
#include <random>
#include "geometry.h"
#include <csignal>
#include <thread>

using namespace std;


// Dimensions de l'image finale
int H = 1024;
int W = 1024;

// Définition de l'image
unsigned char *img = NULL;

void signalHandler( int signum ) {
   cout << "Interrupt signal (" << signum << ") received.\n";


   saveBMP(W, H, img);

   exit(signum);

}



int main(int argc, char *argv[])
{
    int totalPartition = 1;
    int partition = 1;
    if (argc >= 3) {
        partition = std::stoi(argv[1]);
        totalPartition = std::stoi(argv[2]);
    }


    // Définition de l'image
    if (img) {
        free(img);
    }
    img = (unsigned char *)malloc(3*W*H);
    memset(img,0,sizeof(img));

    signal(SIGINT, signalHandler);
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
    Sphere* sphere1 = new Sphere(Vector(0,0,10), 10, white, transparent);
    Sphere* sphere2 = new Sphere(Vector(0,0,20), 10, white, diffuse, 1.0);
    Sphere* sphere3 = new Sphere(Vector(-15,0,20), 3, white, mirror);

    // Définition des "murs"
    Sphere* mur1 = new Sphere(Vector(0,0,-1000), 940., green, diffuse);
    Sphere* mur2 = new Sphere(Vector(0,1000,0), 960., red, diffuse);
    Sphere* mur3 = new Sphere(Vector(0,0,1000), 940., yellow, diffuse);
    Sphere* mur4 = new Sphere(Vector(0,-1000,0), 990., blue, diffuse);
    Sphere* mur5 = new Sphere(Vector(-1000,0,0), 960., yellow, diffuse);
    Sphere* mur6 = new Sphere(Vector(1000,0,0), 960., yellow, diffuse);

    //Chargement du mesh
    Geometry* mesh = new Geometry("girl.obj");

    // Création de la scène en ajoutant les objets à afficher
    Scene scene;
    //scene.L = Vector(-10,20,40); // Lumière de la scène
    //scene.L = Vector(10,10,40);
    Sphere* luxSphere = new Sphere(Vector(10,10,40), 3, white, diffuse,1.0, 750);
    //scene.objects.push_back(sphere1);
    scene.objects.push_back(luxSphere);
    //scene.objects.push_back(sphere2);
    scene.objects.push_back(mesh);
    //scene.objects.push_back(sphere3);
    scene.objects.push_back(mur1);
    scene.objects.push_back(mur2);
    scene.objects.push_back(mur3);
    scene.objects.push_back(mur4);
    scene.objects.push_back(mur5);
    scene.objects.push_back(mur6);

    int sampleNumber = 1;
    static thread_local int linesDone = 0;

#pragma omp parallel for schedule(dynamic,2)
    for (int i=H*(partition-1)/totalPartition; i<H*partition/totalPartition; i++) {
        printProgress(800*linesDone++*totalPartition/H, 8*linesDone);
        for (int j=0; j <W; j++) {

            Vector sum_intensities;
            for (int k = 0; k<sampleNumber; k++) {
                double r1 = doubleRand()-0.5;
                double r2 =doubleRand()-0.5;
                // Direction associée au pixel
                Vector u (j+r1-W/2., H-i+r2-H/2., -W/(2.*tan(fov/2.)));
                u.normalize();

                //profondeur de champ
                /*Vector Pfocal = C + 55*u;
                double r1_bis = doubleRand();
                double r2_bis = doubleRand();
                double x_bis = sqrt(-2*log(r1_bis))*cos(2.*M_PI*r2_bis)*0.2;
                double y_bis = sqrt(-2*log(r1_bis))*sin(2.*M_PI*r2_bis)*0.2;

                Vector ubis = Pfocal - (C+Vector(x_bis, y_bis,0));
                ubis.normalize();*/


                // Calcul du vecteur d'intensité avec profondeur de champ
                //Vector intensity = scene.getColor(Ray(C+Vector(x_bis,y_bis,0), ubis), 5, 5);
                //sans profondeur de champ
                Vector intensity = scene.getColor(Ray(C, u), 5, 5);
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
