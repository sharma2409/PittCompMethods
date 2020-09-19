#include <cstdlib>
#include <iostream>
#include <string>
#include <eigen3/Eigen/Dense>
#include <complex>
#include <cmath>


typedef std::complex<double>Complex;

int main(){

double m=1.0;

Eigen::MatrixXd M(5,5);

double k=1.0; //spring constant value
double k1=k;
double k2=2*k;
double k3=2*k;
double k4=k;

for (int l=0; l<5; l++)
{    for (int k=0; k<5; k++)
    {  M(l,k)=0.0;} //Initialzing K Matrix with zeroes
}


M(0,0)=sqrt(m);
M(1,1)=sqrt(3*m);
M(2,2)=sqrt(2*m);
M(3,3)=sqrt(m);
M(4,4)=sqrt(2*m);


Eigen::MatrixXd K(5,5);
//First Row
for (int i=0; i<5; i++)
{    for (int j=0; j<5; j++)
    {  K(i,j)=0.0;} //Initialzing K Matrix with zeroes
}

//First Row
K(0,0)=k1;
K(0,1)=-k1;

//Second Row
K(1,0)=-k1;
K(1,1)=k1+k2;
K(1,2)=-k2;

//Third Row
K(2,1)=-k2;
K(2,2)=k2+k3;
K(2,3)=-k3;

//Fourth Row
K(3,2)=-k3;
K(3,3)=k3+k4;
K(3,4)=-k4;

//Fifth Row
K(4,3)=-k4;
K(4,4)=k4;

Eigen::MatrixXd M2(5,5);
M2=M.inverse(); //Inverse of square root M

Eigen::MatrixXd delta(5,5);
delta=M2*K*M2; //Delta square matrix

Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> s(delta);

Eigen::VectorXd val=s.eigenvalues();
Eigen::MatrixXd vec=s.eigenvectors();

Eigen::VectorXd x0(5); //Initial Position Vector

x0(0)=-2;
x0(1)=3;
x0(2)=0;
x0(3)=-3;
x0(4)=2;

Eigen::VectorXd eta(5);
eta=vec.transpose()*M2*x0;

Eigen::VectorXd a(5);
a=M2*vec;


return 0;
}
