#include <iostream>
#include <cmath>
#include <limits>
#include <complex>
#include <iomanip>

typedef std::complex<double> Complex;

int main(){
double eps_double=std::numeric_limits<double>::epsilon(); //Calculation of Machine Precision for double 
float eps_float=std::numeric_limits<float>::epsilon(); //Calculation of Machine Precision for float 

std::cout<<eps_double<<std::endl;
std::cout<<eps_float<<std::endl;

Complex x0=1.0;
  Complex x1(1.0/2.,sqrt(3.0)/2.0);
  unsigned int nsides=6;
  while (nsides < std::numeric_limits<int>::max()) {

    float lside = abs(x1-x0);
    float approx=nsides*lside/2.0;
    std::cout << "Sides " << nsides << "; approx=" << std::setprecision(16) << approx- M_PI << std::endl;

    x1=(x1+x0)/abs(x1+x0);
    nsides *=2; }
return 0;

}
