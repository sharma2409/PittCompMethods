#include<complex>
#include<iostream>
#include<cmath>
#include<iomanip>
#include<limits>

typedef std::complex<double>Complex;
int main(){

Complex x0=1;

Complex x1(1.0/2.0,sqrt(3.0)/2.0);

unsigned int nsides=6;

while(nsides<std::numeric_limits<int>::max())
{

double approx=0.5*imag(x1)*nsides;

std::cout<<"Sides "<<nsides<<"; approx=" <<std::setprecision(16)<<approx<<std::endl;

x1=(x1+x0)/abs(x1+x0);
nsides *=2;

}

}
