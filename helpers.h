#ifndef HELPERS_H
#define HELPERS_H
#include "vector.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <iostream>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

inline double dot (const Vector& a, const Vector&b) {
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

inline void saveBMP (int w, int h, const unsigned char * img) {
    FILE *f;
    int filesize = 54 + 3*w*h;  //w is your image width, h is image height, both int

    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[ 2] = (unsigned char)(filesize    );
    bmpfileheader[ 3] = (unsigned char)(filesize>> 8);
    bmpfileheader[ 4] = (unsigned char)(filesize>>16);
    bmpfileheader[ 5] = (unsigned char)(filesize>>24);

    bmpinfoheader[ 4] = (unsigned char)(       w    );
    bmpinfoheader[ 5] = (unsigned char)(       w>> 8);
    bmpinfoheader[ 6] = (unsigned char)(       w>>16);
    bmpinfoheader[ 7] = (unsigned char)(       w>>24);
    bmpinfoheader[ 8] = (unsigned char)(       h    );
    bmpinfoheader[ 9] = (unsigned char)(       h>> 8);
    bmpinfoheader[10] = (unsigned char)(       h>>16);
    bmpinfoheader[11] = (unsigned char)(       h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
    fclose(f);
}

inline double pdf (double x, double mu, double sigma) {
    return exp(-(x-mu)*(x-mu)/(2*sigma*sigma))/(sigma*sqrt(2*M_PI));
}

inline double test_function (double x, double y, double z) {
    return pow(cos(x)*cos(y)*cos(z),20);
}

inline double integrate (double (*f) (double, double, double)) {
    double sum = 0;
    double u,v,x,y,z;
    int N = 10000;
    int add = 0;
    double sigma = 0.25;
    double mu = 0;
    srand(time(NULL));
    for(int i = 0; i < N; i++) {
        u = (double)rand() / (double)RAND_MAX;
        v = (double)rand() / (double)RAND_MAX;
        x = sqrt(-2*log(u))*cos(2*M_PI*v)*sigma+mu;
        y = sqrt(-2*log(u))*sin(2*M_PI*v)*sigma+mu;
        u = (double)rand() / (double)RAND_MAX;
        v = (double)rand() / (double)RAND_MAX;
        z = sqrt(-2*log(u))*cos(2*M_PI*v)*sigma+mu;
        if (x > -M_PI/2 && x < M_PI/2 && y > -M_PI/2 && y < M_PI/2 && z > -M_PI/2 && z < M_PI/2) {
            sum += f(x,z,y)/(pdf(x, mu, sigma)*pdf(y, mu, sigma)*pdf(z, mu, sigma));
            add++;
        }
    }
    sum = sum / add;
    return sum;
}

#endif // HELPERS_H
