#include <iostream>
#include <cmath>
#include <vector>
#include <stdlib.h>
#include <cstring>

using namespace std;

class Vector {
public:
    Vector(double x=0, double y=0, double z=0) {
        xyz[0] = x;
        xyz[1] = y;
        xyz[2] = z;
    }
    Vector(const Vector& b) {
        memcpy(xyz, b.xyz, 3*sizeof(double));
    }

    double xyz[3];

    double operator[](int i) const {
        return xyz[i];
    }
    double squaredNorm() {
        return xyz[0]*xyz[0]+xyz[1]*xyz[1]+xyz[2]*xyz[2];
    }
    void normalize() {
        double norm = sqrt(squaredNorm());
        xyz[0] = xyz[0]/norm;
        xyz[1] = xyz[1]/norm;
        xyz[2] = xyz[2]/norm;
    }
    double dot(Vector& b) {
        return xyz[0]*b[0]+xyz[1]*b[1]+xyz[2]*b[2];
    }
};

Vector operator+(const Vector &a, const Vector &b) {
    return Vector(a[0]+b[0], a[1]+b[1], a[2]+b[2]);
}
Vector operator-(const Vector& a, const Vector& b) {
    return Vector(a[0]-b[0], a[1]-b[1], a[2]-b[2]);
}
Vector operator*(const double a, const Vector& b) {
    return Vector(a*b[0], a*b[1], a*b[2]);
}
Vector operator*(const Vector& a, const double b) {
    return Vector(a[0]*b, a[1]*b, a[2]*b);
}

double dot (const Vector& a, const Vector&b) {
    return a[0]*b[0]+a[1]*b[1]+a[2]*b[2];
}

void saveBMP (int w, int h, const unsigned char * img) {
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

    Vector C(0,0,25);
    Vector O(0,0,0);
    double fov = 60*3.14/180;
    double R = 10;

    Vector L(-10,20,40);

    for (int i=0; i<H; i++) {
        for (int j=0; j <W; j++) {
            Vector u (j-W/2., i-H/2., -W/(2.*tan(fov/2.)));
            u.normalize();

            double a =1;
            double b = 2.*dot(u,C-O);
            double c = (C-O).squaredNorm() - R*R;
            double delta = b*b - 4*a*c;

            if (delta>=0) {

                double t1 = (-b-sqrt(delta))/(2*a);
                double t2 = (-b+sqrt(delta))/(2*a);

                Vector P;
                if (t1 > 0) {
                    P = C+ t1*u;
                }
                else if (t2 > 0) {
                    P = C+ t2*u;
                }
                else {
                    continue;
                }

                Vector N = P-O;
                N.normalize();
                Vector l = L-P;
                double distLight2 = l.squaredNorm();
                l.normalize();
                double intensity = 1000*abs(dot(N,l))/distLight2;
                img[(i*W+j)*3]=std::min(225., 255*intensity);
                img[(i*W+j)*3+1]=std::min(255., 255*intensity);
                img[(i*W+j)*3+2]=std::min(255., 255*intensity);
            }
        }
    }
    saveBMP(W, H, img);
    return 0;
}

