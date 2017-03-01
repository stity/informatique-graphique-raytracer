#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "boundingbox.h"

class Geometry : public Object {
public:

    Geometry(const char* obj) {
        FILE* f = fopen(obj, "r");
        int curGroup = -1;
        while (!feof(f)) {
            char line[255];
            fgets(line, 255, f);
            if (line[0]=='u' && line[1]=='s') {
                curGroup++;
            }
            if (line[0]=='v' && line[1]==' ') {
                double t0, t2, t1;
                //sscanf(line, "v %lf %lf %lf\n", &vec[2], &vec[0], &vec[1]); // car
                sscanf(line, "v %lf %lf %lf\n", &t0, &t2, &t1); // girl
                //sscanf(line, "v %lf %lf %lf\n", &vec[0], &vec[1], &vec[2]);  // dragon
                //vec[2] = -vec[2];
                t1 -= 1.2;
                Vector vec(t0, t1, t2);
                vertices.push_back(vec*30);
            }
            if (line[0]=='v' && line[1]=='n') {
                double t0, t2, t1;
                //sscanf(line, "vn %lf %lf %lf\n", &vec[2], &vec[0], &vec[1]); //car
                sscanf(line, "vn %lf %lf %lf\n", &t0, &t2, &t1); //girl
                //vec[2] = -vec[2];
                Vector vec(t0, t1, t2);
                normals.push_back(vec);
            }
            if (line[0]=='v' && line[1]=='t') {
                double t0, t1;
                sscanf(line, "vt %lf %lf\n", &t0, &t1);
                Vector vec(t0, t1);
                uvs.push_back(vec);
            }
            if (line[0]=='f') {
                int i0, i1, i2;
                int j0, j1, j2;
                int k0, k1, k2;
                faceGroup.push_back(curGroup);
                int nn = sscanf(line, "f %u/%u/%u %u/%u/%u %u/%u/%u\n", &i0, &j0, &k0, &i1, &j1, &k1, &i2, &j2, &k2);
                if (nn==9) {
                    faces.push_back(i0-1);
                    faces.push_back(i1-1);
                    faces.push_back(i2-1);
                    uvIds.push_back(j0-1);
                    uvIds.push_back(j1-1);
                    uvIds.push_back(j2-1);
                    normalIds.push_back(k0-1);
                    normalIds.push_back(k1-1);
                    normalIds.push_back(k2-1);
                } else {
                    int i3, j3;
                    nn = sscanf(line, "f %u/%u %u/%u %u/%u %u/%u\n", &i0, &j0, &i1, &j1, &i2, &j2, &i3, &j3); //le dragon contient des quads
                    if (nn == 8) {
                        faces.push_back(i0-1);
                        faces.push_back(i1-1);
                        faces.push_back(i2-1);
                        faces.push_back(i0-1);
                        faces.push_back(i2-1);
                        faces.push_back(i3-1);
                        faceGroup.push_back(curGroup);
                        uvIds.push_back(j0-1);
                        uvIds.push_back(j1-1);
                        uvIds.push_back(j2-1);
                        uvIds.push_back(j0-1);
                        uvIds.push_back(j2-1);
                        uvIds.push_back(j3-1);
                    } else {
                        nn = sscanf(line, "f %u/%u %u/%u %u/%u\n", &i0, &j0, &i1, &j1, &i2, &j2);
                        faces.push_back(i0-1);
                        faces.push_back(i1-1);
                        faces.push_back(i2-1);
                        uvIds.push_back(j0-1);
                        uvIds.push_back(j1-1);
                        uvIds.push_back(j2-1);
                    }
                }

            }

        }
        fclose(f);
        build_bbox();
    }

    void build_bbox() {
        bbox.bmin = Vector(1E99, 1E99, 1E99);
        bbox.bmax = Vector(-1E99, -1E99, -1E99);
        double bmin0 = 1E99, bmin1 = 1E99, bmin2 = 1E99, bmax0 = -1E99, bmax1 = -1E99, bmax2 = -1E99;

        for (unsigned int i = 0; i < vertices.size(); i++) {
            bmin0 = std::min(bmin0, vertices[i][0]);
            bmin1 = std::min(bmin1, vertices[i][1]);
            bmin2 = std::min(bmin2, vertices[i][2]);

            bmax0 = std::max(bmax0, vertices[i][0]);
            bmax1 = std::max(bmax1, vertices[i][1]);
            bmax2 = std::max(bmax2, vertices[i][2]);
        }
        bbox.bmin = Vector(bmin0, bmin1, bmin2);
        bbox.bmax = Vector(bmax0, bmax1, bmax2);
        std::cout << bbox.bmin[0] << " " << bbox.bmin[1] << " " << bbox.bmin[2] << " " << bbox.bmax[0] << " " << bbox.bmax[1] << " " << bbox.bmax[1]<< std::endl;
    }

    bool intersect(const Ray r, int id, Vector &normale, double &t ) const {

        const Vector &A = vertices[faces[id*3]];
        const Vector &B = vertices[faces[id*3+1]];
        const Vector &C = vertices[faces[id*3+2]];

        normale = (C-A).cross(B-A).getNormalized();

        t = normale.dot(A-r.C)/normale.dot(r.u);
        if (t <=0) {
            return false;
        }
        Vector P = r.C+t*r.u;

        Vector u = B-A;
        Vector v = C-A;
        Vector w = P-A;
        double uu = u.dot(u);
        double uv = u.dot(v);
        double vv = v.dot(v);
        double uw = u.dot(w);
        double vw = v.dot(w);

        double detM = uu*vv-uv*uv;
        double alpha = (uw*vv - vw*uv)/detM;
        double beta = (uu*vw-uv*uw)/detM;

        if (alpha > 0 && beta > 0 && alpha + beta < 1) {
            return true;
        }
        return false;
    }

    bool intersect(const Ray& r, Vector &P,  double &t, Vector &normale) const {

        t =  1E99;
        bool has_intersection = false;

        if (!bbox.intersect(r)) {
            return false;
        }


        for (unsigned int i = 0; i < faces.size()/3; i++) {
            Vector current_n;
            double current_t;
            if (intersect(r, i, current_n, current_t)) {
                has_intersection = true;
                if (current_t < t) {
                    t = current_t;
                    normale = current_n;
                }
            }
        }
        P = r.C + t*r.u;
        return has_intersection;
    }


    std::vector<int> faceGroup;
    std::vector<int> faces;
    std::vector<int> normalIds;
    std::vector<int> uvIds;
    std::vector<Vector> vertices;
    std::vector<Vector> normals;
    std::vector<Vector> uvs; // Vector en 3D mais on n'utilise que 2 composantes

    BoundingBox bbox;
};

#endif // GEOMETRY_H
