#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <cstring>
#include "vector.h"
#include "ray.h"
#include "scene.h"
#include "helpers.h"

using namespace std;

int main()
{
    int H = 1024;
    int W = 1024;

    unsigned char *img = NULL;
    if (img) {
        free(img);
    }
    img = (unsigned char *)malloc(3*W*H);
    memset(img,0,sizeof(img));

    Vector C(0,0,40);
    double fov = 60*3.14/180;
    Vector red(0,0,1.);
    Vector blue(1., 0, 0);
    Vector green(0, 1., 0);
    Vector yellow(0,1.,1.);
    Vector white(1.,1.,1.);
    Vector black(0.,0.,0.);
//    Sphere sphere1(Vector(-5,0,0), 6, white, true);
//    Sphere sphere2(Vector( 5,0,0), 6, white, true);
    Sphere sphere3(Vector(2,0,5), 7, white, false, false, true);
    Sphere mur1(Vector(0,-1000,0), 990, blue, true, false, false);
    Sphere mur2(Vector(0,0,-1000), 990, green, true, false, false);
    Sphere mur3(Vector(0,1000,0), 990, red, true, false, false);
    Sphere mur4(Vector(1000,0,0), 990, yellow, true, false, false);
    Sphere mur5(Vector(-1000,0,0), 990, yellow, true, false, false);

    Scene scene;
//    scene.objects.push_back(sphere1);
//    scene.objects.push_back(sphere2);
    scene.objects.push_back(sphere3);
    scene.objects.push_back(mur1);
    scene.objects.push_back(mur2);
    scene.objects.push_back(mur3);
    scene.objects.push_back(mur4);
    scene.objects.push_back(mur5);

    //scene.L = Vector(-10,20,40);
    scene.L = Vector(0,5,40);

    for (int i=0; i<H; i++) {
        for (int j=0; j <W; j++) {
            Vector u (j-W/2., H-i-H/2., -W/(2.*tan(fov/2.)));
            u.normalize();

            Vector intensity = scene.getColor(Ray(C, u), 10);

            img[(i*W+j)*3]=std::min(225., 255*pow(intensity[0], 1./2.2));
            img[(i*W+j)*3+1]=std::min(255., 255*pow(intensity[1], 1./2.2));
            img[(i*W+j)*3+2]=std::min(255., 255*pow(intensity[2], 1./2.2));
        }
    }
    saveBMP(W, H, img);
    return 0;
}
