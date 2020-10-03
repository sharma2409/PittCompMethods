#include <eigen3/Eigen/Dense>
#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"
#include "QatGenericFunctions/HermitePolynomial.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Square.h"
#include <iostream>
#include <cmath>
int main(int argc, char**argv){

using namespace Genfun;
using namespace Eigen;

MatrixXf mat(6,6);

GaussHermiteRule rule(6);
GaussIntegrator integrator(rule);

double func;

for (int i=0; i<6; i++){

for (int j=0; j<6; j++)
{

Exp exp;
Square square;
GENFUNCTION H=exp(-square/2.0);


func=sqrt(pow(2,i)*tgamma(i+1)*pow(2,j)*tgamma(j+1));

GENFUNCTION phi=(sqrt(M_PI)/func)*H*HermitePolynomial(i)*HermitePolynomial(j);

mat(i,j)=integrator(phi);

}
};

std::cout<<mat<<std::endl;

return 0;
}
