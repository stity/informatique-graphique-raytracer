#include "cylindercsg.h"

CylinderCSG::CylinderCSG(Vector A, Vector B, double R, Material M)
{
    this->A = A;
    this->B = B;
    this->R = R;
    this->material = M;
}

void CylinderCSG::intersect(const Ray &r, std::vector<IntersectionPointCSG *> &LI) const {

    const Vector normale = (B-A).getNormalized();
    const double ndotr = normale.dot(r.u);

    Material m = this->material;

    //intersection demi plan

    double tA = normale.dot(A-r.C)/ndotr;
    Vector PA = r.C+tA*r.u;
    if ((PA-A-(PA-A).dot(normale)*normale).squaredNorm()<R*R && tA > 0) {
        Vector N = (-1)*normale;
        LI.push_back(new IntersectionPointCSG(PA, N, m));
    }

    double tB = normale.dot(B-r.C)/ndotr;
    Vector PB = r.C+tB*r.u;
    if ((PB-A-(PB-A).dot(normale)*normale).squaredNorm()<R*R && tB > 0) {
        Vector N = normale;
        LI.push_back(new IntersectionPointCSG(PB, N, m));
    }

    // intersection cylindre
    Vector deltaC = r.C-A;
    double a = 1- ndotr*ndotr;
    double dcdotn = normale.dot(deltaC);
    double b = 2*(r.u-ndotr*normale).dot(deltaC-dcdotn*normale);
    double c = (deltaC-dcdotn*normale).squaredNorm()-R*R;
    double delta = b*b-4*a*c;
    if (delta > 0) {
        double tc1 = (-b-sqrt(delta))/(2*a);
        Vector Pc1 = r.C+tc1*r.u;
        if (tc1 > 0 && (Pc1-A).dot(normale) > 0 && (Pc1-B).dot(normale) < 0) {
            Vector N = (Pc1-A-(Pc1-A).dot(normale)*normale).getNormalized();
            //N = Vector(0,0,1);
            LI.push_back(new IntersectionPointCSG(Pc1,N,m));
        }

        double tc2 = (-b+sqrt(delta))/(2*a);
        Vector Pc2 = r.C+tc2*r.u;
        if (tc2 > 0 && (Pc2-A).dot(normale) > 0 && (Pc2-B).dot(normale) < 0) {
            Vector N = (Pc2-A-(Pc2-A).dot(normale)*normale).getNormalized();
            //N = Vector(0,0,1);
            LI.push_back(new IntersectionPointCSG(Pc2,N,m));
        }
    }


}
