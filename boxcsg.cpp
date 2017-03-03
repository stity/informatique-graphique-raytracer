#include "boxcsg.h"
#include <limits>

#define epsilon 0.001

BoxCSG::BoxCSG(Vector C, Vector T1, Vector T2, Vector size)
{
    this->C = C;
    this->T1 = T1.getNormalized();
    this->T2 = (T2-T2.dot(T1)*T1).getNormalized();
    this->T3 = T1.cross(T2);
    this->size = size;
}

bool BoxCSG::isInside(const Vector &P) const {

    Vector deltaP = P-C;
    return abs(deltaP.dot(T1)) < size[0]/2 &&  abs(deltaP.dot(T2)) < size[1]/2 && abs(deltaP.dot(T3)) < size[2]/2;

}

bool BoxCSG::isAlmostInside(const Vector &P, bool localSystem = false) const {
    if (!localSystem) {
        Vector deltaP = P-C;
        return abs(deltaP.dot(T1)) < size[0]/2+epsilon &&  abs(deltaP.dot(T2)) < size[1]/2+epsilon && abs(deltaP.dot(T3)) < size[2]/2+epsilon;
    }
    else {
        return abs(P[0]) < size[0]/2+epsilon &&  abs(P[1]) < size[1]/2+epsilon && abs(P[2]) < size[2]/2+epsilon;
    }
}

void BoxCSG::addIntersectionPoint(double t, Vector &E, Vector &D, std::vector<IntersectionPointCSG *> &LI) const {
    Vector P = D+t*E;
    Vector N;
    /*if (abs(P[0]/size[0]) > 1-epsilon) {
        N = T1;
        if (P[0]/size[0] < 0) {
            N = -T1;
        }
    }
    else if (abs(P[1]/size[1]) > 1-epsilon) {
        N = T2;
        if (P[1]/size[1] < 0) {
            N = -T2;
        }
    }
    else {
        N = T3;
        if (P[2]/size[2] < 0) {
            N = -T3;
        }
    }*/

    double min = std::numeric_limits<double>::max();
    double distance = std::abs(size[0] - std::abs(P[0]));
    if (distance < min) {
        min = distance;
        N = (P[0] > 0 ? 1 : -1)*T1;
    }
    distance = std::abs(size[1] - std::abs(P[1]));
    if (distance < min) {
        min = distance;
        N = (P[1] > 0 ? 1 : -1)*T2;
    }
    distance = std::abs(size[2] - std::abs(P[2]));
    if (distance < min) {
        min = distance;
        N = (P[2] > 0 ? 1 : -1)*T3;
    }

    Material m = this->material;
    if (this->isAlmostInside(P, true)) {
        Vector realP = P[0]*T1+P[1]*T2+P[2]*T3;

        IntersectionPointCSG* IP = new IntersectionPointCSG(realP, N, m);
        LI.push_back(IP);
    }
}

void BoxCSG::intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const {
    //changement de repère du rayon pour se ramener au cas où la box est alignée avec les axes
    Vector E(r.u.dot(T1), r.u.dot(T2), r.u.dot(T3));
    Vector D((r.C-C).dot(T1), (r.C-C).dot(T2), (r.C-C).dot(T3));

    double halfx = size[0]/2;
    double halfy = size[1]/2;
    double halfz = size[2]/2;

    /*double tx1 = (-halfx-D[0])/E[0];
    double tx2 = (halfx-D[0])/E[0];
    double ty1 = (-halfy-D[1])/E[1];
    double ty2 = (halfy-D[1])/E[1];
    double tz1 = (-halfz-D[2])/E[2];
    double tz2 = (halfz-D[2])/E[2];

    double tmin = std::min(std::min(std::max(tx1,tx2), std::max(ty1,ty2)), std::max(tz1,tz2));
    double tmax = std::max(std::max(std::min(tx1,tx2), std::min(ty1,ty2)), std::min(tz1,tz2));

    if (tmin>tmax) {
        return;
    }

    Vector N;

    N = -T1;
    addIntersectionPoint(tx1, E, D, N, LI);
    N = T1;
    addIntersectionPoint(tx2, E, D, N, LI);
    N = -T2;
    addIntersectionPoint(ty1, E, D, N, LI);
    N = T2;
    addIntersectionPoint(ty2, E, D, N, LI);
    N = -T3;
    addIntersectionPoint(tz1, E, D, N, LI);
    N = T3;
    addIntersectionPoint(tz2, E, D, N, LI); */

    double tmin, tmax, tymin, tymax, tzmin, tzmax;
    bool rsign0 = E[0] < 0;
    bool rsign1 = E[1] < 0;
    bool rsign2 = E[2] < 0;
    Vector bounds[2];
    bounds[0] = Vector(-halfx, -halfy, -halfz);
    bounds[1] = Vector( halfx,  halfy,  halfz);

    tmin = (bounds[rsign0][0] - D[0]) / E[0];
    tmax = (bounds[1-rsign0][0] - D[0]) / E[0];
    tymin = (bounds[rsign1][1] - D[1]) / E[1];
    tymax = (bounds[1-rsign1][1] - D[1]) / E[1];

    if ((tmin > tymax) || (tymin > tmax))
        return;

    if (tymin > tmin)
        tmin = tymin;
    if (tymax < tmax)
        tmax = tymax;

    tzmin = (bounds[rsign2][2] - D[2]) / E[2];
    tzmax = (bounds[1-rsign2][2] - D[2]) / E[2];

    if ((tmin > tzmax) || (tzmin > tmax))
        return;

    if (tzmin > tmin)
        tmin = tzmin;
    if (tzmax < tmax)
        tmax = tzmax;


    addIntersectionPoint(tmin, E, D, LI);
    addIntersectionPoint(tmax, E, D, LI);
}
