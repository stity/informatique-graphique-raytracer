#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <iostream>
#include <vector>
#include "vector.h"
#include "ray.h"
#include "object.h"
#include "boundingbox.h"
#include "bvh.h"
#include "list"

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
        bbox = build_bbox(0, faces.size()/3);
        bvh = new BVH();
        build_bvh(0, faces.size()/3, bvh);
    }

    BoundingBox build_bbox(int i0, int i1) {
        BoundingBox bbox;
        bbox.bmin = Vector(1E99, 1E99, 1E99);
        bbox.bmax = Vector(-1E99, -1E99, -1E99);
        double bmin0 = 1E99, bmin1 = 1E99, bmin2 = 1E99, bmax0 = -1E99, bmax1 = -1E99, bmax2 = -1E99;

        for (unsigned int i = i0; i < i1; i++) {
            for (int j=0; j<3; j++) {
                bmin0 = std::min(bmin0, vertices[faces[i*3+j]][0]);
                bmin1 = std::min(bmin1, vertices[faces[i*3+j]][1]);
                bmin2 = std::min(bmin2, vertices[faces[i*3+j]][2]);

                bmax0 = std::max(bmax0, vertices[faces[i*3+j]][0]);
                bmax1 = std::max(bmax1, vertices[faces[i*3+j]][1]);
                bmax2 = std::max(bmax2, vertices[faces[i*3+j]][2]);
            }
        }
        bbox.bmin = Vector(bmin0, bmin1, bmin2);
        bbox.bmax = Vector(bmax0, bmax1, bmax2);
        return bbox;
    }

    void build_bvh(int i0, int i1, BVH* bvh) {
        BoundingBox bb = build_bbox(i0,i1);
        bvh->bbox = bb;
        bvh->i0 = i0;
        bvh->i1 = i1;
        Vector diag(bb.bmax[0]-bb.bmin[0], bb.bmax[1]-bb.bmax[1], bb.bmax[2]-bb.bmax[2]);

        int dim_split = 0;
        if(diag[0] > diag[1] && diag[0] > diag[2]) {
            dim_split = 0;
        }
        else if (diag[1] > diag[2]) {
            dim_split = 1;
        }
        else {
            dim_split = 2;
        }

        double coord_pivot = diag[dim_split]/2 + bb.bmin[dim_split];
        int indice_pivot = i0 - 1;

        for (int i = i0; i < i1; i++) {
            Vector center = (vertices[faces[i*3]]+vertices[faces[i*3+1]]+vertices[faces[i*3+2]])*(1./3);

            if (center[dim_split] <= coord_pivot) {
                indice_pivot++;
                std::swap(faces[i*3], faces[indice_pivot*3]);
                std::swap(faces[i*3+1], faces[indice_pivot*3+1]);
                std::swap(faces[i*3+2], faces[indice_pivot*3+2]);
            }

        }

        if (indice_pivot <= i0 || indice_pivot >= i1) {
            return;
        }
        bvh->left = new BVH();
        bvh->right = new BVH();
        build_bvh(i0, indice_pivot, bvh->left);
        build_bvh(indice_pivot, i1, bvh->right);
    }

    bool intersect(const Ray& r, int id, Vector &normale, double &t ) const {

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

        return (alpha > 0 && beta > 0 && alpha + beta < 1);
    }

    bool intersect(const Ray& r, Vector &P,  double &t, Vector &normale, Material& M) const {

        t =  1E99;
        bool has_intersection = false;

        if (!bbox.intersect(r)) {
            return false;
        }

        std::list<BVH*> l;
        l.push_back(bvh);

//        while(!l.empty()) {
//            BVH* node = l.front();
//            l.pop_front();

//            if(node->left && node->left->bbox.intersect(r)) {
//                l.push_back(node->left);
//            }
//            if(node->right && node->right->bbox.intersect(r)) {
//                l.push_back(node->right);
//            }

//            if(!node->left && !node->right) {

////                for (unsigned int i = node->i0; i <= node->i1; i++) {
////                    Vector current_n;
////                    double current_t;
////                    if (intersect(r, i, current_n, current_t)) {
////                        has_intersection = true;
////                        if (current_t < t) {
////                            t = current_t;
////                            normale = current_n;
////                        }
////                    }
////                }
//            }

//        }
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
        M = material;
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
    BVH *bvh;
};

#endif // GEOMETRY_H
