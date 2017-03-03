// résolution de l'intersection trouvée sur http://www.cosinekitty.com/raytrace/chapter13_torus.html

#include "toruscsg.h"
#include "quarticSolver.h"

TorusCSG::TorusCSG(Vector C, Vector u, double R, double r, Material m)
{
    this->C = C;
    this->u = u;
    this->R = R;
    this->r = r;
    this->material = m;
}

void TorusCSG::intersect(const Ray & r, std::vector<IntersectionPointCSG *> & LI) const {

    //changement de repère du rayon pour se ramener au cas où le tore est sur l'axe vertical, centré en l'origine
    Vector T1;
    Vector T2;
    this->u.orthogonalSystem(T1, T2);
    Vector E(r.u.dot(T1), r.u.dot(T2), r.u.dot(this->u));
    Vector D((r.C-C).dot(T1), (r.C-C).dot(T2), (r.C-C).dot(this->u));

    //calcul des coefficients de l'équation d'intersection
    double R2 = R*R;
    double G = 4*R2*(E[0]*E[0]+E[1]*E[1]);
    double H = 8*R2*(D[0]*E[0]+D[1]*E[1]);
    double I = 4*R2*(D[0]*D[0]+D[1]*D[1]);
    double J = E.squaredNorm();
    double K = 2*E.dot(D);
    double L = D.squaredNorm()+R2-this->r*this->r;

    double coef[4];
    double roots[4];
    coef[0] = 2*K/J;
    coef[1] = (2L*L+K*K-G)/(J*J);
    coef[2] = (2*K*L-H)/(J*J);
    coef[3] = (L*L-I)/(J*J);

    //résolution avec le solveur
    unsigned int nbroots = quarticSolver(coef, roots);

    Material m = this->material;

    for (unsigned int i = 0; i <nbroots; ++i) {
        if (roots[i] > 0) {
            Vector P = r.C+roots[i]*r.u;
            Vector Pprime = C+(P-C-(P-C).dot(u)*u).getNormalized()*R; //projeté sur le cercle
            Vector N = (P-Pprime).getNormalized();
            IntersectionPointCSG* IP = new IntersectionPointCSG(P,N,m);
            LI.push_back(IP);
        }
    }
}
