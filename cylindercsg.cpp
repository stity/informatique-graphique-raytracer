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

    Material m = Material(this->material);

    //intersection demi plan

    double tA = normale.dot(A-r.C)/ndotr;
    Vector PA = r.C+tA*r.u;
    if ((PA-A-(PA-A).dot(normale)*normale).squaredNorm()<R*R) {
        Vector N = (-1)*normale;
        LI.push_back(new IntersectionPointCSG(PA, N, m));
    }

    double tB = normale.dot(B-r.C)/ndotr;
    Vector PB = r.C+tB*r.u;
    if ((PB-A-(PB-A).dot(normale)*normale).squaredNorm()<R*R) {
        Vector N = normale;
        LI.push_back(new IntersectionPointCSG(PB, N, m));
    }

    // intersection cylindre

    double a = 1- ndotr*ndotr;
    double cdotn = normale.dot(r.C);
    double b = 2*(r.C.dot(r.u)+r.u.dot(A)-ndotr*cdotn+ndotr*A.dot(normale));
    double c = r.C.squaredNorm()+A.squaredNorm()-cdotn*cdotn-R*R+2*r.C.dot(A)+2*cdotn*A.dot(normale);
    double delta = b*b-4*a*c;
    if (delta > 0) {
        double tc1 = (-b-sqrt(delta))/(2*a);
        Vector Pc1 = r.C+tc1*r.u;
        if ((Pc1-A).dot(normale) > 0 && (Pc1-B).dot(normale) < 0) {
            Vector N = (Pc1-A-(Pc1-A).dot(normale)*normale).getNormalized();
            LI.push_back(new IntersectionPointCSG(Pc1,N,m));
        }

        double tc2 = (-b+sqrt(delta))/(2*a);
        Vector Pc2 = r.C+tc2*r.u;
        if ((Pc2-A).dot(normale) > 0 && (Pc2-B).dot(normale) < 0) {
            Vector N = (Pc2-A-(Pc2-A).dot(normale)*normale).getNormalized();
            LI.push_back(new IntersectionPointCSG(Pc2,N,m));
        }
    }


}
