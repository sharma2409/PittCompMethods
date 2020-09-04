#include<iostream>
#include<cmath>
#include<complex>

typedef std::complex<double> Complex;

int main(){

double x=2; //Value of x

Complex num(0.0,x); //Complex declaration

std::cout<<"Sin(ix) ="<<sin(num)<<std::endl;

std::cout<<"iSinh(x) ="<<sinh(x)<<std::endl;

std::cout<<"Cos(ix) ="<<cos(num)<<std::endl;

std::cout<<"Cosh(x) ="<<cosh(x)<<std::endl;

return 0;
}
