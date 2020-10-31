#include <eigen3/Eigen/Dense>
#include "QatGenericFunctions/GaussQuadratureRule.h"
#include "QatGenericFunctions/GaussIntegrator.h"
#include "QatGenericFunctions/HermitePolynomial.h"
#include "QatGenericFunctions/Exp.h"
#include "QatGenericFunctions/Square.h"
#include "QatGenericFunctions/Variable.h"
#include <iostream>
#include <iomanip>
#include <cmath>

int main(int argc, char**argv){

  std::cout << std::fixed;
  std::cout << std::setprecision(3);
using namespace Genfun;
using namespace Eigen;

MatrixXf X(5,5);
MatrixXf Xsq(5,5);
MatrixXf D(5,5);
MatrixXf Dsq(5,5);
MatrixXf H(5,5);

GaussHermiteRule rule(10);
GaussIntegrator integrator(rule);

double func;
double elem_0, elem_1, elem_2, elem_3, elem_4;
for (int i=0; i<5; i++){

for (int j=0; j<5; j++)
{
func=sqrt(pow(2,i)*tgamma(i+1)*pow(2,j)*tgamma(j+1));
Variable x;
Exp exp;
Square sq;
GENFUNCTION H0=exp((-1*sq(x))/2);

GENFUNCTION expecX=(1.0/sqrt(M_PI)/func)*H0*HermitePolynomial(i)*x*H0*HermitePolynomial(j);
GENFUNCTION expecXsq=(1.0/sqrt(M_PI)/func)*H0*HermitePolynomial(i)*sq(x)*H0*HermitePolynomial(j);
GENFUNCTION expecD=H0*(1.0/sqrt(M_PI)/func)*HermitePolynomial(i)*(H0*HermitePolynomial(j)).prime();
GENFUNCTION expecDsq=H0*(1.0/sqrt(M_PI)/func)*HermitePolynomial(i)*((H0*HermitePolynomial(j)).prime()).prime();
 GENFUNCTION expecH= (1.0/sqrt(M_PI)/func)*H0*HermitePolynomial(i)* ( 0.5*sq(x)*H0*HermitePolynomial(j)-0.5*(H0*HermitePolynomial(j)).prime().prime());

elem_0=integrator(expecX);
elem_1=integrator(expecXsq);
elem_2=integrator(expecD);
elem_3=integrator(expecDsq);
elem_4=integrator(expecH);

X(i,j)=elem_0;
Xsq(i,j)=elem_1;
D(i,j)=elem_2;
Dsq(i,j)=elem_3;
H(i,j)=elem_4;



}
};
std::cout<<X<<std::endl<<std::endl;
std::cout<<Xsq<<std::endl<<std::endl;
std::cout<<D<<std::endl<<std::endl;
std::cout<<Dsq<<std::endl<<std::endl;
std::cout<<H<<std::endl<<std::endl;

return 0;
}
