#ifndef HELPERS_H
#define HELPERS_H
#include "vector.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <thread>
#include <algorithm>
#include <random>
#include <complex>

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


inline void printProgress(int x, int lines=0){
    std::stringstream msg;
    std::string s;
    s="[";
    for (int i=1;i<=(100/2);i++){
        if (i<=(x/2) || x==100)
            s+="=";
        else if (i==(x/2))
            s+=">";
        else
            s+=" ";
    }

    s+="]";
    msg << "\r" << std::setw(-40) << s << " " << x << "% completed.";
    if (lines > 0) {
        msg << "(" << lines << ")";
    }
    msg << std::flush;
    std::cout << msg.str();
}

extern std::mt19937 generator;
inline double doubleRand() {
    /*static thread_local std::mt19937 generator;*/
    std::uniform_real_distribution<double> distrib(0, 1);
    return distrib(generator);
}

#endif // HELPERS_H
